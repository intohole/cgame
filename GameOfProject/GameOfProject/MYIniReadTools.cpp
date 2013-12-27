#include "StdAfx.h"
#include "MYIniReadTools.h"


MYIniReadTools *MYIniReadTools::iniInstence = NULL;
MYIniReadTools::MYIniReadTools(void)
{
}
MYIniReadTools *MYIniReadTools::GetInstence(CString strPathName)
{
	if (iniInstence == NULL)
	{
		iniInstence = new MYIniReadTools(strPathName);
	}
	else
	{
		iniInstence->SetFileName(strPathName);
	}
	return iniInstence;
}
MYIniReadTools::MYIniReadTools(CString strPath)
{
	strcpy(FileName,strPath);
	LoadFile();
}
void MYIniReadTools::SetFileName(CString str)
{
	strcpy(FileName,str);
	LoadFile();
}
void MYIniReadTools::SetFileName(char str[])
{
	strcpy(FileName,str);
	LoadFile();
}
void MYIniReadTools::LoadFile()
{
	mapAllIniInfo.clear();
	FILE *fp;
	char strContainer[512];
	fp=fopen(FileName,"r");
	if (fp == NULL)
	{
		return ;
	}
	vector<INIKEYINFO> st;
	BOOL isFirst=TRUE;
	CString strSection="";
	while(!feof(fp))
	{
		fgets(strContainer,512,fp);
		CString strTmp=CString(strContainer);
		
		if (IsSection(strTmp))
		{
			if (strSection!="")
			{
				mapAllIniInfo.insert(make_pair(strSection,st));
			}
			strSection=strTmp;
			//保存现在的节名
			st.clear();//清空上次保存的节点
		}
		else
		{
			if (isFirst)
			{
				break;
			}
			InsertKeyAndValue(strTmp, st);
		}
		isFirst=FALSE;
	}
	if (strSection!="")
	{
		mapAllIniInfo.insert(make_pair(strSection,st));
	}
}

BOOL MYIniReadTools::IsSection(CString strValue)
{
	strValue.Trim();
	int nLeft=strValue.Find('[',0);
	int nRight=strValue.ReverseFind(']');
	if (nLeft == 0 && nRight == (strValue.GetLength()-1) )
	{
		return TRUE;
	}
	return FALSE;
}
BOOL MYIniReadTools::IsComment(CString str)
{
	str.Trim();
	if (str.Find(';',0)==0)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL MYIniReadTools::IsKeyAndValue(CString str)
{
	str.Trim();
	int nEquale;
	nEquale=str.Find('=',0);
	if (nEquale >0 && nEquale < (str.GetLength()-1))
	{
		return TRUE;
	}
	return FALSE;
}
void MYIniReadTools::GetKeyAndValue(CString &strKey,CString &strValue,CString &strComment,CString str)
{
	int nComment=str.Find(';',0);
	if (nComment!=-1)
	{
		if (str.Find('"',nComment)==-1)
		{
			strComment=str.Right(str.GetLength()-nComment-1);
			str=str.Left(nComment);
		}
	}
	int nEquale=str.Find('=',0);
	strKey=str.Left(nEquale);
	strValue=str.Right(str.GetLength()-nEquale-1);
}
BOOL MYIniReadTools::InsertKeyAndValue( CString strTmpValue, vector<INIKEYINFO> &st ) 
{
	CString strKey;
	CString strValue;
	CString strComment;

	if(IsKeyAndValue(strTmpValue)||IsComment(strTmpValue))
	{
		GetKeyAndValue(strKey,strValue,strComment,strTmpValue);
		INIKEYINFO stInfo;
		stInfo.strKey=strKey;
		stInfo.strValue=strValue;
		stInfo.strComment=strComment;
		st.push_back(stInfo);
		return TRUE;
	}
	return FALSE;
}
 int MYIniReadTools::GetAllSection(vector<CString> &vSection)
{
	int nRet=0;
	map<CString,vector<INIKEYINFO> >::iterator it;
	for (it=mapAllIniInfo.begin();it!=mapAllIniInfo.end();it++)
	{
		int nIndexLeft=it->first.Find('[',0);
		int nIndexRight=it->first.ReverseFind(']');
		CString str=it->first.Mid(nIndexLeft+1,nIndexRight-1);
		vSection.push_back(str);
		nRet++;
	}
	return nRet;
}
 BOOL MYIniReadTools::GetAllValueAndKey(CString strSection,vector<INIKEYINFO> &vIniKeyAndValue)
{

	map<CString,vector<INIKEYINFO> >::iterator it;
	for (it=mapAllIniInfo.begin();it!=mapAllIniInfo.end();it++)
	{
		int nIndexLeft=it->first.Find('[',0);
		int nIndexRight=it->first.ReverseFind(']');
		CString str=it->first.Mid(nIndexLeft+1,nIndexRight-1);
		if(str.CompareNoCase(strSection)==0)
		{
			vector<INIKEYINFO>::iterator iTmp;
			for (iTmp=it->second.begin();iTmp!=it->second.end();iTmp++)
			{
				if (iTmp->strKey!="")
				{
					vIniKeyAndValue.push_back(*iTmp);
				}
			}
			vIniKeyAndValue=it->second;
			return TRUE;
		}
	}
	return FALSE;
}
 int MYIniReadTools::GetKeyValue(CString strSection,CString strKeyValue,CString &strValue,CString defaultValue)
{
	vector<INIKEYINFO> vIniKeyAndValue;
	if (!GetAllValueAndKey(strSection,vIniKeyAndValue))
	{
		strValue=defaultValue;
		return -1;
	}
	for (int i=0;i<vIniKeyAndValue.size();i++)
	{
		if(strKeyValue == vIniKeyAndValue[i].strKey)
		{
			strValue=defaultValue;
			return 0;
		}
	}
	strValue=defaultValue;
	return -1;
}
MYIniReadTools::~MYIniReadTools(void)
{
}
