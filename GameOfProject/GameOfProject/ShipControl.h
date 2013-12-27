#pragma once

class CShipControl
{
public:
	CShipControl(void);
	CShipControl(POINT pos,RECT wallRect,int nWidht,int nHeight);
	~CShipControl(void);
	RECT GetShipRect();
	void SetShipPos(POINT pos);
	void SetRectWall(RECT rect);
	void SetWaterLine(int nSet);
	void SetShipCanPutGun(BOOL bSign);
	int GetShipHeight();
	BOOL GetShipCanPutGun()
	{
		return bCanPutGun;
	}
private:
	int nShipWidth;
	int nShipHeight;
	RECT rectWall;
	POINT shipPos;
	BOOL bCanPutGun;//可以投放子弹吗
	int nWaterLine;
};
