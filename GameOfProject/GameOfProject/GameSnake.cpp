#include "StdAfx.h"
#include "GameSnake.h"

CGameSnake::CGameSnake(void)
{
	rectWall.left=10;
	rectWall.top=10;
	rectWall.right=430;
	rectWall.bottom=340;
	snakeBody=new CSnakeBody(rectWall,10,10,DIRDOWN,10);
	snakeFood=new CSnakeFood(rectWall,10,10);
	dwSankeColor= RGB(0,255,10);
	dwFoodColor = RGB(0,255,255);
	dwSnakeHead= RGB(130,0,0);
}

CGameSnake::~CGameSnake(void)
{
}
int CGameSnake::GameOnPaint(CDC *pDc)
{
	RECT rect;
	pDc->FillSolidRect(&rectWall,RGB(40,150,40)); 
	DrawHead(dwSnakeHead);
	DrawBody(dwSankeColor);	
	if (snakeFood->GetHaveFood())
	{
		DrawFood(dwFoodColor);
	}
	return 1;
}
int CGameSnake::GameOnLButtonDown(UINT nFlags, CPoint point)
{
	return 1;
}
int CGameSnake::GameOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)
	{
	case VK_UP:snakeBody->SetHeadDir(DIRUP);break; 
	case VK_DOWN:snakeBody->SetHeadDir(DIRDOWN);break;
	case VK_LEFT:snakeBody->SetHeadDir(DIRLEFT);break;  
	case VK_RIGHT:snakeBody->SetHeadDir(DIRRIGHT);break;  
	}
	return 1;
}
int CGameSnake::OnGameTimer(UINT_PTR nIDEvent)
{
	
	if (!snakeFood->GetHaveFood())
	{
		snakeFood->SetFoodPos(snakeBody->GetSnakeBody());
		snakeFood->SetHaveFood(TRUE);
		DrawFood(dwFoodColor);
	}
	
	DrawBody(dwBKColor);
	DrawHead(dwBKColor);
	snakeBody->MoveBody();
	snakeBody->MoveHead();
	DrawBody(dwSankeColor);
	DrawHead(dwSnakeHead);
	if (snakeBody->HasHitMyself()||snakeBody->HasHitWall())
	{
		KillGameTimer(GetTimerID(SNAKETIMER));
	}
	if (snakeFood->HaveEatFood(snakeBody->GetSnakePoing(0)))
	{
		snakeFood->SetHaveFood(FALSE);
		DrawFood(dwBKColor);
		snakeBody->AddBody();
		IncreaseScore(10);	
	}
	return 1;
}
void CGameSnake::DrawHead(unsigned long dwColor)
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT headRect;
	snakeBody->GetHeadRect(headRect);
	pLastBrush->CreateSolidBrush(dwColor);
	SelectObject(*pDc,GetStockObject(NULL_BRUSH));
	pOldBrush=pDc->SelectObject(pLastBrush);
	pDc->Rectangle(&headRect);
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
	
}
void CGameSnake::DrawBody(unsigned long dwColor)
{
	CBrush * pNewBrush;
	CBrush * pOldBrush;
	pNewBrush=new CBrush;
	pNewBrush->CreateSolidBrush(dwColor);
	SelectObject(*pDc,GetStockObject(NULL_BRUSH));
	pOldBrush=pDc->SelectObject(pNewBrush);
	RECT rectBody;
	for(int i=1;i<snakeBody->GetBodyLong();i++)
	{
		snakeBody->GetBodyRect(i,rectBody);
		pDc->Rectangle(&rectBody);
	}
	delete pNewBrush;
	pDc->SelectObject(pOldBrush);
	
}
void CGameSnake::DrawFood(unsigned long dwColor)
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT foodRect;
	snakeFood->GetFoodRect(foodRect);
	pLastBrush->CreateSolidBrush(dwColor);
	pOldBrush=pDc->SelectObject(pLastBrush);
	pDc->Rectangle(&foodRect);
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
}
void CGameSnake::ClearLast()
{
	CBrush *pLastBrush=new CBrush;
	CBrush *pOldBrush;
	RECT lastRect;
	snakeBody->GetLastBodyRect(lastRect);
	pLastBrush->CreateSolidBrush(dwBKColor);
	pOldBrush=pDc->SelectObject(pLastBrush);
	pDc->Rectangle(&lastRect);
	delete pLastBrush;
	pDc->SelectObject(pOldBrush);
}
int CGameSnake::StartGame()
{
	
	SetGameTimer(SNAKETIMER,300);
	SetFocus(m_hWnd);
	return 1;
}
BOOL CGameSnake::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if ('A'==pMsg->wParam)
		{
			snakeBody->SetHeadDir(DIRLEFT);
			return TRUE;
		}
		if ('D'==pMsg->wParam)
		{
			snakeBody->SetHeadDir(DIRRIGHT);
			return TRUE;
		}
		if ('S'==pMsg->wParam)
		{
			snakeBody->SetHeadDir(DIRDOWN);
			return TRUE;
		}
		if ('W'==pMsg->wParam)
		{
			snakeBody->SetHeadDir(DIRUP);
			return TRUE;
		}
	} 
	
}
int CGameSnake::PauseGame(BOOL bPause)
{
	if (bPause)
	{
		KillGameTimer(SNAKETIMER);
	}
	else
	{
		SetGameTimer(SNAKETIMER,300);
	}
	return 1;
}
int CGameSnake::ReStartGame()
{
	return 1;
}
