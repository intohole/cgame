#pragma once
#include "StructSet.h"
class CGameTools
{
public:
	CGameTools(void);
	~CGameTools(void);
	static int GetRand(int nMin,int nMax);
	static BOOL RectInRect(RECT rect1,RECT rect2);
	static int MakeRect(POINT pt,int nWidth,int nHeight,RECT &rect);
	static void copyRect(RECT &rectDest,RECT &rectOri);
	static BOOL CireleHitCirele(POINT pos1,POINT pos2,int nRadius1,int nRadius2);
	static RECT CireleToRect(POINT pos,int nRadius);
	static BOOL SetPosInRect(POINT pos,RECT rect,int nRadius);
	static long PointDistance(POINT pos1,POINT pos2);
	static int  PointHitRect(POINT pt,int nRadius,RECT rect);
	static void SetRectWith(int left,int top,int right,int bottom,RECT &rect);
	static HRESULT  ShowPic(TCHAR*   lpstrFile,   HWND   hWnd,   int   nScrWidth,   int   nScrHeight);
	static RECT GetRectWith(POINT pos,int nWidth,int nHeight);
	static BOOL PointInRect(POINT pos,RECT rect);
	static POINT GetRectCentre(RECT rect);
	static vector<CString> GetAllGameName();
	static CString GetIniPathName();
};
