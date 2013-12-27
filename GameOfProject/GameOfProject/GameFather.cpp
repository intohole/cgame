#include "StdAfx.h"
#include "GameFather.h"

CGameFather::CGameFather(void)
{
	dwScore=0;
	nTimerID=0;
}

CGameFather::~CGameFather(void)
{
}
int CGameFather::SetGameTimer(int TimerID,long dDelayTime)
{
	int nID;
	map<int,int>::iterator it;
	for (it=mapTimerID.begin();it!=mapTimerID.end();it++)
	{
		if (it->first == TimerID)
		{
			KillTimer(m_hWnd,TimerID);
			it->second=-1;
		}
	}
	nID=SetTimer(m_hWnd,TimerID,dDelayTime,NULL);
	if (nID!=0)
	{
		mapTimerID.insert(make_pair(TimerID,nID));
	}
	return nTimerID;
}
int CGameFather::KillGameTimer(int nIndexTimer)
{
	
	map<int,int>::iterator it;
	for (it=mapTimerID.begin();it!=mapTimerID.end();it++)
	{
		if (it->first == nIndexTimer&& it->second != -1)
		{
			KillTimer(m_hWnd,nIndexTimer);
			it->second=-1;
		}
	}
	return 1;
}
int CGameFather::KillAllTimer()
{
	map<int,int>::iterator it;
	for(it=mapTimerID.begin();it!=mapTimerID.end();it++)
	{
		if (it->second!=-1&&it->second!=0)
		{
			KillTimer(m_hWnd,it->second);
		}
	}
	mapTimerID.clear();
	return 0;
}
int CGameFather::GetTimerID(int nIndexID)
{
	map<int,int>::iterator it;
	for(it=mapTimerID.begin();it!=mapTimerID.end();it++)
	{
		if (it->first==nIndexID)
		{
			if (it->second>0)
			{
				return it->second;
			}
		}
	}
	return -1;
}
int CGameFather::GameOver(int nIndex)
{
	
	switch(nIndex)
	{
		case 1:
			break;
		case 2:
			KillAllTimer();
			ShowCursor(TRUE);	
			break;
		default:
			break;
	}
	return 0;
}
void CGameFather::GetGameCurSorPos(POINT &pt)
{
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd,&pt);
}