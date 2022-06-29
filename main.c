#include <stdlib.h>
#include <ncurses.h>

int main(char argc,char**argv) {
    int rows,cols;

    initscr();
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
    mvaddch(5,17,ACS_DARROW);

    mvprintw(4,7,"There are %dx%d squares.",rows,cols);

    refresh();
    getch();
    endwin();
    return 0;
}
