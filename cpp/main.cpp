#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
//void jjfunction(void);
void numberGame(void);

int main(void)
{
  numberGame();
}
// this is a number game where you have 5 chances to guess the right number.
void numberGame(void)
{
  int n;
  int key;
  printf("this is a number game ");
  printf("where you have 5 chances to guess the right number.\n");
  for (n=5; n>=1; n-=1)
  {
    if(n==1)
      printf("enter a number between 1 and 10. you have 1 guess left\n");
    else
      printf("enter a number between 1 and 10. you have %d guesses left\n", n);
    key=getchar();
    fflush(stdin);
    printf("you entered the %c key ", key);
    if (key=='4')
    {
      printf("and you are right!");
      break;
    }
    else
      printf("and you are wrong! HA! HA! HA!\n");
  }
}