#pragma once

class CToolView;
class CBackGround
{
public:
	vector<TILE*>		m_vecTile;
	vector<INFO*>		m_vecResource;
	vector<INFO*>		m_vecUnit;
	vector<INFO*>		m_vecBuild;
	CToolView*	m_pMainView;
public:
	void	SetMainView(CToolView*	pMainView);
	D3DXVECTOR3		m_vPos;
public:
	int				GetTileIndex(const D3DXVECTOR3&	vPos);
	bool			Picking(const D3DXVECTOR3& vPos, const int& iIndex);	//직선의 방정식..
	bool			Picking2(const D3DXVECTOR3& vPos, const int& iIndex);	//내적...
	void			TileChange(const D3DXVECTOR3& vPos, const int& iDrawID);
public:
	void			AddResource(const D3DXVECTOR3&	vPos, int _iSel, wstring _wstrObjKey);
	void			AddBuild(const D3DXVECTOR3&	vPos, int _iSel, wstring _wstrObjKey);
	void			AddUnit(const D3DXVECTOR3&	vPos, int _iSel, wstring _wstrObjKey, wstring _wstrStateKey);
public:
	HRESULT			Initialize(void);
	void			Update(void);
	void			Render(void);
	void			MiniViewRender(void);
	void			Release(void);
public:
	CBackGround(void);
	~CBackGround(void);
};
