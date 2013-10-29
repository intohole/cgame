#include "stdio.h"
#define STACKMAX 50
#define TRIGHT 1
#define TLEFT  2
#define TDOWN  3
#define TUP    4

/*
1 ÍùÓÒ
2 ÍùÏÂ
3 ÍùÏÂ
4 ÍùÉÏ
*/

typedef struct WAY
{
int locate[STACKMAX];
int turn[STACKMAX]; 
int pstack;
}step;
int push(step *ps,int lc);
int pop(step *ps);

int main()
{
step ps;
ps.pstack=-1;
push(&ps,1);
push(&ps,2);
push(&ps,4);

printf("%d   %d    %d        %d       %d",ps.pstack,pop(&ps),pop(&ps),pop(&ps),pop(&ps));
return 1;
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

