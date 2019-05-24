#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用ネームスペース
using namespace GameL;

//オブジェクト：弓矢
class CObjBubble :public CObj
{
	public :
		CObjBubble(float x,float y);
		~CObjBubble() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー

		int GetDMG() { return m_damage; }//攻撃力を取得

	private:
		float m_x ;	//オブジェクトの位置X
		float m_y ;	//オブジェクトの位置Y
		float m_vx;	//オブジェクトの移動用ベクトルX
		float m_vy;	//オブジェクトの移動用ベクトルY
		float time2;

		//blockとの衝突状態確認用
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;
		int  m_block_type;

		int m_py;
		int m_px;

		int m_time; //攻撃タイミング用
		int m_event;
		bool m_c;

		int m_damage;
};