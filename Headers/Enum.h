#ifndef __ENUM__H
#define __ENUM__H

enum eSoundType
{
	SOUND_ARROW,
	SOUND_DESTROY,
	SOUND_FIRE,
	SOUND_CANNON,
	SOUND_CANNON_MISS,
	SOUND_SHIP_DEAD,
	SOUND_GROUND_DEAD,
	SOUND_BOOM,
	SOUND_CANNON_BOOM,
	SOUND_BATTLE_START,
	SOUND_MOVE_GROUND,
	SOUND_PICK_GROUND,
	SOUND_MOVE_SEA,
	SOUND_CLICK,
	SOUND_CREATE_GROUND_UNIT,
	SOUND_CREATE_SEA_UNIT,
	SOUND_CREATE_HOME,
	SOUND_CREATE_PORT,
	SOUND_CREATE_BARRACK,
	SOUND_RESOURCE1,
	SOUND_RESOURCE2,
	SOUND_BUILD,
	SOUND_FINISH,
	SOUND_AGE_UPGRADE,
	SOUND_WAR_START,
	SOUND_end
};
enum eTextureType
{
	TEX_SINGLE,
	TEX_MULTI,
	TEX_end
};

enum ePlayerType
{
	PT_NONE,
	PT_PLAYER,
	PT_ENEMY,
	PT_end,
};

enum eGroundType
{
	GT_EMPTY,
	GT_GROUND,
	GT_UNIT,
	GT_SEA,
	GT_BUILD,
	GT_end
};

enum eResourceType
{
	RT_NONE,
	RT_TREE,
	RT_GOLD,
	RT_STONE,
	RT_FISH,
	RT_CHERRY,
	RT_end,

};
enum eDeleteType
{
	DT_STATIC,
	DT_DYNAMIC,
	DT_end
};

enum eUnitType
{
	UT_VILLAGER,
	UT_FISHER,
	UT_GALLYSHIP,
	UT_FIRESHIP,
	UT_TRANSSHIP,
	UT_CANNONSHIP,
	UT_DESTROYSHIP,
	UT_SOLDIER,
	UT_ARCHER,
	UT_KNIGHT,
	UT_CANNON,
	UT_FOG,
	UT_end,
};

enum eBuildType
{
	BT_TOWN,
	BT_HOME,
	BT_MINE,
	BT_WOOD,
	BT_PORT,
	BT_BARRACK,
	BT_MILL,
	BT_WALL,
	BT_TOWER,
	BT_FINDEND,
	BT_FINDSTART,
	BT_end,
};

enum eAgeType
{
	AT_DARK,
	AT_FEUDAL,
	AT_IMPERIAL,
	AT_CASTLE,
	AT_end
};

enum eSceneType
{
	ST_LOGO,
	ST_STAGE,
	ST_end
};

enum eSortType
{
	SORT_FIRST,
	SORT_MOVE_EFFECT,
	SORT_OBJECT,
	SORT_NORMAL,
	SORT_UI,
	SORT_LOADING,
	SORT_MINIMAP,
	SORT_LAST,
	SORT_MOUSE,
	SORT_end
};

// �ؽ��� Ű
enum eIMG_OBJKEY
{
	OBJKEY_NONE,
	OBJKEY_TILE, // Ÿ�� 
	OBJKEY_RESOURCE, // �ڿ� 
	OBJKEY_BUILD, // �ǹ�
	OBJKEY_VILLAGER, // �ϲ�
	OBJKEY_SHADOW, // �׸���;
	OBJKEY_END,
};

enum eIMG_STATEKEY
{
	STATEKEY_NONE,
	STATEKEY_TILE, // Ÿ�� 
	
	STATEKEY_TREE,
	STATEKEY_ROCK,
	STATEKEY_GOLD,
	STATEKEY_CHERRY,
	STATEKEY_FISH,
	STATEKEY_CHAMCHI,

	STATEKEY_TREESHADOW,
	STATEKEY_END,
};

enum eOBJ_TYPE
{
	OT_NONE,
	OT_TILE,
	OT_RESOURCE,
	OT_UNIT,
	OT_BUILD,
	OT_MOUSE,
	OT_end
};

enum eSTATE_TYPE
{
	STATE_STD,
	STATE_WALK,
	STATE_WALK_BUILD,
	STATE_ATTACK,
	STATE_MINING_GOLD,
	STATE_MINING_STONE,
	STATE_WOOD_CUTTING,
	STATE_GET_CHEERY,
	STATE_CARRY_WOOD,
	STATE_CARRY_CHERRY,
	STATE_CARRY_STONE,
	STATE_CARRY_GOLD,
	STATE_BUILD,
	STATE_FISHING,
	STATE_FISHING_WORK,
	STATE_FOLLOW,
	STATE_DYING,
	STATE_DEATH,
	STATE_end,
};

