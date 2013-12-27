#pragma once
#include "StructSet.h"
class CFishControl
{
public:
	CFishControl(void);
	CFishControl(int nSpeedMaxX,int nSpeedMaxY,int nSpeedMinX,int nSpeedMinY,int nWidth,int nHeight,int nLife,int nMinLine,RECT rect);
	~CFishControl(void);
	void SetFishWH(int nWidth,int nHeight);
	void SetWallRect(RECT rect);
	void SetSpeedXY(int nMaxX,int nMaxY,int nMinX,int nMinY);
	void Move();
	void HasHitWall();
	int RandSpeed(int nValue);
	void InitFishInfo(FISHINFO &stFish,int nLife);
	void SetWaterLine(int nLine);
	int RandSpeedX();
	int RandSpeedY();
	void SetFishLife(int nLife);
	int GetFishSum()
	{
		return listFishSave.size();
	}
	int HasHitGun(list<POINT> &listGunSave,int nWidth,int nHeight);
	void GetFishRectWith(int nIndex,RECT &rect);
	POINT CreatePos();
	void AddFish();
private:
	list<FISHINFO> listFishSave;
	SpeedStruct stSpeed;
	int nFishWidth;
	int nFishHeight;
	RECT rectWall;
	int nWaterLine;
	int nFishLife;
};
