#include "StdAfx.h"
#include "GameFlyControl.h"

CGameFlyControl::CGameFlyControl(void)
{
	rectWall.left=10;
	rectWall.top=10;
	rectWall.right=430;
	rectWall.bottom=340;
	birdBody= new CBirdBody(50,150,30,30,rectWall);
	birdBody->SetBirdSpeed(5);
	nHardLevel=2;
	gunControl=new CGunControl(24,8,2,10,10,rectWall);
	bLButtonDown=FALSE;
	bIsAddStat=TRUE;
	SetBGColor(RGB(0,255,255),RGB(255,0,10));
}

CGameFlyControl::~CGameFlyControl(void)
{
}
int CGameFlyControl::GameOnLButtonDown(UINT nFlags, CPoint point)
{
	bIsAddStat=!bIsAddStat;
	bLButtonDown=TRUE;
		
	return 2;
}
int CGameFlyControl::GameOnLButtonUp(UINT nFlags, CPoint point)
{
	bIsAddStat=!bIsAddStat;
	bLButtonDown=FALSE;
	
	return 2;
}
int CGameFlyControl::GameOnPaint(CDC *pDc)
{
	RECT rect;
	pDc->FillSolidRect(&rectWall,RGB(40,150,40)); 
	DrawBirdBody(dwBirdColor);
	DrawGunBody(dwGunColor);
	return 2;
}

int CGameFlyControl::OnGameTimer(UINT_PTR nIDEvent)
{

	int nTimer1=GetTimerID(BIRDMOVETIMER);
	int nTimer2=GetTimerID(BIRDFLYLEVELTIMER);
	if (nIDEvent == nTimer1)
	{
		DrawBirdBody(RGB(40,150,40));
		birdBody->MoveBirdPos();
		DrawBirdBody(dwBirdColor);
		if(birdBody->HasHitWall())
		{
				KillAllTimer();
				return -2;
		}
		if (birdBody->HasHitBird(gunControl->GetGunArry(),gunControl->GetGunWidth(),gunControl->GetGunHight()))
		{
			KillAllTimer();
			return -2;
		}
		ClearLast();
		DrawGunBody(RGB(40,150,40));
		gunControl->MoveGun();
		DrawGunBody(dwGunColor);
		if (gunControl->HasHitBird(birdBody->GetBirdRect()))
		{
			KillAllTimer();
			return -2;
		}
		IncreaseScore(1);
		gunControl->HasHitWall();
		gunControl->ReSetGunPos();
	}
	if (nIDEvent == nTimer2)
	{
		
			if (nHardLevel<21)
			{
				nHardLevel++;
				gunControl->SetMaxGun(nHardLevel);
			}
	}
	if (nIDEvent==GetTimerID(GUNMOVETIMER))
	{
		birdBody->ChangeBirdSpeed(bLButtonDown,0.6);
	}
		
	
	return 2;
}
int CGameFlyControl::StartGame()
{
	SetGameTimer(BIRDMOVETIMER,100);
	SetGameTimer(BIRDFLYLEVELTIMER,18000);
	SetGameTimer(GUNMOVETIMER,60);
	return 2;
}
BOOL CGameFlyControl::PreTranslateMessage(MSG* pMsg)
{
	return TRUE;
}
void CGameFlyControl::DrawBirdBody(unsigned long dwRGB)
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT birdRect;
	birdBody->GetBirdRect(birdRect);
	pLastBrush->CreateSolidBrush(dwRGB);
	SelectObject(*pDc,GetStockObject(NULL_PEN));
	pOldBrush=pDc->SelectObject(pLastBrush);
	pDc->Rectangle(&birdRect);
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
}
void CGameFlyControl::DrawGunBody(unsigned long dwRGB)
{
	CBrush * pNewBrush;
	CBrush * pOldBrush;
	pNewBrush=new CBrush;
	pNewBrush->CreateSolidBrush(dwRGB);
	SelectObject(*pDc,GetStockObject(NULL_PEN));
	pOldBrush=pDc->SelectObject(pNewBrush);
	RECT rectBody;
	for(int i=0;i<gunControl->GetGunLong();i++)
	{
		if (!gunControl->GetGunHide(i))
		{
			gunControl->GetGunRect(i,rectBody);
			pDc->Rectangle(&rectBody);
		}	
	}
	delete pNewBrush;
	pDc->SelectObject(pOldBrush);
}
// void CGameFlyControl::ClearBirdBody()
// {
// 	CBrush *pLastBrush=new CBrush;
// 	CBrush *pOldBrush;
// 	RECT birdRect;
// 	birdBody->GetBirdRect(birdRect);
// 	pLastBrush->CreateSolidBrush(RGB(40,150,40));
// 	SelectObject(*pDc,GetStockObject(NULL_PEN));//创建无边框的
// 	pOldBrush=pDc->SelectObject(pLastBrush);
// 	pDc->Rectangle(&birdRect);
// 	delete pLastBrush;
// 	pDc->SelectObject(pOldBrush);
// }
// void CGameFlyControl::CleadGunBody()
// {
// 	CBrush * pNewBrush;
// 	CBrush * pOldBrush;
// 	pNewBrush=new CBrush;
// 	pNewBrush->CreateSolidBrush(RGB(40,150,40));
// 	SelectObject(*pDc,GetStockObject(NULL_PEN));
// 	pOldBrush=pDc->SelectObject(pNewBrush);
// 	RECT rectBody;
// 	for(int i=0;i<gunControl->GetGunLong();i++)
// 	{
// 		if (!gunControl->GetGunHide(i))
// 		{
// 			gunControl->GetGunRect(i,rectBody);
// 			pDc->Rectangle(&rectBody);
// 		}	
// 	}
// 	delete pNewBrush;
// 	pDc->SelectObject(pOldBrush);
// }
void CGameFlyControl::ClearLast()
{
	CBrush * pNewBrush;
	CBrush * pOldBrush;
	pNewBrush=new CBrush;
	pNewBrush->CreateSolidBrush(RGB(40,150,40));
	SelectObject(*pDc,GetStockObject(NULL_PEN));
	pOldBrush=pDc->SelectObject(pNewBrush);
	RECT rect;
	rect.left=rectWall.left;
	rect.top=rectWall.top;
	rect.right=rect.left+13;
	rect.bottom=rectWall.bottom;
	pDc->Rectangle(&rect);
	delete pNewBrush;
	pDc->SelectObject(pOldBrush);
}
int CGameFlyControl::PauseGame(BOOL bPause)
{
	if (bPause)
	{
		KillAllTimer();
	}
	else
	{
		SetGameTimer(BIRDMOVETIMER,100);
		SetGameTimer(BIRDFLYLEVELTIMER,18000);
		SetGameTimer(GUNMOVETIMER,60);
	}
	return 2;
}
int CGameFlyControl::ReStartGame()
{
	return 2;
}
