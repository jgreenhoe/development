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
int invdrs(char c, int *Row,int *Col, int g);
void drpbmb(void);
void enemy(char c, int row, int col);
void jerase(int row,int col);
void plyr(int row, int col);

CHAR GetCh (VOID);

//int y_pos, x_pos;

WINDOW *screen;
int pstn[5][3] = {
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

void bmb(int row4, int col4)
{
    mvwaddch(screen, row4, col4, (chtype) '0');
    wrefresh(screen);
}

void enemy(char c, int row2, int col2)
{
    mvwaddch(screen, row2, col2, (chtype) c);
    wrefresh(screen);
}

void jerase(int row, int col)
{
    mvwaddch(screen, row, col, (chtype) ' ');
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
  int row2=0, col2=0;
  int row3=row, col3=col;
  int row4=row, col4=col2;
  int row5=0, col5=1;
  int row6=0, col6=3;
  int row7=0, col7=5;
  int row8=0, col8=4;
  int row9=0, col9=5;
  int row10=0, col10=6;
  int oldrow=row, oldcol=col;
  int oldrow2=row2, oldcol2=col2;
  int oldrow3=row3, oldcol3=col3;
  int oldrow4=row4, oldcol4=col4;
  int oldrow5=row5, oldcol5=col5;
  int oldrow6=row6, oldcol6=col6;
  int t=1;
  int key;
  int r=0;
  int o=1;
  int r2=0;
  int o2=1;
  int *Row;
  int *Col;
  int g=1;
  int y;
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
g=invdrs('1', &row5,&col5,g);
g=invdrs('2', &row5,&col6,g);
g=invdrs('3', &row5,&col7,g);
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

int invdrs(char c, int *Row,int *Col, int g)
{
  int row=*Row;
  int col=*Col;
  jerase(row,col);
    if(col==0) row++;
    if(col==0 || g==1)
    {
      col++;
      g=1;
    }
     if(col==99) row++;
    if(col==99 || g==0)
    {
      col--;
      g=0;
    }
    *Row=row;
    *Col=col;
    enemy(c, row,col);
    return g;
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
