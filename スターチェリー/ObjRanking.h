#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include"ObjTime.h"
//使用するネームスペース
using namespace GameL;

//定数
//マウスクリックのメイン遷移（せんい）
#define MOU_MAIN_HIT_X (230)
#define MOU_MAIN_HIT_V (450)
#define MOU_MAIN_HIT_Y (400)
#define MOU_MAIN_HIT_H (430)

//描画関係の定数
#define RANKING_CLASS_MAX (10)
#define CLASS_INIT (1)
#define CLASS_POS_X (89)
#define CLASS_ALL_POS_X (89)
#define CLASS_ALL_POS_X2 (174)
#define CLASS_POS_Y (109)
#define CLASS_ALL_POS_Y (105)
#define CLASS_ALL_POS_Y2 (140)
#define CLASS_FONT_SIZE (35)
#define CLASS_INTERVAL (45)

#define RANKING_POS_X (256)
#define RANKING_POS_Y (22)
#define RANKING_FONT_SIZE (50)
#define RANKING_SCORE_MAX (9)

#define STR_MAX (256)
#define STR_MAX2 (256)


#define CLICK_TITLE_GO_X  (30)
#define CLICK_TITLE_GO_Y  (50)
#define TITLE_FONT_SIZE (15)

#define SCORE_INIT (1)
#define SCORE_POS_X (516)
#define SCORE_POS_Y (109)
#define SCORE_POINT_MAX (100)
#define SCORE_INTERVAL (45)
#define SCORE_FONT_SIZE (35)

#define CLICK_RESET_POS_X (670)
#define CLICK_RESET_POS_Y (570)
#define CLICK_RESET_FONT_SIZE (20)

#define CLICK_RESET_POS_X (670)
#define CLICK_RESET_POS_Y (570)
#define CLICK_RESET_FONT_SIZE (20)


//オブジェクト : タイトル
class CObjRanking : public CObj
{
public:
	CObjRanking() {};
	~CObjRanking() {};
	void Init();   //イ二シャライズ
	void Action();	//アクション
	void Draw();    //ドロー

private:
	float m_mou_x;  //マウスの位置X
	float m_mou_y;  //マウスの位置Y
	bool m_mou_r;   //マウスの右ボタン
	bool m_mou_l;   //マウスの左ボタン

private:
	bool m_key_flag;//キーフラグ
	int choose;
	int m_time;

	//ランキングソートメゾット
	void RankingSort(int rank[10]);
};