#include "main.h"
#include <windows.h>
#include <ncurses.h>
#define NROWS 35
#define NCOLS 95
CHAR GetCh (VOID);

void videoGame(void)
{
char screen[NROWS][NCOLS];
int i,j,row=17,col=35;
int w;
int a;
int s;
int d;
int key;
while(1)
{
for(i=0; i<NROWS; i++)
{


  for(j=0; j<NCOLS; j++) screen[i][j] = '.';
  screen[i][NCOLS-1] = '\0';
}
  screen[row][col]='o';
  for(i=0; i<NROWS; i++) printf("%s\n",screen[i]);

  key=GetCh();
  fflush(stdin);
  switch(key)
  {
    case'w': row-=2; break;
    case's': row+=2; break;
    case'd': col+=2; break;
    case'a': col-=2; break;
  }
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