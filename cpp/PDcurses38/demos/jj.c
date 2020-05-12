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
void shld(int n);
void mkshld(void);
void jerase(int row,int col);
void plyr(int row, int col);

CHAR GetCh (VOID);
enum spaceships {ROW,COL,STATE,APRNCE,LIFE,M,MAX};

WINDOW *screen;
int pstn[55][7] = {
 {0, 1, 1, '&', 1, 0, 8}, // spaceship 0
 {0, 6, 1, '&', 1, 0, 8}, // spaceship 1
 {0,11, 1, '&', 1, 0, 8}, // spaceship 2
 {0,16, 1, '&', 1, 0, 8}, // spaceship 3
 {0,21, 1, '&', 1, 0, 8}, // spaceship 4
 {0,26, 1, '&', 1, 0, 8}, // spaceship 5
 {0,31, 1, '&', 1, 0, 8}, // spaceship 6
 {0,36, 1, '&', 1, 0, 8}, // spaceship 7
 {0,41, 1, '&', 1, 0, 8}, // spaceship 8
 {0,46, 1, '&', 1, 0, 8}, // spaceship 9
 {0,51, 1, '&', 1, 0, 8}, // spaceship 10
 {2, 1, 1, '$', 1, 0, 8}, // spaceship 11
 {2, 6, 1, '$', 1, 0, 8}, // spaceship 12
 {2,11, 1, '$', 1, 0, 8}, // spaceship 13
 {2,16, 1, '$', 1, 0, 8}, // spaceship 14
 {2,21, 1, '$', 1, 0, 8}, // spaceship 15
 {2,26, 1, '$', 1, 0, 8}, // spaceship 16
 {2,31, 1, '$', 1, 0, 8}, // spaceship 17
 {2,36, 1, '$', 1, 0, 8}, // spaceship 18
 {2,41, 1, '$', 1, 0, 8}, // spaceship 19
 {2,46, 1, '$', 1, 0, 8}, // spaceship 20
 {2,51, 1, '$', 1, 0, 8}, // spaceship 21
 {4, 1, 1, '%', 1, 0, 8}, // spaceship 22
 {4, 6, 1, '%', 1, 0, 8}, // spaceship 23
 {4,11, 1, '%', 1, 0, 8}, // spaceship 24
 {4,16, 1, '%', 1, 0, 8}, // spaceship 25
 {4,21, 1, '%', 1, 0, 8}, // spaceship 26
 {4,26, 1, '%', 1, 0, 8}, // spaceship 27
 {4,31, 1, '%', 1, 0, 8}, // spaceship 28
 {4,36, 1, '%', 1, 0, 8}, // spaceship 29
 {4,41, 1, '%', 1, 0, 8}, // spaceship 30
 {4,46, 1, '%', 1, 0, 8}, // spaceship 31
 {4,51, 1, '%', 1, 0, 8}, // spaceship 32
 {6, 1, 1, '@', 1, 0, 8}, // spaceship 33
 {6, 6, 1, '@', 1, 0, 8}, // spaceship 34
 {6,11, 1, '@', 1, 0, 8}, // spaceship 35
 {6,16, 1, '@', 1, 0, 8}, // spaceship 36
 {6,21, 1, '@', 1, 0, 8}, // spaceship 37
 {6,26, 1, '@', 1, 0, 8}, // spaceship 38
 {6,31, 1, '@', 1, 0, 8}, // spaceship 39
 {6,36, 1, '@', 1, 0, 8}, // spaceship 40
 {6,41, 1, '@', 1, 0, 8}, // spaceship 41
 {6,46, 1, '@', 1, 0, 8}, // spaceship 42
 {6,51, 1, '@', 1, 0, 8}, // spaceship 43
 {8, 1, 1, '=', 1, 0, 8}, // spaceship 44
 {8, 6, 1, '=', 1, 0, 8}, // spaceship 45
 {8,11, 1, '=', 1, 0, 8}, // spaceship 46
 {8,16, 1, '=', 1, 0, 8}, // spaceship 47
 {8,21, 1, '=', 1, 0, 8}, // spaceship 48
 {8,26, 1, '=', 1, 0, 8}, // spaceship 49
 {8,31, 1, '=', 1, 0, 8}, // spaceship 50
 {8,36, 1, '=', 1, 0, 8}, // spaceship 51
 {8,41, 1, '=', 1, 0, 8}, // spaceship 52
 {8,46, 1, '=', 1, 0, 8}, // spaceship 53
 {8,51, 1, '=', 1, 0, 8}, // spaceship 54
//|  |  |   |   |  |  |_max row
//|  |  |   |   |  |____m variable
//|  |  |   |   |_______alive=1 dead=0
//|  |  |   |___________spaceship aperance
//|  |  |_______________g=1==>forward g=0==>backwards
//|  |__________________column
//|_____________________row
};

