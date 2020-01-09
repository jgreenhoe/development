#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int drawCard(void)
{
  int randNum;
  randNum=rand()%12+1;
  return randNum;
}
void blackjack(void)
{
  int n;
  int key;
  int prandNum;
  int crandNum;
  int csum=0;
  int psum=0;
  int L;
  int s;
  srand(time(NULL));
  printf("this is a blackjack game ");
  printf("where you compete againsts the computer to get closest to 21.\n");
for(L=1; L<=10&&n>1; L++)
  {
  printf("Level %d\n",L);
  prandNum=rand()%12+1;
  crandNum=rand()%12+1;

  for (n=1; n++;);
  {
  if(n==1)
    printf("enter 'h' for to draw a card.\n");
  else
    printf("enter 'h' for hit me to draw another card. enter 's' to stop drawing\n");
  key=getchar();
  if(key=='h')
    {
      prandNum=drawCard();
      crandNum=drawCard();
      psum+=prandNum;
      csum+=crandNum;
      printf("you drew a %d card.you now have %d points\n",prandNum ,psum);
      printf("your opponent drew a %d card.He now has %d points\n",crandNum ,csum);
  if(psum>21)
  {
  printf("you lose.");
  break;
  }
    if(csum>21)
    printf("you have completed Level %d.",L);
    if(L>=10)
    {
    printf("you won!");
    break;
    }
    }
  if(key==s)
  if(csum<=psum)
  drawCard();
  }
  }
  }