#include "StdAfx.h"
#include "SoundMgr.h"
#include "Func.h"

CSoundMgr*	CSoundMgr::m_pInstance = NULL;

CSoundMgr::CSoundMgr(void)
{
	m_pSystem = NULL;
	for(int i = 0; i < SOUND_end; ++i)
		m_pEffect[i] = NULL;
	m_pMainBGM = NULL;


	m_iVersion = 0;

	Initialize();
}

CSoundMgr::~CSoundMgr(void)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter = m_mapSound.begin();
	map<TCHAR*, FMOD_SOUND*>::iterator iter_end = m_mapSound.end();

	for( ; iter != iter_end;)
	{
		m_Result = FMOD_Sound_Release(iter->second);
		ErrorCheck(m_Result);

		delete [] (iter->first);

		iter = m_mapSound.erase(iter);
		iter_end = m_mapSound.end();

		if(iter == iter_end)
			break;
	}

	m_Result = FMOD_System_Close(m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Release(m_pSystem);
	ErrorCheck(m_Result);
}

void CSoundMgr::Initialize(void)
{
	m_Result = FMOD_System_Create(&m_pSystem);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_GetVersion(m_pSystem, &m_iVersion);
	ErrorCheck(m_Result);

	m_Result = FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(m_Result);

	
}
void CSoundMgr::ErrorCheck(FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
	{
		cout << "에러!!" << endl;
		system("pause");
		return;
	}
}
void CSoundMgr::LoadSoundFile(void)
{
	_finddata_t fd; // 순차적으로 찾기 위한

	long handle;

	int iResult = 1;

	handle = _findfirst("..\\Sound\\*.*", &fd);

	if(handle == -1)
		return;

	while(iResult != -1)
	{
		TCHAR szName[256];

		ZeroMemory(szName, sizeof(szName)); // 매크로함수 : 내부적으로 memset

		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,
							fd.name, strlen(fd.name), szName, 256); 
			// 멀티바이트를 유니코드로 변경해주는 함수.
		TCHAR* pName = new TCHAR[256];
		ZeroMemory(pName, sizeof(TCHAR) * 256);
		lstrcpy(pName, szName);		// 유니코드 문자열 복사.

		char szFullName[256];

		strcpy_s(szFullName, "..\\Sound\\");
		strcat_s(szFullName, fd.name);

		FMOD_SOUND* pSound;

		m_Result = FMOD_System_CreateSound(m_pSystem, szFullName,
											FMOD_HARDWARE, 0, &pSound);

		if(m_Result == FMOD_OK)
		{
			// 사운드파일 정상적인 완성!
			m_mapSound.insert( make_pair(pName, pSound) );
		}
		else
		{
			delete [] pName;
		}

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);

	m_Result = FMOD_System_Update(m_pSystem);
	ErrorCheck(m_Result);
}
void CSoundMgr::ClickSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CLICK]);
	ErrorCheck(m_Result);
}
void CSoundMgr::CreateHomeSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CREATE_HOME]);
	ErrorCheck(m_Result);
}

void CSoundMgr::CreatePortSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CREATE_PORT]);
	ErrorCheck(m_Result);
}

void CSoundMgr::CreateBarrackSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CREATE_BARRACK]);
	ErrorCheck(m_Result);
}

void CSoundMgr::CreateGroundUnit( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CREATE_GROUND_UNIT]);
	ErrorCheck(m_Result);
}

void CSoundMgr::CreateSeaUnit( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CREATE_SEA_UNIT]);
	ErrorCheck(m_Result);
}

void CSoundMgr::VillagerPickSound( TCHAR* pSoundKey )
{	
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_PICK_GROUND]);
	ErrorCheck(m_Result);
}

void CSoundMgr::VillagerMoveSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_MOVE_GROUND]);
	ErrorCheck(m_Result);
}


void CSoundMgr::SeaMoveSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_MOVE_SEA]);
	ErrorCheck(m_Result);
}

void CSoundMgr::GetResource( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_RESOURCE1]);
	ErrorCheck(m_Result);
}

void CSoundMgr::GetResource2( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_RESOURCE2]);
	ErrorCheck(m_Result);
}

void CSoundMgr::VillagerBuild( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_BUILD]);
	ErrorCheck(m_Result);
}

void CSoundMgr::ArrowStartSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pEffect[SOUND_ARROW]);
	ErrorCheck(m_Result);
}

void CSoundMgr::FireStartSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_FIRE]);
	ErrorCheck(m_Result);
}

void CSoundMgr::CannonStartSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CANNON]);
	ErrorCheck(m_Result);
}

void CSoundMgr::CannonBoomSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CANNON_BOOM]);
	ErrorCheck(m_Result);
}

void CSoundMgr::DestroySound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_DESTROY]);
	ErrorCheck(m_Result);
}

void CSoundMgr::CannonMissSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_CANNON_MISS]);
	ErrorCheck(m_Result);
}


void CSoundMgr::ShipDead( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_SHIP_DEAD]);
	ErrorCheck(m_Result);

}

void CSoundMgr::GroundDead( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_GROUND_DEAD]);
	ErrorCheck(m_Result);

}

void CSoundMgr::GroundBoomSound( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_BOOM]);
	ErrorCheck(m_Result);
}

void CSoundMgr::AgeUpgrade( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_AGE_UPGRADE]);
	ErrorCheck(m_Result);
}
void CSoundMgr::WarStart( TCHAR* pSoundKey )
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
		iter->second, 0, &m_pEffect[SOUND_WAR_START]);
	ErrorCheck(m_Result);
}
void CSoundMgr::PlayBGMSound(TCHAR* pSoundKey)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	iter = find_if(m_mapSound.begin(), m_mapSound.end(), CStringCmp(pSoundKey));

	if(iter == m_mapSound.end())
		return;

	FMOD_Sound_SetMode(iter->second, FMOD_LOOP_NORMAL);

	m_Result = FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_REUSE,
									iter->second, 0, &m_pMainBGM);

	FMOD_Channel_SetVolume(m_pMainBGM, 0.5f);
	ErrorCheck(m_Result);

}
void CSoundMgr::SoundAllStop(void)
{
	if(m_pMainBGM)
	{
		m_Result = FMOD_Channel_Stop(m_pMainBGM);
		ErrorCheck(m_Result);
	
	}

	for(int i = 0; i < SOUND_end; ++i)
	{
		if(m_pEffect[i])
		{
			m_Result = FMOD_Channel_Stop(m_pEffect[i]);
			ErrorCheck(m_Result);
		}
	}
	
}
void CSoundMgr::SkillSoundStop(int i)
{
}











