#include "StdAfx.h"
#include "ShipControl.h"
#include "GameTools.h"

CShipControl::CShipControl(void)
{
}
CShipControl::CShipControl(POINT pos,RECT wallRect,int nWidht,int nHeight)
{
	shipPos.x=pos.x;
	shipPos.y=pos.y;
	CGameTools::copyRect(rectWall,wallRect);
	nShipWidth=nWidht;
	nShipHeight=nHeight;
	bCanPutGun=TRUE;
}
CShipControl::~CShipControl(void)
{
}
RECT CShipControl::GetShipRect()
{
	return	CGameTools::GetRectWith(shipPos,nShipWidth,nShipHeight);
}
void CShipControl::SetShipPos(POINT pos)
{
	if ((pos.x+nShipWidth)>rectWall.right)
	{
		pos.x=rectWall.right-nShipWidth;
	}
	if (pos.x<rectWall.left)
	{
		pos.x=rectWall.left;
	}
	shipPos.x=pos.x;
}
void CShipControl::SetRectWall(RECT rect)
{
	 CGameTools::copyRect(rectWall,rect);
}
void CShipControl::SetWaterLine(int nSet)
{
	shipPos.y=nSet-nShipHeight;
}
void CShipControl::SetShipCanPutGun(BOOL bSign)
{
	bCanPutGun=bSign;
}
int CShipControl::GetShipHeight()
{
	return nShipHeight;
}