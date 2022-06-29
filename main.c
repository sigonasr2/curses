#include <stdlib.h>
#include <ncurses.h>

int main(char argc,char**argv) {
    initscr();
    printw("Hello World!");

    refresh();
    getch();
    endwin();
    return 0;
}
