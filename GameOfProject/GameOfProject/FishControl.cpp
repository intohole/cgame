#include "StdAfx.h"
#include "FishControl.h"
#include "GameTools.h"

CFishControl::CFishControl(void)
{
}
CFishControl::CFishControl(int nSpeedMaxX,int nSpeedMaxY,int nSpeedMinX,int nSpeedMinY,int nWidth,int nHeight,int nLife,int nMinLine,RECT rect)
{
	SetSpeedXY(nSpeedMaxX,nSpeedMaxY,nSpeedMinX,nSpeedMinY);
	SetFishWH(nWidth,nHeight);
	SetFishLife(nLife);
	SetWaterLine(nMinLine);
	CGameTools::copyRect(rectWall,rect);
}
CFishControl::~CFishControl(void)
{
}
void CFishControl::SetFishWH(int nWidth,int nHeight)
{
	nFishHeight=nHeight;
	nFishWidth=nWidth;
}
void CFishControl::SetWallRect(RECT rect)
{
	CGameTools::copyRect(rectWall,rect);
}
void CFishControl::SetSpeedXY(int nMaxX,int nMaxY,int nMinX,int nMinY)
{
	stSpeed.MaxX=nMaxX;
	stSpeed.MaxY=nMaxY;
	stSpeed.MinX=nMinX;
	stSpeed.MinY=nMinY;
}
void CFishControl::Move()
{
	list<FISHINFO>::iterator it;
	for (it=listFishSave.begin();it!=listFishSave.end();it++)
	{
		it->pos.x-=it->nSpeedX;
	}
}
void CFishControl::HasHitWall()
{
	list<FISHINFO>::iterator it;
	for (it=listFishSave.begin();it!=listFishSave.end();)
	{
		if ((it->pos.x+nFishWidth)<=rectWall.left)
		{
			list<FISHINFO>::iterator tmp=it;
			it++;
			listFishSave.erase(tmp);
		}
		else  if ((it->pos.y-nFishHeight)>=rectWall.bottom)
		{
			list<FISHINFO>::iterator tmp=it;
			it++;
			listFishSave.erase(tmp);
		}
		else
		{
			it++;
		}
	}
}

int CFishControl::RandSpeedX()
{
	return rand()%(stSpeed.MaxX-stSpeed.MinX+1)+stSpeed.MinX;	
}
int CFishControl::RandSpeedY()
{
	return rand()%(stSpeed.MaxY-stSpeed.MinY+1)+stSpeed.MinY;
}
POINT CFishControl::CreatePos()
{
	POINT pt;
	pt.y=rand()%((rectWall.bottom-nFishHeight)-nWaterLine+1)+nWaterLine;
	pt.x=rectWall.right-nFishWidth;
	return pt;
}
void CFishControl::InitFishInfo(FISHINFO &stFish,int nLife)
{
	stFish.nLife=nLife;
	stFish.pos=CreatePos();
	stFish.nSpeedX=RandSpeedX();
	stFish.nSpeedY=0;//暂设为0 以后可扩展
}
void CFishControl::SetWaterLine(int nLine)
{
	nWaterLine=nLine;
}
void CFishControl::SetFishLife(int nLife)
{
	nFishLife=nLife;
}
void CFishControl::GetFishRectWith(int nIndex,RECT &rect)
{
	list<FISHINFO>::iterator it;
	int i=0;
	for (it=listFishSave.begin();it!=listFishSave.end();i++,it++)
	{
		if(i == nIndex)
		{
			rect=CGameTools::GetRectWith(it->pos,nFishWidth,nFishHeight);
			return;
		}
	}
	memset(&rect,0,sizeof(rect));
}
void CFishControl::AddFish()
{
	FISHINFO stFish;
	InitFishInfo(stFish,nFishLife);
	listFishSave.push_back(stFish);
}
int CFishControl::HasHitGun(list<POINT> &listGunSave,int nWidth,int nHeight)
{
	list<FISHINFO>::iterator it;
	list<POINT>::iterator gun;
	RECT gunRect;
	RECT fishRect;
	int KillNum=0;
	for (it=listFishSave.begin();it!=listFishSave.end();it++)
	{
		CGameTools::MakeRect(it->pos,nFishWidth,nFishHeight,fishRect);
		for (gun=listGunSave.begin();gun!=listGunSave.end();)
		{
			CGameTools::MakeRect(*gun,nWidth,nHeight,gunRect);
			if (CGameTools::RectInRect(gunRect,fishRect))
			{
				if ((it->nLife-1)==0)//碰撞检测 生命值剩下一条 去除当前子弹并且去除鱼
				{
					list<FISHINFO>::iterator tmpFish=it;
					it++;
					listFishSave.erase(tmpFish);
					listGunSave.erase(gun);
					KillNum++;
					if (it == listFishSave.end())
					{
						return KillNum;
					}
					break;
				}
				else//否则 只去除子弹
				{
					list<POINT>::iterator gunTmp=gun;
					gun++;
					listGunSave.erase(gunTmp);
					it->nLife-=1;//生命值减1
				}
				
			}
			else
			{
				gun++;
			}
		}
	}
	return KillNum;
}