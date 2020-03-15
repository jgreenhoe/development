#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int testrep(int z1, int z2, int z3, int z4);
int testrep(int z1, int z2, int z3, int z4)
{
  if(z1==z2 || z1==z3 || z1==z4 || z2==z3 || z2==z4 || z3==z4)
  return 1;
  else
  return 0;
}
int pickNumber(void);
int pickNumber(void)
{
 int randnum=rand()%10;
  return randnum;
}
void codeBreaker(void)
{
  int n=-1;
  int k1=0;
  int k2=0;
  int k3=0;
  int k4=0;
  int L;
  int s;
  int key=s;
  int d1=0;
  int d2=0;
  int d3=0;
  int d4=0;
  int A=0;
  int B=0;
  int r;
  int i;
  char keystring[20];
  srand(time(NULL));
  printf("code breaker\n");
  printf("press i for instructions or c to continue.\n");
  key=getchar();
  fflush(stdin);
  if(key=='i')
  {
    printf("the computer randomly generates 4 numbers. you need to guess what it is.\n");
    printf("enter 4 numbers. if one of your numbers matches one of the computer's\n");
    printf("randomly generated numbers, and it's in the corresponding spot,\n");
    printf("you earn an A. if one of your numbers matches one of the computer's\n");
    printf("randomly generated numbers, but it's in the incorrect spot,you earn a B.\n");
    printf("when you earn 4 A's, you complete the level, and go on to the next.\n");
    printf("you win when all three levels are completed.\n");
    printf("you lose if you fail to guess the numbers in 15 tries.\n");
  }
  if(key=='c' || key=='i')
  for(L=1; L<=4; L++)
  {
    if(L==4)
    {
      printf("you won!");
      break;
    }
    key=s;
    n=0;
    printf("Level %d\n",L);
    for (n=1; n<15; n++)
    {
      while(testrep(d1,d2,d3,d4))
      {
        d1=pickNumber();
        d2=pickNumber();
        d3=pickNumber();
        d4=pickNumber();
      }
      if(key==s)
      {
        if(n==1)
        {
          printf("enter 4 numbers from 0 to 9.\n");
          key=s;
        }
      else
        printf("enter 4 numbers from 0 to 9 based on your last guess.\n");
      }
      A=0;
      B=0;
      gets(keystring);
      i=sscanf(keystring,"%1d%1d%1d%1d",&k1,&k2,&k3,&k4);
      key=s;
      if(testrep(k1,k2,k3,k4) || k1<0 || k2<0 || k3<0 || k4<0 || i!=4)
      {
        printf("do not repeat numbers or enter less or more than 4 numbers. please enter a different set of numbers.\n");
        key=r;
      }
      if(k1==d1)
      {
        A+=1;
      }
       if(k1==d2 || k1==d3 || k1==d4 )
      {
        B+=1;
      }
      if(k2==d2)
      {
        A+=1;
      }
       if(k2==d1 || k2==d3 || k2==d4 )
      {
        B+=1;
      }
      if(k3==d3)
      {
        A+=1;
      }
       if(k3==d1 || k3==d2 || k3==d4 )
      {
        B+=1;
      }
      if(k4==d4)
      {
        A+=1;
      }
       if(k4==d1 || k4==d2 || k4==d3 )
      {
        B+=1;
      }
          if(key==s)
          printf("%dA, %dB\n",A,B);
          if(A==4)
          {
            if(n==1)
            printf("you have completed Level %d. you did this in 1 try.\n",L);
            printf("you have completed Level %d. you did this in %d tries.\n",L,n);
            if(L<3)
            printf("can you do even better?\n");

            d1=0;
            d2=0;
            d3=0;
            d4=0;
            n=-2;
            break;
          }
    }
  }
}