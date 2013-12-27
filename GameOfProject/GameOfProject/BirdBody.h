#pragma once
#include "StructSet.h"
class CBirdBody
{
public:
	CBirdBody(void);
	CBirdBody(int pos_x,int pos_y,int nBirdWidth,int nBirdHeight,int lx,int ly,int rx,int ry);
	CBirdBody(int pos_x,int pos_y,int nBirdWidth,int nBirdHeight,RECT rect);
	~CBirdBody(void);
	void GetBirdRect(RECT &rect);
	RECT GetBirdRect();
	void SetBirdPos(POINT birdPos);
	int GetBirdLife()
	{
		return nBirdLife;
	}
	int SetSnakeLife(int nLife);
	void SetBirdLife(int nLife);
	int MoveBirdPos();
	void SetRectWall(RECT rect);
	void SetRectWall(int lx,int ly,int rx,int ry);
	void RetBirdPos();
	BOOL HasHitBird(vector<GunInfo> vGun,int nWidth,int nHeight);
	void SetBirdSpeed(double nSpeed)
	{
		this->nSpeed=(double)nSpeed;
	}
	void ChangeBirdSpeed(BOOL bAddSign,double nChangeSpeed);
	void MoveBird(BOOL bAddSign,int nChangeSpeed)
	{
		ChangeBirdSpeed(bAddSign,nChangeSpeed);
		MoveBirdPos();
	}
	BOOL HasHitWall();
	double GetBirdSpeed()
	{
		return nSpeed;
	}
private:
	POINT birdPos;
	int   nBirdWidth;
	int   nBirdHeight;
	double   nSpeed;
	int   nBirdLife;
	RECT  rectWall;
};
