#pragma once
//使用するヘッダー
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト:スティック
class CObjStick :public CObj
{
public:
	CObjStick(float x, float y) ;  //コンストラクタ
	~CObjStick() {};
	void Init();
	void Action();
	void Draw();

private:
	bool m_f = true;
	float m_x;		//X方向の位置用変数
	float m_y;		//Y方向の位置用変数
	float m_vx;		//X方向の速度用変数
	float m_vy;		//Y方向の速度用変数
	
	float m_hero_x;
	float m_hero_y;
	int m_ani_time;
	int m_ani_frame;

};

