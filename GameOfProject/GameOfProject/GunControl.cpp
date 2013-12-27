#include "StdAfx.h"
#include "GunControl.h"
#include "GameTools.h"

CGunControl::CGunControl(void)
{
}

CGunControl::CGunControl(int nLimit,int Speed,int nMax,int nWidth,int nHeight,RECT rect)
{
	this->nSpeed=Speed;
	SetRectWall(rect);
	SetGunWH(nWidth,nHeight);
	SetGunSpeed(Speed);
	SetLimitNum(nLimit);
	SetMaxGun(nMax);
	InitGunPos();
	srand((unsigned)time(NULL));
	ReSetGunPos();

}
CGunControl::~CGunControl(void)
{
}
void CGunControl::InitGunPos()
{
	for (int i=0;i<nLimitNum;i++)
	{
		GunInfo stInfo;
		stInfo.bIsHide=TRUE;
		vGunSave.push_back(stInfo);
	}
}
POINT CGunControl::GetRandGunPos()
{
	
	POINT pt;
	BOOL bFind=FALSE;
	while(!bFind)
	{
		bFind=TRUE;
		pt.x=rectWall.right-10;
		pt.y=rand()%(rectWall.bottom-rectWall.top)+rectWall.top;
		if (pt.y<rectWall.top||(pt.y+nGunHeight)>rectWall.bottom)
 		{
			bFind=FALSE;
 		}
	}
	return pt;
}
void CGunControl::AddHardLevel()
{
	GunInfo stGun;
	stGun.bIsHide=FALSE;
	vGunSave.push_back(stGun);
}
void CGunControl::ReSetGunPos()
{
	int nMax=0;
	for (int i=0;i<vGunSave.size();i++)
	{
		if (vGunSave[i].bIsHide==TRUE)
		{
			nMax++;
			POINT pt=GetRandGunPos();
			vGunSave[i].GunPos.x=pt.x;
			vGunSave[i].GunPos.y=pt.y;
			vGunSave[i].bIsHide=FALSE;
			vGunSave[i].GunSpeed=rand()%nSpeed+1;
			if (nMax>(nMaxGun-1))
			{
				break;
			}
		}
		else if (!vGunSave[i].bIsHide)
		{
			nMax++;
			if (nMax>(nMaxGun-1))
			{
				break;
			}
		}
		
	}
}
int CGunControl::GetGunRect(int nIndex,RECT &rect)
{
	if ((nIndex-1)>GetGunLong()||nIndex<0)
	{
		rect.left=0;
		rect.bottom=0;
		rect.right=0;
		rect.top=0;
		return -1;
	}
	else
	{
		rect.left=vGunSave[nIndex].GunPos.x;
		rect.right=vGunSave[nIndex].GunPos.x+nGunWidth;
		rect.top=vGunSave[nIndex].GunPos.y;
		rect.bottom=vGunSave[nIndex].GunPos.y+nGunHeight;
	}
	return 0;
}
void CGunControl::MoveGun()
{
	for (int i=0;i<vGunSave.size();i++)
	{
 		if (!vGunSave[i].bIsHide)
		{
			vGunSave[i].GunPos.x-=nSpeed;
		}
	}
}
int CGunControl::HasHitWall()
{
	for (int i=0;i<vGunSave.size();i++)
	{
		if ((vGunSave[i].GunPos.x-nSpeed)<=rectWall.left)
		{
			vGunSave[i].bIsHide=TRUE;
		}
	}
	return 0;
}
void CGunControl::SetMaxGun(int nMax)
{
	if (nMax>nLimitNum)
	{
		nMax=nLimitNum;
	}
	this->nMaxGun=nMax;
}
void CGunControl::SetGunWH(int nWidth,int nHeight)
{
	this->nGunWidth=nWidth;
	this->nGunHeight=nHeight;
}
void CGunControl::SetGunSpeed(int nSpeed)
{
	this->nSpeed=nSpeed;
}
void CGunControl::SetLimitNum(int nLimit)
{
	this->nLimitNum=nLimit;
}
void CGunControl::SetRectWall(RECT rectWall)
{
	this->rectWall.left=rectWall.left;
	this->rectWall.top=rectWall.top;
	this->rectWall.right=rectWall.right;
	this->rectWall.bottom=rectWall.bottom;
}
BOOL CGunControl::HasHitBird(RECT rectBird)
{
	for(int i=0;i<vGunSave.size();i++)
	{
		RECT gunRect;
		if (vGunSave[i].bIsHide)
		{
			continue;
		}
		GetGunRect(i,gunRect);
		if (CGameTools::RectInRect(rectBird,gunRect))
		{
			return TRUE;
		}
	}
	return FALSE;
}



