#include "StdAfx.h"
#include "SnakeFood.h"

CSnakeFood::CSnakeFood(void)
{
	bHaveFood=FALSE;
	posFood.x=0;
	posFood.y=0;
}
CSnakeFood::CSnakeFood(RECT rectWall,int foodWidth,int foodHeight)
{
	this->rectWall=rectWall;
	this->foodHeight=foodHeight;
	this->foodWidth=foodWidth;
	posFood.x=150;
	posFood.y=300;
	bHaveFood=TRUE;
}
CSnakeFood::~CSnakeFood(void)
{
}
BOOL CSnakeFood::GetHaveFood()
{
	return bHaveFood;
}
void CSnakeFood::SetHaveFood(BOOL bSignFood)
{
	bHaveFood=bSignFood;
}
BOOL CSnakeFood::SetFoodPos(vector<POINT> vPos)
{

	BOOL bFind=FALSE;
	while (!bFind)
	{
		bFind=TRUE;
		posFood=RandPos();
		for (int i=0;i<vPos.size();i++)
		{
			if (vPos[i].x== posFood.x && vPos[i].y == posFood.y)
			{
				bFind=FALSE;
				break;
			}
		}
	}
	return TRUE;
}
POINT CSnakeFood::RandPos()
{
	POINT pt;
	srand(time(NULL));
	pt.x=rand()%(rectWall.right-rectWall.left+1)+rectWall.left;
	pt.y=rand()%(rectWall.bottom-rectWall.top+1)+rectWall.top;
	pt.x=pt.x/foodWidth*foodWidth;
	pt.y=pt.y/foodHeight*foodHeight;
	if (pt.x<rectWall.left)
	{
		pt.x=rectWall.left;
	}
	if ((pt.x+foodWidth)>rectWall.right)
	{
		pt.x=rectWall.right-foodWidth;
	}
	if (pt.y<rectWall.top)
	{
		pt.x=rectWall.top;
	}
	if ((pt.x+foodHeight)>rectWall.bottom)
	{
		pt.x=rectWall.bottom-foodWidth;
	}
	return pt;
}
POINT CSnakeFood::GetFoodPos()
{
	return posFood;
}
void CSnakeFood::SetWallRect(RECT rectWall)
{
	this->rectWall=rectWall;
}
void CSnakeFood::GetFoodRect(RECT &rect)
{
	rect.left=posFood.x;
	rect.top=posFood.y;
	rect.right=posFood.x+foodWidth;
	rect.bottom=posFood.y+foodHeight;
}
BOOL CSnakeFood::HaveEatFood(POINT pt)
{
	if (pt.x == posFood.x && pt.y == posFood.y)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}