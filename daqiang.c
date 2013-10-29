#include "stdio.h"
#include "time.h"
#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4b00
#define RIGHT 0x4d00
#define ESC 0x11b
#define BS  0x3920
/*
*  1 代表   飞机
*  0 代表   空
*  2        子弹
*  4 代表   射手
*
*/
typedef struct GUN
{
int gun_r;/* 子弹的 坐标 */
struct GUN *next;
struct GUN *last;
}gun;

void insertgun(gun *head,int gunrow,int num[])
{
    gun *tmp;
    gun *newgun;
    tmp=head;

    while(tmp->next!=NULL)
    {

    tmp=tmp->next;


    }
    newgun=(gun *)malloc(sizeof(struct GUN));
    tmp->next=newgun;
    newgun->next=NULL;
    newgun->last=tmp;
    newgun->gun_r=gunrow;
    *(num+gunrow)=2;
}
void create(gun *head)
{
  head=(gun *)malloc(sizeof(struct GUN));
  head->next=NULL;
  head->last=NULL;

}
void delte(gun *head,int delrow)
{
gun *tmp;
tmp=head->next;
while(tmp!=NULL)
{
if(tmp->gun_r==delrow)
  {
  /*
  找到 删除的
  */
  if(tmp->next==NULL)
  {
  tmp->last->next=NULL;


  }
  else
  {
  tmp->last->next=tmp->next;
  tmp->next->last=tmp->last;

  }

    break;
  }
  else
  {
 tmp=tmp->next;
  }
}

   free(tmp);
}
void gun_move(gun *head,int num[],int n)
{
 gun *tmp;
 gun *l;
 tmp=head->next;
 /* 指向上一个删除的指针  */
 while(tmp!=NULL)
  {

      if((tmp->gun_r-n)<0)
      {


           if(tmp->next==NULL)
           {
           tmp->last->next=NULL;

           }
           else
           {
           tmp->last->next=tmp->next;
           tmp->next->last=tmp->last;

            }
            *(num+tmp->gun_r-n)=0;
            *(num+tmp->gun_r)=0;

      }
      else
      {



      if(*(num+tmp->gun_r-n)==1)
      {
      *(num+tmp->gun_r)=0;
      *(num+tmp->gun_r-n)=0;
      tmp->last->next=tmp->next;


      }
      else
      {

       *(num+tmp->gun_r)=0;

       *(num+tmp->gun_r-n)=2;
       tmp->gun_r=tmp->gun_r-n;

      }

      }


      tmp=tmp->next;

  }



}



