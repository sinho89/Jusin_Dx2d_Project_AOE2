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


//PathRelativePathTo �Լ��� ����ϱ� ���ؼ� �����ؾ� �ϴ� ����...
#include <Shlwapi.h>
#pragma comment (lib, "shlwapi.lib")

//CImage Ŭ������ ����ϱ� ���ؼ� �����ؾ� �ϴ� ����...
#include <atlimage.h>


//_finddata_t �� ����ϱ� ���ؼ� �����ؾ� �ϴ� ����..
#include <io.h>

//cfilefind �� ���� ���ؼ� �����ϴ� ����
#ifdef __TOOL__
#include <afx.h>	//�̰� MFC �����ۿ� ������
#endif

#pragma warning(disable:4996)

#include <string>

//msxml
/*#import <msxml4.dll>
using namespace MSXML2;*/


//wofstream �� ����ϱ� ���ؼ� �����ؾ� �ϴ� ����
#include <fstream>

//cstring �� ����Ϸ���
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