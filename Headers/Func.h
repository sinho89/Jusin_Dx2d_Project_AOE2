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

//lamda 이런 문법으로도 functor 대신해서 쓸 수가 있어...
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

	//한 경로에서 다른 경로로 가는 상대 경로를 추출하는 것임...
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

		//디렉토리가 아닌 경우만 파일 카운트 해서 중첩..
		if(!Find.IsDirectory())
			++iFileCount;
	}
	//다세면 반환해라...
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
		//파일의 유무를 검사할 수 있다...
		iContinue = Find.FindNextFile();

		//. .. 이런얘들은 버려...
		if(Find.IsDots())
			continue;

		//폴더인 경우는 폴더 안에서 재귀호출로 더 타고들어가라...
		if(Find.IsDirectory())
		{
			wstring wstTemp = Find.GetFilePath();
			wstTemp += L"\\*.*";
			DirectoryInfoExtraction(wstTemp, rPathInfo);
		}
		else	//파일인 경우에 대한 처리...
		{
			//파일은 파일인데 시스템 파일인 경우에 넘기자...
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

			//상대 경로로 만들어서 집어넣고
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