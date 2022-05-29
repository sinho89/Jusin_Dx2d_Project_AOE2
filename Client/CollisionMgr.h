#pragma once

class CObj;
class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)
public:
	bool SelectUnit();
	bool SetGroupUnit(RECT _rcCollBox);
	int GetPushButtonIndex();
	bool MouseAndUnitCol();
	bool BuildAndTileCol(eBUILD_SIZE_TYPE	_eType);
	void UnitCollision(CObj*	pObj);
	void BuildCollision(CObj*	pObj);
	void ResourceCollision(CObj*	pObj);
	void InitTileSightCollision(CObj*	pObj);
	void TileSightCollision(CObj*	pObj);
	void BuildTileSightCollision(CObj*	pObj);
	void EnemySightCollisoin(CObj* pObj);
	CObj*  UnitBattleFunc(CObj*	pObj);
	void TransGroundUnit(CObj* pObj);
	void SoldierAttCollision(CObj* pObj);
private:
	CCollisionMgr(void);
public:
	~CCollisionMgr(void);
};
