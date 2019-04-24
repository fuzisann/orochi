#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト
class CObjHeroSword : public CObj
{
	public:
		CObjHeroSword(float x, float y);		//コンストラクタ
		~CObjHeroSword() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー

	private:
		float m_x;		//X方向の位置用変数
		float m_y;		//Y方向の位置用変数
		float m_vx;		//X方向の速度用変数
		float m_vy;		//Y方向の速度用変数

		float m_hero_x;
		float m_hero_y;

		bool m_hit;	//衝突判定
		float m_posture;	//向き

		int m_ani_frame_x;	//アニメーション用変数
		int m_ani_frame_y;

		int m_sword_time;		//剣が消える時間

		int m_time;

		//blockとの衝突状態確認用
		bool m_hit_left;
		bool m_hit_right;
};

