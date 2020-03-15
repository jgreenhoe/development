#include "main.h"
void mainMenu(void);
void blackjack(void);
void numberGame(void);
void codeBreaker(void);
void videoGame(void);
void tmp(void);
int main(void);
int key;
int main(void)
{
  mainMenu();
}
void mainMenu(void)
{
  printf("please choose a game\n");
  printf("press 1 for secret number\n");
  printf("press 2 for blackjack\n");
  printf("press 3 for code breaker\n");
  printf("press 4 for video game\n");
  key=getchar();
  fflush(stdin);
  switch(key)
  {
    case'1':
      numberGame();
      break;
    case'2':
      blackjack();
      break;
    case'3':
      codeBreaker();
      break;
    case'4':
      videoGame();
      break;
  }
}
