#include "stdio.h"
#include "graphics.h"
#include "math.h"
#define g 9.8
#define PI 3.1415926
void init(int color);
void draws(double speed,double direction,double ox,double oy);
void main(){
init(WHITE);
draws(40,5,4,479);
getch();
draws(10,30,4,479);
getch();
closegraph();
}
void init(int color)
{
int drive,mode=VGAHI;
drive=DETECT;
registerbgidriver(EGAVGA_driver);
initgraph(&drive,&mode,"");
setbkcolor(color);

}

void draws(double speed,double direction,double ox,double oy)
{
double x_s,y_s;
double dy;
double t=0;
double tmp=t;
x_s=speed*cos(direction*PI/180.0);
y_s=speed*sin(direction*PI/180.0);
setcolor(RED);
moverel(0,479);
while((ox>=0&&ox<=639)&&(oy>=0&&oy<=479))
{

ox=x_s*t*10;


oy-=(y_s*t-(1.0/2.0)*g*t*t); /*
setfillstyle(SOLID_FILL,RED);
pieslice((int)ox,(int)oy,0,360,3);*/
lineto(ox,oy);
t=t+0.01;
delay(1200);
}




}

