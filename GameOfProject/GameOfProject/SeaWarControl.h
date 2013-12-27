#pragma once
#include "GameFather.h"
#include "ShipControl.h"
#include "BombControl.h"
#include "FishControl.h"
class CSeaWarControl
	:public CGameFather
{
public:
	CSeaWarControl(void);
	~CSeaWarControl(void);
	virtual int GameOnPaint(CDC *pDc);
	virtual int OnGameTimer(UINT_PTR nIDEvent);
	virtual int GameOnLButtonDown(UINT nFlags, CPoint point);
	virtual int StartGame();
	virtual int ReStartGame();
	virtual int PauseGame(BOOL bPause);
private:
	void DrawShip(unsigned long dwColor);
	void DrawGun(unsigned long dwColor);
	void DrawFish(unsigned long dwColor);
	RECT rectWall;
	unsigned long dwShipColor;
	unsigned long dwGunColor;
	unsigned long dwFishColor;
	CShipControl *shipControl;
	CBombControl *bombControl;
	CFishControl *fishControl;
	int nKillFishNum;
};
