#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;


extern float g_px;
extern float g_py;

//オブジェクト : 主人公
class CObjHero : public CObj
{
public:
	CObjHero(int map[19][100]) {};
	~CObjHero() {};
	void Init();   //イ二シャライズ
	void Action();	//アクション
	void Draw();    //ドロー

#define HEROX (64)
#define HEROY (64)

	float GetX() { return g_px; }
	float GetY() { return g_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }
	int GetBT() { return m_block_type; }
	int GetHP() { return m_hero_hp; }	//主人公のHPを取得

	void SetX(float x) { g_px = x; }
	void SetY(float y) { g_py = y; }
	void SetVY(float vy) { m_vy = vy; }
	void SetVX(float vx) { m_vx = vx; }
	void SetBT(int t) { m_block_type = t; }

	void SetUp(bool b) { m_hit_up = b; }
	void SetDown(bool b) { m_hit_down = b; }
	void SetLeft(bool b) { m_hit_left = b; }
	void SetRight(bool b) { m_hit_right = b; }

private:
	int m_map[19][100]; //マップ情報
	float m_vx;      //移動ベクトル
	float m_vy;
	float m_posture; //姿勢

	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;  //描画フレーム

	int m_hero_hp;	//体力(戦闘)
	int m_max_hp;	//HPの最大値

	int m_damage;	//主人公が受けるダメージ用

	float m_speed_power; //スピードパワー
	float m_speed_pow;   //しゃがむ速度
	float m_ani_max_time;//アニメーション動画間隔最大値

	int m_time_d;	//ダメージ無敵時間用

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//踏んでいるblockの種類を確認用
	int m_block_type;
	int s;
	int m_time;
	int m_x;
	int m_y;
	bool m_key_flag; //キーフラグ

};