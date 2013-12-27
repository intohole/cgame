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

1 ´ú±íºÚÆå
2 ´ú±í °×Æå
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
Îå×ÓÆå¾²Ì¬ÆÀ¹Àº¯Êý
*/
int cross(int row,int line,int whochess);
int stand(int row,int line,int whochess);
int rslant(int row,int line,int whochess);
int lslant(int row,int line,int whochess);
int rechesstype(int mychess,int zero,int lz,int rz);
int point1(int cross,int stand,int lslant,int rslant);

int compuer(mc *pmc);
void drawturn(int whochess);
/*

·µ»Ø µ±Ç°Îå×ÓÆåÔ¤¹À¾ÖÃæ
*/
int getcount(int num[2]);
int main(){
  mc pmc;
  int key;

  init(WHITE);
  drawceboard(RED);
  pmc.row=7;
  pmc.line=7;
  drawturn(who);
  while(1)
  {

    key=bioskey(0);
    presskey(key,&pmc);
    if(win!=0)
    {
      cleardevice();
      setbkcolor(BLACK);
      setfillstyle(SOLID_FILL,win+3);
      outtextxy(150,200,"Win this game is :");
      bar(350,200,450,250);
      getch();
      closegraph();
      exit(1);

    }




  }
  closegraph();




}
void init(int color)
{
  int drive,mode;

  drive=DETECT;
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
line(c_x+4,c_y-4,c_x+9,c_y-4);/*   ÓÒÉÏ - */
line(c_x+4,c_y-4,c_x+4,c_y-9);/*    ÓÒÉÏ |*/
line(c_x-4,c_y+4,c_x-9,c_y+4);/*   ×óÏÂ -   */
line(c_x-4,c_y+4,c_x-4,c_y+9);/*   ×óÏÂ  |     */
line(c_x+4,c_y+4,c_x+9,c_y+4);/*   ÓÒÏÂ -    */
line(c_x+4,c_y+4,c_x+4,c_y+9);/*    ÓÒÏÂ |     */
}

void presskey(int key,mc *pmc)
{
 mc tmp;
 int mychess=0;
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
if(chess[pmc->row][pmc->line]==0)
{
  drawchess(pmc,who+3);
  chess[pmc->row][pmc->line]=who;
  judge(pmc,who);
  mychess=rslant(pmc->row,pmc->line,who);


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
int rp;/*  ¼ì²âÐ±ÏòµÄÊ±ºò  */

                 /*

                 ºáÏòÅÐ¶Ï

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
 int lz=0,rz=0;/* lz Îª ×î×ó±ßÎª 0 rz Îª ×îÓÒ±ßÎª0 */

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
         0Îª ÓÐ×è°­
         1 ÎªÎÞ×è°­
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
 int lz=0,rz=0;/* lz Îª ×î×ó±ßÎª 0 rz Îª ×îÓÒ±ßÎª0 */

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
         0Îª ÓÐ×è°­
         1 ÎªÎÞ×è°­
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
    {
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
         0Îª ÓÐ×è°­
         1 ÎªÎÞ×è°­
  */

       }
       while(chess[s_rp][s_lp]==0&&(lp>=0&&rp>=0))
       {

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
         0Îª ÓÐ×è°­
         1 ÎªÎÞ×è°­
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
1 Îªµ¥»î
2 ÎªË«»î
*/
 /*  ¸öÎ» Îª Æå×ÓÊýÄ¿ Ê®Î» wei Ë«»î »òÕßµ¥»î */



}



}
int point1(int cross,int stand,int lslant,int rslant)
{
 int gpoint=0;
 if((cross=25||cross==15)||(stand==25||stand==15)||(lslant==25||lslant==15)||(rslant==15||rslant==25))
 {

   gpoint+=1000;

 }
 else if(cross==24||stand==24||lslant==24||rslant==24)
 {


  gpoint+=90;

}
else if((cross==14&&(stand==14||lslant==14||rslant==14))||(stand==14&&(cross==14||lslant==14||rslant==14))||(rslant==14&&(stand==14||lslant==14||cross==14))||(rslant==14&&(stand==14||lslant==14||cross==14)))
{

 gpoint+=90;


}
else if((cross==23&&(stand==14||lslant==14||rslant==14))||(stand==23&&(cross==14||lslant==14||rslant==14))||(rslant==23&&(stand==14||lslant==14||cross==14))||(rslant==23&&(stand==14||lslant==14||cross==14)))
{

  gpoint+=90;


}
else if((cross==23&&(stand==23||lslant==23||rslant==23))||(stand==23&&(cross==23||lslant==23||rslant==23))||(rslant==23&&(stand==23||lslant==23||cross==23))||(rslant==23&&(stand==23||lslant==23||cross==23)))
{
  gpoint=80;

}
else if((cross==23&&(stand==13||lslant==13||rslant==13))||(stand==23&&(cross==13||lslant==13||rslant==13))||(rslant==23&&(stand==13||lslant==13||cross==13))||(rslant==23&&(stand==13||lslant==13||cross==13)))
{
  gpoint+=70;

}
else if(cross==14||stand==14||lslant==14||rslant==14)
{
 gpoint+=60;

}
else if(cross==23||stand==23||lslant==23||rslant==23)
{

 gpoint+=50;

}
else if(cross==22||stand==22||lslant==22||rslant==22)
{
 gpoint+=20;
}
else if(cross==13||stand==13||lslant==13||rslant==13)
{

 gpoint+=30;
}
else if(cross==12||stand==12||lslant==12||rslant==12)
{

 gpoint+=10;
}
else if((cross==11||cross==12)||(stand==11||stand==12)||(rslant==11||rslant==12)||(lslant==11||lslant==12))
{
 gpoint+=0;
}
return gpoint;

}
int compuer(mc *pmc)
{
  int row,line;
  int max=-99999;
  int pcomputer=0;
  int player=0;
  int point;
  int tmprow,tmpline;
  int pcross,pstand,plslant,prslant;
  for(row=0;row<15;row++)
    for(line=0;line<15;line++)
    {
      if(chess[row][line]==0)
      {
       chess[row][line]=1;
       pcomputer=point1(cross(row,line,1),stand(row,line,1),lslant(row,line,1),rslant(row,line,1));


       chess[row][line]=2;


       point=pcomputer-player;
       if(point>max)
       {
         max=point;
         tmprow=row;
         tmpline=line;

       }
       chess[row][line]=0;
     }



   }



 }
