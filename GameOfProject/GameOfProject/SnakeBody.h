#pragma once
#include "StructSet.h"
class CSnakeBody
{
public:
	CSnakeBody(void);
	CSnakeBody(RECT rectWall,int nBodyHeight,int nBodyWidth,int nHeadDirction,int nSpeed);
	~CSnakeBody(void);
	BOOL MoveBody();
	BOOL HasHitWall();
	void MoveHead();
	BOOL HasHitMyself();
	void GetLastBodyRect(RECT &rect);
	void GetHeadRect(RECT &rect);
	void SetWallRect(RECT rectWall);
	void SetSpeed(int nSpeed);
	void AddBody();
	vector<POINT> GetSnakeBody();
	void ClearBoy();
	void SetHeadDir(int nDir);
	int GetBodyLong();
	POINT GetSnakePoing(int nIndex);
	void InitSnakeBody();
	int GetBodyRect(int nIndex,RECT &bodyRect);
	void RectToSnakeRect(RECT rect,SnakeRect &snake);
	int GetSnakeLife();
	void SetSnakeLife(int nLife);
private:
	int nHeadDirction;
	RECT rectWall;
	int nBodyWidth;
	int nBodyHeight;
	POINT lastPos;
	vector<POINT> vSnakeBody;
	int nSpeed;
	int nLife;
};
