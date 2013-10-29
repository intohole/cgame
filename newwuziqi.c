 #include "graphics.h"
#include "stdio.h"
#include "dos.h"
#define UP   0x4800
#define DOWN  0x5000
#define LEFT   0x4b00
#define RIGHT 0x4d00
#define ESC   0x11b
#define BKCOLOR WHITE
#define BR    BKCOLOR
#define MR    BLUE
#define BS    0x3920


int who=1;/*

1 代表黑棋
2 代表 白棋
*/
int win=0;

unsigned char chess[15][15]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
unsigned char computer[15][15][4]={0};
unsigned char player[15][15][4]={0};

typedef struct MOVECHESS
{
 int row;
 int line;
}mc;

void drawceboard(int color);
void init(int color);

void movechess(mc *pmc,int color);

void presskey(int key,mc *pmc);
void drawchess(mc *pmc,int color);
int judge(mc *pmc,int whochess);


/*
五子棋静态评估函数
*/
int cross(int row,int line,int whochess);
int stand(int row,int line,int whochess);
int rslant(int row,int line,int whochess);
int lslant(int row,int line,int whochess);
int rechesstype(int mychess,int zero,int lz,int rz);

int getpoint(int cross,int stand,int lslant,int rslant);


int compuer(mc *pmc);
int plusnum(int num);
void drawturn(int whochess);
/*

返回 当前五子棋预估局面
*/
int getcount(int num[2]);
void wingame();
int main(){
mc pmc;
int key;

init(WHITE);
drawceboard(RED);
pmc.row=7;
pmc.line=7;
drawturn(who);
   movechess(&pmc,BR);
    pmc.row=7;
    pmc.line=7;
    chess[7][7]=1;
    drawchess(&pmc,who+3);
    movechess(&pmc,MR);
    who=2;
while(1)
{
while(!kbhit())
{
if(who==1)
{

compuer(&pmc);
judge(&pmc,1);
wingame();
}



}
key=bioskey(0);
presskey(key,&pmc);
judge(&pmc,1);
wingame();




}
closegraph();




}
void init(int color)
{
int drive,mode;

drive=DETECT;
registerbgidriver(EGAVGA_driver);
initgraph(&drive,&mode,"");
setbkcolor(color);

}



void drawceboard(int color){

int row=100;
setlinestyle(0,0,1);
setcolor(color);
for(;row<=380;row=row+20)
{
line(100,row,380,row);
line(row,100,row,380);


}

}

void movechess(mc *pmc,int color)
{
int c_x,c_y;
setcolor(color);
c_x=pmc->line*20+100;
c_y=pmc->row*20+100;
/*
 | |
-   -
-   -
 | |
*/
line(c_x-4,c_y-9,c_x-4,c_y-4);/*  |  */
line(c_x-4,c_y-4,c_x-9,c_y-4);/* -  */
line(c_x+4,c_y-4,c_x+9,c_y-4);/*   右上 - */
line(c_x+4,c_y-4,c_x+4,c_y-9);/*    右上 |*/
line(c_x-4,c_y+4,c_x-9,c_y+4);/*   左下 -   */
line(c_x-4,c_y+4,c_x-4,c_y+9);/*   左下  |     */
line(c_x+4,c_y+4,c_x+9,c_y+4);/*   右下 -    */
line(c_x+4,c_y+4,c_x+4,c_y+9);/*    右下 |     */
}

