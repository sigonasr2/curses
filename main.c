#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "project/extras.h"
#include "project/utils/utils.h"

struct data{
    int val1;
    int val2;
    int val3;
};

int main(int argc,char**argv) {
    int*keyLog=calloc(25,sizeof(int));
    struct data*dataVals=calloc(3,sizeof(struct data));
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

    dataVals[0].val1=14;
    dataVals[0].val2=16;
    dataVals[0].val3=22;
    dataVals[1].val1=39;
    dataVals[1].val2=7;
    dataVals[1].val3=64;
    dataVals[2].val1=42;
    dataVals[2].val2=14;
    dataVals[2].val3=69;


    mvprintw(2,7,"%d %d %d",dataVals[0].val1,dataVals[0].val2,dataVals[0].val3);
    mvprintw(3,7,"%d %d %d",dataVals[1].val1,dataVals[1].val2,dataVals[1].val3);
    mvprintw(4,7,"%d %d %d",dataVals[2].val1,dataVals[2].val2,dataVals[2].val3);
    refresh();
    getmaxyx(stdscr,rows,cols);
    int ch=ERR;
    while (true) {
        if ((ch=getch())!=ERR) {
            keyLog[currentLogCounter]=ch;
            currentLogCounter=(currentLogCounter+1)%25;
        }
        if (clock()-lastTime>FRAMETIME) {
            mvprintw(5,7,"There are %dx%d squares. (%d)",rows,cols,frameCount++);
            for (int i=0;i<25;i++) {
                if (keyLog[i]>0) {
                    mvprintw(6+i,2,"Key %d was pressed.",keyLog[i]);
                }
            }
            refresh();
            lastTime=clock();
        }
    }
    free(keyLog);
    free(dataVals);
    endwin();
    return 0;
}
