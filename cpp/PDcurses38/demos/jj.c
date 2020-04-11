#include <curses.h>
#include <windows.h>
#include <math.h>
void intro(void);
void del_msg(void);
void plyrCntrl(void);
void path(void);
void arc(void);
int cnvrt(int y);
int drctn(int col);
void spcInvdrs(void);
void invdrs(void);
void drpbmb(void);
void enemy(int n);
void jerase(int row,int col);
void plyr(int row, int col);

CHAR GetCh (VOID);
enum spaceships {ROW,COL,DIR,NAME};

//int y_pos, x_pos;

WINDOW *screen;
int pstn[5][4] = {
 {0, 0, 1, '0'}, // spaceship 0
 {0, 2, 1, '1'}, // spaceship 1
 {0, 4, 1, '2'}, // spaceship 2
 {0, 6, 1, '3'}, // spaceship 3
 {0, 8, 1, '4'}, // spaceship 4
//|  |  |   |_ spaceship design
//|  |  |_____ g=1==>forward g=0==>backwards
//|  |________ column
//|___________ row
};

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

    intro();
    del_msg();
    napms(1000);
    spcInvdrs();

    napms(1000);

    napms(1000);

    napms(3000);
    return 0;

}
void plyr(int row, int col)
{
    mvwaddch(screen, row, col, (chtype) '^');
    wrefresh(screen);
}

void blt(int row3, int col3)
{
    mvwaddch(screen, row3, col3, (chtype) '|');
    wrefresh(screen);
}

//void bmb(int row4, int col4)
//{
//    mvwaddch(screen, row4, col4, (chtype) '0');
//    wrefresh(screen);
//}

void enemy(int n)
{
    mvwaddch(screen, pstn[n][0], pstn[n][1], pstn[n][NAME]);
    wrefresh(screen);
}

void jerase(int row, int col)
{
    mvwaddch(screen, row, col, (chtype) ' ');
    wrefresh(screen);
}
void eerase(int n)
{
    mvwaddch(screen, pstn[n][0], pstn[n][1], (chtype) ' ');
    wrefresh(screen);
}

void intro(void)
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
    mvaddch( 7, 3, 'G');
    mvaddch(11, 3, 'a');
    mvaddch(15, 3, 'm');
    mvaddch(19, 3, 'e');
}

void del_msg(void)
{
    refresh();
}

void spcInvdrs(void)
{
  int row=39, col=50;
  int row3=row, col3=col;
  int oldrow=row, oldcol=col;
  int oldrow3=row3, oldcol3=col3;
  int t=1;
  int key;
  int r=0;
  int o=1;
  int r2=0;
  int o2=1;
  while(1)
  {
    napms(75);
//player tank----------------------------------------------------
     key=GetCh();
     oldrow=row;
     oldcol=col;
     switch(key)
     {
       case'd': col+=1; break;
       case'a': col-=1; break;
       case'x': exit(0);
     }
     jerase(oldrow,oldcol);
     plyr(row,col);
//player bullet--------------------------------------------------

if(key==' ' && row3==row)
{
  col3=col;
  o=r;
}
if(o==r)
{
  oldrow3=row3;
  oldcol3=col3;
  row3--;
  o=r;
  key=0;
  jerase(oldrow3,oldcol3);
  blt(row3,col3);
}
if(row3<0)
{
  row3=row;
  col3=col;
  o=1;
}
//enemy----------------------------------------------------------
invdrs();
//enemy bomb-----------------------------------------------------
//drpbmb(row5,col5);
//drpbmb(row6,col6);
//drpbmb(row7,col7);
//------------------------------------------------------------------------------
  }
}

void plyrCntrl(void)
{
  int key;
  int row=39;
  int col=50;
  int oldrow=row;
  int oldcol=col;
  while(1)
  {
     key=GetCh();
     oldrow=row;
     oldcol=col;
     switch(key)
     {
       case'd': col+=2; break;
       case'a': col-=2; break;
       case'x': exit(0);
     }
     jerase(oldrow,oldcol);
     plyr(row,col);
  }
}