void presskey(int key,mc *pmc)
{
 mc tmp;

 tmp.row=pmc->row;
 tmp.line=pmc->line;

  switch(key)
  {
  case LEFT:
  if(pmc->line>0)
  {
  movechess(pmc,BR);
  pmc->line-=1;
  movechess(pmc,MR);
  if(chess[tmp.row][tmp.line]!=0)
  {
  drawchess(&tmp,chess[tmp.row][tmp.line]+3);
   }
  }
  break;
  case RIGHT:
  if(pmc->line<14)
  {
   movechess(pmc,BR);
  pmc->line+=1;
  movechess(pmc,MR);
    if(chess[tmp.row][tmp.line]!=0)
  {
  drawchess(&tmp,chess[tmp.row][tmp.line]+3);
   }

  }
  break;

  case UP:
  if(pmc->row>0)
  {
    movechess(pmc,BR);
  pmc->row-=1;
  movechess(pmc,MR);
    if(chess[tmp.row][tmp.line]!=0)
  {
  drawchess(&tmp,chess[tmp.row][tmp.line]+3);
   }

  }
  break;
  case DOWN:
     if(pmc->row<14)
     {
     movechess(pmc,BR);
  pmc->row+=1;
  movechess(pmc,MR);
      if(chess[tmp.row][tmp.line]!=0)
  {
  drawchess(&tmp,chess[tmp.row][tmp.line]+3);
   }

     }
  break;
  case BS:
         if(chess[pmc->row][pmc->line]==0&&who==2)
         {
        drawchess(pmc,who+3);
        chess[pmc->row][pmc->line]=who;
        judge(pmc,who);



        who=3-who;
        drawturn(who);
         }
           break;

  case ESC:exit(1);break;


  default:break;


  }


}
void drawchess(mc *pmc,int color)
{
 int c_x,c_y;

c_x=pmc->line*20+100;
c_y=pmc->row*20+100;
setcolor(color);
setfillstyle(SOLID_FILL,color);
pieslice(c_x,c_y,0,360,6);

}
int judge(mc *pmc,int whochess)
{
int end,start;
int lp;
int count=0;
int rp;/*  检测斜向的时候  */

                 /*

                 横向判断

                 */
lp=pmc->line-4;
while(lp<=(pmc->line+4))
{
if((lp>=0&&lp<15))
{
if(chess[pmc->row][lp]==whochess)
{
count+=1;

if(count==5)
{
win=whochess;
return whochess;;
}
 }
}
else if(chess[pmc->row][lp]!=whochess&&count>0)
{

count=0;


}

lp++;
}
lp=0;
count=0;
  lp=pmc->row-4;
while(lp<=(pmc->row+4))
{
if((lp>=0&&lp<15))
{
if(chess[lp][pmc->line]==whochess)
{
count+=1;

if(count==5)
{
win=whochess;
return whochess;;
}
 }
}
else if(chess[lp][pmc->line]!=whochess&&count>0)
{

count=0;
}

lp++;
}
lp=0;
rp=0;
count=0;
lp=pmc->line-4;
rp=pmc->row-4;
while(lp<=(pmc->line+4))
{
if((lp>=0&&lp<15)&&(rp>=0&&rp<15))
{
if(chess[rp][lp]==whochess)
{
count+=1;

if(count==5)
{
win=whochess;
return whochess;;
}
 }
}
else if(chess[rp][lp]!=whochess&&count>0)
{

count=0;


}

lp++;
rp++;
}
lp=0;
rp=0;
count=0;
lp=pmc->line-4;
rp=pmc->row+4;
while(lp<=(pmc->line+4))
{
if((lp>=0&&lp<15)&&(rp>=0&&rp<15))
{
if(chess[rp][lp]==whochess)
{
count+=1;

if(count==5)
{
win=whochess;
return whochess;;
}
 }
}
else if(chess[rp][lp]!=whochess&&count>0)
{

count=0;


}

lp++;
rp--;
}

}


void drawturn(int whochess)
{
setfillstyle(SOLID_FILL,whochess+3);
outtextxy(0,10,"Turn:");
bar(40,10,60,30);


}

