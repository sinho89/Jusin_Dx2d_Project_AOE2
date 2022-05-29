#include "StdAfx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr(void)
{
}

CTimeMgr::~CTimeMgr(void)
{
}

float CTimeMgr::GetTime(void)
{
	return m_fTime;
}

void CTimeMgr::InitTime(void)
{
	//1/10000 초단위로 타이머를 반환해준다...gettickcount 와 비슷한녀석...
	//cpu 가 발생시키는 시간이다...
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);

	//타이머의 주기 1초당 진동수를 반환해 준다....
	QueryPerformanceFrequency(&m_CpuTick);
}

void CTimeMgr::SetTime(void)
{
	//매번 루프마다 갱신을 한다..
	QueryPerformanceCounter(&m_FrameTime);

	//새로 구한 시간하고 초기 init되었을 때 시간 차이를 잰다..
	if(m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		//프로세스 부하가 걸렸을 때 시간이 뒤틀린다..
		//이 때 재갱신을 해 주어야 함...
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	//메인게임 update 가 한 번 호출되고
	//다음 호출 시까지의 인터벌을 cpu 진동수로 나누어 1초로 만드는 방식...
	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart)
		/ m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;
}
