/******************************************************************************/
/*                                                                            */
/******************************************************************************/

#include <curses.h>
#include <windows.h>


//void boxit(void);
//void seas(void);
//void greet(void);
//void fromwho(void);
//void del_msg(void);
void jerase(int row,int col);
void ball(int row, int col);

//#define FROMWHO "From Larry Bartz, Mark Hessling and William McBrine and Jonathan!"
CHAR GetCh (VOID);

int y_pos, x_pos;

WINDOW *treescrn2;

int main(int argc, char **argv)
{

    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    nonl();
    refresh();

    if (has_colors())
        start_color();
    curs_set(0);

    treescrn2 = newwin(0, 0, 0, 0);

    clear();
    refresh();
    napms(1000);

//    boxit();
//    del_msg();
//    napms(1000);

    int key;
    int row=0;
    int col=12;
    int oldrow=row;
    int oldcol=col;
//    seas();
//    del_msg();
//    napms(1000);
    while(1)
    {
       key=GetCh();
       fflush(stdin);

       oldrow=row;
       oldcol=col;
       switch(key)
       {
         case'w': row-=2; break;
         case's': row+=2; break;
         case'd': col+=2; break;
         case'a': col-=2; break;
       }
       jerase(oldrow,oldcol);
       ball(row,col);
    }
    napms(1000);

    napms(3000);
    return 0;
}

void ball(int row, int col)
{
    mvwaddch(treescrn2, row, col, (chtype) 'O');
    wrefresh(treescrn2);
//    wrefresh(w_del_msg);
}
void jerase(int row, int col)
{
    mvwaddch(treescrn2, row, col, (chtype) ' ');
    wrefresh(treescrn2);
//    wrefresh(w_del_msg);
}

void boxit(void)
{
    int x;

    for (x = 0; x < 20; ++x)
        mvaddch(x, 7, '|');

    for (x = 0; x < 80; ++x)
    {
        if (x > 7)
            mvaddch(19, x, '_');

        mvaddch(22, x, '_');
    }
}

void seas(void)
{
    mvaddch(4, 1, 'H');
    mvaddch(6, 1, 'E');
    mvaddch(8, 1, 'L');
    mvaddch(10, 1, 'L');
    mvaddch(12, 1, 'O');
    mvaddch(14, 1, '!');
    mvaddch(16, 1, '!');
    mvaddch(18, 1, '!');
}

void greet(void)
{
    mvaddch(3, 5, 'E');
    mvaddch(5, 5, 'V');
    mvaddch(7, 5, 'E');
    mvaddch(9, 5, 'R');
    mvaddch(11, 5, 'R');
    mvaddch(13, 5, 'Y');
    mvaddch(15, 5, 'O');
    mvaddch(17, 5, 'N');
    mvaddch(19, 5, 'E');
}

//void fromwho(void)
//{
//    mvaddstr(21, 13, FROMWHO);
//}

void del_msg(void)
{
    refresh();
}

// http://www.cplusplus.com/forum/articles/19975/
CHAR GetCh (VOID)
{
  HANDLE hStdin = GetStdHandle (STD_INPUT_HANDLE);
  INPUT_RECORD irInputRecord;
  DWORD dwEventsRead;
  CHAR cChar;

  while(ReadConsoleInputA (hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
    if (irInputRecord.EventType == KEY_EVENT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
    {
      cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
	ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */
	return cChar;
    }
  return EOF;
}
