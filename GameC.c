  #include "stdio.h"
#include "graphics.h"
#include "time.h"
#define NUM 15
#define LMAX   20
#define GSPEED 10
#define USPEED 10
int lost=0;
int create=0;
int input=0;
struct  CHARCTER{
 int x;
 int y;
 int speed;
 char str[2];


}goal[NUM],gun[NUM];
void initGraph(int color);
void initGame(int width);
int rand_1(int max,int min);
void insertgoal(int level);
int find(char c);
void insertgun(char c,int row);
void showc(int x,int y,int color,char *str);
void deletec(int row);
void move(int color);
void past();
void hit();
char tohigh(char ch);
void drawshell(int startx,int starty,int wiedth ,int height,int color);
void main()
{
 char ch;
 int row;
 int times=1;
 srand(time(NULL));
 initGraph(WHITE);
 initGame(400);
 insertgoal(12);
 drawshell((getmaxx()-400)/2-1,49,(getmaxx()-400)/2+401,getmaxy()-101,GREEN);
 while(1)
 {
   while(!kbhit())
   {
     if((times=times%20)==0)
     {
       insertgoal(4);

     }
     move(RED);
     past();
     times++;
     delay(12000000000000);
   }
   ch=getch();
   if(ch==89)
   {
     closegraph();
     break;

   }
   ch=tohigh(ch);
   if(ch>='A'&&ch<='Z')
   {
    input++;
    row=find(ch);
    if(row==-1)
    {
      continue;
    }
    else
    {
      deletec(row);

    }


  }

}


}
void initGame(int width )
{
 int row;
 int startx=(getmaxx()-width)/2;
 for(row=0;row<NUM;row++)
 {
  goal[row].x=startx+width/NUM*row;


  goal[row].y=50;
  goal[row].speed=GSPEED;

  goal[row].str[0]=' ';
  goal[row].str[1]='\0';
     /*
      gun[row].x=starty+width/NUM*row;
        gun[row].y=getmaxy()-50;
          gun[row].speed=USPEED;
            gun[row].str[0]=' ';
          gun[row].str[1]='\0';

       */
        }


      }

      int rand_1(int max,int min)
      {

        return rand()%(max-min+1)+min;



      }

      void insertgoal(int level)
      {
       int row;
       for(row=0;row<NUM;row++)
         {   if(goal[row].str[0]==' ')
       {
        if(rand_1(LMAX,1)<=level)
        {
         goal[row].str[0]=rand_1('Z','A');
         goal[row].speed=rand_1(13,5);
         create++;
       }

     }
   }




 }

 int find(char c)
 {
  int row=-1;
  for(row=0;row<NUM;row++)
  {
    if(goal[row].str[0]==c)
    {

     return row;
   }

 }
 return row;
}

 /*
void insertgun(char c,int row)
  {

     gun[row].str[0]=c;
     gun[row].y=getmaxy()-50;
      }
   */
      void showc(int x,int y,int color,char *str)
      {
        setcolor(color);
        outtextxy(x,y,str);

      }
 /*
 void hit()
 {
 int row;
 for(row=0;row<NUM;row++)
   {
   if(goal[row].str[0]==gun[row].str[0])
     {
       if(goal[row].y==gun[row].y)
       {
         showc(goal[row].x,goal[row].y,goal[row].str);
         goal[row].y=50;
         goal[row].str[0]=' ';
         gun[row].y=getmaxy()-50;
         gun[row].str[0]=' ';

           }

       }

   }


 }
 */
 void deletec(int row)
 {
  setfillpattern(SOLID_FILL,BLUE);
  bar(goal[row].x,goal[row].y,goal[row].x+10,goal[row].y+10);
  delay(1200000);
  setfillpattern(SOLID_FILL,getbkcolor());
  bar(goal[row].x,goal[row].y,goal[row].x+10,goal[row].y+10);
  goal[row].str[0]=' ';
  goal[row].y=50;

}
void move(int color)
{
 int row;
 for(row=0;row<NUM;row++)
   { if(goal[row].str[0]!=' ')
 {
  setfillpattern(SOLID_FILL,getbkcolor());
  bar(goal[row].x,goal[row].y,goal[row].x+10,goal[row].y+10);
  goal[row].y+=goal[row].speed;
  showc(goal[row].x,goal[row].y,color,goal[row].str);

}

}


}

void initGraph(int color)
{
  int drive,mode;
  drive=DETECT;
  registerbgidriver(EGAVGA_driver);
  initgraph(&drive,&mode,"");
  setbkcolor(color);
}
void past()
{
 int row;
 for(row=0;row<NUM;row++)
 {
  if((goal[row].y+goal[row].speed)>=(getmaxy()-50))
  {
    deletec(row);
    printf("good!");
    lost+=1;
  }

}

}
char tohigh(char ch)
{
  ch=ch&223;
  return ch;

}

void drawshell(int startx,int starty,int width ,int height,int color)
{
  setcolor(GREEN);
  rectangle(startx,starty,startx+width,starty+height);
}
