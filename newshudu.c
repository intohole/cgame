/*

数独 可以用九皇后问题解决
生成一个数组 随机排序的
之后观察faxian 数独 每行每列都有一个
唯一一个数字
*/

#include "stdio.h"
#include "time.h"
#define RAND_MAX 0x7FFF
#define MAXROW
#define CHECK pri(); getch();clrscr();
int shudu[9][9]={0};
int svshu[9][9];
long times=0;
void cshudu();
int getnum(int num[],int n);
int rand_3(int max,int min);
void pri();
int yesno(int row,int line,int num);

void main()
{
 srand(time(NULL));
 cshudu();
 pri();
  getch();



}
void cshudu()
{
int num[9];
int lp,rp,numrow;
int sign=0;
int tmp;
getnum(num,9);
numrow=0;
for(numrow=0;numrow<9;numrow++)
{

 rp=0;
 lp=0;
 tmp=0;
 while(rp<9)
 {
 tmp=rand_3(8,0);
    if(shudu[rp][tmp]==0)
    {
    if(yesno(rp,tmp,num[numrow]))
    {
    shudu[rp][tmp]=num[numrow];
      rp++;


    }



    }



 }


    }








}

int getnum(int num[],int n)
{
int rp,lp;
int ti,tmp;
for(rp=0;rp<n;rp++)
{

*(num+rp)=rp+1;

}
for(ti=0;ti<100;ti++)
{

rp=rand_3(0,n-1);
lp=rand_3(0,n-1);
if(rp!=lp)
{
tmp=*(num+rp);
*(num+rp)=*(num+lp);
*(num+lp)=tmp;

}

}

}

int rand_3(int max,int min)
{
int ran;
ran=(int)((double)rand()/(double)RAND_MAX*(max-min+1))+min;
  return ran;

}
int yesno(int row,int line,int num)
{
int lp;
int sign=1;
shudu[row][line]=num;
for(lp=0;lp<9;lp++)
{

if(shudu[lp][line]==num&&row!=lp)
{
shudu[row][line]=0;
sign=0;

}

}


return sign;


}
void pri()
{
int row,line;
for(row=0;row<9;row++)
{  printf("\n\n\t\t");
  for(line=0;line<9;line++)
  printf("%4d",shudu[row][line]);
 }
}

