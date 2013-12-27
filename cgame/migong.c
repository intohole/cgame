#include "stdio.h"
#include "time.h"
#include "graphics.h"
#define LEN  10
#define TRIGHT 1
#define TLEFT  2
#define TDOWN  3
#define TUP    4
#define N      33
/* 33 为此迷宫 极限值 具体为什么 我也不怎么了解 */
#define STACKMAX 400
#define UP   0x4800
#define DOWN  0x5000
#define LEFT   0x4b00
#define RIGHT 0x4d00
#define ESC   0x11b
#define BS    0x3920
/*
1 往右
2 往下
3 往下
4 往上
*/

unsigned char path[N][N];
/*
{ 
    {1,1,1,1,1,1,1,1,1,1}, 
    {1,0,0,1,0,0,0,1,0,1}, 
    {1,1,0,1,0,1,0,1,0,1}, 
    {1,0,0,0,0,1,1,0,0,1}, 
    {1,0,1,1,1,0,0,0,1,1}, 
    {1,0,0,0,1,1,0,0,1,1}, 
    {1,0,1,0,0,0,1,0,0,1}, 
    {1,0,1,1,1,0,1,1,0,1}, 
    {1,1,0,0,0,0,0,0,0,1}, 
    {1,1,1,1,1,1,1,1,1,1} 
};
*/
typedef struct WAY
{
  int locate[STACKMAX];
  
  int pstack;
}step;
void initstack(step *ps);

int push(step *ps,int lc);
int pop(step *ps);

int mix(int row,int line);
int dv(int ans,int *row,int *line);
int move(step *ps);
void pri_num();
void randmap();
int rand_2(int max,int min);
int createmap(step *ps);
void del_23();
void init(int color);
void drawmap(int color);
void mybar(int topx,int topy);
void drawpeople(int row,int line,int color);
int computermove(int row,int line,step *ps);
int main()
{
  step ps;
  int key;
  int row=1,line=1;
  init(WHITE);
  createmap(&ps);

  drawmap(BLUE);
  drawpeople(row,line,RED);
  while(1)
  {


    key=bioskey(0);
    switch(key)
    {
     case UP:if(path[row-1][line]==0)
     {
      drawpeople(row,line,WHITE);
      row--;
      drawpeople(row,line,RED);

    }break;
    case DOWN:if(path[row+1][line]==0)
    {
      drawpeople(row,line,WHITE);
      row++;
      drawpeople(row,line,RED);

    }break;
    case RIGHT:if(path[row][line+1]==0)
    {
      drawpeople(row,line,WHITE);
      line++;
      drawpeople(row,line,RED);

    }break;
    case LEFT:if(path[row][line-1]==0)
    {
      drawpeople(row,line,WHITE);
      line--;
      drawpeople(row,line,RED);

    }break;
    case ESC:closegraph();exit(0); break;
    case BS: computermove(row,line,&ps);
    del_23();
    getch();
    cleardevice();
    drawmap(BLUE);
    drawpeople(row,line,RED);
    default :break;


  }
  if(line==(N-2)&&row==(N-2))
  {

    closegraph();
    printf("\n\n\n\n\t\t\t\tGood Job");
    sleep(5);
    break;

  }

}
return 1;
}

void initstack(step *ps)
{
  ps->pstack=-1;
}
int push(step *ps,int lc)
{
  if (ps->pstack<STACKMAX) {
   
    ps->locate[++ps->pstack]=lc;
    
    return 1;
  }
  else
  {

    return -1;

  }

}


int pop(step *ps)
{
  int re;
  if (ps->pstack>=0) {
    re=ps->locate[ps->pstack--];
    
    return re;
  }
  else
  {

    return -1;

  }



}


int mix(int row,int line)
{
  return row+line*1000;
}


int dv(int ans,int *row,int *line)
{
  
  *row=ans%1000;
  *line=ans/1000;
  return 0;
}



