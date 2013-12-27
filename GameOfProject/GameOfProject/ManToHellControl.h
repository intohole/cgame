#pragma once
#include "GameFather.h"
#include "PersonControl.h"
#include "ArmyControl.h"

class CManToHellControl
	:public CGameFather
{
public:
	CManToHellControl(void);
	~CManToHellControl(void);
// 	virtual int GameOnLButtonDown(UINT nFlags, CPoint point);
// 	virtual int GameOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
 	virtual int GameOnPaint(CDC *pDc);
 	virtual int OnGameTimer(UINT_PTR nIDEvent);
 	virtual int StartGame();
	virtual int GameOnMouseMove(UINT nFlags, CPoint point);
	virtual int ReStartGame();
	virtual int PauseGame(BOOL bPause);
// 	virtual BOOL PreTranslateMessage(MSG* pMsg);
// 	virtual int GameOnLButtonUp(UINT nFlags, CPoint point);
private:
	void DrawPerSon();
	void ClearPerson();
	void DrawArmy(unsigned long dwArmyColor);
	CPersonControl *personControl;
	CArmyControl *armyControl;
	RECT rectWall;
	POINT ptMouse;
	BOOL isStart;
	unsigned long dwArmyDrawColor;
};
