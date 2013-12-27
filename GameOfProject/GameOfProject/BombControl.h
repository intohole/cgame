#pragma once
#include "StructSet.h"
class CBombControl
{
public:
	CBombControl(void);
	CBombControl(int nSpeed,int nWidth,int nHeight,RECT rect);
	~CBombControl(void);
	void AddGun(POINT pos);
	void SetSpeed(int nSpeed);
	void SetGunWH(int nWidth,int nHeight);
	void GetGunRect(int nIndex,RECT &rect);
	int GetGunSum();
	void GunMove();
	list<POINT> GetListGunSave()
	{
		return listGunSave;
	}
	void ReSetGame();
	void HasHitWall();
	int GetGunWidth()
	{
		return nGunWidth;
	}
	int GetGunHeight()
	{
		return nGunHeight;
	}
private:
	int nGunSpeed;
	int nGunWidth;
	int nGunHeight;
	RECT rectWall;
	list<POINT> listGunSave;
};