int move(step *ps)
{

  int row=1;
  int line=1;


  while (row!=(N-2)||line!=(N-2)) {

    if (path[row][line+1]==0) {
     
      push(ps,mix(row,line));
      
      line++;
      path[row][line]=2;
      

      
    }
    else 
    {


      if (path[row+1][line]==0) {

        
        
        push(ps,mix(row,line));
        
        row++;
        path[row][line]=2;
        
      }

      else
      {

        if (path[row][line-1]==0) {
          
          push(ps,mix(row,line));
          
          
          line--;
          path[row][line]=2;
          
        }
        else

        {
          if (path[row-1][line]==0) {
            push(ps,mix(row,line));
            
            row--;
            path[row][line]=2;
          }
          else
          {
           if(row==1&&line==1)
           {
             return -1;
           }
           else
           {
            path[row][line]=3;
            dv(pop(ps),&row,&line);
          }
          
        }
        
        
        
      }


    }


  }
  


}

return 1;
}

void pri_num()
{
  int row,line;
  
  for(row=0;row<N;row++)
    {  printf("\n\t\t\t");
  for(line=0;line<N;line++)
    printf("%3d",path[row][line]);
  
  
}
 /*  delay(1200000000000);
    clrscr();
   */

  }
  void randmap()
  {
   
    int row=0;
    int line=0;
    for(;row<N;row++)

      for(line=0;line<N;line++)
      {
        if(row==0||line==0||row==(N-1)||line==(N-1))
        {
          
          path[row][line]=1;

        }
        else
        {
          path[row][line]=rand_2(1,0);
        }


      }

      path[1][1]=0;
      path[N-2][N-2]=0;

    }
    int rand_2(max,min)
    {

      return rand()%(max-min+1)+min;

    }
    int createmap(step *ps)
    {
      initstack(ps);
      srand(time(NULL));
      randmap();
      while(move(ps)==-1)
      {

        randmap();
        initstack(ps);


      }
      del_23();



    }
    void del_23()
    {
      int row=0;
      int line;
      for(;row<N;row++)
        for(line=0;line<N;line++)
        {
          if(path[row][line]==2||path[row][line]==3)
          {

           path[row][line]=0;

         }



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


    void drawmap(int color)
    {
      int row=0;
      int line;
      int start_x=100;
      int start_y=100;
      cleardevice();
      setfillstyle(SOLID_FILL,color);

      for(row=0;row<N;row++)
      {

       start_x=LEN*row+100;
       start_y=100;
       for(line=0;line<N;line++)
       {
        start_y=LEN*line+100;
        if(path[row][line]==1)
        {

          mybar(start_y,start_x);
        }


      }

    }

    setcolor(RED);

    rectangle(100+(N-2)*LEN,100+(N-2)*LEN,100+(N-2)*LEN+LEN,100+(N-2)*LEN+LEN);
  }
  void mybar(int topx,int topy)
  {

    bar(topx,topy,topx+LEN,topy+LEN);

  }
  void drawpeople(int row,int line,int color)
  {
    int y=100+row*LEN+LEN/2;
    int x=100+line*LEN+LEN/2;

 /* setfillstyle(SOLID_FILL,color);
  pieslice(x,y,0,360,(LEN/2-LEN/5));
   */
  setcolor(color);
  circle(x,y,(LEN/2-LEN/5));

}

int computermove(int row,int line,step *ps)
{

  initstack(ps);


  while (row!=(N-2)||line!=(N-2)) {

    if (path[row][line+1]==0) {
     
      push(ps,mix(row,line));
      drawpeople(row,line,WHITE);
      line++;
      path[row][line]=2;
      drawpeople(row,line,RED);

      
    }
    else 
    {


      if (path[row+1][line]==0) {

        
        
        push(ps,mix(row,line));
        drawpeople(row,line,WHITE);
        row++;
        path[row][line]=2;
        drawpeople(row,line,RED);
      }

      else
      {

        if (path[row][line-1]==0) {
          
          push(ps,mix(row,line));
          
          drawpeople(row,line,WHITE);
          line--;
          path[row][line]=2;
          drawpeople(row,line,RED);
        }
        else

        {
          if (path[row-1][line]==0) {
            push(ps,mix(row,line));
            drawpeople(row,line,WHITE);
            row--;
            path[row][line]=2;
            drawpeople(row,line,RED);
          }
          else
          {
           if(row==1&&line==1)
           {
             return -1;
           }
           else
           {
            path[row][line]=3;
            drawpeople(row,line,BROWN);
            dv(pop(ps),&row,&line);
            drawpeople(row,line,BROWN);
          }
          
        }
        
        
        
      }


    }


  }
  
  sleep(1);

}

return 1;





}
