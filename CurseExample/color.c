/*-------------------------------------------------------------- 
     A simple curses color demo program 
     Coder:  jellen 
     Date:   3-26-2004 
-------------------------------------------------------------*/ 
#include <curses.h> 
int main() 
{ 
    initscr();  /*��ʼ����Ļ*/ 
    if(start_color() == OK)  /*������ɫ*/ 
    { 
        init_pair(1, COLOR_RED, COLOR_GREEN);  /*����һ����ɫ��*/ 
        attron(COLOR_PAIR(1));                /*�����ַ������ɫ*/ 
        move(LINES/2, COLS/2); 
        waddstr(stdscr, "Yet another Hello, world!"); 
        attroff(COLOR_PAIR(1));                 /*�ر���ɫ��ʾ*/ 
        refresh(); 
    } 
    else 
    { 
        waddstr(stdscr, "Can not init color"); 
        refresh(); 
    } 
    getch();
    endwin();            /*�ر�curses״̬*/ 
    return 0; 
}

