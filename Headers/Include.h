#ifndef	__INCLUDE__H
#define __INCLUDE__H

#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;


#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


//PathRelativePathTo 함수를 사용하기 위해서 포함해야 하는 파일...
#include <Shlwapi.h>
#pragma comment (lib, "shlwapi.lib")

//CImage 클래스를 사용하기 위해서 포함해야 하는 파일...
#include <atlimage.h>


//_finddata_t 를 사용하기 위해서 포함해야 하는 파일..
#include <io.h>

//cfilefind 를 쓰기 위해서 포함하는 파일
#ifdef __TOOL__
#include <afx.h>	//이거 MFC 에서밖에 못쓴대
#endif

#pragma warning(disable:4996)

#include <string>

//msxml
/*#import <msxml4.dll>
using namespace MSXML2;*/


//wofstream 을 사용하기 위해서 포함해야 하는 파일
#include <fstream>

//cstring 을 사용하려면
#include <atlstr.h>




#include "Const.h"
#include "Define.h"
#include "Enum.h"
#include "Extern.h"
#include "Struct.h"
#include "Device.h"
#include "Func.h"


#include "fmod.h"
#include "fmod.hpp"
#include "fmod_dsp.h"
#include "fmod_errors.h"

#pragma comment (lib, "fmodex_vc.lib")
#endif