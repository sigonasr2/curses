#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "project/extras.h"
#include "project/utils/utils.h"

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
    endwin();
    return 0;
}
