#include <curses.h>
void
usage ()
{
  fprintf (stderr, "\nposition error!\n\
 the win_H + pos_y cannot be more than LINES\n\
 the win_W + pos_x cannot be more than COLS\n\
 the win_W cannot be less than 3\n\
 the win_H cannot be less than 3\n\
 the pos_x cannot be less than 0\n\
 the pos_y cannot be less than 0\n\
");
}

int
main (int argc, char *argv[])
{
  int k = 0;
  int i = 0;
  int j = 1;
  int ch = 0;
  char **words = NULL;
  char se[80] = { 0 };
  int win_h = 0;
  int win_w = 0;
  int pos_x = 0;
  int pos_y = 0;
  WINDOW *win;


  printf ("\n\tinput the height of the box:");
  scanf ("%d", &win_h);
  printf ("\n\tinput the width of the box:");
  scanf ("%d", &win_w);
  printf ("\n\tinput the X position of the box:");
  scanf ("%d", &pos_x);
  printf ("\n\tinput the Y position of the box:");
  scanf ("%d", &pos_y);

  words = (char **) calloc (sizeof (char *), win_h - 2);

/*loop for inpu to the words*/

  for (i = 0; i < (win_h - 2); i++)
    {
      while (1)
	{
	  words[i] = (char *) calloc (sizeof (char), win_w - 1);
	  printf ("\n\tinput the input the words:");
	  scanf ("%s", se);
	  if (strlen (se) < (win_w - 1))
	    {
	      strcpy (words[i], se);
	      break;
	    }
	  else
	    {
	      printf ("\n\terror input!please input again:");
	      continue;
	    }
	}
    }
  /*��ʼcurses���� */
  initscr ();
  cbreak;
  noecho ();
  nonl ();
  keypad (stdscr, TRUE);
/*��֤�����Ϸ���*/
  if ((win_h + pos_y) > LINES
      || (win_w + pos_x) > COLS
      || win_w < 3 || win_h < 3 || pos_x < 0 || pos_y < 0)
    {
      endwin ();
      usage ();
      return 1;
    }

/*��ʼ��win*/

  win = newwin (win_h, win_w, pos_y, pos_x);
  box (win, '|', '-');
  for (i = 1; i < (win_h - 1); i++)
    {
      mvwaddstr (win, i, 1, words[i - 1]);
    }
  wattron (win, A_STANDOUT);
  mvwaddstr (win, 1, 1, words[0]);
  wattroff (win, A_STANDOUT);
  refresh ();
  touchwin (win);		/* wrefresh() ǰ�� touchwin() */
  wrefresh (win);
  /* �����޻�Ȧ���ϵȴ�����             */
  k = 0;
  j = 1;
  do
    {
      ch = getch ();		//�ȴ��Լ���������Ԫ
      switch (ch)
	{			/* �ж�������ԪΪ��                   */
	case KEY_UP:
	  {
	    k = ((k + (win_h - 2)) - 1) % (win_h - 2);
	    /* �ж��Ƿ�"��"�������� */
	    /*    mvaddstr(1,20,"up"); */
	    break;
	  }
	case KEY_DOWN:
	  {
	    k = (k + 1) % (win_h - 2);
	    /* �ж��Ƿ�"��"��������               */
	    /*    mvaddstr(1,20,"down"); */
	    break;
	  }
	case '\r':		/* �ж��Ƿ� ENTER ��������            */
	  {
	    j = 0;
	    break;
	  }
	default:
	  {
	    break;
	  }
	}
      /*����k��ֵ�ı�ͼ�β���ʾ */
      for (i = 1; i < (win_h - 1); i++)
	{
	  mvwaddstr (win, i, 1, words[i - 1]);
	}
      wattron (win, A_STANDOUT);
      mvwaddstr (win, k + 1, 1, words[k]);
      wattroff (win, A_STANDOUT);
      refresh ();
      touchwin (win);		/* wrefresh() ǰ�� touchwin() */
      wrefresh (win);

    }
  while (j);
  endwin ();
  printf ("\n\t%s\n", words[k]);	/*�����ѡ�����Ǹ��ִ���� */
}
