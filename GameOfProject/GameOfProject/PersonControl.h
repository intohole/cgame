#pragma once
#include "StructSet.h"
class CPersonControl
{
public:
	CPersonControl(void);
	CPersonControl(int pos_x,int pos_y,int nR,RECT rect);
	~CPersonControl(void);
	void SetPersonPos(POINT pt);
	void SetPersonPos(int lx,int ly);
	void SetPersonradius(int nRadius);
	RECT GetPersonRect();
	int MovePerson(POINT pt);
	void SetRectWall(int lx,int ly,int rx,int ry);
	void SetRectWall(RECT rect);
	BOOL HasHitWall();
	BOOL HasHitGun(vector<ArmyInfo> vArmy,int nArmyRadius);
	void ResetPerson(POINT pt);
	int GetPersonRadius()
	{
		return nRadius;
	}
private:
	POINT personPos;
	int   nRadius;
	int   nPersonSpeedX;
	int   nPersonSpeedY;
	RECT  rectWall;//Åö×²Õâ¸öÇ½ 

};
