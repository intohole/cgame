#pragma once
#include "gamefather.h"
#include "snakebody.h"
#include "SnakeFood.h"
#include "TimerIDDefine.h"
class CGameSnake :
	public CGameFather
{
public:
	CGameSnake(void);
	~CGameSnake(void);
	virtual int GameOnLButtonDown(UINT nFlags, CPoint point);
	virtual int GameOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual int GameOnPaint(CDC *pDc);
	virtual int OnGameTimer(UINT_PTR nIDEvent);
	virtual int StartGame();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int ReStartGame();
	virtual int PauseGame(BOOL bPause);
	virtual int GameOnLButtonUp(UINT nFlags, CPoint point)
	{
		return 1;
	}

private:
	void DrawHead(unsigned long dwColor);
	void ClearLast();
	void DrawBody(unsigned long dwColor);
	void DrawFood(unsigned long dwColor);
	unsigned long dwSankeColor;
	unsigned long dwFoodColor;
	unsigned long dwSnakeHead;
	RECT rectWall;
	CSnakeFood *snakeFood;
	CSnakeBody *snakeBody;
};
