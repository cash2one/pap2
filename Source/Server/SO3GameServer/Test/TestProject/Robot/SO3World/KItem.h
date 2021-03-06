/************************************************************************/
/* 道具			                                                        */
/* Copyright : Kingsoft 2005										    */
/* Author	 : Zhu Jianqiu												*/
/* History	 :															*/
/*		2004.12.31	Create												*/
/************************************************************************/
#ifndef _KITEM_H_
#define _KITEM_H_

#include "Global.h"
#include "KBaseObject.h"
#include "KAttribute.h"
#include "KItemInfoList.h"
#include "Luna.h"

//道具的种类
enum ITEM_GENRE
{
	igEquipment = 0,	//装备
	igPotion,			//药品
	igTaskItem,			//任务道具
	igMaterial,			//材料
	igTotal
};

//装备的大致分类
enum EQUIPMENT_SUB_TYPE
{
	estMeleeWeapon = 0,		//近战武器
	estRangeWeapon,			//远程武器
	estChest,				//上衣
	estHelm,				//头部
	estAmulet,				//项链
	estRing,				//戒指
	estWaist,				//腰带
	estPendant,				//腰缀
	estPants,				//裤子
	estBoots,				//鞋子
	estBangle,				//护臂
	estExtend,				//扩展类装备，酒壶之类的
	estPackage,				//包裹
	estArrow,				//暗器
	estTotal
};

//武器的具体分类
enum WEAPON_DETAIL_TYPE
{
    wdtWand = 0,        // 棍
    wdtSpear,           // 枪
    wdtSword,           // 剑
    wdtFist,            // 拳套
    wdtDoubleWeapon,    // 双手武器,比如: 双刀,双伞
    wdtPen,             // 笔
    wdtSlingShot,       // 钝器
    wdtDart,            // 锐器
    wdtMachDart,        // 机关暗器
	wdtTotal
};

//道具品质
enum ITEM_QUALITY
{
	iqLow = 0,				//劣品
	iqNormal,				//普通装备，白色
	iqGood,					//优质
	iqTotal
};

//绑定类型
enum ITEM_BIND_TYPE
{
	ibtInvalid = 0,
	ibtNeverBind,
	ibtBindOnEquipped,
	ibtBindOnPicked,
	ibtTotal
};

enum USE_ITEM_SKILL_TYPE
{
	uistInvalid = 0,

	uistCannotUse,
	uistUseInPackage,
	uistUseWhenEquipped,

	uistTotal
};

typedef struct _COMMON_ATTRIBUTE
{
	char				szItemName[ITEM_NAME_LEN];	// 名称
	int					nLevel;						// 等级
	int					nPrice;						// 价格
	int					nGenre;						// 大类
	int					nSub;						// 小类
	int					nDetail;					// 细类
	int					nBindType;					// 绑定类型
	BOOL				bCanTrade;					// 是否可买卖
	BOOL				bCanDestory;				// 是否可摧毁	TODO： --spe
	BOOL				bConsumeDurabiltity;		// 是否消耗耐久
	BOOL				bStack;						// 是否能够叠放
	int					nAbradeRate;				// 被磨损机率
} COMMON_ATTRIBUTE;

typedef struct _GENERATE_PARAM
{
	int					nVersion;
	DWORD				dwTabType;
	DWORD				dwIndex;
	time_t				nGenTime;
	DWORD				dwRandSeed;
	int					nQuality;					// 道具品质 (普通? 黄金? )
	int					nMagicIndex[MAX_ITEM_MAGIC_COUNT];
} GENERATE_PARAM;

class KItem : public KBaseObject
{
//数值属性
public:
	KItem(void);
	~KItem(void);

	BOOL Init(void);
	BOOL UnInit(void);

	GENERATE_PARAM		m_GenParam;				//生成需要的参数
	COMMON_ATTRIBUTE	m_Common;				//一般属性

	USE_ITEM_SKILL_TYPE	m_eUseType;				//使用物品技能的类型
	DWORD				m_dwSkillID;			//技能ID
	DWORD				m_dwSkillLevel;			//技能等级

	KAttribute*			m_pBaseAttr;			//基础属性
	KAttribute*			m_pRequireAttr;			//需求属性
	KAttribute*			m_pMagicAttr;			//魔法属性
	KAttribute*			m_pEnchant;				//附魔属性
	KAttribute*			m_pTemporaryEnchant;	//限时附魔
	int					m_nTemporaryEnchantTime;//限时附魔结束时间

