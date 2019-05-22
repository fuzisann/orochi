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
	CObjHero(int map[50][150]) {};
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
	float GetPOS() { return m_posture; }//主人公の向きを取得
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
	int m_map[50][150]; //マップ情報
	
	float m_px;			//位置
	float m_py;
	float m_vx;      //移動ベクトル
	float m_vy;
	float m_posture; //姿勢
	float Gethp() { return m_hero_hp; }

	int m_ani_time; //アニメーションフレーム動作間隔
	int m_ani_frame;  //描画フレーム

	int m_hero_hp;	//体力(戦闘)
	int m_max_hp;	//HPの最大値
	int Width;      //画像の幅最大値

	int m_damage;	//主人公が受けるダメージ用

	float m_speed_power; //スピードパワー
	float m_speed_pow;   //しゃがむ速度
	float m_ani_max_time;//アニメーション動画間隔最大値
	float m_swordwidth; //ソード幅

	int m_time_d;	//ダメージ無敵時間用
	int m_sword_delay;	//剣攻撃間隔用

	int m_time_dead;	//死亡用
	
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
	bool m_gate_on;		//ゲートオンオフ切り替え用

	int m_ani;			//死亡アニメーション用
	int m_ani_time_d;	//死亡アニメーション間隔タイム
	bool m_del;			//削除チェック
	bool m_eff_flag;	//エフェクト用フラグ

	bool  m_inputf;	//死亡用キー入力制御
	bool  m_inputw;	//攻撃キー入力制御用

	wchar_t str[256];
};