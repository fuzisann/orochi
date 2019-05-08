#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


extern float g_px;
extern float g_py;

//オブジェクト : ゴールブロック
class CObjgoalblock : public CObj
{
#define ALL_BLOCK_SIZE (64.0f)
public:
	CObjgoalblock(float x,float y);
	~CObjgoalblock() {};
	void Init();   //イ二シャライズ
	void Action();	//アクション
	void Draw();    //ドロー
	int m_map[50][150]; //マップ情報

private:
	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;  //描画フレーム
	float m_ani_max_time;//アニメーション動画間隔最大値
	int m_py;
	int m_px;
};