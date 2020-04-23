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
enum spaceships {ROW,COL,STATE,APRNCE,LIFE,M};

WINDOW *screen;
int pstn[55][6] = {
 {0, 1, 1, '&', 1, 0}, // spaceship 0
 {0, 6, 1, '&', 1, 0}, // spaceship 1
 {0,11, 1, '&', 1, 0}, // spaceship 2
 {0,16, 1, '&', 1, 0}, // spaceship 3
 {0,21, 1, '&', 1, 0}, // spaceship 4
 {0,26, 1, '&', 1, 0}, // spaceship 6
 {0,31, 1, '&', 1, 0}, // spaceship 7
 {0,36, 1, '&', 1, 0}, // spaceship 8
 {0,41, 1, '&', 1, 0}, // spaceship 9
 {0,46, 1, '&', 1, 0}, // spaceship 10
 {0,51, 1, '&', 1, 0}, // spaceship 11
 {2, 1, 1, '$', 1, 0}, // spaceship 12
 {2, 6, 1, '$', 1, 0}, // spaceship 13
 {2,11, 1, '$', 1, 0}, // spaceship 14
 {2,16, 1, '$', 1, 0}, // spaceship 15
 {2,21, 1, '$', 1, 0}, // spaceship 16
 {2,26, 1, '$', 1, 0}, // spaceship 17
 {2,31, 1, '$', 1, 0}, // spaceship 18
 {2,36, 1, '$', 1, 0}, // spaceship 19
 {2,41, 1, '$', 1, 0}, // spaceship 20
 {2,46, 1, '$', 1, 0}, // spaceship 21
 {2,51, 1, '$', 1, 0}, // spaceship 22
 {4, 1, 1, '%', 1, 0}, // spaceship 23
 {4, 6, 1, '%', 1, 0}, // spaceship 24
 {4,11, 1, '%', 1, 0}, // spaceship 25
 {4,16, 1, '%', 1, 0}, // spaceship 26
 {4,21, 1, '%', 1, 0}, // spaceship 27
 {4,26, 1, '%', 1, 0}, // spaceship 28
 {4,31, 1, '%', 1, 0}, // spaceship 29
 {4,36, 1, '%', 1, 0}, // spaceship 30
 {4,41, 1, '%', 1, 0}, // spaceship 31
 {4,46, 1, '%', 1, 0}, // spaceship 32
 {4,51, 1, '%', 1, 0}, // spaceship 33
 {6, 1, 1, '@', 1, 0}, // spaceship 34
 {6, 6, 1, '@', 1, 0}, // spaceship 35
 {6,11, 1, '@', 1, 0}, // spaceship 36
 {6,16, 1, '@', 1, 0}, // spaceship 37
 {6,21, 1, '@', 1, 0}, // spaceship 38
 {6,26, 1, '@', 1, 0}, // spaceship 39
 {6,31, 1, '@', 1, 0}, // spaceship 40
 {6,36, 1, '@', 1, 0}, // spaceship 41
 {6,41, 1, '@', 1, 0}, // spaceship 42
 {6,46, 1, '@', 1, 0}, // spaceship 43
 {6,51, 1, '@', 1, 0}, // spaceship 44
 {8, 1, 1, '?', 1, 0}, // spaceship 45
 {8, 6, 1, '=', 1, 0}, // spaceship 46
 {8,11, 1, '=', 1, 0}, // spaceship 47
 {8,16, 1, '=', 1, 0}, // spaceship 48
 {8,21, 1, '=', 1, 0}, // spaceship 49
 {8,26, 1, '=', 1, 0}, // spaceship 50
 {8,31, 1, '=', 1, 0}, // spaceship 51
 {8,36, 1, '=', 1, 0}, // spaceship 52
 {8,41, 1, '=', 1, 0}, // spaceship 53
 {8,46, 1, '=', 1, 0}, // spaceship 54
 {8,51, 1, '=', 1, 0}, // spaceship 55
//|  |  |   |   |  |_m variable
//|  |  |   |   |____alive=1 dead=0
//|  |  |   |________spaceship aperance
//|  |  |____________g=1==>forward g=0==>backwards
//|  |_______________column
//|__________________row
};