	DWORD				m_dwScriptID;			//脚本ID

	union
	{
		int				m_nCurrentDurability;	//当前耐久度
		int				m_nStackNum;			//当前叠加数量
	};
	union
	{
		int				m_nMaxDurability;		//最大耐久度(某些装备，此值会动态变化)
		int				m_nMaxStackNum;			//最大叠加上限
		int				m_nPackageSize;			//背包格子数量
	};

	BOOL				m_bBound;				//是否被绑定
	int					m_nRepresentId;			//表现逻辑ID
	BOOL				m_bApplyed;				//是否已应用属性
	BOOL				m_bEquiped;				//是否已经装备

#if defined(_CLIENT)
	int					m_nUiId;				//界面ID
#endif	//_CLIENT

public:
	BOOL				SetStackNum(int nStackNum);
	int					GetStackNum();
	int					GetMaxStackNum();
	int					GetMaxExistAmount();				//获取物品的数量限制,0是无限制
	int					GetMaxExistTime();					//下线后物品的存在时间,0是无限制
	int					Stack(int nCount);
    BOOL                SetCurrentDurability(int nDurability);
    int                 GetCurrentDurability();
    int                 GetMaxDurability();
	int					GetGenre() { return m_Common.nGenre; };
	int					GetPrice() { return m_Common.nPrice; };
	BOOL				IsBound() { return m_bBound; };
	BOOL				IsStackable();
	BOOL				IsRepairable();
	BOOL				IsCanTrade() { return m_Common.bCanTrade; };
	BOOL				IsCanDestory() { return m_Common.bCanDestory; };
	BOOL				CanStack(KItem* pDest);
	int					Repair();
	BOOL				Abrade();

public:
	//Lua脚本接口
	DECLARE_LUA_CLASS(KItem);

	DECLARE_LUA_STRUCT_STRING(Name, ITEM_NAME_LEN, m_Common.szItemName);
	DECLARE_LUA_STRUCT_INTEGER(Level, m_Common.nLevel);
	DECLARE_LUA_STRUCT_INTEGER(Price, m_Common.nPrice);
	DECLARE_LUA_STRUCT_INTEGER(Genre, m_Common.nGenre);
	DECLARE_LUA_STRUCT_INTEGER(Sub, m_Common.nSub);
	DECLARE_LUA_STRUCT_INTEGER(Detail, m_Common.nDetail);
	DECLARE_LUA_STRUCT_INTEGER(BindType, m_Common.nBindType);
	DECLARE_LUA_STRUCT_BOOL(CanTrade, m_Common.bCanTrade);
	DECLARE_LUA_STRUCT_BOOL(CanDestory, m_Common.bCanDestory);
	DECLARE_LUA_STRUCT_BOOL(CanStack, m_Common.bStack);
	DECLARE_LUA_STRUCT_BOOL(CanConsume, m_Common.bConsumeDurabiltity);
	DECLARE_LUA_STRUCT_DWORD(TabType, m_GenParam.dwTabType);
	DECLARE_LUA_STRUCT_DWORD(Index, m_GenParam.dwIndex);
	DECLARE_LUA_STRUCT_INTEGER(Quality, m_GenParam.nQuality)

	DECLARE_LUA_STRUCT_INTEGER(Version, m_GenParam.nVersion);

	DECLARE_LUA_INTEGER(CurrentDurability);
	DECLARE_LUA_INTEGER(StackNum);
	DECLARE_LUA_INTEGER(MaxDurability);
	DECLARE_LUA_INTEGER(MaxStackNum);

	DECLARE_LUA_BOOL(Bound);
	DECLARE_LUA_INTEGER(RepresentId);
#if defined(_CLIENT)
	DECLARE_LUA_INTEGER(UiId);
#endif	//_CLIENT
	int LuaGetBaseAttrib(Lua_State* L);
	int LuaGetRequireAttrib(Lua_State* L);
	int LuaGetMagicAttrib(Lua_State* L);
	int LuaGetUseSkill(Lua_State* L);
	int LuaHasScript(Lua_State* L);
};
#endif	//_KITEM_H_