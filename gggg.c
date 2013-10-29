#include"stdio.h"
#include"dos.h"
#include"graphics.h"

typedef struct PaletteColor
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}PalColor,*PalColor_p;

PalColor_p GetPalColor(int index)   /*获取序号为index的调色板寄存器的颜色信息*/
{
    PalColor_p color;
    outp(0x3c6,0xff);
    outp(0x3c7,index);
    color->red=inp(0x3c9);
    color->green=inp(0x3c9);
    color->blue=inp(0x3c9);
    return color;
}

void SetPalColor(int index, PalColor_p color) /*设置序号为index的调色板寄存器颜色*/
{
    outp(0x3c6,0xff);
    outp(0x3c8,index);
    outp(0x3c9,color->red);
    outp(0x3c9,color->green);
    outp(0x3c9,color->blue);
}

main()
{
    int i,j,index;
    int gd=DETECT,gm;
    PalColor *old_color,color;   /*其中old_color用于保存原寄存器颜色信息*/
    initgraph(&gd,&gm,"");
    index=1;                 /*设置将要使用的调色板寄存器序号为1号*/
    setcolor(15);
    circle(300,200,50);
    setfillstyle(1,index);
    /*使用1号调色板寄存器内存放的颜色（初始为蓝色）来填充圆*/
    floodfill(300,200,15);
    old_color=GetPalColor(index); /*保存1号寄存器的蓝颜色信息*/
    color.red=color.green=color.blue=0; /*将三原色都初始化为0*/
    getch();
    for(i=0;i<63;i++)
    {
        /*使三原色的值依次加1*/
        color.red+=1;   
        color.green+=0;
        color.blue+=1;
        SetPalColor(1,&color); /*设置由color指定的新的颜色到1号寄存器内*/
        for(j=0;j<10;j++)     /*延时*/
        delay(5000);
    }
    SetPalColor(1,old_color);
    /*当圆内的颜色达到最亮时重新设回由old_color保存的蓝色*/
    getch();
}
