#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "bios.h"
#include "conio.h"
int rand_3(int max,int min)
{

	return rand()%(max-min+1)+min;


}
void init()
{
	srand(time(NULL));

}

void pri_ran()
{

	int num[41];
	int row=0;
	int ti=0;
	init();
	textcolor(2);

	clrscr();
	for(row=0;row<41;row++)
	{
		num[row]=0;
	}

	while(!bioskey(1))
	{


		for(row=1;row<=40;row++)
		{

			if(row%3==0)
			{

				num[row]=rand_3(1,0);

			}
/*else
{
       if(rand_3(10,0)<=3)
       {
       num[row]=rand_3(1,0);


       }


}
  */
}
printf("%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d%2d",num[1],num[2],num[3],num[4],num[5],num[6],num[7],num[8],num[9],num[10],num[11],num[12],num[13],num[14],num[15],num[16],num[17],num[18],num[19],num[20],num[21],num[22],num[23],num[24],num[25],num[26],num[27],num[28],num[29],num[30],num[31],num[32],num[33],num[34],num[35],num[36],num[37],num[38],num[39],num[40]);

delay(1000);

}

}
void main()
{

	pri_ran();

}
