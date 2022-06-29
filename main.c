#include <stdlib.h>
#include <ncurses.h>
#include "project/extras.h"
#include "project/utils/utils.h"

int main(int argc,char**argv) {
    int rows,cols;

    initscr();
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    getmaxyx(stdscr,rows,cols);
    raw();
    keypad(stdscr,TRUE);
    noecho();
    addch(ACS_BULLET);
    addch(ACS_BOARD);
    addch(ACS_CKBOARD);
    addch(ACS_BBSS);
    addch(ACS_BLOCK);
    addch(ACS_BSBS);
    addch(ACS_BTEE);
    addch(' ');
    writeExtras();
    testReach();
    mvaddch(5,17,ACS_DARROW);

    attron(COLOR_PAIR(1));
    mvprintw(4,7,"There are %dx%d squares.",rows,cols);
    attroff(COLOR_PAIR(1));
    refresh();
    getch();
    endwin();
    return 0;
}
