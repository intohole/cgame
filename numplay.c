#include "stdio.h"
#include "time.h"
#include "graphics.h"
#define RAND_MAX 37627
#define TIMES  150
#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4b00
#define RIGHT 0x4d00
#define ESC 0x11b
void createnum(int (*nub)[3])


{
int row,line,times,r_row,r_line,r_0,l_0;
int temp;
int key;

for(times=0;times<TIMES;times++)
{
row=rand_3(4,2)-2;
line=rand_3(4,2)-2;
  r_row=rand_3(4,2)-2;
r_line=rand_3(4,2)-2;
   if((row!=r_row)||(line!=r_line))
   {

    temp=*(*(nub+row)+line);
       *(*(nub+row)+line)=*(*(nub+r_row)+r_line);
            *(*(nub+r_row)+r_line)=temp;


            }




                 }
for(row=0;row<3;row++)
   for(line=0;line<3;line++)
   {

     if(*(*(nub+row)+line)==0)
     {
     r_0=row;
     l_0=line;

     }


   }

temp=*(*(nub+2)+2);
*(*(nub+2)+2)=*(*(nub+r_0)+l_0);
*(*(nub+r_0)+l_0)=temp;
r_0=2;
l_0=2;
for(row=0;row<3;row++)
{printf("\n");
                        for(line=0;line<3;line++)
                  {
                          if(*(*(nub+row)+line)==0)
                        {
                        printf("        ");
                          continue;
                        }
                        printf("%5d   ",*(*(nub+row)+line));


                           }
 }
while(1)
{
  key=bioskey(0);
  switch(key)
  {
  case DOWN:if((r_0-1)>=0)
           {
              temp=*(*(nub+r_0-1)+l_0);
               *(*(nub+r_0-1)+l_0)=*(*(nub+r_0)+l_0);
                       *(*(nub+r_0)+l_0)=temp;
              r_0=r_0-1;
              clrscr();
             for(row=0;row<3;row++)
                 {printf("\n");
                        for(line=0;line<3;line++)
                  {
                         if(*(*(nub+row)+line)==0)
                        {
                        printf("        ");
                          continue;
                        }
                        printf("%5d   ",*(*(nub+row)+line));


                           }
                           }
 }
if(re_good(nub)==1)
 {
 printf("\n\n\t\tgood good !");
 exit(0);

 }
              break;
              case UP:if((r_0+1)<=2)
           {
              temp=*(*(nub+r_0+1)+l_0);
               *(*(nub+r_0+1)+l_0)=*(*(nub+r_0)+l_0);
                       *(*(nub+r_0)+l_0)=temp;
              r_0=r_0+1;
              clrscr();
             for(row=0;row<3;row++)
                 {printf("\n");
                        for(line=0;line<3;line++)
                  {
                        if(*(*(nub+row)+line)==0)
                        {
                        printf("        ");
                          continue;
                        }
                        printf("%5d   ",*(*(nub+row)+line));


                           }
                           }

 }
 if(re_good(nub)==1)
 {
 printf("\n\n\t\tgood good !");
 exit(0);

 }
              break;
           case LEFT:if((l_0+1)<=2)
           {
              temp=*(*(nub+r_0)+l_0+1);
               *(*(nub+r_0)+l_0+1)=*(*(nub+r_0)+l_0);
                       *(*(nub+r_0)+l_0)=temp;
              l_0=l_0+1;
              clrscr();
             for(row=0;row<3;row++)
                 {printf("\n");
                        for(line=0;line<3;line++)
                  {
                         if(*(*(nub+row)+line)==0)
                        {
                        printf("        ");
                          continue;
                        }
                        printf("%5d   ",*(*(nub+row)+line));


                           }
                           }
 }
            if(re_good(nub)==1)
 {
 printf("\n\n\t\tgood good !");
 exit(0);

 }
              break;
              case RIGHT:if((l_0-1)>=0)
           {
              temp=*(*(nub+r_0)+l_0-1);
               *(*(nub+r_0)+l_0-1)=*(*(nub+r_0)+l_0);
                       *(*(nub+r_0)+l_0)=temp;
              l_0=l_0-1;
              clrscr();
             for(row=0;row<3;row++)
                 {printf("\n");
                        for(line=0;line<3;line++)
                  {
                         if(*(*(nub+row)+line)==0)
                        {
                        printf("        ");
                          continue;
                        }
                        printf("%5d   ",*(*(nub+row)+line));


                           }
                           }
 }
 if(re_good(nub)==1)
 {
 printf("\n\n\t\tgood good !");
 exit(0);

 }
              break;
  case ESC:clrscr();
         printf("EXIT WINDOW");
         exit(0);





  }





}

}

int re_good(int (*nub)[3])
{    int n=1;
int row,line;
   int nc[3][3]={{1,2,3},{4,5,6},{7,8,0}};
 for(row=0;row<3;row++)
   for(line=0;line<3;line++)
   {

     if(*(*(nub+row)+line)==nc[row][line])
     {


     }
     else
         {

         return 0;
         }


   }
   return 1;




}

int rand_2(int max,int min)
{
 int te=max-min+2;

 return  ((int)(((double)rand()/(double)RAND_MAX)*te)+min);




}
 int rand_3(int max,int min)
 {

 return rand()%(max-min+1)+min;


 }

void main()
{
  int num[3][3]={{1,2,3},{4,5,6},{7,8,0}};
   int row,line;



  srand((unsigned)time(NULL));


createnum(num);
/* setbkcolor(WHITE);
 setcolor(GREEN);
 outtextxy(100,200,"");
*/

    getch();
}
