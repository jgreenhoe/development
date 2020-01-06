#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// this is a number game where you have 8 chances to guess the right number.
void blackjack(void)
{
  int n;
  int key;
  int randNum;
  int L;
  srand(time(NULL));
  printf("this is a blackjack game ");
  printf("where you compete againsts the computer to get closest to 21.\n");
for(L=1; L<=10&&n>1; L++)
  {
  printf("Level %d\n",L);
  randNum=rand()%10;
  for (n=1; n>=1; n+=1)
  {
  if(n==1)
    printf("enter 'h' for hit me to draw a card.\n");
  else
    printf("enter 'h' for hit me to draw another card. enter 's' for stop to stop drawing\n\n", n);
  key=getchar();
  if(key=='h')
    {
      printf("you drew a %d card.\n",randNum);
      n=2;
      if(L>=10)
      printf("you won!");
      break;
    }
    else
      {
      if(n!=1)
      {
      if(key>randNum)
      printf("that is too high! Guess lower.");
      if(key<randNum)
      printf("that is too low!guess higher.");
      }
      if(n==1)
        {
      printf("you are wrong.\nGame over\n");
      break;
      }
        }
     }
  }
    if(key!=randNum)
  printf("the correct answer is %d!",randNum);
}