int bpstn[55][4] = {
 {1, 1, 0, 0}, // bomb 0 
 {1, 6, 0, 0}, // bomb 1 
 {1,11, 0, 0}, // bomb 2 
 {1,16, 0, 0}, // bomb 3 
 {1,21, 0, 0}, // bomb 4 
 {1,26, 0, 0}, // bomb 5 
 {1,31, 0, 0}, // bomb 6 
 {1,36, 0, 0}, // bomb 7 
 {1,41, 0, 0}, // bomb 8 
 {1,46, 0, 0}, // bomb 9 
 {1,51, 0, 0}, // bomb 10
 {3, 1, 0, 0}, // bomb 11
 {3, 6, 0, 0}, // bomb 12
 {3,11, 0, 0}, // bomb 13
 {3,16, 0, 0}, // bomb 14
 {3,21, 0, 0}, // bomb 15
 {3,26, 0, 0}, // bomb 16
 {3,31, 0, 0}, // bomb 17
 {3,36, 0, 0}, // bomb 18
 {3,41, 0, 0}, // bomb 19
 {3,46, 0, 0}, // bomb 20
 {3,51, 0, 0}, // bomb 21
 {5, 1, 0, 0}, // bomb 22
 {5, 6, 0, 0}, // bomb 23
 {5,11, 0, 0}, // bomb 24
 {5,16, 0, 0}, // bomb 25
 {5,21, 0, 0}, // bomb 26
 {5,26, 0, 0}, // bomb 27
 {5,31, 0, 0}, // bomb 28
 {5,36, 0, 0}, // bomb 29
 {5,41, 0, 0}, // bomb 30
 {5,46, 0, 0}, // bomb 31
 {5,51, 0, 0}, // bomb 32
 {7, 1, 0, 0}, // bomb 33
 {7, 6, 0, 0}, // bomb 34
 {7,11, 0, 0}, // bomb 35
 {7,16, 0, 0}, // bomb 36
 {7,21, 0, 0}, // bomb 37
 {7,26, 0, 0}, // bomb 38
 {7,31, 0, 0}, // bomb 39
 {7,36, 0, 0}, // bomb 40
 {7,41, 0, 0}, // bomb 41
 {7,46, 0, 0}, // bomb 42
 {7,51, 0, 0}, // bomb 43
 {9, 1, 0, 0}, // bomb 44
 {9, 6, 0, 0}, // bomb 45
 {9,11, 0, 0}, // bomb 46
 {9,16, 0, 0}, // bomb 47
 {9,21, 0, 0}, // bomb 48
 {9,26, 0, 0}, // bomb 49
 {9,31, 0, 0}, // bomb 50
 {9,36, 0, 0}, // bomb 51
 {9,41, 0, 0}, // bomb 52
 {9,46, 0, 0}, // bomb 53
 {9,51, 0, 0}, // bomb 54
//|  |  |  |__ random variables
//|  |  |_____ ready to drop=0, in action=1
//|  |________ column
//|___________ row
};

