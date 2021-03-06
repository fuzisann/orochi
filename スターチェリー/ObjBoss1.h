#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト : ボス
class CObjBoss1 : public CObj
{
	public:
		CObjBoss1(float x, float y);
		~CObjBoss1() {};
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
		float m_vxb;      //移動ベクトル
		float m_vyb;
		float m_posture; //姿勢

		int m_ani_time; //アニメーションフレーム動作間隔
		int m_ani_frame;  //描画フレーム
		int m_dotime;

		int m_boss_hp;		//敵の体力
		int m_damage;

		int m_time_d;	//ダメージ時のカラー変更用タイム
		int m_time_die;	//死亡時用タイム

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

		//踏んでいるblockの種類を確認用
		//int m_block_type;
		int s;
		int m_time;
		int m_x;
		int m_y;
		bool m_do_f;//突進フラグ

		float m_subtract;		//追尾用1
		float m_hero_position;	//追尾用2

		bool m_change;	//スイッチのオンオフ
		bool m_delete;
};

