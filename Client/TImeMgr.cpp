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
	//1/10000 �ʴ����� Ÿ�̸Ӹ� ��ȯ���ش�...gettickcount �� ����ѳ༮...
	//cpu �� �߻���Ű�� �ð��̴�...
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);

	//Ÿ�̸��� �ֱ� 1�ʴ� �������� ��ȯ�� �ش�....
	QueryPerformanceFrequency(&m_CpuTick);
}

void CTimeMgr::SetTime(void)
{
	//�Ź� �������� ������ �Ѵ�..
	QueryPerformanceCounter(&m_FrameTime);

	//���� ���� �ð��ϰ� �ʱ� init�Ǿ��� �� �ð� ���̸� ���..
	if(m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		//���μ��� ���ϰ� �ɷ��� �� �ð��� ��Ʋ����..
		//�� �� �簻���� �� �־�� ��...
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	//���ΰ��� update �� �� �� ȣ��ǰ�
	//���� ȣ�� �ñ����� ���͹��� cpu �������� ������ 1�ʷ� ����� ���...
	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart)
		/ m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;
}