int bmbpstn[55][4] = {
 {0, 1, 0, 0}, // bomb 0
 {0, 6, 0, 0}, // bomb 1
 {0,11, 0, 0}, // bomb 2
 {0,16, 0, 0}, // bomb 3
 {0,21, 0, 0}, // bomb 4
 {0,26, 0, 0}, // bomb 5
 {0,31, 0, 0}, // bomb 6
 {0,36, 0, 0}, // bomb 7
 {0,41, 0, 0}, // bomb 8
 {0,46, 0, 0}, // bomb 9
 {0,51, 0, 0}, // bomb 10
 {2, 1, 0, 0}, // bomb 12
 {2, 6, 0, 0}, // bomb 13
 {2,11, 0, 0}, // bomb 14
 {2,16, 0, 0}, // bomb 15
 {2,21, 0, 0}, // bomb 16
 {2,26, 0, 0}, // bomb 17
 {2,31, 0, 0}, // bomb 18
 {2,36, 0, 0}, // bomb 19
 {2,41, 0, 0}, // bomb 20
 {2,46, 0, 0}, // bomb 21
 {2,51, 0, 0}, // bomb 22
 {4, 1, 0, 0}, // bomb 23
 {4, 6, 0, 0}, // bomb 24
 {4,11, 0, 0}, // bomb 25
 {4,16, 0, 0}, // bomb 26
 {4,21, 0, 0}, // bomb 27
 {4,26, 0, 0}, // bomb 28
 {4,31, 0, 0}, // bomb 29
 {4,36, 0, 0}, // bomb 30
 {4,41, 0, 0}, // bomb 31
 {4,46, 0, 0}, // bomb 32
 {4,51, 0, 0}, // bomb 33
 {6, 1, 0, 0}, // bomb 34
 {6, 6, 0, 0}, // bomb 35
 {6,11, 0, 0}, // bomb 36
 {6,16, 0, 0}, // bomb 37
 {6,21, 0, 0}, // bomb 38
 {6,26, 0, 0}, // bomb 39
 {6,31, 0, 0}, // bomb 40
 {6,36, 0, 0}, // bomb 41
 {6,41, 0, 0}, // bomb 42
 {6,46, 0, 0}, // bomb 43
 {6,51, 0, 0}, // bomb 44
 {8, 1, 0, 0}, // bomb 45
 {8, 6, 0, 0}, // bomb 46
 {8,11, 0, 0}, // bomb 47
 {8,16, 0, 0}, // bomb 48
 {8,21, 0, 0}, // bomb 49
 {8,26, 0, 0}, // bomb 50
 {8,31, 0, 0}, // bomb 51
 {8,36, 0, 0}, // bomb 52
 {8,41, 0, 0}, // bomb 53
 {8,46, 0, 0}, // bomb 54
 {8,51, 0, 0}, // bomb 55
//|  |  |  |__ random variables
//|  |  |_____ ready to drop=0, in action=1
//|  |________ column
//|___________ row
};

int b=0;
int s=0;
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
    napms(20);
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
  for( e=0; e<55; e++)
  {
    if(row==bmbpstn[e][ROW] && col==bmbpstn[e][COL])
       exit(0);
  }
//player bullet--------------------------------------------------
for(e=0; e<55; e++)
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
for(e=0; e<55; e++)
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
  if((b++)%20==3)
  {
    for(e=0; e<55; e++) eerase(e);
    for(e=0; e<55; e++)
    {

      if(pstn[e][COL]==0 && pstn[e][LIFE]==1)
      {
        for(e=0; e<55; e++)
        {
          pstn[e][ROW]++;
          pstn[e][M]=0;
        }
      }
    }
    for(e=0; e<55; e++)
    {
      if(pstn[e][COL]==0 || pstn[e][STATE]==1 || pstn[e][M]==0)
      {
        pstn[e][COL]++;
        pstn[e][STATE]=1;
      }
    }
    for(e=0; e<55; e++)
    {
      if(pstn[e][COL]==99 && pstn[e][LIFE]==1)
      {
        for(e=0; e<55; e++)
        {
          pstn[e][ROW]++;
          pstn[e][M]=1;
        }
      }
    }
    
    for(e=0; e<55; e++)
    {
      if(pstn[e][COL]==99 || pstn[e][STATE]==0 || pstn[e][M]==1)
      {
        pstn[e][COL]--;
        pstn[e][STATE]=0;
      }
    }
  
  for(e=0; e<55; e++)
  {
    if(pstn[e][LIFE]==1)
      enemy(e);
  }}
}
void drpbmb(void)
{
  int e;

  for(e=0; e<55; e++)
  {
    if(bmbpstn[e][ROW]!=pstn[e][ROW])
      berase(e);
    if(bmbpstn[e][STATE]==0 && pstn[e][LIFE]==1)
    {
      bmbpstn[e][3]=rand()%100;
      bmbpstn[e][ROW]=pstn[e][ROW];
      bmbpstn[e][COL]=pstn[e][COL];
    }
    if(bmbpstn[e][3]==0)
      bmbpstn[e][STATE]=1;
    if(bmbpstn[e][STATE]==1)
    {
      bmbpstn[e][ROW]++;
      if(bmbpstn[e][ROW]>39)
        bmbpstn[e][STATE]=0;
      if(bmbpstn[e][ROW]!=pstn[e][ROW])
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