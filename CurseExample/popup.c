#include <curses.h>
void usage()
{
fprintf(stderr, "\nformat error!\n\
EXAMPLE: popup win_Height win_Width \
position_x position_y\n\
and: the win_H + pos_y cannot be more than LINES\n\
and: the win_W + pos_x cannot be more than COLS\n\
");
}

int main(int argc, char* argv[] )
{
    int ch,x,y;
    int win_h,win_w,pos_x,pos_y;
    WINDOW *win;
    initscr();   //     ←┐
    cbreak;       //      │ 启动 curses 模式
    noecho();     //      │
    nonl();       //    ←┘

    if( 5 != argc )
    {
        endwin();
        usage();
        return 1;
    }

    win_h = atoi( argv[1] );
    win_w = atoi( argv[2] );
    pos_x = atoi( argv[3] );
    pos_y = atoi( argv[4] );

    if( 5 != argc )
    {
        endwin();
        usage();
        return 1;
    }

    if( (win_h + pos_y )> LINES || (win_w + pos_x )> COLS)
    {
        usage();
        endwin();
        return 1;
    }

    win=newwin( win_h,win_w,pos_y,pos_x);
//    atoi(argv[2]),LINES/2-3, COLS/2-15);/* 建立一个新视窗, 其中LINES,COLS*/
       box(win,'|','-');                  /* 为 curses 内定值,即萤幕行/列数*/
/*    mvwaddstr(win,1,4,"This is another screen");
    mvwaddstr(win,2,2,"Press anykey to continue..");*/
         refresh();
             touchwin(win);        /* wrefresh() 前需 touchwin() */
            wrefresh(win);
           getch();              /* 按任意键关闭视窗 */
		   endwin();
} 
