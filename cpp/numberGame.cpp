#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void numberGame(void)
{
  int n=2;
  int i;
  int key;
  int c;
  int randNum;
  int L=1;
  char keystring[20];
  srand(time(NULL));
  printf("secret number\npress i for instructions or c to continue.\n");
  key=getchar();
  fflush(stdin);
  if(key=='i')
  {
    printf("a secret number is chosen. you have 8 chances to guess what it is.\n");
    key='c';
  }
  if(key=='c')
  {
    for(L=1; L<=10&&n>1; L++)
    {
      printf("Level %d\n",L);
      randNum=rand()%100;
      for (n=8; n>=1; n-=1)
      {
        if(n==1)
          printf("you have 1 more guess. try again.\n");
        if(n==8)
          printf("you have 8 guesses. enter a number between 0 and 99.\n");
        if(n>1 && n<8)
          printf("you have %d more guesses. try again.\n",n);
        gets(keystring);
        sscanf(keystring,"%d",&key);
        printf("you entered the number %d and ",key);
        if(key==randNum)
        {
          printf("you are correct!\n");
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
  }
    if(key!=randNum)
  printf("the correct answer is %d!",randNum);
}