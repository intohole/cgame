#pragma once
#include "StructSet.h"
#include "StructSet.h"
class CGameFather
{
public:
	CGameFather(void);
	~CGameFather(void);
	virtual int GameOnLButtonDown(UINT nFlags, CPoint point)
	{
		return 0;
	}
	virtual int GameOnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		return 0;
	}
	virtual int GameOnPaint(CDC *pDc)
	{
		return 0;
	}

	virtual int OnGameTimer(UINT_PTR nIDEvent)
	{
		return 0;
	}
	virtual int StartGame()=0;
	virtual int ReStartGame()=0;
	virtual int PauseGame(BOOL bPause)=0;
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return 0;
	}
	virtual int GameOnLButtonUp(UINT nFlags, CPoint point)
	{
		return 0;
	}
	virtual int GameOnMouseMove(UINT nFlags, CPoint point)
	{
		return 0;
	}
	int GameOver(int nIndex);
	int SetGameTimer(int TimerID,long dDelayTime);
	int KillGameTimer(int TimerID);
	int KillAllTimer();
	int GetTimerID(int nIndexID);
	void SetScore(CString &strScore)
	{
		strScore.Format("ตรทึ: %d",dwScore);
	}
	void IncreaseScore(long score)
	{
		dwScore+=score;
	}
	void DecreaseScore(long score)
	{
		dwScore-=score;
	}
	void SetHWnd(HWND hWnd)
	{
		m_hWnd=hWnd;
	}
	void SetCDC(CDC *pDc)
	{
		this->pDc=pDc;
	}
	void SetGameBkColor(unsigned long dwColor)
	{
		dwBKColor=dwColor;
	}
	void GetGameCurSorPos(POINT &pt);
protected:
	unsigned long dwScore;
	CDC *pDc;
	HWND m_hWnd;
	int nTimerID;
	map<int,int> mapTimerID;
	unsigned long dwBKColor;
};
