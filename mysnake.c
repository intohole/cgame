#include "stdio.h"
#include "graphics.h"
#define SLEFT  0
#define SRIGHT 1
#define SUP    2
#define SDOWN  3
#define UP   0x4800
#define DOWN  0x5000
#define LEFT   0x4b00
#define RIGHT 0x4d00
#define ESC   0x11b
#define BS    0x3920
#define MAXBODY 100
typedef struct FOOD
{
int x;
int y;
int sign;
}fo;
struct SNAKE
{
int x[MAXBODY];
int y[MAXBODY];
int d_rc;
int n;
struct SNAKE *next;
}snake;
/******************************************************/
void init(int color);  /* 初始化图形界面 */
void foodxy(struct SNAKE *snake,fo *fd,int max,int min);   /* 设置食物 坐标 */
int eatefood(fo *fd,struct SNAKE *snake);;
void setfood(struct SNAKE *snake,fo *fd);  /* 检测食物存在 sign 0 无 生成食物 1 有  重画食物  */
int cgdirc(struct SNAKE *snake,int key); /* 方向键 控制蛇头方向 */
void initsnake(struct SNAKE *snake);
void drawbody(struct SNAKE *snake);
void movebody(struct SNAKE *snake);
void headmove(struct SNAKE *snake);
void addbody(struct SNAKE *snake);
int judgedeath(struct SNAKE *snake);
void pri_mes(int score);
char *numtostr(int num);

/******************************************************/
void main()
{
 fo fd;
 int key;
 int death=0;
 int score=0;

 srand();
 fd.sign=0;
 snake.n=3;
 init(BLACK);
 initsnake(&snake);
 /*size=imagesize(380,10,470,80);
 getimage(380,10,470,80,buf);
   */
 drawbody(&snake);
 while(!death)
 {
 while(!kbhit())
 {
 pri_mes(score);
 setfood(&snake,&fd);
 movebody(&snake);
 death=judgedeath(&snake);
 if(death)
 {
 break;
 }
 if(eatefood(&fd,&snake))
 {

 addbody(&snake);
 score+=10;
 }
 else
 {


 }

delay(1200000000);
 }
 key=bioskey(0);
 cgdirc(&snake,key);
  }
  sleep(5);
  closegraph();
  getch();

}
/******************************************************/
void init(int color)
{
int drive,mode=VGAHI;
drive=VGA;
registerbgidriver(EGAVGA_driver);
initgraph(&drive,&mode,"");
setbkcolor(color);
setcolor(8);
rectangle(99,99,401,401);
setcolor(RED);
outtextxy(100,50,"Your_Score");

}
void foodxy(struct SNAKE *snake,fo *fd,int max,int min)
{
int row;
int sign=1;
while(sign)
{
fd->x=rand()%(max-min+1)+min;
fd->y=rand()%(max-min+1)+min;
fd->x=(fd->x/10)*10;
fd->y=(fd->y/10)*10;
sign=0;
for(row=0;row<=snake->n;row++)
{
if(fd->x==snake->x[row]&&fd->y==snake->y[row])
{
sign=1;
break;

}

}

 }
}

int eatefood(fo *fd,struct SNAKE *snake)
{
if(fd->x==snake->x[0]&&fd->y==snake->y[0])
   {
        fd->sign=0;
        return 1;

   }
   else
   {

   return 0;
   }

}
void setfood(struct SNAKE *snake,fo *fd)
{
if(fd->sign==0)
{
 foodxy(snake,fd,400,100);
 setcolor(RED);
 rectangle(fd->x,fd->y,fd->x+10,fd->y+10);
 fd->sign=1;
}
else
{
  setcolor(RED);
 rectangle(fd->x,fd->y,fd->x+10,fd->y+10);

}


}




int cgdirc(struct SNAKE *snake,int key)
{
  switch(key)
  {
  case LEFT:
  if(snake->d_rc!=SRIGHT)
 {
  snake->d_rc=SLEFT;
  }
  break;
  case RIGHT:
  if(snake->d_rc!=SLEFT)
  {
  snake->d_rc=SRIGHT;
  }
  break;

  case UP:
  if(snake->d_rc!=SDOWN)
  {
  snake->d_rc=SUP;
  } break;
  case DOWN:
  if(snake->d_rc!=SUP)
  {
  snake->d_rc=SDOWN;
  }
  break;
  case ESC:exit(1);break;
  case BS:getch();break;

  default:break;


  }
   return 1;
}


void initsnake(struct SNAKE *snake)
{
snake->x[0]=200;
snake->y[0]=200;
snake->y[1]=200;
snake->x[1]=190;
snake->x[2]=180;
snake->y[2]=200;
snake->d_rc=SRIGHT;
snake->n=3;

}
void drawbody(struct SNAKE *snake)
{
int row;
setcolor(BROWN);
rectangle(snake->x[0],snake->y[0],snake->x[0]+10,snake->y[0]+10);
for(row=1;row<snake->n;row++)
{
setcolor(BLUE);
rectangle(snake->x[row],snake->y[row],snake->x[row]+10,snake->y[row]+10);


}


}
void movebody(struct SNAKE *snake)
{
int row;
setcolor(getbkcolor());
rectangle(snake->x[snake->n-1],snake->y[snake->n-1],snake->x[snake->n-1]+10,snake->y[snake->n-1]+10);
setcolor(BLUE);
rectangle(snake->x[snake->n-2],snake->y[snake->n-2],snake->x[snake->n-2]+10,snake->y[snake->n-2]+10);
rectangle(snake->x[0],snake->y[0],snake->x[0]+10,snake->y[0]+10);
for(row=snake->n;row>0;row--)
{
snake->x[row]=snake->x[row-1];
snake->y[row]=snake->y[row-1];

}
headmove(snake);
setcolor(BROWN);
rectangle(snake->x[0],snake->y[0],snake->x[0]+10,snake->y[0]+10);
}

void headmove(struct SNAKE *snake)
{
switch(snake->d_rc)
{
case SRIGHT:snake->x[0]+=10;break;
case SLEFT:snake->x[0]-=10;break;
case SUP:snake->y[0]-=10;break;
case SDOWN:snake->y[0]+=10;break;
default:break;
}


}

void addbody(struct SNAKE *snake)
{
setcolor(getbkcolor());
 rectangle(snake->x[snake->n],snake->y[snake->n],snake->x[snake->n]+10,snake->y[snake->n]+10);

 snake->n+=1;

}
int judgedeath(struct SNAKE *snake)
{   int row,line;

if(snake->x[0]<100||snake->x[0]==400||snake->y[0]<100||snake->y[0]==400)
{

return 1;

}
else
{
   for(row=0;row<snake->n-1;row++)
     for(line=row+1;line<snake->n&&row!=line;line++)
        {
        if(snake->x[row]==snake->x[line]&&snake->y[row]==snake->y[line])
           {
           return 1;
           }
        }
  return 0;
}

}
void pri_mes(int score)
{
char str[12];
itoa(score,str,10);

setfillstyle(EMPTY_FILL,WHITE);
bar(200,50,300,80);

setcolor(RED);
outtextxy(200,50,str);

}

char *numtostr(int num)
{
char *str;
int tmp;
int row=0;
str=(char *)malloc(sizeof(char)*12);
if(num!=0)
{
while(num)
{
tmp=num%10;
*(str+row)=tmp+48;
num/=10;
row++;

}
*(str+row)='\0';
}
else
{
*(str)='0';
*(str+1)='\0';

}

return str;
}
/******************************************************/