int cross(int row,int line,int whochess)
{
 int mychess=0;
 int lp,rp;
 int zero=0;
 int lz=0,rz=0;/* lz 为 最左边为 0 rz 为 最右边为0 */

  for(lp=line-1;lp>=0&&chess[row][lp]==whochess;lp--);

 for(rp=line+1;rp<15&&chess[row][rp]==whochess;rp++);
 mychess=rp-lp-1; /* 01110   rp=5 lp=1  */
 if(chess[row][lp]==0)
 {
 lz=1;

 }
 if(chess[row][rp]==0)
 {


 rz=1;/*
         0为 有阻碍
         1 为无阻碍
  */

 }
 while(chess[row][lp]==0&&lp>=0)
 {

 zero++;
 lp-=1;
}
while(chess[row][rp]==0&&rp<15)
{
zero++;
rp++;


}

return rechesstype(mychess,zero,lz,rz);



}
int stand(int row,int line,int whochess)
{
 int mychess=0;
 int lp,rp;
 int zero=0;
 int lz=0,rz=0;/* lz 为 最左边为 0 rz 为 最右边为0 */

  for(lp=row-1;lp>=0&&chess[lp][line]==whochess;lp--);

 for(rp=row+1;rp<15&&chess[rp][line]==whochess;rp++);
 mychess=rp-lp-1; /* 01110   rp=5 lp=1  */
 if(chess[lp][line]==0)
 {
 lz=1;

 }
 if(chess[rp][line]==0)
 {


 rz=1;/*
         0为 有阻碍
         1 为无阻碍
  */

 }
 while(chess[row][lp]==0&&lp>=0)
 {

 zero++;
 lp-=1;
}
while(chess[row][rp]==0&&rp<15)
{
zero++;
rp++;


}

return rechesstype(mychess,zero,lz,rz);
}
int rslant(int row,int line,int whochess)
{    /*
          右斜线判断但行棋的类型
     */
  int mychess=0;
 int lp,rp;
 int zero=0;
 int lz=0,rz=0;
int s_rp,s_lp;
 for(s_rp=row-1,s_lp=line+1;(s_lp>=0&&s_rp>=0)&&chess[s_rp][s_lp]==whochess;s_lp++,s_rp--);


for(rp=row,lp=line;(lp<15&&rp<15)&&chess[rp][lp]==whochess;lp--,rp++);
  mychess=rp-s_rp-1;
  if(chess[s_rp][s_lp]==0)
 {
 lz=1;

 }
 if(chess[rp][lp]==0)
 {


 rz=1;/*
         0为 有阻碍
         1 为无阻碍
  */

 }
 while(chess[s_rp][s_lp]==0&&(lp>=0&&rp>=0))
 {     /*
          举例
          201102 这个判断为活二 但 无法凑足五子空间
          所以这个为无效

     */

 zero++;
 s_rp-=1;
 s_lp+=1;

}
while(chess[rp][lp]==0&&(rp<15&&lp<15))
{
zero++;
rp++;
lp--;

}
 return rechesstype(mychess,zero,lz,rz);



}
int lslant(int row,int line,int whochess)
{

 int mychess=0;
 int lp,rp;
 int zero=0;
 int lz=0,rz=0;
int s_rp,s_lp;
 for(s_rp=row-1,s_lp=line-1;(s_lp>=0&&s_rp>=0)&&chess[s_rp][s_lp]==whochess;s_lp--,s_rp--);


for(rp=row,lp=line;(lp<15&&rp<15)&&chess[rp][lp]==whochess;lp++,rp++);
  mychess=rp-s_rp-1;
  if(chess[s_rp][s_lp]==0)
 {
 lz=1;

 }
 if(chess[rp][lp]==0)
 {


 rz=1;/*
         0为 有阻碍
         1 为无阻碍
  */

 }
 while(chess[s_rp][s_lp]==0&&(lp>=0&&rp>=0))
 {

 zero++;
 s_rp-=1;
 s_lp-=1;

}
while(chess[rp][lp]==0&&(rp<15&&lp<15))
{
zero++;
rp++;
lp++;

}
 return rechesstype(mychess,zero,lz,rz);



}
int rechesstype(int mychess,int zero,int lz,int rz)
{
if((mychess+zero)<5)
{
return 0;

}

else
{

return mychess+(rz+lz)*10;
/*
1 为单活
2 为双活
*/
 /*  个位 为 棋子数目 十位 wei 双活 或者单活 */



}



}




