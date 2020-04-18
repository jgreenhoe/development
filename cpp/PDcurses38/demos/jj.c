#include <curses.h>
#include <windows.h>
#include <math.h>
#include <time.h>
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
void bmb(int n);
void enemy(int n);
void jerase(int row,int col);
void plyr(int row, int col);

CHAR GetCh (VOID);
enum spaceships {ROW,COL,STATE,APRNCE,LIFE};

WINDOW *screen;
int pstn[5][5] = {
 {0, 1, 1, '0', 1}, // spaceship 0
 {0, 3, 1, '1', 1}, // spaceship 1
 {0, 5, 1, '2', 1}, // spaceship 2
 {0, 7, 1, '3', 1}, // spaceship 3
 {0, 9, 1, '4', 1}, // spaceship 4
//              |_ alive=1 dead=0
//|  |  |   |_____ spaceship aperance
//|  |  |_________ g=1==>forward g=0==>backwards
//|  |____________ column
//|_______________ row
};

int bmbpstn[5][3] = {
 {0, 0, 0}, // bomb 0
 {0, 2, 0}, // bomb 1
 {0, 4, 0}, // bomb 2
 {0, 6, 0}, // bomb 3
 {0, 8, 0}, // bomb 4
//|  |   |_____ ready to drop=0, in action=1
//|  |________ column
//|___________ row
};

int randvrb[5][1] = {
 {0}, // random variable 0
 {0}, // random variable 1
 {0}, // random variable 2
 {0}, // random variable 3
 {0}, // random variable 4
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

void bmb(int n)
{
    mvwaddch(screen, bmbpstn[n][0], bmbpstn[n][1], (chtype)'#');
    wrefresh(screen);
}

void enemy(int n)
{
    mvwaddch(screen, pstn[n][0], pstn[n][1], pstn[n][APRNCE]);
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
void berase(int n)
{
    mvwaddch(screen, bmbpstn[n][0], bmbpstn[n][1], (chtype) ' ');
    wrefresh(screen);
}
void intro(void)
{
    mvaddch( 6, 1, 'S');
    mvaddch( 8, 1, 'p');
    mvaddch(10, 1, 'a');
    mvaddch(12, 1, 'c');
    mvaddch(14, 1, 'e');
    mvaddch( 4, 3, 'i');
    mvaddch( 6, 3, 'n');
    mvaddch( 8, 3, 'v');
    mvaddch(10, 3, 'a');
    mvaddch(12, 3, 'd');
    mvaddch(14, 3, 'e');
    mvaddch(16, 3, 'r');
    mvaddch(18, 3, 's');
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
  int key;
  int r=0;
  int o=1;

srand(time(NULL));

  while(1)
  {
    napms(55);
//player tank----------------------------------------------------
     key=GetCh();
     oldrow=row;
     oldcol=col;
     int e;
     switch(key)
     {
       case'd': col+=1; break;
       case'a': col-=1; break;
       case'x': exit(0);
     }
     jerase(oldrow,oldcol);
     plyr(row,col);
  for( e=0; e<5; e++)
  {
    if(row==bmbpstn[e][ROW] && col==bmbpstn[e][COL])
       exit(0);
  }
//player bullet--------------------------------------------------
for(e=0; e<5; e++)
{
  if(row3==pstn[e][ROW] && col3==pstn[e][COL] && pstn[e][LIFE]==1)
  {
    pstn[e][LIFE]=0;
    row3=row;
    col3=col;
    o=1;
  }
}

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
for(e=0; e<5; e++)
{
  if(row3==pstn[e][ROW] && col3==pstn[e][COL] && pstn[e][LIFE]==1)
  {
    pstn[e][LIFE]=0;
    row3=row;
    col3=col;
    o=1;
  }
}
//enemy----------------------------------------------------------
invdrs();
//enemy bomb-----------------------------------------------------
drpbmb();
//---------------------------------------------------------------
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
  int e;
  int l=0;

  for(e=0; e<5; e++)
    eerase(e);

  for(e=0; e<5; e++)
  {
    if(pstn[e][COL]==0 || l==1)
    {
      pstn[e][ROW]++;
      l=1;
    }
  }
  for(e=0; e<5; e++)
  {
    if(pstn[e][COL]==0 || pstn[e][STATE]==1)
    {
      pstn[e][COL]++;
      pstn[e][STATE]=1;
    }
  }
  for(e=4; e>-1; e--)
  {
    if(pstn[e][COL]==99 || l==1)
    {
      pstn[e][ROW]++;
      l=1;
    }
  }

  for(e=0; e<5; e++)
  {
    if(pstn[e][COL]==99 || pstn[e][STATE]==0)
    {
      pstn[e][COL]--;
      pstn[e][STATE]=0;
    }

  }
  for(e=0; e<5; e++)
  {
    if(pstn[e][LIFE]==1)
      enemy(e);
  }
}
void drpbmb(void)
{
  int e;

  for(e=0; e<5; e++)
    berase(e);

  for(e=0; e<5; e++)
  {
    if(bmbpstn[e][STATE]==0 && pstn[e][LIFE]==1)
    {
      randvrb[e][0]=rand()%20;
      bmbpstn[e][ROW]=pstn[e][ROW];
      bmbpstn[e][COL]=pstn[e][COL];
    }
  }

  for(e=0; e<5; e++)
  {
    if(randvrb[e][0]==0)
      bmbpstn[e][STATE]=1;
  }

  for(e=0; e<5; e++)
  {
  if(bmbpstn[e][STATE]==1)
    {
      bmbpstn[e][ROW]++;
      if(bmbpstn[e][ROW]>39)
        bmbpstn[e][STATE]=0;
      bmb(e);
    }
  }
}
//http: www.cplusplus.com/forum/articles/19975/  with modification
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