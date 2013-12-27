#include "StdAfx.h"
#include "ArmyControl.h"
#include "GameTools.h"

CArmyControl::CArmyControl(void)
{
}
CArmyControl::CArmyControl(int level,int nRadius,int speedMaxX,int speedMaxY,POINT pPos,RECT rWall,RECT HitWall)
{
	this->nLevel=level;
	this->nSelfRaduis=nRadius;
	this->nSpeedXMax=speedMaxX;
	this->nSpeedYMax=speedMaxY;
	this->personPoint=pPos;
	CGameTools::copyRect(this->rectWall,rWall);
	CGameTools::copyRect(this->rectHitWall,HitWall);
	srand(time(NULL));
	InitArmy();
}
CArmyControl::~CArmyControl(void)
{
}
void CArmyControl::AddArmy()
{
	ArmyInfo stArmyInfo;
	InitArmyInfo(stArmyInfo);
	vArmySave.push_back(stArmyInfo);
	nLevel++;
}
void CArmyControl::InitArmy()
{
	vArmySave.clear();
	ArmyInfo stArmyInfo;
	for (int i=0;i<nLevel;i++)
	{
		InitArmyInfo(stArmyInfo);
		vArmySave.push_back(stArmyInfo);
	}
}
void CArmyControl::ArmyMove()
{
	for(int i=0;i<vArmySave.size();i++)
	{
		vArmySave[i].pos.x+=vArmySave[i].nSpeedX;
		vArmySave[i].pos.y+=vArmySave[i].nSpeedY;
		HasHitRectWall(vArmySave[i]);
		HasHitHitWall(vArmySave[i]);
	}
}
void CArmyControl::SetLevel(int nLevel)
{
	this->nLevel=nLevel;
}
void CArmyControl::SetRadius(int nRaduis)
{
	this->nSelfRaduis=nRaduis;
}
BOOL CArmyControl::HasHitPerson(POINT pos,int nRadius)
{
	for(int i=0;i<vArmySave.size();i++)
	{
		if (CGameTools::CireleHitCirele(pos,vArmySave[i].pos,nRadius,nSelfRaduis))
		{
			return TRUE;
		}
	}
	return FALSE;
}
void CArmyControl::SetSpeedMax(int nMaxX,int nMaxY)
{
	this->nSpeedXMax=nMaxX;
	this->nSpeedXMax=nMaxY;
}
POINT CArmyControl::CreatPos(POINT pt)
{
	BOOL bFind=FALSE;
	POINT rePt;
	while(!bFind)
	{
		bFind=TRUE;
		rePt.x=rand()%(rectWall.right-rectWall.left+1-2*nSelfRaduis)+rectWall.left-nSelfRaduis;
		rePt.y=rand()%(rectWall.bottom-rectWall.top+1-2*nSelfRaduis)+rectWall.top-nSelfRaduis;
		if (CGameTools::PointDistance(pt,rePt)<25)
		{
			bFind=FALSE;
		}
	}
	return rePt;
}

void CArmyControl::InitArmyInfo(ArmyInfo &stArmyInfo)
{
	ZeroMemory(&stArmyInfo,sizeof(stArmyInfo));
	stArmyInfo.pos=CreatPos(personPoint);
	stArmyInfo.nSpeedX=RandSpeed(this->nSpeedXMax);
	stArmyInfo.nSpeedY=RandSpeed(this->nSpeedYMax);
	stArmyInfo.bHideSign=FALSE;
}
int CArmyControl::RandSpeed(int nMax)
{
	return rand()%(nMax+1);
}
int CArmyControl::GetArmyRect(int nIndex,RECT &rect)
{
	if (nIndex>(vArmySave.size()-1))
	{
		ZeroMemory(&rect,sizeof(rect));
		return -1;
	}
	else
	{
		ArmyInfo tmp=vArmySave[nIndex];
		rect.left=tmp.pos.x-nSelfRaduis;
		rect.top=tmp.pos.y-nSelfRaduis;
		rect.right=tmp.pos.x+nSelfRaduis;
		rect.bottom=tmp.pos.y+nSelfRaduis;
		return 0;
	}
}
void CArmyControl::HasHitRectWall(ArmyInfo &stArmyInfo)
{
	BOOL bHitWall=TRUE;
	if(CGameTools::SetPosInRect(stArmyInfo.pos,rectWall,nSelfRaduis))
	{
		bHitWall=FALSE;
	}
	stArmyInfo.bHideSign=bHitWall;
}
BOOL CArmyControl::GetArmyHide(int nIndex)
{
	if (nIndex>(GetArmyNum()-1))
	{
		return TRUE;
	}
	return  vArmySave[nIndex].bHideSign;
	
}
void CArmyControl::HasHitHitWall(ArmyInfo &stArmyInfo)
{
	if ((stArmyInfo.pos.x-nSelfRaduis)<=rectHitWall.left)
	{
		stArmyInfo.nSpeedX=abs(stArmyInfo.nSpeedX);
	}
	if ((stArmyInfo.pos.x+nSelfRaduis)>=rectHitWall.right)
	{
		stArmyInfo.nSpeedX=-abs(stArmyInfo.nSpeedX);
	}
	if((stArmyInfo.pos.y-nSelfRaduis)<=rectHitWall.top)
	{
		stArmyInfo.nSpeedY=abs(stArmyInfo.nSpeedY);
	}
	if ((stArmyInfo.pos.y+nSelfRaduis)>=rectHitWall.bottom)
	{
		stArmyInfo.nSpeedY=-abs(stArmyInfo.nSpeedY);
	}
}