int spstn[][3] = {
 {25,10, 1}, {25,11, 1}, {25,12, 1}, {25,13, 1}, {25,14, 1}, {25,15, 1}, {25,16, 1}, {25,17, 1},
 {26,10, 1}, {26,11, 1}, {26,12, 1}, {26,13, 1}, {26,14, 1}, {26,15, 1}, {26,16, 1}, {26,17, 1},
 {27,10, 1}, {27,11, 1}, {27,12, 1}, {27,13, 1}, {27,14, 1}, {27,15, 1}, {27,16, 1}, {27,17, 1},
 {28,10, 1}, {28,11, 1}, {28,12, 1}, {28,13, 1}, {28,14, 1}, {28,15, 1}, {28,16, 1}, {28,17, 1},

 {25,30, 1}, {25,31, 1}, {25,32, 1}, {25,33, 1}, {25,34, 1}, {25,35, 1}, {25,36, 1}, {25,37, 1},
 {26,30, 1}, {26,31, 1}, {26,32, 1}, {26,33, 1}, {26,34, 1}, {26,35, 1}, {26,36, 1}, {26,37, 1},
 {27,30, 1}, {27,31, 1}, {27,32, 1}, {27,33, 1}, {27,34, 1}, {27,35, 1}, {27,36, 1}, {27,37, 1},
 {28,30, 1}, {28,31, 1}, {28,32, 1}, {28,33, 1}, {28,34, 1}, {28,35, 1}, {28,36, 1}, {28,37, 1},

 {25,50, 1}, {25,51, 1}, {25,52, 1}, {25,53, 1}, {25,54, 1}, {25,55, 1}, {25,56, 1}, {25,57, 1},
 {26,50, 1}, {26,51, 1}, {26,52, 1}, {26,53, 1}, {26,54, 1}, {26,55, 1}, {26,56, 1}, {26,57, 1},
 {27,50, 1}, {27,51, 1}, {27,52, 1}, {27,53, 1}, {27,54, 1}, {27,55, 1}, {27,56, 1}, {27,57, 1},
 {28,50, 1}, {28,51, 1}, {28,52, 1}, {28,53, 1}, {28,54, 1}, {28,55, 1}, {28,56, 1}, {28,57, 1},

 {25,70, 1}, {25,71, 1}, {25,72, 1}, {25,73, 1}, {25,74, 1}, {25,75, 1}, {25,76, 1}, {25,77, 1},
 {26,70, 1}, {26,71, 1}, {26,72, 1}, {26,73, 1}, {26,74, 1}, {26,75, 1}, {26,76, 1}, {26,77, 1},
 {27,70, 1}, {27,71, 1}, {27,72, 1}, {27,73, 1}, {27,74, 1}, {27,75, 1}, {27,76, 1}, {27,77, 1},
 {28,70, 1}, {28,71, 1}, {28,72, 1}, {28,73, 1}, {28,74, 1}, {28,75, 1}, {28,76, 1}, {28,77, 1},
//|  |  |_____ destroyed=0, not destroyed=1
//|  |________ column
//|___________ row
};
int b=0;
int u=0;
int e=0;
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
    mvwaddch(screen, bpstn[n][0], bpstn[n][1], (chtype)'#');
    wrefresh(screen);
}

void shld(int n)
{
    mvwaddch(screen, spstn[n][0], spstn[n][1], (chtype)'A');
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
    mvwaddch(screen, bpstn[n][0], bpstn[n][1], (chtype) ' ');
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
     int f;
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
    if(row==bpstn[e][ROW] && col==bpstn[e][COL])
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
    if(pstn[e][ROW]==pstn[e][MAX])
      for(f=0; f<55; f++)
      {
        if(pstn[e][COL]==pstn[f][COL])
        {
          pstn[f][MAX]-=2;
          if(pstn[f][MAX]==pstn[f][LIFE] && pstn[f][LIFE]==0)
            pstn[f][MAX]-=2;
        }
      }
  }
}
//enemy----------------------------------------------------------
invdrs();
//enemy bomb-----------------------------------------------------
drpbmb();
//shield---------------------------------------------------------
mkshld();
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
  if((b++)%20==1)
  {
    for(e=0; e<55; e++)
      eerase(e);
    for(e=0; e<55; e++)
    {
      if(pstn[e][COL]==99 && pstn[e][LIFE]==1)
      {
        for(e=0; e<55; e++)
        {
          pstn[e][MAX]++;
          pstn[e][ROW]++;
          if(bpstn[e][STATE]==0)
            bpstn[e][ROW]++;
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
      if(pstn[e][COL]==0 && pstn[e][LIFE]==1)
      {
        for(e=0; e<55; e++)
        {
          pstn[e][MAX]++;
          pstn[e][ROW]++;
          if(bpstn[e][STATE]==0)
            bpstn[e][ROW]++;
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
  }
  for(e=0; e<55; e++)
  {
    if(pstn[e][LIFE]==1)
      enemy(e);
  }
}

void drpbmb(void)
{
  if((u++)%2)
  {
    for(e=0; e<55; e++)
    {
      if(bpstn[e][STATE]==1 && bpstn[e][ROW]>pstn[e][MAX])
        berase(e);
      if(bpstn[e][STATE]==0 && pstn[e][LIFE]==1)
      {
        bpstn[e][3]=rand()%50;
        bpstn[e][ROW]=pstn[e][MAX]+1;
        bpstn[e][COL]=pstn[e][COL];
      }
      if(bpstn[e][STATE]==0 && bpstn[e][3]==10)
        bpstn[e][STATE]=1;
      if(pstn[e][ROW]==pstn[e][MAX])
      {
        bpstn[e][ROW]++;
        if(bpstn[e][ROW]>39)
          bpstn[e][STATE]=0;
        if(bpstn[e][STATE]==1 && bpstn[e][ROW]>pstn[e][MAX])
          bmb(e);
      }
    }
  }
}

void mkshld(void)
{
  for(e=0; e<55; e++)
  {
    if(spstn[e][STATE]==1)
      shld(e);
    if(bpstn[e][ROW]==spstn[e][ROW] && bpstn[e][COL]==spstn[e][COL])
    {
      eerase(e);
      spstn[e][STATE]=0;
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