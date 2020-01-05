#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
void numberGame(void);

int main(void)
{
  numberGame();
}
// this is a number game where you have 8 chances to guess the right number.
void numberGame(void)
{
  int n;
  int key;
  int randNum;
  int L;
  char keystring[20];
  srand(time(NULL));
  printf("this is a number game ");
  printf("where you have 8 chances to guess the right number.%d\n",key);
for(L=1; L<=10&&n>1; L++)
  {
  printf("Level %d\n",L);
  randNum=rand()%100;
for (n=8; n>=1; n-=1)
  {
  if(n==1)
    printf("enter a number between 0 and 9. you have 1 guess left\n");
  else
    printf("enter a number between 0 and 9. you have %d guesses left\n", n);
  gets(keystring);
  sscanf(keystring,"%d",&key);
  printf("you entered the %d key and ",key);
  if(key==randNum)
    {
      printf("you are right!\n");
      n=2;
      if(L>=10)
      printf("you won!");
      break;
    }
    else
      {
      if(n!=1)
      if(key>randNum)
      printf("that is too high! Guess lower.");
      if(key<randNum)
      printf("that is too low!guess higher.");
      if(n==1)
        {
      printf("\nGame over\n");
      break;
      }
        }
     }
  }
    if(key!=randNum)
  printf("the correct answer is %d!",randNum);
}