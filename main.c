#include <curses.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "project/utils/utils.h"

void drawBorder(WINDOW*box) {
    int rows=getmaxy(box)+1;
    int cols=getmaxx(box)+2;
    int x=getbegx(box);
    int y=getbegy(box);
    //mvwprintw(box,3,1,"%d %d %d %d",x,y,rows,cols);
    move(y-1,x-1);
    for (int yy=0;yy<rows+1;yy++) {
        for (int xx=0;xx<cols;xx++) {
            if (xx==0||xx==cols-1) {
                if (yy==0&&xx==0) {
                    addch(ACS_ULCORNER);
                } else 
                if (yy==0&&xx==cols-1) {
                    addch(ACS_URCORNER);
                } else 
                if (yy==rows&&xx==0) {
                    addch(ACS_LLCORNER);
                } else 
                if (yy==rows&&xx==cols-1) {
                    addch(ACS_LRCORNER);
                } else {
                    addch(ACS_VLINE);
                }
            } else {
                if (yy==0||yy==rows) {
                    addch(ACS_HLINE);
                } else {
                    move(getcury(stdscr),getcurx(stdscr)+1);
                }
            }
        }
    }
}

//Returns true if the window was toggled on, or false if it got hidden.
boolean ToggleWindow(WINDOW**win,int w,int h,int x,int y) {
    if (*win!=NULL) {
        *win=NULL;
        delwin(*win);
        clear();
        return false;
    } else {
        *win=newwin(h,w,y,x);
        return true;
    }
}

void changeColor(int*oldcol,int newcol) {
    attroff(COLOR_PAIR(*oldcol));
    attron(COLOR_PAIR(newcol));
    *oldcol=newcol;
}

//Provide the width and height that the background needs to cover as well as an offset x and y value.
void drawBackground(int*currentcol,int background_id,int x,int y,int w,int h) {
    int oldcol=*currentcol;
    switch(background_id) {
        case 0:{
            move(y,x);
            changeColor(currentcol,3);
            for (int yy=0;yy<h;yy++) {
                for (int xx=0;xx<w;xx++) {
                    addch(ACS_DIAMOND);
                }
                move(getcury(stdscr)+1,x);
            }
        }break;
    }
    changeColor(currentcol,oldcol);
}

int main(int argc,char**argv) {
    int*keyLog=calloc(25,sizeof(int));
    unsigned short currentLogCounter=0;
    unsigned int frameCount = 0;
    int rows,cols;
    clock_t lastTime = clock();
    int FRAMETIME = CLOCKS_PER_SEC/60;
    int currentcol=1;

    initscr();

    start_color();
    getmaxyx(stdscr,rows,cols);
    cbreak();
    keypad(stdscr,TRUE);
    nodelay(stdscr,TRUE);
    noecho();

    init_pair(1,COLOR_BLACK,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    init_pair(5,COLOR_BLUE,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(7,COLOR_CYAN,COLOR_BLACK);
    init_pair(8,COLOR_WHITE,COLOR_BLACK);
    changeColor(&currentcol,6);

    WINDOW*messageBox=newwin(4,cols-2,rows-5,1);
    drawBorder(messageBox);
    //box(messageBox,0,0);

    boolean resizeOccured=false;

    refresh();
    getmaxyx(stdscr,rows,cols);
    int ch=ERR;
    while (true) {
        if ((ch=getch())!=ERR) {
            keyLog[currentLogCounter]=ch;
            currentLogCounter=(currentLogCounter+1)%25;
            switch (ch) {
                case 'A':
                case 'a':{
                    ToggleWindow(&messageBox,cols-2,4,1,rows-5);
                }break;
                case KEY_RESIZE:{
                    resizeOccured=true;
                    getmaxyx(stdscr,rows,cols);
                }break;
                case KEY_RIGHT:{
                    changeColor(&currentcol,(currentcol+1)%8);
                }break;
                case KEY_LEFT:{
                    changeColor(&currentcol,(currentcol-1>=0)?currentcol-1:7);
                }break;
            }
        }
        if (clock()-lastTime>FRAMETIME) {
            if (resizeOccured) {
                resizeOccured=false;
                clear();
                delwin(messageBox);
                messageBox=newwin(4,cols-2,rows-5,1);
            }
            //mvprintw(5,7,"There are %dx%d squares. (%d)",cols,rows,frameCount++);
            drawBackground(&currentcol,0,4,4,4,4);
            if (messageBox!=NULL) {
                drawBorder(messageBox);
                mvwprintw(messageBox,0,0,"There are %dx%d squares. (%d) It is good!",cols,rows,frameCount);
            }
            for (int i=0;i<25;i++) {
                if (keyLog[i]>0) {
                    mvprintw(6+i,2,"Key %d was pressed.",keyLog[i]);
                    short r,g,b;
                    color_content(currentcol,&r,&g,&b);
                    mvprintw(6+i,30,"%d %d %d",r,g,b);
                }
            }
            refresh();
            wrefresh(messageBox);
            lastTime=clock();
            frameCount++;
        }
    }
    free(keyLog);
    endwin();
    return 0;
}
