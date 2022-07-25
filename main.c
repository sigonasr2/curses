#include <curses.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "project/extras.h"
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

int main(int argc,char**argv) {
    int*keyLog=calloc(25,sizeof(int));
    unsigned short currentLogCounter=0;
    unsigned int frameCount = 0;
    int rows,cols;
    clock_t lastTime = clock();
    int FRAMETIME = CLOCKS_PER_SEC/60;

    initscr();
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    getmaxyx(stdscr,rows,cols);
    cbreak();
    keypad(stdscr,TRUE);
    nodelay(stdscr,TRUE);
    noecho();

    WINDOW*messageBox=newwin(4,cols-2,rows-5,1);
    drawBorder(messageBox);
    //box(messageBox,0,0);

    refresh();
    getmaxyx(stdscr,rows,cols);
    int ch=ERR;
    while (true) {
        if ((ch=getch())!=ERR) {
            keyLog[currentLogCounter]=ch;
            currentLogCounter=(currentLogCounter+1)%25;
            if (ch==KEY_RESIZE) {
                getmaxyx(stdscr,rows,cols);
                delwin(messageBox);
                messageBox=newwin(4,cols-2,rows-5,1);
            }
        }
        if (clock()-lastTime>FRAMETIME) {
            //mvprintw(5,7,"There are %dx%d squares. (%d)",cols,rows,frameCount++);
            drawBorder(messageBox);
            mvwprintw(messageBox,0,0,"There are %dx%d squares. (%d) It is good!",cols,rows,frameCount++);
            mvwprintw(messageBox,1,0,"There are %dx%d squares. (%d) It is good!",cols,rows,frameCount++);
            mvwprintw(messageBox,2,0,"There are %dx%d squares. (%d) It is good!",cols,rows,frameCount++);
            mvwprintw(messageBox,3,0,"There are %dx%d squares. (%d) It is good!",cols,rows,frameCount++);
            for (int i=0;i<25;i++) {
                if (keyLog[i]>0) {
                    mvprintw(6+i,2,"Key %d was pressed.",keyLog[i]);
                }
            }
            refresh();
            wrefresh(messageBox);
            lastTime=clock();
        }
    }
    free(keyLog);
    endwin();
    return 0;
}
