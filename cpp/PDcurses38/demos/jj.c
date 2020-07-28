#include <curses.h>
#include <windows.h>
#include <math.h>
#include <time.h>
void intro1(void);
void intro2(void);
void intro3(void);
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
 {4, 1, 1, '$', 1, 0, 8}, // spaceship 22
 {4, 6, 1, '$', 1, 0, 8}, // spaceship 23
 {4,11, 1, '$', 1, 0, 8}, // spaceship 24
 {4,16, 1, '$', 1, 0, 8}, // spaceship 25
 {4,21, 1, '$', 1, 0, 8}, // spaceship 26
 {4,26, 1, '$', 1, 0, 8}, // spaceship 27
 {4,31, 1, '$', 1, 0, 8}, // spaceship 28
 {4,36, 1, '$', 1, 0, 8}, // spaceship 29
 {4,41, 1, '$', 1, 0, 8}, // spaceship 30
 {4,46, 1, '$', 1, 0, 8}, // spaceship 31
 {4,51, 1, '$', 1, 0, 8}, // spaceship 32
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
 {8, 1, 1, '@', 1, 0, 8}, // spaceship 44
 {8, 6, 1, '@', 1, 0, 8}, // spaceship 45
 {8,11, 1, '@', 1, 0, 8}, // spaceship 46
 {8,16, 1, '@', 1, 0, 8}, // spaceship 47
 {8,21, 1, '@', 1, 0, 8}, // spaceship 48
 {8,26, 1, '@', 1, 0, 8}, // spaceship 49
 {8,31, 1, '@', 1, 0, 8}, // spaceship 50
 {8,36, 1, '@', 1, 0, 8}, // spaceship 51
 {8,41, 1, '@', 1, 0, 8}, // spaceship 52
 {8,46, 1, '@', 1, 0, 8}, // spaceship 53
 {8,51, 1, '@', 1, 0, 8}, // spaceship 54
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
 {25,16, 1}, {25,17, 1}, {25,18, 1}, {25,19, 1}, {25,20, 1}, {25,21, 1}, {25,22, 1}, {25,23, 1},
 {26,16, 1}, {26,17, 1}, {26,18, 1}, {26,19, 1}, {26,20, 1}, {26,21, 1}, {26,22, 1}, {26,23, 1},
 {27,16, 1}, {27,17, 1}, {27,18, 1}, {27,19, 1}, {27,20, 1}, {27,21, 1}, {27,22, 1}, {27,23, 1},
 {28,16, 1}, {28,17, 1}, {28,18, 1}, {28,19, 1}, {28,20, 1}, {28,21, 1}, {28,22, 1}, {28,23, 1},

 {25,36, 1}, {25,37, 1}, {25,38, 1}, {25,39, 1}, {25,40, 1}, {25,41, 1}, {25,42, 1}, {25,43, 1},
 {26,36, 1}, {26,37, 1}, {26,38, 1}, {26,39, 1}, {26,40, 1}, {26,41, 1}, {26,42, 1}, {26,43, 1},
 {27,36, 1}, {27,37, 1}, {27,38, 1}, {27,39, 1}, {27,40, 1}, {27,41, 1}, {27,42, 1}, {27,43, 1},
 {28,36, 1}, {28,37, 1}, {28,38, 1}, {28,39, 1}, {28,40, 1}, {28,41, 1}, {28,42, 1}, {28,43, 1},

 {25,56, 1}, {25,57, 1}, {25,58, 1}, {25,59, 1}, {25,60, 1}, {25,61, 1}, {25,62, 1}, {25,63, 1},
 {26,56, 1}, {26,57, 1}, {26,58, 1}, {26,59, 1}, {26,60, 1}, {26,61, 1}, {26,62, 1}, {26,63, 1},
 {27,56, 1}, {27,57, 1}, {27,58, 1}, {27,59, 1}, {27,60, 1}, {27,61, 1}, {27,62, 1}, {27,63, 1},
 {28,56, 1}, {28,57, 1}, {28,58, 1}, {28,59, 1}, {28,60, 1}, {28,61, 1}, {28,62, 1}, {28,63, 1},

 {25,76, 1}, {25,77, 1}, {25,78, 1}, {25,79, 1}, {25,80, 1}, {25,81, 1}, {25,82, 1}, {25,83, 1},
 {26,76, 1}, {26,77, 1}, {26,78, 1}, {26,79, 1}, {26,80, 1}, {26,81, 1}, {26,82, 1}, {26,83, 1},
 {27,76, 1}, {27,77, 1}, {27,78, 1}, {27,79, 1}, {27,80, 1}, {27,81, 1}, {27,82, 1}, {27,83, 1},
 {28,76, 1}, {28,77, 1}, {28,78, 1}, {28,79, 1}, {28,80, 1}, {28,81, 1}, {28,82, 1}, {28,83, 1},
