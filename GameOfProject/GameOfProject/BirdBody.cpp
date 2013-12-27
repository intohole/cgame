#include "StdAfx.h"
#include "BirdBody.h"
#include "GameTools.h"

CBirdBody::CBirdBody(void)
{
}
CBirdBody::CBirdBody(int pos_x,int pos_y,int nBirdWidth,int nBirdHeight,int lx,int ly,int rx,int ry)
{
	birdPos.x=pos_x;
	birdPos.y=pos_y;
	this->nBirdWidth=nBirdWidth;
	this->nBirdHeight=nBirdHeight;
	SetRectWall(lx,ly,rx,ry);
}
CBirdBody::CBirdBody(int pos_x,int pos_y,int nBirdWidth,int nBirdHeight,RECT rect)
{
	birdPos.x=pos_x;
	birdPos.y=pos_y;
	this->nBirdWidth=nBirdWidth;
	this->nBirdHeight=nBirdHeight;
	SetRectWall(rect);
}
CBirdBody::~CBirdBody(void)
{
}
void CBirdBody::SetBirdLife(int nLife)
{
	this->nBirdLife=nLife;
}
void CBirdBody::GetBirdRect(RECT &rect)
{
	rect.left=birdPos.x;
	rect.top=birdPos.y;
	rect.right=birdPos.x+nBirdWidth;
	rect.bottom=birdPos.y+nBirdHeight;
}
RECT CBirdBody::GetBirdRect()
{
	RECT rect;
	GetBirdRect(rect);
	return rect;
}
int CBirdBody::MoveBirdPos()
{
	if ((birdPos.y+nBirdHeight-nSpeed)<rectWall.top)
	{
		nBirdLife--;
		if (nBirdLife==0)
		{
			return -1;
		}
		return -2;
	}
	else
	{
		birdPos.y=birdPos.y+nSpeed;
	}
	return 0;	
}
// int CBirdBody::SubBirdPos()
// {
// 	if ((birdPos.y+nBirdHeight+nSpeed)>rectWall.bottom)
// 	{
// 		nBirdLife--;
// 		if (nBirdLife==0)
// 		{
// 			return -1;
// 		}
// 		return -2;
// 	}
// 	else
// 	{
// 		birdPos.y=birdPos.y+nSpeed;
// 	}
// 	return 0;
// }
void CBirdBody::SetRectWall(RECT rect)
{
	rectWall=rect;
}
void CBirdBody::SetRectWall(int lx,int ly,int rx,int ry)
{
	rectWall.left=lx,
	rectWall.top=ly;
	rectWall.right=rx;
	rectWall.bottom=ry;
}
BOOL CBirdBody::HasHitBird(vector<GunInfo> vGun,int nWidth,int nHeight)
{
	for (int i=0;i<vGun.size();i++)
	{
		RECT gunRect;
		RECT birdRect;
		CGameTools::MakeRect(vGun[i].GunPos,nWidth,nHeight,gunRect);
		GetBirdRect(birdRect);
		if (CGameTools::RectInRect(gunRect,birdRect))
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CBirdBody::HasHitWall()
{
	if (birdPos.y<rectWall.top||(birdPos.y+nBirdHeight)>rectWall.bottom)
	{
		return TRUE;
	}
	return FALSE;
}
void CBirdBody::ChangeBirdSpeed(BOOL bAddSign,double nChangeSpeed)
{
	if (bAddSign)
	{
		SetBirdSpeed(GetBirdSpeed()-nChangeSpeed);
	}
	else
	{
		SetBirdSpeed(GetBirdSpeed()+nChangeSpeed);
	}
}
void CBirdBody::RetBirdPos()
{
	birdPos.x=rectWall.left+10;
	birdPos.y=(rectWall.top+rectWall.bottom-nBirdHeight)/2;
}
