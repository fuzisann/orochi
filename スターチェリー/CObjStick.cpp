//使用するヘッダーファイル
#include"GameHead.h"
#include"CObjStick.h"
#include"GameL\DrawTexture.h"
#include"GameL\HitBoxManager.h"


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjStick::CObjStick(float x, float y)
{
	m_x=x;
	m_y=y;
}

//イニシャライズ
void CObjStick::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hero_x = 0.0f;
	m_hero_y = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 0;

	Hits::SetHitBox(this, m_x, m_y, 50, 50, ELEMENT_MAGIC, OBJ_STICK, 1);
}

//アクション
void CObjStick::Action()
{
	//主人公の情報を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
		m_hero_x = hero->GetX();
		m_hero_y = hero->GetY();
	

}
//ドロー
void CObjStick::Draw()

{
	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 909.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1600.0f;
	dst.m_bottom = 920.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(4, &src, &dst, c, 0.0f);

}