//|  |  |_____ destroyed=0, not destroyed=1
//|  |________ column
//|___________ row
};
int b=0;
int u=0;
int w=0;
int e=0;
int g=0;
int pts=0;
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

    int key;
// intro 1
    intro1();
    refresh();
    erase();
// intro 2
    while(key!='c')
      key=GetCh();
    if(key=='c')
    {
      intro2();
      refresh();
      erase();
      key=b;
    }
    while(key!='c')
      key=GetCh();
    if(key=='c')
      key=b;
// intro 3
    while(key!='c')
      key=GetCh();
    if(key=='c')
    {
      intro3();
      refresh();
      erase();
      key=b;
    }
    while(key!='c')
      key=GetCh();
    if(key=='c')
      key=b;
// space invaders
    while(key!='c')
      key=GetCh();
    if(key=='c')
      spcInvdrs();
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
    mvwaddch(screen, spstn[n][0], spstn[n][1], (chtype)'O');
    wrefresh(screen);
}

void enemy(int n)
{
    mvwaddch(screen, pstn[n][0], pstn[n][1], pstn[n][APRNCE]);
    wrefresh(screen);
}

void mstryshp(int row, int col)
{
    mvwaddstr(screen, row, col, "<==>");
    wrefresh(screen);
}

void jerase(int row, int col)
{
    mvwaddch(screen, row, col, (chtype) ' ');
    wrefresh(screen);
}
void merase(int row, int col)
{
    mvwaddstr(screen, row, col, "    ");
    wrefresh(screen);
}

void eerase(int n)
{
    mvwaddch(screen, pstn[n][0], pstn[n][1], (chtype) ' ');
    wrefresh(screen);
}
void serase(int n)
{
    mvwaddch(screen, spstn[n][0], spstn[n][1], (chtype) ' ');
    wrefresh(screen);
}
void berase(int n)
{
    mvwaddch(screen, bpstn[n][0], bpstn[n][1], (chtype) ' ');
    wrefresh(screen);
}
void intro1(void)
{
    mvaddstr(10, 35, "Space invaders");
    mvaddstr(13, 25, "Shoot down all the alien spaceships to win (&, $, @),");
    mvaddstr(16, 25, "But be careful not to get hit by any of their deadly bombs (#)!");
    mvaddstr(19, 25, "Also, destroy the mystery ship for extra points (<==>)!");
    mvaddstr(21, 25, "press c to continue");
}
void intro2(void)
{
    mvaddstr(10, 35, "Controls");
    mvaddstr(13, 35, "a = move left");
    mvaddstr(16, 35, "d = move right");
    mvaddstr(19, 35, "spacebar = fire missiles");
    mvaddstr(21, 35, "press c to continue");
}
void intro3(void)
{
    mvaddstr(10, 35, "Types of spaceships");
    mvaddstr(13, 35, "& = 30 points");
    mvaddstr(16, 35, "$ = 20 points");
    mvaddstr(19, 35, "@ = 10 points");
    mvaddstr(22, 35, "<==> =  ???");
    mvaddstr(24, 35, "press c to begin!");
}

