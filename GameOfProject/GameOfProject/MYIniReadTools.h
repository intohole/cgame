#pragma once
#include "StructSet.h"
class MYIniReadTools
{
public:
	MYIniReadTools(void);
	MYIniReadTools(CString strPath);
	~MYIniReadTools(void);
	int GetAllSection(vector<CString> &vSection);
	int GetKeyValue(CString strSection,CString strKeyValue,CString &strValue,CString defaultValue);
	BOOL GetAllValueAndKey(CString strSection,vector<INIKEYINFO> &vIniKeyAndValue);
	void GetKeyAndValue(CString &strKey,CString &strValue,CString &strComment,CString str);
	void SetFileName(CString str);
	void SetFileName(char str[]);
	static MYIniReadTools *GetInstence(CString strPathName);
	static MYIniReadTools *iniInstence;
private:
	
	void LoadFile();
	BOOL InsertKeyAndValue( CString strTmpValue, vector<INIKEYINFO> &st ) ;
	BOOL IsSection(char str[]);
	BOOL IsSection(CString strValue);
	BOOL IsKeyAndValue(CString str);
	BOOL IsComment(CString str);

	vector<INIKEYINFO> GetSectionAllKeyInfo();
	map<CString,vector<INIKEYINFO> > mapAllIniInfo;	
	char FileName[MAX_PATH];
};
