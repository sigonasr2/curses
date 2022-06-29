#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "project/extras.h"
#include "project/utils/utils.h"

int main(int argc,char**argv) {
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
    int ch = getch(); //410 is used when resizing the window.
    getmaxyx(stdscr,rows,cols);
    while (true) {
        if (clock()-lastTime>FRAMETIME) {
            mvprintw(5,7,"There are %dx%d squares. (%d)(%d)",rows,cols,frameCount++,getch());
            refresh();
            lastTime=clock();
        }
    }
    endwin();
    return 0;
}
