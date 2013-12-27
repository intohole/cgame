#include "stdio.h"
#include "math.h"
#define RAND_MAX 0xffff
int rand_3(int max,int min)
{
 return rand()%(max+min+1)+min;

}

int rand_2(int max,int min)
{
  return (int)((float)rand()/(float)RAND_MAX*(max-min+1))+min;

}
void cg_num(int num[],int n)
{

 int row=0;

 row=rand_3(n,0);
 *(num+row)=1;

}
void initgame(int num[],int n)
{
  int row=0;
  for(;row<n;row++)
  {
   *(num+row)=0;

 }
}
void pri_num(int num[],int n,int win,int lost,int miss)
{
  int row=0;
  printf("\t\t     ");
  for(;row<n;row++)
  {
    printf("%5d",row+1);
  }
  printf("\n\n\t\t");

  for(row=0;row<n;row++)
  {
    printf("%5d",num[row]);
  }
  printf("\n\n\t\tYou win :%4d  You lost :%4d You miss  :%4d",win,lost,miss);
}
int getspa(int *num,int n)
{
  num=(int *)malloc(n*sizeof(int));
  if(num!=NULL)
  {
    return 1;

  }
  else
  {
    return 0;

  }
}
void  winlost(int key,int num[],int *win,int *lost)
{
  switch(key)
  {
    case 561:jia_1(num,win,lost,0);break;
    case  818:jia_1(num,win,lost,1);break;
    case 1075:jia_1(num,win,lost,2);break;
    case 1332:jia_1(num,win,lost,3);break;
    case 1589:jia_1(num,win,lost,4);break;
    case 1846:jia_1(num,win,lost,5);break;
    case 2103:jia_1(num,win,lost,6);break;
    case 2360:jia_1(num,win,lost,7);break;
    case 2617:jia_1(num,win,lost,8);break;
    case 2864:jia_1(num,win,lost,9);break;
    default :break;

  }


}
int jia_1(int num[],int *win,int *lost,int n)
{
 if(*(num+n)==1)
 {
   *win+=1;

 }
 else
 {

   *lost+=1;
 }
 return 1;
}
void main()
{
 int win_=0;
 int lost_=0;
 int *num;
 int key=0;
 int n=9;
 int ti=0;
 int have_p=0;
 int miss=0;
 getspa(num,n);


 while(1)
 {

  while(!kbhit())
  {
    ti=0;
    clrscr();

    initgame(num,n);
    cg_num(num,n);
    have_p++;
    miss=have_p-lost_-win_;
    pri_num(num,n,win_,lost_,miss);
    while(!kbhit()&&ti<12)
    {
      delay(80000);
      ti++;
    }

  }

  key=bioskey(0);
  winlost(key,num,&win_,&lost_);
  clrscr();

  pri_num(num,n,win_,lost_,miss);
  if((miss+lost_-win_)>=25)
  {

    clrscr();
    printf("\n\n\n\n\t\t\tYou are Lost!!!");
    getch();
    break;
  }


}



}