void spcInvdrs(void)
{
  int row=39, col=50;
  int oldrow=row, oldcol=col;
  int row2=0, col2=-3;
  int oldrow2=row2, oldcol2=col2;
  int row3=row, col3=col;
  int oldrow3=row3, oldcol3=col3;
  int key;
  int r=0;
  int o=1;
  int f=0;
  int l=1;

  char score[100];

  srand(time(NULL));

  while(1)
  {
    napms(20);
//score----------------------------------------------------------
    sprintf(score, "score:%04d",pts);
    mvwaddstr(screen, 39, 0, score);
//player tank----------------------------------------------------
    oldrow=row;
    oldcol=col;
    jerase(oldrow,oldcol);
    key=GetCh();
    if(col<99 && key=='d') col++;
    if(col>0 && key=='a') col--;
    if(key=='x') exit(0);
    plyr(row,col);
    for( e=0; e<55; e++)
    {
      if(row==bpstn[e][ROW] && col==bpstn[e][COL])
        exit(0);
    }
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
    for(e=0; e<55; e++)
    {
      if(row3==pstn[e][ROW] && col3==pstn[e][COL] && pstn[e][LIFE]==1)
      {
          if(pstn[e][APRNCE]=='&') pts+=30;
          if(pstn[e][APRNCE]=='$') pts+=20;
          if(pstn[e][APRNCE]=='@') pts+=10;
          pstn[e][LIFE]=0;
          jerase(row3,col3);
          row3=row;
          col3=col;
          o=1;
          if(pstn[e][ROW]==pstn[e][MAX])
            {
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
    }
      int j;
      for(j=0; j<=3; j++)
      {
      if((row3==row2 && col3==col2+j) && l==1)
      {
        pts+=500;
        l=0;
      }
      }
    for(e=0; e<128; e++)
    {
      if(row3==spstn[e][ROW] && col3==spstn[e][COL] && spstn[e][STATE]==1)
      {
        spstn[e][STATE]=0;
        jerase(row3,col3);
        row3=row;
        col3=col;
        o=1;
      }
    }
//enemy----------------------------------------------------------
    invdrs();
//enemy bomb-----------------------------------------------------
    drpbmb();
//shield---------------------------------------------------------
    mkshld();
//mystery ship---------------------------------------------------
  oldrow2=row2;
  oldcol2=col2;
  int v=0;
  merase(oldrow2, oldcol2);
  if(col2>99)
  {
    col2=-3;
    l=0;
    v=0;
  }
  for(g=0;g<=36; g+=4)
  {
    if(g==pstn[0][ROW]+2)
      v=1;
    if(v==1 && (w++)%15==1 && l==1)
      col2++;
    if(g==pstn[0][ROW])
      l=1;
  }
  if(l==1)
    mstryshp(row2, col2);
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
         case'd': col++; break;
         case'a': col--; break;
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
          pstn[e][MAX]+=2;
          pstn[e][ROW]+=2;
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
          pstn[e][MAX]+=2;
          pstn[e][ROW]+=2;
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
  for(e=0; e<55; e++)
  {
    if(pstn[e][ROW]==39 && pstn[e][LIFE]==1)
    {
    mvaddstr(20, 46, "You lose!");
    exit(0);
    }
  }
}

void drpbmb(void)
{
  if((u++)%2)
  {
    for(e=0; e<55; e++)
    {
      if(bpstn[e][ROW]>pstn[e][MAX])
        berase(e);
      if(bpstn[e][STATE]==0 && pstn[e][LIFE]==1)
      {
        bpstn[e][3]=rand()%50;
        bpstn[e][ROW]=pstn[e][MAX]+1;
        bpstn[e][COL]=pstn[e][COL];
      }
      if(bpstn[e][STATE]==0 && bpstn[e][3]==1 && pstn[e][LIFE]==1)
        bpstn[e][STATE]=1;
      if(pstn[e][ROW]==pstn[e][MAX])
      {
        bpstn[e][ROW]++;
        if(bpstn[e][ROW]>39 && pstn[e][LIFE]==1)
          bpstn[e][STATE]=0;
        if(bpstn[e][STATE]==1 && bpstn[e][ROW]>pstn[e][MAX])
          bmb(e);
      }
    }
  }
}

void mkshld(void)
{
  int f=0;
  for(e=0; e<128; e++)
  {
    if(spstn[e][STATE]==1)
      shld(e);
    for(f=0; f<55; f++)
    {
      if(bpstn[f][ROW]==spstn[e][ROW] && bpstn[f][COL]==spstn[e][COL] && spstn[e][STATE]==1)
      {
        spstn[e][STATE]=0;
        serase(e);
        bpstn[f][STATE]=0;
        berase(f);
      }
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