void path(void)
{
  int row=41;
  int col=0;
  int l;
  int oldrow=row;
  int oldcol=col;
  for(l=0; l<40; l++)
  {
    oldrow=row;
    oldcol=col;
    row-=1;
    col+=2;
    napms(100);
    jerase(oldrow,oldcol);
    plyr(row,col);
  }
}

void arc(void)
{
  int row=39;
  int x;
  int y;
  int u=1;
  int col=0;
  int oldrow=row;
  int oldcol=col;
  for(x=col; x<100; x++)
  {
    oldrow=row;
    oldcol=col;
    col=x;
    y=x*tan(M_PI/4.0)-9.80665*x*x/(2*u*u*cos(M_PI/4.0))/700;
    row=cnvrt(y);
    napms(100);
    jerase(oldrow,oldcol);
    plyr(row,col);
  }
}

int cnvrt(int y)
{
int row;
  row=39-y;
return row;
}

void invdrs(void)
{

  eerase(0);
  eerase(1);
  eerase(2);
      if(pstn[0][COL]==0)
      {
        pstn[0][ROW]++;
        pstn[1][ROW]++;
        pstn[2][ROW]++;
      }
      if(pstn[0][COL]==0 || pstn[0][DIR]==1)
      {
        pstn[0][COL]++;
        pstn[1][COL]++;
        pstn[2][COL]++;
        pstn[0][DIR]=1;
        pstn[1][DIR]=1;
        pstn[2][DIR]=1;
      }
     if(pstn[2][COL]==99)
     {
       pstn[0][ROW]++;
       pstn[1][ROW]++;
       pstn[2][ROW]++;
     }

    if(pstn[2][COL]==99 || pstn[2][DIR]==0)
    {
      pstn[0][COL]--;
      pstn[1][COL]--;
      pstn[2][COL]--;
      pstn[0][DIR]=0;
      pstn[1][DIR]=0;
      pstn[2][DIR]=0;
    }
    enemy(0);
    enemy(1);
    enemy(2);
}
//void drpbmb(void)
//{
//  int r2=0;
//  int o2=1;
//  int t=1;
//  if(t==1)
//  {
//    col4=col2;
//    o2=r2;
//  }
//    oldrow4=row4;
//    oldcol4=col4;
//    t=0;
//  if(o2==r2)
//  {
//
//    row4++;
//    o2=r2;
//    jerase(oldrow4,oldcol4);
//    bmb(row4,col4);
//  }
//  if(row4>39)
//  {
//    t=1;
//    row4=row2;
//    col4=col2;
//    o2=1;
//  }
//if(row4==row && col4==col)
//exit(0);
//}
// http://www.cplusplus.com/forum/articles/19975/  with modification
CHAR GetCh (VOID)
{
  HANDLE hStdin = GetStdHandle (STD_INPUT_HANDLE);
  INPUT_RECORD irInputRecord;
  DWORD dwEventsRead;
  CHAR cChar;
  unsigned long numEvents;                                  //<== NEW!!! ^___^
  LPDWORD lpcNumberOfEvents = &numEvents;                   //<== NEW!!! ^___^
  GetNumberOfConsoleInputEvents(hStdin, lpcNumberOfEvents); //<== NEW!!! ^___^

if(numEvents>0){                                             //<== NEW!!! ^___^

//  while(ReadConsoleInputA (hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
ReadConsoleInputA (hStdin, &irInputRecord, 1, &dwEventsRead); /* Read key press */    //<== CHANGED!!! ^___^
    if (irInputRecord.EventType == KEY_EVENT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
    {
      cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
	//ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */  //<== CHANGED!!! ^___^
	return cChar;
}
}
return '0';
  //return EOF;
}
