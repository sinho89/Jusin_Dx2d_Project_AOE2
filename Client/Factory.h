#pragma once

class CObj;

template <typename T>
class CFactory
{
public:
	static CObj* CreateObject()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3	_vPos)
	{
		CObj* pObj = new T(_vPos);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3	_vPos, bool _bShot)
	{
		CObj* pObj = new T(_vPos, _bShot);
		pObj->Initialize();
		return pObj;
	} 
	static CObj* CreateObject(CObj*	pUnit, CObj*	pTargetUnit, eSIXTEEN_DIRECTION_TYPE	_eType)
	{
		CObj* pObj = new T(pUnit, pTargetUnit, _eType);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3 _vPos, eGAUGE_TYPE _type)
	{
		CObj* pObj = new T(_vPos, _type);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3 _vPos, eDIRECTION_TYPE _DirType)
	{
		CObj* pObj = new T(_vPos, _DirType);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3 _vPos, eSIXTEEN_DIRECTION_TYPE _DirType)
	{
		CObj* pObj = new T(_vPos, _DirType);
		pObj->Initialize();
		return pObj;
	}


	static CObj* CreateObject(D3DXVECTOR3	_vPos, int	_iIndex)
	{
		CObj* pObj = new T(_vPos, _iIndex);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3	_vPos, eResourceType _Type, BYTE _byDrawID)
	{
		CObj* pObj = new T(_vPos, _Type, _byDrawID);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3	_vPos, eResourceType _Type, BYTE _byDrawID, int iIndex)
	{
		CObj* pObj = new T(_vPos, _Type, _byDrawID, iIndex);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3 _vStart, D3DXVECTOR3 _vTarget, float _fInitV)
	{
		CObj* pObj = new T(_vStart, _vTarget, _fInitV);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(INFO* pInfo)
	{
		CObj* pObj = new T(pInfo);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3 _vPos, eBuildType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		CObj* pObj = new T(_vPos, _Type, _TeamType, _byDrawID);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3 _vPos, eUnitType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		CObj* pObj = new T(_vPos, _Type, _TeamType, _byDrawID);
		pObj->Initialize();
		return pObj;
	}
	static CObj* CreateObject(D3DXVECTOR3 _vPos, D3DXVECTOR3 _vWayPos, eUnitType _Type, ePlayerType _TeamType, BYTE _byDrawID)
	{
		CObj* pObj = new T(_vPos, _vWayPos, _Type, _TeamType, _byDrawID);
			pObj->Initialize();
		return pObj;
	}

	static CObj* CreateObject(D3DXVECTOR3 _vPos, eBUILD_SIZE_TYPE _SizeType, eBuildType _BuildType)
	{
		CObj* pObj = new T(_vPos, _SizeType, _BuildType);
		pObj->Initialize();
		return pObj;
	}

public:
	CFactory(void);
	~CFactory(void);
};
