#include <curses.h>
#include <windows.h>
void seas(void);
void greet(void);
void del_msg(void);
void plyrCntrl(void);
void path(void);
void jerase(int row,int col);
void ball(int row, int col);

CHAR GetCh (VOID);

int y_pos, x_pos;

WINDOW *screen;

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

    screen = newwin(0, 0, 0, 0);

    clear();
    refresh();
    napms(1000);

    seas();
    greet();
    del_msg();
    napms(1000);
    path();
  
    napms(1000);

    napms(3000);
    return 0;

}
void ball(int row, int col)
{
    mvwaddch(screen, row, col, (chtype) 'J');
    wrefresh(screen);
}
void jerase(int row, int col)
{
    mvwaddch(screen, row, col, (chtype) ' ');
    wrefresh(screen);
}

void seas(void)
{
    mvaddch( 4, 1, 'J');
    mvaddch( 6, 1, 'o');
    mvaddch( 8, 1, 'n');
    mvaddch(10, 1, 'a');
    mvaddch(12, 1, 't');
    mvaddch(14, 1, 'h');
    mvaddch(16, 1, 'a');
    mvaddch(18, 1, 'n');
    mvaddch(20, 1, '\'');
    mvaddch(22, 1, 's');
}

void greet(void)
{
    mvaddch( 7, 3, 'G');
    mvaddch(11, 3, 'a');
    mvaddch(15, 3, 'm');
    mvaddch(19, 3, 'e');
}

void del_msg(void)
{
    refresh();
}

void plyrCntrl(void)
{
  int key;
  int row=35;
  int col=0;
  int oldrow=row;
  int oldcol=col;
  while(1)
  {
     key=GetCh();
     oldrow=row;
     oldcol=col;
     switch(key)
     {
       case'w': row-=2; break;
       case's': row+=2; break;
       case'd': col+=2; break;
       case'a': col-=2; break;
       case'x': exit(0);
     }
     jerase(oldrow,oldcol);
     ball(row,col);
  }
}
void path(void)
{
  int row=40;
  int col=0;
  int oldrow=row;
  int oldcol=col;
  while(row<90)
  {
    oldrow=row;
    oldcol=col;
    row-=2;
    col+=2;
    napms(500);
    jerase(oldrow,oldcol);
    ball(row,col);
  }
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
