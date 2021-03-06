#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト : 敵(あじ)
class CObjEnemy1 : public CObj
{
	#define ALL_ENEMY_SIZE (32.0f)
	public:
		CObjEnemy1(float x, float y) ;
		~CObjEnemy1() {};
		void Init();   //イ二シャライズ
		void Action();	//アクション
		void Draw();    //ドロー

		float GetVX() { return m_vx; }
		int GetDMG() { return m_damage; }//攻撃力を取得

	private:
		int m_map[50][150]; //マップ情報
		float m_px;      //位置
		float m_py;
		float m_vx;      //移動ベクトル
		float m_vy;
		float m_posture; //姿勢

		int m_ani_time; //アニメーションフレーム動作間隔
		int m_ani_frame;  //描画フレーム

		int m_enemy_hp;		//敵の体力
		int m_damage;

		int m_time_d;	//ダメージ時のカラー変更用タイム

		float m_speed_power; //スピードパワー
		float m_ani_max_time;//アニメーション動画間隔最大値

		//blockとの衝突状態確認用
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;

		//移動の向き制御用
		bool m_move;

		bool m_del;			//削除チェック
		bool m_eff_flag;	//エフェクト用フラグ

		int m_time_dead;	//死亡用
		bool  m_inputf;	//動き制御用

		int hero_hp;

		//踏んでいるblockの種類を確認用
		//int m_block_type;
		int s;
		int m_time;
		int m_x;
		int m_y;
};
