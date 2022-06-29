#include <stdlib.h>
#include <ncurses.h>

int main(char argc,char**argv) {
    initscr();
    raw();
    keypad(stdscr,TRUE);
    noecho();

    printw("Type any character:");
    int ch=getch();

    if (ch==KEY_F(1)) {
        printw("F1 Key pressed!");
    } else {
        attron(A_BOLD);
        printw("%c",ch);
        attroff(A_BOLD);
    }

    refresh();
    getch();
    endwin();
    return 0;
}
