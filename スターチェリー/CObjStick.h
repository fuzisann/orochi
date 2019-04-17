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
	bool m_x;
	bool m_y;
	int m_ani_time;
	int m_ani_frame;

};

