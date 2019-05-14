#pragma once
//使用するヘッダーファイル
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//描画関係の定数

#define GAME_CLEAR_X (110)
#define GAME_CLEAR_Y (200)
#define GAME_CLEAR_FONT_SIZE (84)

#define NEXT_STAGE_YES_X (190)
#define NEXT_STAGE_YES_Y (380)
#define NEXT_STAGE_YES_FONT_SIZE (62)

#define NEXT_STAGE_NO_X (260)
#define NEXT_STAGE_NO_Y (480)
#define NEXT_STAGE_NO_FONT_SIZE (50)

#define STR_MAX (256)
#define SCORE_INIT (1)
#define SCORE_POS_X (670)
#define SCORE_POS_Y (24)
#define SCORE_POINT_MAX (100)
#define SCORE_INTERVAL (24)
#define SCORE_FONT_SIZE (12)

#define CLICK_START_POS_X (230)
#define CLICK_START_POS_Y (400)
#define CLICK_START_FONT_SIZE (30)

#define CLICK_RESET_POS_X (680)
#define CLICK_RESET_POS_Y (380)
#define CLICK_RESET_FONT_SIZE (16)


//オブジェクト:ステージクリア
class CObjStageClear : public CObj
{
public:
	CObjStageClear() {};
	~CObjStageClear() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	bool m_key_flag;//キーフラグ
	float m_mou_x;  //マウスの位置X
	float m_mou_y;  //マウスの位置Y
	bool m_mou_r;   //マウスの右ボタン
	bool m_mou_l;   //マウスの左ボタン
	int choose;
};