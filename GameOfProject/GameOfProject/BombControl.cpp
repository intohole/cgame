#include "StdAfx.h"
#include "BombControl.h"
#include "GameTools.h"

CBombControl::CBombControl(void)
{
}
CBombControl::CBombControl(int nSpeed,int nWidth,int nHeight,RECT rect)
{
	nGunSpeed=nSpeed;
	nGunHeight=nHeight;
	nGunWidth=nWidth;
	CGameTools::copyRect(rectWall,rect);
}
void CBombControl::AddGun(POINT pos)
{
	pos.y+=nGunHeight/2;
	listGunSave.push_back(pos);
}
void CBombControl::SetSpeed(int nSpeed)
{
	nGunSpeed=nSpeed;
}
void CBombControl::SetGunWH(int nWidth,int nHeight)
{
	nGunWidth=nWidth;
	nGunHeight=nHeight;
}
void CBombControl::GetGunRect(int nIndex,RECT &rect)
{
	list<POINT>::iterator it;
	int i=0;
	for (it=listGunSave.begin();it!=listGunSave.end();it++,i++)
	{
		if (i==nIndex)
		{
			rect=CGameTools::GetRectWith(*it,nGunWidth,nGunHeight);
		}
	}
}
int CBombControl::GetGunSum()
{
	return listGunSave.size();
}
void CBombControl::GunMove()
{
	list<POINT>::iterator it;
	for (it=listGunSave.begin();it!=listGunSave.end();it++)
	{
		it->y+=nGunSpeed;
	}
}
void CBombControl::HasHitWall()
{
	list<POINT>::iterator it;
	for (it=listGunSave.begin();it!=listGunSave.end();)
	{
		if ((it->y+nGunHeight)>=rectWall.bottom)
		{
			list<POINT>::iterator temp_it = it;
			it++;
			listGunSave.erase(temp_it);
		}
		else
		 it++;
	}
}
void CBombControl::ReSetGame()
{
	listGunSave.clear();
}
CBombControl::~CBombControl(void)
{
}