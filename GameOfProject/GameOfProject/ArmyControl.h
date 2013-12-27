#pragma once
#include "StructSet.h"
class CArmyControl
{
public:
	CArmyControl(void);
	CArmyControl(int level,int nRadius,int speedMaxX,int speedMaxY,POINT pPos,RECT rWall,RECT HitWall);
	~CArmyControl(void);
	int GetArmyNum()
	{
		return vArmySave.size();
	}
	void AddArmy();
	void AddArmy(POINT pPos);
	int GetArmyRect(int nIndex,RECT &rect);
	POINT CreatPos(POINT pt);
	/*ArmyInfo CreateArmy();*/
	void ArmyMove();
	void SetLevel(int nLevel);
	BOOL HasHitPerson(POINT pos,int nRadius);
	void HasHitRectWall(ArmyInfo &stArmyInfo);
	void HasHitHitWall(ArmyInfo &stArmyInfo);
	void SetRadius(int nRaduis);
	void InitArmy();
	void SetSpeedMax(int nMaxX,int nMaxY);
	void InitArmyInfo(ArmyInfo &stArmyInfo);
	int RandSpeed(int nMax);
	BOOL GetArmyHide(int nIndex);
	vector<ArmyInfo> GetArmySave()
	{
		return vArmySave;
	}
	int GetArmyRaduis()
	{
		return nSelfRaduis;
	}
private:
	vector<ArmyInfo> vArmySave;
	RECT rectWall;//在这个墙外面的均不显示
	RECT rectHitWall;//这个是碰撞墙
	int nLevel;
	int nSelfRaduis;
	int nSpeedXMax;
	int nSpeedYMax;
	POINT personPoint;
};
