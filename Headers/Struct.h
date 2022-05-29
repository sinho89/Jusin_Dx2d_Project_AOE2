#ifndef __STRUCT__H
#define __STRUCT__H

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9	pTexture;
	D3DXIMAGE_INFO		ImgInfo;		
}TEXINFO;

typedef struct tagFrame
{
	float fFrame;	//얘가 증가하면서 이미지 가져옴...
	float fCount;	//속도...
	float fMax;		//최대 장수...
	float fOriFrame;
	tagFrame(void){}
	tagFrame(float _fFrame, float _fCount, float _fMax, float _fOriFrame)
		:fFrame(_fFrame), fCount(_fCount), fMax(_fMax), fOriFrame(_fOriFrame){}
}FRAME;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;
	D3DXVECTOR3	vSize;
	BYTE		byOption;
	BYTE		byDrawID;
	BYTE		byOriID;
	eResourceType	m_eType;
	eGroundType		m_GroundType;
	eUnitType		m_UnitType;
	eBuildType		m_BuildType;

	wstring		wstrObjKey;
	wstring		wstrStateKey;

}TILE;

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vGoalPos;
	D3DXVECTOR3 vSavePos;
	D3DXVECTOR3 vWayPos;
	D3DXVECTOR3 vMakePos;
	D3DXMATRIX  matWorld;

	wstring		wstrObjKey;
	wstring		wstrStateKey;

	ePlayerType				m_ePlayerType;
	eResourceType			m_eResourceType;
	eGroundType				m_eGroundType;
	eBuildType				m_eBuildType;
	eUnitType				m_eUnitType;
	eAgeType				m_eAgeType;
	eOBJ_TYPE				m_eObjType;
	eSTATE_TYPE				m_eStateType;
	eDIRECTION_TYPE			m_eDirType;
	eSAVE_RESOURCE_TYPE		m_eSaveType;
	eCONTROL_DRAW_TYPE		m_eControlDrawType;
	eBUILD_SIZE_TYPE		m_eSizeType;
	eGAUGE_TYPE				m_eGaugeType;
	eSIXTEEN_DIRECTION_TYPE	m_eSixteenDirType;
	
	BYTE		byDrawID;
	BYTE		bySailDrawID;
	BYTE		byOriID;
	BYTE		byOriSailID;

	bool		bAlive;
	bool		bSelection;
	bool		bRenderCheck;
	bool		bChangeButton;
	bool		bMove;
	bool		bRelly;
	bool		bBuildHome;
	bool		bBuildRender;
	bool		bBuildPort;
	bool		bBuildWood;
	bool		bBuildMine;
	bool		bBuildBarracks;
	bool		bBuildMill;
	bool		bBuildLimit;
	bool		bBuildStartVillager;
	bool		bDirCheck;
	bool		bFishing;
	bool		bView;
	bool		bDeath;
	bool		bBoom;
	bool		bPortButtonChange;
	bool		bTest;
	bool		bTrans;
	bool		bAttack;
	bool		bFormation;

	float		fSpeed;
	float		fAngle;
	float		fCollRange;

	int			iHp, iMaxHp;
	int			iAtt, iDef;
	int			iRange, iSight;
	int			iBoomRange;
	int			iGetResourceCount;
	int			iWorkingIndex;

	int			iTreeNum;
	int			iFoodNum;
	int			iStoneNum;
	int			iGoldNum;

	int			iUnitCount;
	int			iUnitMaxCount;
	int			iIndex;

	tagInfo(){;}

}INFO;

typedef struct tagTexturePath
{
	wstring				wstrObjKey;
	wstring				wstrStateKey;
	wstring				wstrPath;
	int			iCount;
}IMGPATH;


typedef struct tagSPath
{
	const TCHAR*		szObjKey;
	const TCHAR*		szImgPath;
}SPATH;

#endif