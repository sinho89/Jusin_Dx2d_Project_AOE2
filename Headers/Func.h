#ifndef	__FUNC__H
#define __FUNC__H

typedef	struct tagStrComPare
{
	template<typename T>
	bool operator()(T Data)
	{
		return !lstrcmp(Data.first, m_pString);
	}
	const TCHAR*	m_pString;
	tagStrComPare(const TCHAR*	pKey)
		:m_pString(pKey){}
}STRCOMPARE;

//lamda �̷� �������ε� functor ����ؼ� �� ���� �־�...
//TR1 

typedef struct tagDeleteMap
{
	template<typename T>
	void operator()(T& Temp)
	{
		if(Temp.second)
		{
			delete[] Temp.first;
			delete Temp.second;
			Temp.second = NULL;
		}
	}
}DELMAP;

inline wstring ConvertRelativePath(wstring	strFullPath)
{
	TCHAR	szRelativePath[MAX_PATH] = L"";
	TCHAR	szDirectoryPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirectoryPath), szDirectoryPath);

	//�� ��ο��� �ٸ� ��η� ���� ��� ��θ� �����ϴ� ����...
	PathRelativePathTo((LPWSTR)szRelativePath, szDirectoryPath,
		FILE_ATTRIBUTE_DIRECTORY, strFullPath.c_str(),
		FILE_ATTRIBUTE_NORMAL);

	return szRelativePath;
}

#ifdef __TOOL__

inline int DirectoryFileCount(wstring& wstrPath)
{
	wstring wstrTemp = wstrPath;
	wstrTemp += L"\\*.png";

	CFileFind	Find;
	Find.FindFile(wstrTemp.c_str());

	int iContinue = 1;
	int iFileCount = 0;

	while(iContinue)
	{
		iContinue = Find.FindNextFile();

		//���丮�� �ƴ� ��츸 ���� ī��Ʈ �ؼ� ��ø..
		if(!Find.IsDirectory())
			++iFileCount;
	}
	//�ټ��� ��ȯ�ض�...
	return iFileCount;
}

inline void	DirectoryInfoExtraction(const wstring& wstrPath,
									vector<IMGPATH*>& rPathInfo)
{
	CFileFind	Find;
	Find.FindFile(wstrPath.c_str());

	int iContinue = 1;

	while(iContinue)
	{
		//������ ������ �˻��� �� �ִ�...
		iContinue = Find.FindNextFile();

		//. .. �̷������ ����...
		if(Find.IsDots())
			continue;

		//������ ���� ���� �ȿ��� ���ȣ��� �� Ÿ�����...
		if(Find.IsDirectory())
		{
			wstring wstTemp = Find.GetFilePath();
			wstTemp += L"\\*.*";
			DirectoryInfoExtraction(wstTemp, rPathInfo);
		}
		else	//������ ��쿡 ���� ó��...
		{
			//������ �����ε� �ý��� ������ ��쿡 �ѱ���...
			if(Find.IsSystem())
				continue;

			IMGPATH*	pPath = new IMGPATH;
			TCHAR	szPathBuf[MAX_PATH] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().operator LPCWSTR());
			PathRemoveFileSpec(szPathBuf);

			pPath->iCount = DirectoryFileCount(wstring(szPathBuf));

			wstring	wstrTextureName = Find.GetFileTitle().operator LPCWSTR();

			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";

			TCHAR szBuf[MAX_PATH] = L"";
			lstrcpy(szBuf, (LPWSTR)Find.GetFilePath().operator LPCWSTR());

			PathRemoveFileSpec(szBuf);

			PathCombine(szBuf, szBuf, (LPWSTR)wstrTextureName.c_str());

			//��� ��η� ���� ����ְ�
			pPath->wstrPath = ConvertRelativePath(szBuf);


			PathRemoveFileSpec(szBuf);
			pPath->wstrStateKey = PathFindFileName(szBuf);

			PathRemoveFileSpec(szBuf);
			pPath->wstrObjKey = PathFindFileName(szBuf);

			rPathInfo.push_back(pPath);

			Find.FindFile(Find.GetFilePath());

			Find.FindNextFile();
		}
	}
}

#endif

inline static bool	GetKey(int iKey)
{
	if(g_bFocus == false)
		return false;

	if(GetAsyncKeyState(iKey) && g_bFocus == true)
		return true;

	return false;
}

#endif