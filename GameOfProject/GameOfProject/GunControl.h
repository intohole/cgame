#pragma once
#include "StructSet.h"
class CGunControl
{
public:
	CGunControl(void);
	CGunControl(int nLimit,int Speed,int nMax,int nWidth,int nHeight,RECT rect);
	~CGunControl(void);
	void InitGunPos();
	void AddHardLevel();
	void ReSetGunPos();
	POINT GetRandGunPos();
	int GetGunRect(int nIndex,RECT &rect);
	void MoveGun();
	vector<GunInfo> GetGunArry()
	{
		return vGunSave;
	}
	int GetGunLong()
	{
		return vGunSave.size();
	}
	int HasHitWall();
	void SetMaxGun(int nMax);
	void SetGunWH(int nWidth,int nHeight);
	int GetGunWidth(){return nGunWidth;};
	int GetGunHight(){return nGunHeight;};
	void SetGunSpeed(int nSpeed);
	void SetLimitNum(int nLimit);
	void SetRectWall(RECT rectWall);
	BOOL GetGunHide(int nIndex)
	{
		return vGunSave[nIndex].bIsHide;
	}
	BOOL HasHitBird(RECT rectBird);

private:
	vector<GunInfo> vGunSave;
	int nSpeed;
	int nMaxGun;
	int nLimitNum;
	RECT rectWall;
	int nGunWidth;
	int nGunHeight;

};