void init(int num[],int n)
{
   int row=0;
   for(;row<n*n;row++)
  {
    *(num+row)=0;
   }

}
int getnum(int num[],int n)
{

num=(int *)malloc(sizeof(int)*(n*n));
if(num==NULL)
{
    return 0;

}
else
{

return 1;
}

}
int rand_3(int max,int min)
{
return rand()%(max-min+1)+min;

}
int cg_fir(int num[],int n)
{
   int row=0;
   int time_1=0;
while(time_1<=rand_3((n/3-1),1))
  {
    row=rand_3(n,0);
    if(*(num+row)!=1)
    {
    *(num+row)=1;
    time_1++;
   }


  }
  for(row=0;row<n;row++)
  {
  if(*(num+row)!=1)
  {
     *(num+row)=0;

         }
  }

}
void move_(int num[],int n,int m_row,gun *head)
{
int row=0,time_1=0;



 for(row=(n*n-1);row>=0;row--)
   {

   if(*(num+row)==2&&*(num+row-n)==1)
   {
          *(num+row)=0;
          *(num+row-n)=0;
          delte(head,row);
   }
   else if(*(num+row)==4&&*(num+row-n)==1)
     {

         printf("\n\n\t\tYou Are Lost!!!");
          getch();
          exit(1);
     }
     else if(*(num+row)==2||*(num+row)==4)
     {

     }
     else
    {
    *(num+row)=*(num+row-n);

     }
   /*

   if(row!=m_row)
      {

      if(*(num+row)!=2)
            {
            if(*(num+row-n)!=2)
            {


        *(num+row)=*(num+row-n);
            }
            else
            {
             if(*(num+row)==1)
             {
             *(num+row)=0;
             *(num+row-n)=0;
             delte(head,row);

             }


            }

       }

       }

      else
      {
      if(*(num+row-n)==1)
      {

      printf("\n\n\t\tYou Are Lost!!!");
          getch();
          exit(1);
      }

      }

     }
     */
     }
 cg_fir(num,n);
}
void pri_num(int num[],int n)
{

int row=0;
 textcolor(15);
 printf("\t\t");
 for(row=1;row<=n;row++)

 {
 printf("%6c",' ');

 }
for(row=0;row<n*n;row++)
  {
  if(row%n==0)
     {
     printf("\n\n  \t\t");

     }
     if(*(num+row)==0)
     {
  printf("%5c",' ');

      }
      else if(*(num+row)==1)
      {
      printf("%5c",'$');


      }
      else if(*(num+row)==2)
      {
      printf("%5c",'.');


      }
      else  if(*(num+row)==4)
      {

      printf("%5c",'o');


      }
      else
      {

      printf("%5c",' ');

      }
  }

}
void pe_judge()
{
 /*
if(*(num+*row)!=1)
                {
                *(num+save)=0;
                *(num+*row)=4;

                }
                else
                { */
                clrscr();
                printf("\n\n\n\t\t\tYOU ARE LOST!");
                   getch();
                   exit(1);

               /* }*/

}
int pe_move(int key,int *row,int *num,int n,gun *head)
{
int save=*row;
  switch(key)
  {
  case ESC:clrscr();
              printf("\n\n\n\n\t\t\tGOOD BYE!BROTHER!");
           getch();
           exit(0);

/* case UP:if((*row-n)>(n-1))
                  {
                 if(*(num+*row-n)!=1)
                 {
                 *(num+*row)=0;
                 *row=*row-n;
                 *(num+*row)=4;
                 }
                 else
                 {
                    pe_judge(row,num,*row+n);

                  }
                            }
                            break;
  */
               case BS:insertgun(head,*row-n,num);break;
                 case DOWN:if((*row+n)<n*n)
                  {

                  if(*(num+*row+n)!=1)
                 {
                 *(num+*row)=0;
                 *row=*row+n;
                 *(num+*row)=4;
                 }
                 else
                 {
                    pe_judge();

                  }
                            }
                            break;
                 case LEFT:if((*row-1)>=((*row/n)*n))
                       {if(*(num+*row-1)!=1)
                 {
                 *(num+*row)=0;
                 *row=*row-1;
                 *(num+*row)=4;
                 }
                 else
                 {
                    pe_judge();

                  }
                                }
                                 break;
            case RIGHT:if((*row+1)<=((*row/n+1)*n-1))
                       {
                         if(*(num+*row+1)!=1)
                 {
                 *(num+*row)=0;
                 *row=*row+1;
                 *(num+*row)=4;
                 }
                 else
                 {
                    pe_judge();

                  }
                                 }
                                 break;

                                 default :break;

               }




}
void main()
{
int *sp;
int sign=0;
int ti=0;
int key;
int n=9;
int m_row=n*(n-1)+n/2;
gun *head;/*  枪  子弹的 头指针  */
srand(time(NULL));
  sign=getnum(sp,n);

  init(sp,n);
  *(sp+m_row)=4;
  create(head);
  while(1)
  {
    while(!kbhit())
    {
    ti=0;
    clrscr();
    gun_move(head,sp,n);
    move_(sp,n,m_row,head);

    pri_num(sp,n);

    while(ti<15)
             {
                      delay(80000);
                  ti++;
             }



    }
    key=bioskey(0);
    pe_move(key,&m_row,sp,n,head);
  }

}
