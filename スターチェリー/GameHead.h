#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,
	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	COBJ_HERO,
	OBJ_MAIN,
	OBJ_TITLE,
	OBJ_BACKGROUND,
	OBJ_CLEAR,
	OBJ_BLOCK,
	OBJ_OVER,
	OBJ_TIME,
	OBJ_GOAL_BLOCK,

	OBJ_ENEMY,
	OBJ_ENEMY_FIRST,
	OBJ_ENEMY_SECOND,

	OBJ_BOSS_FIRST,
	OBJ_BOSS_SECOND,
	OBJ_BOSS_THIRD,

	OBJ_STICK,
	OBJ_SWORD,
	OBJ_GEAR,
	OBJ_SWITCH,
	OBJ_CHANGESWITCH,
	OBJ_CHANGEGATE,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,
	//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
	ELEMENT_ATTACK,
	ELEMENT_GEAR,
	ELEMENT_MYSTERY,
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ

};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--
extern int g_map_chenge;//マップ変更
extern int block2;

//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
#include "CObjHero.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjClear.h"
#include "Objgoalblock.h"
#include "ObjOver.h"
#include "ObjTitle.h"
#include "ObjEnemy1.h"
#include "ObjEnemy2.h"
#include "ObjMain.h"
#include "CObjStick.h"
#include "Objgear.h"
#include "CObjHeroSword.h"
#include "ObjBoss1.h"
#include "ObjBoss2.h"
#include "ObjBoss3.h"
#include "ObjSwitch.h"
#include "ObjChangeSwitch.h"
#include "ObjChangeGate1.h"
#include "ObjChangeGate2.h"

//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneOver.h"
#include "SceneTitle.h"

//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START CSceneMain
#define SET_GAME_START CSceneTitle
//-----------------------------------------------