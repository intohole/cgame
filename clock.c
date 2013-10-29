#include<graphics.h>
#include<math.h>
#include<dos.h>
#define pi 3.1415926
#define X(a,b,c) x=a*cos(b*c*pi/180-pi/2)+300;
#define Y(a,b,c) y=a*sin(b*c*pi/180-pi/2)+240;
#define d(a,b,c) X(a,b,c);Y(a,b,c);line(300,240,x,y)
void init()
{int i,l,x1,x2,y1,y2;
 setbkcolor(1);
 circle(300,240,200);
 circle(300,240,205);
 circle(300,240,5);
 for(i=0;i<60;i++)
 {if(i%5==0) l=15;
 else l=5;
 x1=200*cos(i*6*pi/180)+300;
  y1=200*sin(i*6*pi/180)+240;
   x2=(200-l)*cos(i*6*pi/180)+300;
  y2=(200-l)*sin(i*6*pi/180)+240;
  line(x1,y1,x2,y2);
  }
  }
  main()
  {
   int x,y;
   int gd=VGA,gm=2;
   unsigned char h,m,s;
   struct time t[1];
   initgraph(&gd,&gm,"d:\\tc");
   init();
   setwritemode(1);
   gettime(t);
   h=t[0].ti_hour;
   m=t[0].ti_min;
   s=t[0].ti_sec;
   setcolor(7);
   d(150,h,30);
   setcolor(14);
   d(170,m,6);
   setcolor(4);
   d(190,s,6);
   while(!kbhit())
   {while(t[0].ti_sec==s)
   gettime(t);
   sound(400);
   delay(70);
   sound(200);
   delay(30);
   nosound();
   setcolor(4);
   d(190,s,6);
   s=t[0].ti_sec;
   d(190,s,6);
   if (t[0].ti_min!=m)
   {
   setcolor(14);
   d(170,m,6);
   m=t[0].ti_min;
   d(170,m,6);
   }
   if (t[0].ti_hour!=h)
   { setcolor(7);
     d(150,h,30);
     h=t[0].ti_hour;
     d(150,h,30);
     sound(1000);
     delay(240);
     nosound();
     delay(140);
     sound(2000);
     delay(240);
     nosound();
   }
   }
   getch();
   closegraph();
   }
