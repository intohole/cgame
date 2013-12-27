#include "StdAfx.h"
#include "GameTools.h"
#include <math.h>
CGameTools::CGameTools(void)
{
}

CGameTools::~CGameTools(void)
{
}
int CGameTools::GetRand(int nMin,int nMax)
{
	srand(time(NULL));
	int nRand=-1;
	nRand=(int)((double)rand()/RAND_MAX*(nMax-nMin+1)+nMin);
	return nRand;
}
/*
碰撞函数 两个矩形碰撞
*/
BOOL CGameTools::RectInRect(RECT rect1,RECT rect2)
{

    int p1x=max(rect1.left,rect2.left);
	int p2x=min(rect1.right,rect2.right);
	int p1y=max(rect1.top,rect2.top);
	int p2y=min(rect1.bottom,rect2.bottom);
	if (p1x<=p2x&&p1y<=p2y)
	{
		return TRUE;
	}
	return FALSE;//没有碰撞
}
int CGameTools::MakeRect(POINT pt,int nWidth,int nHeight,RECT &rect)
{
	rect.left=pt.x;
	rect.right=pt.x+nWidth;
	rect.top=pt.y;
	rect.bottom=pt.y+nHeight;
	return 0;
}
void CGameTools::copyRect(RECT &rectDest,RECT &rectOri)
{
	rectDest.left=rectOri.left;
	rectDest.top=rectOri.top;
	rectDest.right=rectOri.right;
	rectDest.bottom=rectOri.bottom;
}
BOOL CGameTools::CireleHitCirele(POINT pos1,POINT pos2,int nRadius1,int nRadius2)
{
	double fLen=sqrt((double)((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y)));
	double fPoint=fLen-(double)((int)fLen);
	long dLen;
	if (fPoint>0.5)
	{
		dLen=(long)fLen+1;
	}
	else
	{
		dLen=(long)fLen;
	}
	if (dLen>(nRadius1+nRadius2))
	{
		return FALSE;
	}
	return TRUE;
}
RECT CGameTools::CireleToRect(POINT pos,int nRadius)
{
	RECT rect;
	rect.left=pos.x-nRadius;
	rect.top=pos.y-nRadius;
	rect.right=pos.x+nRadius;
	rect.bottom=pos.y+nRadius;
	return rect;
}
/*

查看pos点是否在rect中
不在 返回 False
在　　TRUE
*/
BOOL CGameTools::SetPosInRect(POINT pos,RECT rect,int nRadius)
{
	if ((pos.x-nRadius)<rect.left||(pos.x+nRadius)>rect.right)
	{
		return FALSE;
	}
	if ((pos.y-nRadius)<rect.top||(pos.y+nRadius)>rect.bottom)
	{
		return FALSE;
	}
	return TRUE;
}
long CGameTools::PointDistance(POINT pos1,POINT pos2)
{
	double fLen=sqrt((double)((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y)));
	double fPoint=fLen-(double)((int)fLen);
	long dLen;
	if (fPoint>0.5)
	{
		dLen=(long)fLen+1;
	}
	else
	{
		dLen=(long)fLen;
	}
	return dLen;
}
int  CGameTools::PointHitRect(POINT pt,int nRadius,RECT rect)
{
	if ((pt.x-nRadius)<rect.left)
	{
		return 1;
	}
	if ((pt.x+nRadius)>rect.right)
	{
		return 2;
	}
	if ((pt.x-nRadius)<rect.top)
	{
		return 3;
	}
	return 0;
}
void CGameTools::SetRectWith(int left,int top,int right,int bottom,RECT &rect)
{
	rect.left=left;
	rect.top=top;
	rect.right=right;
	rect.bottom=bottom;
}
RECT CGameTools::GetRectWith(POINT pos,int nWidth,int nHeight)
{
	RECT rect;
	rect.left=pos.x;
	rect.top=pos.y;
	rect.right=pos.x+nWidth;
	rect.bottom=pos.y+nHeight;
	return rect;
}
BOOL CGameTools::PointInRect(POINT pos,RECT rect)
{
	if ( (pos.x>rect.right||pos.x<rect.left) || (pos.y<rect.top||pos.y>rect.bottom) )
	{
		return FALSE;
	}
	return TRUE;

}
POINT CGameTools::GetRectCentre(RECT rect)
{
	POINT pos;
	pos.x=(rect.left+rect.right)/2;
	pos.y=(rect.bottom+rect.top)/2;
	return pos;
}
vector<CString> CGameTools::GetAllGameName()
{
	vector<CString> vSection;
	return vSection;
}
CString CGameTools::GetIniPathName()
{
	CString strPathName;
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH
	GetModuleFileName(NULL,exeFullPath,MAX_PATH);//得到程序模块名称，全路径
	strPathName.Format("%s",exeFullPath);
	strPathName = strPathName.Left(strPathName.ReverseFind('\\')+1);
	return strPathName;
}
HRESULT  CGameTools::ShowPic(TCHAR*   lpstrFile,   HWND   hWnd,   int   nScrWidth,   int   nScrHeight)   
{ 
	HDC   hDC_Temp=GetDC(hWnd);   

	IPicture   *pPic;   
	IStream   *pStm;   

	BOOL   bResult;   
	HANDLE   hFile   =   NULL;   
	DWORD   dwFileSize,   dwByteRead;   

	//打开硬盘中的图形文件   
	hFile=CreateFile(lpstrFile,   GENERIC_READ,   FILE_SHARE_READ,   NULL,   OPEN_EXISTING,   FILE_ATTRIBUTE_NORMAL,   NULL);   

	if   (hFile   !=   INVALID_HANDLE_VALUE)   
	{   
		dwFileSize=GetFileSize(hFile,   NULL);//获取文件字节数   
		if   (dwFileSize==0xFFFFFFFF)   
			return   E_FAIL;   
	}   
	else   
	{   
		return   E_FAIL;   
	}   


	//分配全局存储空间   
	HGLOBAL   hGlobal   =   GlobalAlloc(GMEM_MOVEABLE,   dwFileSize);   
	LPVOID   pvData   =   NULL;   

	if   (hGlobal   ==   NULL)   
		return   E_FAIL;   

	if   ((pvData   =   GlobalLock(hGlobal))   ==   NULL)//锁定分配内存块   
		return   E_FAIL;   

	ReadFile(hFile,   pvData,   dwFileSize,   &dwByteRead,   NULL);//把文件读入内存缓冲区   
	GlobalUnlock(hGlobal);   
	CreateStreamOnHGlobal(hGlobal,   TRUE,   &pStm);   

	//装入图形文件   
	bResult   =   OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic);   

	if(FAILED(bResult))   
		return   E_FAIL;   

	OLE_XSIZE_HIMETRIC   hmWidth;//图片的真实宽度   
	OLE_YSIZE_HIMETRIC   hmHeight;//图片的真实高度   
	pPic-> get_Width(&hmWidth);   
	pPic-> get_Height(&hmHeight);   


	//将图形输出到屏幕上（有点像BitBlt）   

	bResult   =   pPic-> Render(hDC_Temp,   0,   0,   nScrHeight,   nScrWidth,   0,   hmHeight,   hmWidth,   -hmHeight,   NULL);   

	pPic-> Release();   

	CloseHandle(hFile);//关闭打开的文件   

	if   (SUCCEEDED(bResult))   
	{   
		return   S_OK;   
	}   
	else   
	{   
		return   E_FAIL;   
	}   
} 