#include "stdio.h"
#include<graphics.h>
#include<math.h>
#include "dos.h"
#include "time.h"
#define pi 3.1415926
typedef struct mouse
{
  int x;
  int y;


}mu;
/***************************************************************************/
void init(int color);
void drawclock(int cir_x,int cir_y,int r,int color);
void drawhand(int cir_x,int cir_y,int color,int sec_r,int cg,int index);
void drawhour(int cir_x,int cir_y,int color,int sec_r,int hour,int min);
int re_x(int cir_x,int hand,int cg,int index);
int re_y(int cir_y,int hand,int cg,int index);
int move(int *cir_x,int *cir_y,int *dx,int *dy,int r);
int juedui(int num);
void  initmouse();
int mousemove(mu *mouse);
/****************************************************************************/

void main()
{

 struct time t,tmp;
 int sec=0,hour=0,min=0;
 int dx=10,dy=10;
 int cir_x,cir_y,r=100;
 mu mouse,ori;
 init(WHITE);
 srand(time(NULL));
 cir_x=rand()%400+100;
 cir_y=rand()%300+100;
 initmouse();
 mousemove(&ori);
 while(!kbhit())
 {
   mousemove(&mouse);
   if(!((mouse.x>(ori.x-10)&&mouse.x<=(ori.x+10))||(mouse.y<(ori.y-10)||mouse.y<=(ori.y+10))))
   {

     break;

   }
   drawclock(cir_x,cir_y,r,WHITE);
   drawhand(cir_x,cir_y,WHITE,85,t.ti_sec,6);
   drawhand(cir_x,cir_y,WHITE,60,t.ti_min,6);
   drawhour(cir_x,cir_y,WHITE,35,t.ti_hour,t.ti_min);
   gettime(&t);
   move(&cir_x,&cir_y,&dx,&dy,r);
   drawclock(cir_x,cir_y,r,rand()%15+1);
   drawhand(cir_x,cir_y,BLUE,85,t.ti_sec,6);
   drawhand(cir_x,cir_y,MAGENTA,60,t.ti_min,6);
   drawhour(cir_x,cir_y,RED,35,t.ti_hour,t.ti_min);
 /* drawhand(300,200,rand()%15+1,45,hour,30); */

   delay(40000000000000);

 }


}
void init(int color)
{
 int drive,mode;
 drive=DETECT;
 registerbgidriver(EGAVGA_driver);
 initgraph(&drive,&mode,"");
 setbkcolor(color);
}

char *str[]={"12","1","2","3","4","5","6","7","8","9","10","11"};
void drawclock(int cir_x,int cir_y,int r,int color)
{
 int row=0;
 int l;
 int x,y,e_x,e_y;

 setcolor(color);
 circle(cir_x,cir_y,r);
 for(row=0;row<60;row++)
 {
   if(row%5!=0)
   {
     l=6;
   }
   else
   {
     l=14;
   }
   x=r*cos(row*6*pi/180)+cir_x;
   y=r*sin(row*6*pi/180)+cir_y;
   e_x=(r-l)*cos(row*6*pi/180)+cir_x;
   e_y=(r-l)*sin(row*6*pi/180)+cir_y;
   line(x,y,e_x,e_y);

 }
 for(row=0;row<12;row++)
 {
   if(row<6)
   {
     x=re_x(cir_x,r+8,row,30);
     y=re_y(cir_y,r+8,row,30);
   }
   else
   {
    x=re_x(cir_x,r+12,row,30);
    y=re_y(cir_y,r+12,row,30);
  }
  outtextxy(x,y,str[row]);
}
}
void drawhand(int cir_x,int cir_y,int color,int sec_r,int cg,int index)
{
 int x,y;
 setcolor(color);

 x=re_x(cir_x,sec_r,cg,index);
 y=re_y(cir_y,sec_r,cg,index);

 line(cir_x,cir_y,x,y);


}
void drawhour(int cir_x,int cir_y,int color,int sec_r,int hour,int min)
{
  int x,y;
  setcolor(color);
  if(min!=0)
  {
    x=35*cos(hour*30*pi/180+((double)min/(double)60)*30*pi/180-pi/2)+cir_x;
    y=35*sin(hour*30*pi/180+((double)min/(double)60)*30*pi/180-pi/2)+cir_y;
    line(cir_x,cir_y,x,y);
  }
  else
  {
    drawhand(cir_x,cir_y,RED,35,hour,30);
  }

}

int re_x(int cir_x,int hand,int cg,int index)
{
 return hand*cos(cg*index*pi/180-pi/2)+cir_x;
}



int re_y(int cir_y,int hand,int cg,int index)
{
 return hand*sin(cg*index*pi/180-pi/2)+cir_y;

}

int move(int *cir_x,int *cir_y,int *dx,int *dy,int r)
{
  if(*cir_x<=(10+r))
  {
   *dx=juedui(*dx);
 }
 if(*cir_x>=(640-r-10))
 {

  *dx=-juedui(*dx);
}
if(*cir_y<=(r+10))
{
 *dy=juedui(*dy);
}
if(*cir_y>=(440-r-10))
{

  *dy=-juedui(*dy);
}
*cir_x+=*dx;
*cir_y+=*dy;
return ;

}
int juedui(int num)
{
  if(num>=0)
  {
    return num;

  }
  else
  {
    return -num;

  }
}
void  initmouse()
{
  _AX=0x00;
  geninterrupt(0x33);


}
int mousemove(mu *mouse)
{
  _AX=0x03;
  geninterrupt(0x33);
  mouse->x=_CX;
  mouse->y=_DX;

}
