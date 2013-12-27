#include "StdAfx.h"
#include "SnakeBody.h"

CSnakeBody::CSnakeBody(void)
{
	lastPos.x=0;
	lastPos.y=0;
	InitSnakeBody();
}
CSnakeBody::CSnakeBody(RECT rectWall,int nBodyHeight,int nBodyWidth,int nHeadDirction,int nSpeed)
{
	InitSnakeBody();
	this->rectWall=rectWall;
	this->nBodyHeight=nBodyHeight;
	this->nBodyWidth=nBodyWidth;
	this->nHeadDirction=nHeadDirction;
	this->nSpeed=nSpeed;
	this->nLife=1;
}
CSnakeBody::~CSnakeBody(void)
{
}
BOOL CSnakeBody::MoveBody()
{
	lastPos=vSnakeBody[vSnakeBody.size()-1];
	for (int i=vSnakeBody.size()-1;i>0;i--)
	{
		vSnakeBody[i].x=vSnakeBody[i-1].x;
		vSnakeBody[i].y=vSnakeBody[i-1].y;
	}
	return TRUE;
}
void CSnakeBody::MoveHead()
{
	
	switch (nHeadDirction)
	{
		case DIRUP:
			vSnakeBody[0].y=vSnakeBody[0].y-nSpeed;
			break;
		case DIRDOWN:
			vSnakeBody[0].y=vSnakeBody[0].y+nSpeed;
			break;
		case DIRLEFT:
			vSnakeBody[0].x=vSnakeBody[0].x-nSpeed;
			break;
		case DIRRIGHT:
			vSnakeBody[0].x=vSnakeBody[0].x+nSpeed;
			break;
		default:
			return ;
	}
}
BOOL CSnakeBody::HasHitMyself()
{
	for (int i=1;i<vSnakeBody.size();i++)
	{
		if (vSnakeBody[0].x==vSnakeBody[i].x&&vSnakeBody[0].y==vSnakeBody[i].y)
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CSnakeBody::HasHitWall()
{
	if (vSnakeBody[0].x<rectWall.left)
	{
		return TRUE;
	}
	if (vSnakeBody[0].y<rectWall.top)
	{
		return TRUE;
	}
	if ((vSnakeBody[0].x+nBodyWidth)>rectWall.right)
	{
		return TRUE;
	}
	if ((vSnakeBody[0].y+nBodyHeight)>rectWall.bottom)
	{
		return TRUE;
	}
	return FALSE;
}
void CSnakeBody::InitSnakeBody()
{
	POINT pt;
	pt.x=100;
	pt.y=30;
	nBodyHeight=10;
	nBodyWidth=10;
	nHeadDirction=DIRDOWN;
	nSpeed=10;
	nSpeed=10;
	for(int i=0;i<3;i++)
	{
		vSnakeBody.push_back(pt);
		pt.x+=nBodyWidth;
	}
}
int CSnakeBody::GetBodyRect(int nIndex,RECT &bodyRect)
{
	if (nIndex>GetBodyLong())
	{
		return -1;
	}
	POINT pt=vSnakeBody[nIndex];
	bodyRect.left=pt.x;
	bodyRect.top=pt.y;
	bodyRect.right=pt.x+nBodyWidth;
	bodyRect.bottom=pt.y+nBodyHeight;
	return 0;
}
void CSnakeBody::GetLastBodyRect(RECT &rect)
{
	if (lastPos.x == 0 && lastPos.y == 0)
	{
		rect.left=0;
		rect.bottom=0;
		rect.right=0;
		rect.top=0;
	}
	rect.left=lastPos.x;
	rect.top=lastPos.y;
	rect.right=lastPos.x+nBodyWidth;
	rect.bottom=lastPos.y+nBodyHeight;
}
void CSnakeBody::GetHeadRect(RECT &rect)
{
	GetBodyRect(0,rect);
}
void CSnakeBody::SetWallRect(RECT rectWall)
{
	this->rectWall=rectWall;
}
void CSnakeBody::SetSpeed(int nSpeed)
{
	this->nSpeed=nSpeed;
	
}
void CSnakeBody::AddBody()
{
	POINT pt=vSnakeBody[GetBodyLong()-1];
	vSnakeBody.push_back(pt);
}
vector<POINT> CSnakeBody::GetSnakeBody()
{
	return vSnakeBody;
}
void CSnakeBody::ClearBoy()
{
	vSnakeBody.clear();
}
void CSnakeBody::SetHeadDir(int nDir)
{
	if (nHeadDirction==DIRLEFT&&nDir==DIRRIGHT)
	{
		return;
	}
	if (nHeadDirction==DIRRIGHT&&nDir==DIRLEFT)
	{
		return;
	}
	if (nHeadDirction==DIRDOWN&&nDir==DIRUP)
	{
		return;
	}
	if (nHeadDirction==DIRUP&&nDir==DIRDOWN)
	{
		return;
	}
	nHeadDirction=nDir;
}
int CSnakeBody::GetBodyLong()
{
	return vSnakeBody.size();
}
POINT CSnakeBody::GetSnakePoing(int nIndex)
{
	return vSnakeBody[nIndex];
}
void CSnakeBody::RectToSnakeRect(RECT rect,SnakeRect &snake)
{
	snake.lx=rect.left;
	snake.ly=rect.top;
	snake.rx=rect.right;
	snake.ry=rect.bottom;
}
int CSnakeBody::GetSnakeLife()
{
	if (nLife==0)
	{
		return 0;
	}
	if (nLife>0)
	{
		return 1;
	}
}
void CSnakeBody::SetSnakeLife(int nLife)
{
	this->nLife=nLife;
}