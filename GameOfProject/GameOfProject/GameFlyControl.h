#include "GameFather.h"
#include "BirdBody.h"
#include "GunControl.h"
#include "TimerIDDefine.h"
#pragma once

class CGameFlyControl
	:public CGameFather
{
public:
	CGameFlyControl(void);
	~CGameFlyControl(void);
	virtual int GameOnLButtonDown(UINT nFlags, CPoint point);
	virtual int GameOnPaint(CDC *pDc);
 	virtual int OnGameTimer(UINT_PTR nIDEvent);
	virtual int StartGame();
	virtual int ReStartGame();
	virtual int PauseGame(BOOL bPause);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int GameOnLButtonUp(UINT nFlags, CPoint point);
	void SetBGColor(unsigned long dwBirdColor,unsigned long dwGunColor)
	{
		this->dwBirdColor=dwBirdColor;
		this->dwGunColor=dwGunColor;
	}
private:
	void DrawGunBody(unsigned long dwRGB);
	void DrawBirdBody(unsigned long dwRGB);
	void ClearLast();
private:
	int nHardLevel;
	RECT rectWall;
	CBirdBody *birdBody;
	CGunControl *gunControl;
	BOOL bLButtonDown;
	BOOL bIsAddStat;
	int nChangespeed;
	unsigned long dwBirdColor;
	unsigned long dwGunColor;
};
