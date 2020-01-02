//============================================================================
// This is a comment
//=============================================================================
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
void jjfunction(void);
void numberGame(void);

//-----------------------------------------------------------------------------
// This is a comment
// kdjfkdjfkd this is what I think
//-----------------------------------------------------------------------------
int main(void)
{
  numberGame();
}

//-----------------------------------------------------------------------------
// This is a function
//-----------------------------------------------------------------------------
void jjfunction(void)
{
  int j;
  for(j=78; j>=-200  ; j-=20)
  {
    printf("k=%d  Hello Jonathan!!!\n", j);    
    printf("this is a test.\n");
    printf("hello everyone!!!!!!");
  }
}
//-----------------------------------------------------------------------------
// this is a number game
//-----------------------------------------------------------------------------
void numberGame(void)
{
  int j;
  int key;
  for (j=1; j<=5; j+=1)
  {
    printf("enter a number between 1 and 10\n");
   key=getchar();
   fflush(stdin);
   printf("you pressed the %c key\n", key);
  if (key=='8'){ 
  printf("you guessed right!");
  break;
  }  
else
  printf("HA! HA! HA! guess again\n");
}
}