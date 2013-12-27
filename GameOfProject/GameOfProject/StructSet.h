#pragma once
#include <vector>
#include <list>
#include <map>
using namespace std;
enum
{
	DIRUP=1,
	DIRDOWN=2,
	DIRLEFT=3,
	DIRRIGHT=4
};
typedef struct SnakeBoyRect
{
	int lx;//左上角
	int ly;//左上角
	int rx;//右下角
	int ry;//右下角
}SnakeRect;
typedef struct GUNINFOMATION
{
	POINT GunPos;
	BOOL  bIsHide;
	int GunSpeed;
	GUNINFOMATION()
	{
		GunPos.x=GunPos.y=-1;
		bIsHide=FALSE;
		GunSpeed=-1;
	}
}GunInfo;
//男人就下100  敌人结构体
typedef struct ARMYINFOMATION
{
	POINT pos;
	int nSpeedX;
	int nSpeedY;
	BOOL bHideSign;
	ARMYINFOMATION()
	{
		pos.x=pos.y=-1;
		nSpeedY=nSpeedX=-1;
		bHideSign=TRUE;
	}
}ArmyInfo;
typedef struct MANSPEEDSTRUCT
{
	int MaxX;
	int MaxY;
	int MinX;
	int MinY;
}SpeedStruct;
typedef struct FISHINFOSTRUCT
{
	POINT pos;
	int nSpeedX;
	int nSpeedY;
	int nLife;//》0 鱼的生命值 =0 死亡
}FISHINFO;
typedef struct STRUCTINIKEYINFO 
{
	CString strKey;
	CString strValue;
	CString strComment;
}INIKEYINFO;