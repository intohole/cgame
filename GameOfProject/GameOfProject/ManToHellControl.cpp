#include "StdAfx.h"
#include "ManToHellControl.h"
#include "TimerIDDefine.h"
#include "GameTools.h"

CManToHellControl::CManToHellControl(void)
{
	RECT hitWall;
	CGameTools::SetRectWith(10,10,430,340,rectWall);
	CGameTools::SetRectWith(-20,-20,460,370,hitWall);
	ptMouse.x=200;
	ptMouse.y=170;
	isStart=FALSE;
	personControl=new CPersonControl(200,170,10,rectWall);
	POINT pPos;
	pPos.x=200;
	pPos.y=170;
	armyControl=new CArmyControl(10,5,7,7,pPos,rectWall,hitWall);
	dwArmyDrawColor=RGB(230,150,170);
}

CManToHellControl::~CManToHellControl(void)
{
}

int CManToHellControl::GameOnPaint(CDC *pDc)
{
	RECT rect;
	pDc->FillSolidRect(&rectWall,dwBKColor); 
	DrawPerSon();
	DrawArmy(dwArmyDrawColor);
	return 3;
}
int CManToHellControl::OnGameTimer(UINT_PTR nIDEvent)
{
	if (GetTimerID(MANMOVETIMER) == nIDEvent)
	{
		ClearPerson();
		personControl->SetPersonPos(ptMouse);
		if (personControl->HasHitGun(armyControl->GetArmySave(),armyControl->GetArmyRaduis()))
		{
			GameOver(2);
		}
		DrawPerSon();
		DrawArmy(dwBKColor);
		armyControl->ArmyMove();
		if(armyControl->HasHitPerson(ptMouse,personControl->GetPersonRadius()))
		{
			GameOver(2);
		}
		DrawArmy(dwArmyDrawColor);
		IncreaseScore(1);
	}
	else if (GetTimerID(MANLEVELTIMER))
	{
		armyControl->AddArmy();
	}	
	return 3;
}
int CManToHellControl::GameOnMouseMove(UINT nFlags, CPoint point)
{
	if (isStart)
	{
		ptMouse=point;
	}
	
	return 3;
}
int CManToHellControl::StartGame()
{
	SetGameTimer(MANMOVETIMER,1000/24);
	SetGameTimer(MANLEVELTIMER,3000);
	isStart=TRUE;
	return 3;
}
void CManToHellControl::ClearPerson()
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT pRect=personControl->GetPersonRect();
	pLastBrush->CreateSolidBrush(RGB(40,150,40));
	SelectObject (*pDc, GetStockObject (NULL_PEN));
	pOldBrush=pDc->SelectObject(pLastBrush);
	pDc->Ellipse(&pRect);
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
	
		
}
void CManToHellControl::DrawPerSon()
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
 	RECT pRect=personControl->GetPersonRect();
	pLastBrush->CreateSolidBrush(RGB(255,0,255));
	SelectObject(*pDc,GetStockObject(NULL_PEN));
	pOldBrush=pDc->SelectObject(pLastBrush);
	pDc->Ellipse(&pRect);
	DeleteObject(*pLastBrush);
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
}
void CManToHellControl::DrawArmy(unsigned long dwArmyColor)
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT pRect;
	pLastBrush->CreateSolidBrush(dwArmyColor);
	SelectObject(*pDc,GetStockObject(NULL_PEN));
	pOldBrush=pDc->SelectObject(pLastBrush);
	for (int i=0;i<armyControl->GetArmyNum();i++)
	{
		if (!armyControl->GetArmyHide(i))
		{
			armyControl->GetArmyRect(i,pRect);
			pDc->Ellipse(&pRect);
		}
		
	}
	DeleteObject(*pLastBrush);
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
}
int CManToHellControl::PauseGame(BOOL bPause)
{
	if (bPause)
	{
		KillAllTimer();
	}
	else
	{
		SetGameTimer(MANMOVETIMER,1000/24);
		SetGameTimer(MANLEVELTIMER,3000);
		isStart=TRUE;
	}
	return 2;
}
int CManToHellControl::ReStartGame()
{
	return 2;
}