enum eDIRECTION_TYPE
{
	DIR_UP,
	DIR_UP_L,
	DIR_UP_R,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_DOWN_L,
	DIR_DOWN_R,
	DIR_end
};

enum eSIXTEEN_DIRECTION_TYPE
{
	SIXTEEN_DIR_UP,
	SIXTEEN_DIR_UP_L1,
	SIXTEEN_DIR_UP_L2,
	SIXTEEN_DIR_UP_L3,
	SIXTEEN_DIR_UP_R1,
	SIXTEEN_DIR_UP_R2,
	SIXTEEN_DIR_UP_R3,
	SIXTEEN_DIR_LEFT,
	SIXTEEN_DIR_RIGHT,
	SIXTEEN_DIR_DOWN,
	SIXTEEN_DIR_DOWN_L1,
	SIXTEEN_DIR_DOWN_L2,
	SIXTEEN_DIR_DOWN_L3,
	SIXTEEN_DIR_DOWN_R1,
	SIXTEEN_DIR_DOWN_R2,
	SIXTEEN_DIR_DOWN_R3,
	SIXTEEN_DIR_end
};

enum eARROW_DIRECTION
{
	ARROW_DIR_DOWN,
	ARROW_DIR_DOWN_L7,
	ARROW_DIR_DOWN_L6,
	ARROW_DIR_DOWN_L5,
	ARROW_DIR_DOWN_L4,
	ARROW_DIR_DOWN_L3,
	ARROW_DIR_DOWN_L2,
	ARROW_DIR_DOWN_L1,
	ARROW_DIR_LEFT,
	ARROW_DIR_UP_L1,
	ARROW_DIR_UP_L2,
	ARROW_DIR_UP_L3,
	ARROW_DIR_UP_L4,
	ARROW_DIR_UP_L5,
	ARROW_DIR_UP_L6,
	ARROW_DIR_UP_L7,
	ARROW_DIR_UP,
	ARROW_DIR_UP_R7,
	ARROW_DIR_UP_R6,
	ARROW_DIR_UP_R5,
	ARROW_DIR_UP_R4,
	ARROW_DIR_UP_R3,
	ARROW_DIR_UP_R2,
	ARROW_DIR_UP_R1,
	ARROW_DIR_RIGHT,
	ARROW_DIR_DOWN_R1,
	ARROW_DIR_DOWN_R2,
	ARROW_DIR_DOWN_R3,
	ARROW_DIR_DOWN_R4,
	ARROW_DIR_DOWN_R5,
	ARROW_DIR_DOWN_R6,
	ARROW_DIR_DOWN_R7,
	ARROW_DIR_end,
};

enum eSAVE_RESOURCE_TYPE
{
	SRT_EVERYTHING,
	SRT_TREE,
	SRT_FOOD,
	SRT_MINE,
	SRT_PORT,
	SRT_end,
};

enum eCONTROL_DRAW_TYPE
{
	CDT_VILLAGER_BASE,
	CDT_BATTILEUNIT_BASE,
	CDT_VILLAGER_BUILD_DEST,
	CDT_VILLAGER_BUILD_SOURCE,
	CDT_UNIT_CONTROL,
	CDT_TOWN,
	CDT_PORT,
	CDT_PORT2,
	CDT_BARRACKS,
	CDT_end
};

enum eBUILD_SIZE_TYPE
{
	BST_MIN,
	BST_MID,
	BST_MAX,
	BST_PORT,
	BST_end
};
enum eFORMATION_TYPE
{
	FT_ELLIPSE,
	FT_RECT,
	FT_CHASE,
	FT_LINE,
	FT_end
};
enum eGAUGE_TYPE
{
	GAUGE_MAKE_VILLAGER,
	GAUGE_MAKE_SOLDIER,
	GAUGE_MAKE_KNIGHT,
	GAUGE_MAKE_ARCHER,
	GAUGE_MAKE_GALLYSHIP,
	GAUGE_MAKE_FIRESHIP,
	GAUGE_MAKE_FISHSHIP,
	GAUGE_MAKE_TRANSSHIP,
	GAUGE_MAKE_STONESHIP,
	GAUGE_MAKE_DESTROYSHIP,
	GAUGE_MAKE_SCORPION,
	GAUGE_MAKE_CATAPULT,
	GAUGE_UPGRADE_VILLAGER_SPEED,
	GAUGE_UPGRADE_SOLDIER,
	GAUGE_UPGRADE_KNIGHT,
	GAUGE_UPGRADE_ARCHER,
	GAUGE_UPGRADE_GALLYSHIP,
	GAUGE_UPGRADE_TRANSSHIP,
	GAUGE_UPGRADE_DESTROYSHIP,
	GAUGE_UPGRADE_SCORPION,
	GAUGE_UPGRADE_CATAPULT,
	GAUGE_UPGRADE_AGE,
	UPGRADE_end
};

enum eTRANS_TYPE
{
	TT_ON,
	TT_OFF,
	TT_end,
};
#endif