#ifndef __DEFINE__H
#define __DEFINE__H

#define PURE = 0
#define SAFE_DELETE(p)if(p){delete p; p = NULL;}

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)       ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


#define DECLARE_SINGLETON(ClassName)		\
private:									\
	static ClassName*	m_pInstance;			\
public:										\
	static ClassName*	GetInstance(void)	\
	{										\
	if(m_pInstance == NULL)				\
	m_pInstance = new ClassName;	\
	\
	return m_pInstance;					\
	}										\
	void DestroyInstance(void)				\
	{										\
	if(m_pInstance)						\
		{									\
		delete m_pInstance;				\
		m_pInstance = NULL;				\
		}									\
	}										\



#define IMPLEMENT_SINGLETON(ClassName)		\
	ClassName* ClassName::m_pInstance = NULL;	\

#ifdef __TOOL__
#define MSG_BOX(String) AfxMessageBox(String)
#else
#define MSG_BOX(String) MessageBox(g_hWnd, String, L"System Error!!", MB_OK)
#endif

#define GETTIME	CTimeMgr::GetInstance()->GetTime()


#endif