int compuer(mc *pmc)
{
int row,line;
int max=-10000;

int pcomputer=0;
int player=0;
int point,mpoint;
int tmprow,tmpline;
int minrow,minline,maxrow,maxline;
int pcross,pstand,plslant,prslant;
for(row=0;row<15;row++)
{
  for(line=0;line<15;line++)

  if(chess[row][line]==0)
  {
   chess[row][line]=1;                                                                             /* 30 为电脑进攻奖励分数 越大 进攻的强度越高 但后果是很严重的 */
   pcomputer=getpoint(cross(row,line,1),stand(row,line,1),lslant(row,line,1),rslant(row,line,1))+30;


   chess[row][line]=2;

    player=getpoint(cross(row,line,2),stand(row,line,2),lslant(row,line,2),rslant(row,line,2));
    point=pcomputer-player;
    point=plusnum(point);
    if(point>max)
    {
    max=point;
    tmprow=row;
    tmpline=line;

    }


   chess[row][line]=0;
      }



           }


    movechess(pmc,BR);
    pmc->row=tmprow;
    pmc->line=tmpline;
    chess[tmprow][tmpline]=1;

    drawchess(pmc,who+3);
    who=3-who;
    movechess(pmc,MR);

    return 0;
}
int getpoint(int cross,int stand,int lslant,int rslant)
{   /*

为五子棋静态评估函数

*/
  int gp=0;
  if(cross==15||cross==25||stand==15||stand==25||lslant==15||lslant==25||rslant==15||rslant==25)
  {
     /*
        如果为 五子 不管是否是 活死 3000 是为了怕和其他不必要的棋竞争点数
     */
  gp=gp+3000;
  }
 else if(cross==24||stand==24||lslant==24||rslant==24)
 {
  /*
       2 代表 活 活四
     */

  gp=gp+1500;

 }
 else if((cross==14&&(stand==14||lslant==14||rslant==14))||(stand==14&&(cross==14||lslant==14||rslant==14))||(rslant==14&&(stand==14||lslant==14||cross==14))||(rslant==14&&(stand==14||lslant==14||cross==14)))
 {
            /*
       双死四
     */
 gp=gp+1200;


 }
 else if((cross==23&&(stand==14||lslant==14||rslant==14))||(stand==23&&(cross==14||lslant==14||rslant==14))||(rslant==23&&(stand==14||lslant==14||cross==14))||(rslant==23&&(stand==14||lslant==14||cross==14)))
  {
         /*
     活三一死四
     */

  gp=gp+1200;


  }
  else if((cross==23&&(stand==23||lslant==23||rslant==23))||(stand==23&&(cross==23||lslant==23||rslant==23))||(rslant==23&&(stand==23||lslant==23||cross==23))||(rslant==23&&(stand==23||lslant==23||cross==23)))
  {
  gp=gp+1050;
  /*
       双活三
     */

  }
  else if((cross==23&&(stand==13||lslant==13||rslant==13))||(stand==23&&(cross==13||lslant==13||rslant==13))||(rslant==23&&(stand==13||lslant==13||cross==13))||(rslant==23&&(stand==13||lslant==13||cross==13)))
  {
  /*   活三死三

     */
    gp=gp+900;

  }
  else if(cross==14||stand==14||lslant==14||rslant==14)
   {
   /*
       死四
     */
   gp=gp+700;

   }
   else if(cross==23||stand==23||lslant==23||rslant==23)
   {
           /*
       1活三
     */
     gp=gp+500;

   }
   else if(cross==22||stand==22||lslant==22||rslant==22)
   {
   /*
       活二
     */
   gp=gp+150;
   }
   else if(cross==13||stand==13||lslant==13||rslant==13)
   {
           /*
       死三
     */
   gp=gp+230;
   }
   else if(cross==12||stand==12||lslant==12||rslant==12)
   {      /*
       死二
     */

   gp=gp+90;
   }
   else if(cross==11||stand==11||rslant==11||lslant==11)
   {

   gp=gp+0;
   }
    else if(cross==21||stand==21||rslant==21||lslant==21)
   {
   /*

     */
   gp=gp+0;
   }

   return gp;

}
int plusnum(int num)
{   /*
       返回绝对值
     */
if(num<0)
{

return -num;
}
else
{
return num;

}



}
void wingame()
{
             /*
       判断win值
       1 电脑获胜
       2 游戏玩家获胜
     */
switch(win)
{
  case 0:break;
  case 1:
  sleep(6);
     cleardevice();
     setbkcolor(RED);
     setcolor(BLUE);
     setfillstyle(SOLID_FILL,YELLOW);
     bar(100,100,539,250);
     settextstyle(0,0,3);
     outtextxy(130,120,"COMPUTER|WIN|GAME");
      sleep(5);
      closegraph();
      exit(1);
  break;
  case 2:
  sleep(6);
     cleardevice();
     setbkcolor(RED);
     setcolor(BLUE);
     setfillstyle(SOLID_FILL,YELLOW);
     bar(100,100,539,250);
     settextstyle(0,0,3);
     outtextxy(130,120,"PLAYER|WIN|GAME");
      getch();
      closegraph();
      exit(1);   break;
      default:break;
 

}



}
