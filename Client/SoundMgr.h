#pragma once


class CSoundMgr
{
private:
	static CSoundMgr* m_pInstance;
public:
	static CSoundMgr* GetInstance()
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CSoundMgr;
		}
		return m_pInstance;
	}
	void DestroyInstance()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

	/////////////// fmod �������̽�
private:
	FMOD_SYSTEM*	m_pSystem;		//fmod �ý��� ������
	FMOD_CHANNEL*	m_pEffect[SOUND_end];
	FMOD_CHANNEL*	m_pMainBGM;		//�����

	FMOD_RESULT		m_Result;		// fmod �����߿� ����üũ

	unsigned int	m_iVersion;

	map<TCHAR*, FMOD_SOUND*>		m_mapSound;
	
	//��� �Լ��� ��������.

public:
	void Initialize(void);
	void LoadSoundFile(void);
	void ClickSound(TCHAR* pSoundKey);
	void CreateHomeSound(TCHAR* pSoundKey);
	void CreatePortSound(TCHAR* pSoundKey);
	void CreateBarrackSound(TCHAR* pSoundKey);
	void CreateGroundUnit(TCHAR* pSoundKey);
	void CreateSeaUnit(TCHAR* pSoundKey);
	void ArrowStartSound(TCHAR* pSoundKey);
	void FireStartSound(TCHAR* pSoundKey);
	void CannonStartSound(TCHAR* pSoundKey);
	void CannonBoomSound(TCHAR* pSoundKey);
	void CannonMissSound(TCHAR* pSoundKey);
	void DestroySound(TCHAR* pSoundKey);
	void GroundBoomSound(TCHAR* pSoundKey);
	void ShipDead(TCHAR* pSoundKey);
	void GroundDead(TCHAR* pSoundKey);
	void AgeUpgrade(TCHAR* pSoundKey);
	void VillagerPickSound(TCHAR* pSoundKey);
	void VillagerMoveSound(TCHAR* pSoundKey);
	void SeaMoveSound(TCHAR* pSoundKey);
	void GetResource(TCHAR* pSoundKey);
	void GetResource2(TCHAR* pSoundKey);
	void VillagerBuild(TCHAR* pSoundKey);
	void WarStart(TCHAR* pSoundKey);
	void PlayBGMSound(TCHAR* pSoundKey);
	void SoundAllStop(void);
	void SkillSoundStop(int i);

public:
	map<TCHAR*, FMOD_SOUND*>* GetSoundMap(void)
	{
		return &m_mapSound;
	}
private:
	void ErrorCheck(FMOD_RESULT _result);
private:
	CSoundMgr(void);
public:
	~CSoundMgr(void);
};
