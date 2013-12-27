#include "StdAfx.h"
#include "SeaWarControl.h"
#include "GameTools.h"
#include "TimerIDDefine.h"

CSeaWarControl::CSeaWarControl(void)
{
	POINT pt;
	pt.x=200;
	pt.y=80;
	CGameTools::SetRectWith(10,10,430,340,rectWall);
	dwShipColor=RGB(255,0,0);
	dwFishColor=RGB(255,255,0);
	shipControl=new CShipControl(pt,rectWall,30,10);
	bombControl=new CBombControl(5,10,10,rectWall);
	fishControl=new CFishControl(7,7,1,1,20,10,1,80+shipControl->GetShipHeight(),rectWall);
	
	dwGunColor=RGB(0,0,0);
}

CSeaWarControl::~CSeaWarControl(void)
{
}
int CSeaWarControl::GameOnPaint(CDC *pDc)
{
	RECT rect;
	pDc->FillSolidRect(&rectWall,RGB(40,150,40)); 
	DrawShip(dwShipColor);
	return 4;
}
int CSeaWarControl::GameOnLButtonDown(UINT nFlags, CPoint point)
{
	if (shipControl->GetShipCanPutGun())//ÄÜÍ¶µ¯
	{
		bombControl->AddGun(CGameTools::GetRectCentre(shipControl->GetShipRect()));
		shipControl->SetShipCanPutGun(FALSE);
	}
	return 4;
}
int CSeaWarControl::OnGameTimer(UINT_PTR nIDEvent)
{
	
		if(nIDEvent == GetTimerID(SHIPMOVETIMER))
		{
			POINT pt;
			int nTmp;
			GetGameCurSorPos(pt);
			if (!CGameTools::PointInRect)
			{
				ShowCursor(TRUE);
			}
			else
			{
				ShowCursor(FALSE);
			}
			DrawShip(dwBKColor);
			shipControl->SetShipPos(pt);
			DrawShip(dwShipColor);
			DrawGun(dwBKColor);
			bombControl->GunMove();
			nTmp=fishControl->HasHitGun(bombControl->GetListGunSave(),bombControl->GetGunWidth(),bombControl->GetGunHeight());
			if (nTmp>0)
			{
				GameOnPaint(pDc);
				IncreaseScore(20);
			}
			nKillFishNum+=nTmp;
			bombControl->HasHitWall();
			DrawGun(dwGunColor);
		}
		if(nIDEvent == GetTimerID(SHIPCANTAKEGUN))
		{
			shipControl->SetShipCanPutGun(TRUE);
			
		}
		if(nIDEvent == GetTimerID(FISHMOVETIMER))
		{	
			int nTmp=0;
			DrawFish(dwBKColor);
			fishControl->Move();
			nTmp=fishControl->HasHitGun(bombControl->GetListGunSave(),bombControl->GetGunWidth(),bombControl->GetGunHeight());
			if (nTmp>0)
			{
				GameOnPaint(pDc);
				IncreaseScore(20);
			}
			nKillFishNum+=nTmp;
			DrawFish(dwFishColor);
			fishControl->HasHitWall();
		}
		else if(nIDEvent==GetTimerID(FISHADDHARD))
		{
			fishControl->AddFish();
		}
		else if (nIDEvent == GetTimerID(FISHHARDADD))
		{
			fishControl->AddFish();
		}
		else if (nIDEvent == GetTimerID(FISHHARDADD2) )
		{
			fishControl->AddFish();
		}
		else
		{

		}
		
	return 4;
}
int CSeaWarControl::StartGame()
{
	SetGameTimer(SHIPMOVETIMER,43);
	SetGameTimer(SHIPCANTAKEGUN,500);
	SetGameTimer(FISHMOVETIMER,45);
	SetGameTimer(FISHADDHARD,3000);
	SetGameTimer(FISHHARDADD,5000);
	SetGameTimer(FISHHARDADD2,7000);
	ShowCursor(FALSE);
	nKillFishNum=0;
	return 4;
}
int CSeaWarControl::ReStartGame()
{
	return 4;
}
int CSeaWarControl::PauseGame(BOOL bPause)
{
	KillAllTimer();
	return 4;
}
void CSeaWarControl::DrawShip(unsigned long dwColor)
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT birdRect;
	birdRect=shipControl->GetShipRect();
	pLastBrush->CreateSolidBrush(dwColor);
	SelectObject(*pDc,GetStockObject(NULL_PEN));
	pOldBrush=pDc->SelectObject(pLastBrush);
	pDc->Rectangle(&birdRect);
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
}
void CSeaWarControl::DrawGun(unsigned long dwColor)
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT gunRect;
	
	pLastBrush->CreateSolidBrush(dwColor);
	SelectObject(*pDc,GetStockObject(NULL_PEN));
	pOldBrush=pDc->SelectObject(pLastBrush);

	for (int i=0;i<bombControl->GetGunSum();i++)
	{
		bombControl->GetGunRect(i,gunRect);
		pDc->Rectangle(&gunRect);
	}
	
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
}
void CSeaWarControl::DrawFish(unsigned long dwColor)
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT gunRect;

	pLastBrush->CreateSolidBrush(dwColor);
	SelectObject(*pDc,GetStockObject(NULL_PEN));
	pOldBrush=pDc->SelectObject(pLastBrush);

	for (int i=0;i<fishControl->GetFishSum();i++)
	{
		fishControl->GetFishRectWith(i,gunRect);
		pDc->Rectangle(&gunRect);
	}

	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
}