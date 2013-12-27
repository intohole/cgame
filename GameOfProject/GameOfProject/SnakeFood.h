#pragma once
#include <vector>
using namespace std;
class CSnakeFood
{
public:
	CSnakeFood(void);
	CSnakeFood(RECT rectWall,int foodWidth,int foodHeight);
	~CSnakeFood(void);
	BOOL GetHaveFood();
	void SetHaveFood(BOOL bSignFood);
	BOOL SetFoodPos(vector<POINT> vPos);
	POINT RandPos();
	POINT GetFoodPos();
	void SetWallRect(RECT rectWall);
	void GetFoodRect(RECT &rect);
	BOOL HaveEatFood(POINT pt);
private:
	BOOL bHaveFood;
	RECT rectWall;
	POINT posFood;
	int foodWidth;
	int foodHeight;
};
