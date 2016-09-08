/*----------------------------------------------------------------- 
          A very simple example of curses programming 
                    coder:   jellen 
                              date:    3-26-2004 
----------------------------------------------------------------*/ 
#include <curses.h> 
int main() 
{ 
    initscr(); 
    move(LINES/3, COLS/3);              /*move the cursor to the center*/ 
    box(stdscr, ACS_VLINE, ACS_HLINE);  /*draw a box*/ 
//  box(stdscr, ACS_VLINE, ACS_HLINE/2);  /*draw a box*/ 
//  box(stdscr, ACS_VLINE/2, ACS_HLINE);  /*draw a box*/ 
    move(LINES/2, COLS/2);              /*move the cursor to the center*/ 
    waddstr(stdscr, "It`s my world!");   
    refresh(); 
	getch(); 
    endwin(); 
    return 0; 
}

