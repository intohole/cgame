#include "StdAfx.h"
#include "PersonControl.h"
#include "GameTools.h"

CPersonControl::CPersonControl(void)
{
}
CPersonControl::CPersonControl(int pos_x,int pos_y,int nR,RECT rect)
{
	SetPersonPos(pos_x,pos_y);
	SetPersonradius(nR);
	SetRectWall(rect);
}
CPersonControl::~CPersonControl(void)
{
}
void CPersonControl::SetPersonPos(POINT pt)
{
	BOOL bShowCursor=FALSE;
 	if ((personPos.x-nRadius)<rectWall.left)//||(personPos.x+nRadius)>rectWall.right)
 	{
		bShowCursor=TRUE;
 		pt.x=rectWall.left+nRadius;
 	}
	if ((personPos.x+nRadius)>rectWall.right)
	{
		bShowCursor=TRUE;
		pt.x=rectWall.right-nRadius;
	}
	if ((personPos.y-nRadius)<rectWall.top)
	{
		bShowCursor=TRUE;
		pt.y=rectWall.top+nRadius;
	}
	if ((personPos.y+nRadius)>rectWall.bottom)
	{
		bShowCursor=TRUE;
		pt.y=rectWall.bottom-nRadius;
	}
	if (((pt.x-nRadius)>rectWall.left&&(pt.x+nRadius)<rectWall.right)&&((pt.y-nRadius)>=rectWall.top&&(pt.y+nRadius)<=rectWall.bottom))
	{
	
		ShowCursor(bShowCursor);
		personPos.x=pt.x;
		personPos.y=pt.y;	
	}
	
}
void CPersonControl::SetPersonPos(int lx,int ly)
{
	personPos.x=lx;
	personPos.y=ly;
}
void CPersonControl::SetPersonradius(int nRadius)
{
	this->nRadius=nRadius;
}
RECT CPersonControl::GetPersonRect()
{
	return CGameTools::CireleToRect(personPos,nRadius);
}
int CPersonControl::MovePerson(POINT pt)
{
	if ((personPos.x-nRadius)<rectWall.left)
	{
		ShowCursor(TRUE);
		personPos.x=rectWall.left+nRadius;
	}
	else if ((personPos.x+nRadius)>rectWall.right)
	{
		ShowCursor(TRUE);
		personPos.x=rectWall.right-nRadius;
	}
	else if ((personPos.y-nRadius)>rectWall.top)
	{
		ShowCursor(TRUE);
		personPos.y=rectWall.top+nRadius;
	}
	else if ((personPos.y+nRadius)>rectWall.bottom)
	{
		ShowCursor(TRUE);
		personPos.y=rectWall.bottom+nRadius;
	}
	else
	{
		ShowCursor(FALSE);
		personPos.x=pt.x;
		personPos.y=pt.y;
	}

	return 1;
}
void CPersonControl::SetRectWall(int lx,int ly,int rx,int ry)
{
	rectWall.left=lx;
	rectWall.right=rx;
	rectWall.top=ly;
	rectWall.bottom=ry;
}
void CPersonControl::SetRectWall(RECT rect)
{
	CGameTools::copyRect(rectWall,rect);
}
BOOL CPersonControl::HasHitWall()
{
	if ((personPos.x-nRadius)<rectWall.left)
	{
		return TRUE;
	}
	if ((personPos.x+nRadius)>rectWall.right)
	{
		return TRUE;
	}
	if ((personPos.y-nRadius)>rectWall.top)
	{
		return TRUE;
	}
	if ((personPos.y+nRadius)>rectWall.bottom)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CPersonControl::HasHitGun(vector<ArmyInfo> vArmy,int nArmyRadius)
{
	for(int i=0;i<vArmy.size();i++)
	{
		if (CGameTools::CireleHitCirele(personPos,vArmy[i].pos,nRadius,nArmyRadius))
		{
			return TRUE;
		}
	}
	return FALSE;
}
void CPersonControl::ResetPerson(POINT pt)
{
	
}