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
  int n=-1;
  int key;
  int prandNum;
  int crandNum;
  int csum=0;
  int psum=0;
  int L;
  int s;
  srand(time(NULL));
  printf("blackjack\npress i for instructions or c to continue.\n");
  key=getchar();
  fflush(stdin);
  if(key=='i')
  {
    printf("you and the computer will take turns to draw cards.\n");
    printf("each card will be between 1 and 13. you and the computer are competing to be the closest to 21.\n");
    printf("but don't go over, or you lose.\n");
    printf("if you think that you are close enough to 21, you can stop drawing,\n");
    printf("and the computer can continue drawing. the opposite is also true.\n");
    printf("this game has 10 levels, and you win when they are completed.\n");
    key='c';
  }
  if(key=='c')
  for(L=1; (L<=11) && (n<0); L++)
  {
    if(L==11)
    {
      printf("you won!");
      break;
    }
    csum=0;
    psum=0;
    n=2;
    printf("Level %d\n",L);
    prandNum=rand()%12+1;
    crandNum=rand()%12+1;
    for (n=2; n>1; n++)
    {
      if(n==2)
        printf("enter 'h'to draw a card.\n");
      else
        printf("enter 'h'to draw another card. enter 's' to stop drawing\n");
      key=getchar();
      fflush(stdin);
      if(key=='h')
      {
        prandNum=drawCard();
        crandNum=drawCard();
        if(csum>=psum && (csum-psum)<(21-csum) || psum>csum)
        {
          csum+=crandNum;
          printf("your opponent drew a %d card.He now has %d points\n",crandNum ,csum);
          if(csum>21)
          {
            printf("you have completed Level %d.\n",L);
            n=-2;
            break;
          }
          if(csum<21)
          {
            psum+=prandNum;
            printf("you drew a %d card.you now have %d points\n",prandNum ,psum);
            if(psum>21)
            {
              printf("you lose");
              n=0;
              break;
            }
          }
        }
        else
        {
          printf("your opponent has stopped drawing.would you like to keep drawing?\n");
          while(n>1)
          {
            key=getchar();
            fflush(stdin);
            if(key=='h')
            {
              prandNum=drawCard();
              psum+=prandNum;
              if(psum>21)
              {
                printf("you drew a %d card.you now have %d points.\nyou lose\n",prandNum,psum,n);
                n=0;
                break;
              }
              printf("you drew a %d card.you now have %d points.\n",prandNum,psum);
              if(psum<=csum)
                printf("would you like to keep drawing?\n");
            }
              if(key=='s' && csum>=psum && csum<=21)
              {
                printf("you lose");
                n=0;
                key='1';
                break;
              }
            if(psum>csum)
            {
              printf("you have completed Level %d.\n",L);
              n=-2;
              break;
            }
          }
        }
      }
        if(key=='s' && csum>psum && csum<=21)
        {
          printf("you lose");
          n=0;
          break;
        }
        if(key=='s')
        while(csum<=psum && csum<=21 && n>1)
        {
          crandNum=drawCard();
          csum+=crandNum;
          printf("your opponent drew again.he drew a %d card. he now has %d points\n",crandNum,csum);
          if(csum>psum && csum<=21 || psum>21)
          {
            printf("you lose");
            n=0;
            break;
          }
        if(csum>21 && psum<=21)
        {
          printf("you have completed Level %d.\n",L);
          n=-2;
          break;
        }
        }
    }
  }
}