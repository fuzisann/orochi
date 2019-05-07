//使用すvxるヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameHead.h"
#include"GameL\WinInputs.h"

#include"ObjBackground.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void  C0bjBackground::Init()
{
	m_x1 = 0.0f;
}

//アクション
void  C0bjBackground::Action()
{
	//主人公の位置を取得
	CObjHero*hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
}

//ドロー
void C0bjBackground::Draw()

{

	//描写カラー情報　R=RED G=Green A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,5.0f };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	if (g_map_chenge == 0)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 600.0f;
	}
	else if (g_map_chenge == 1)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 600.0f;
	}
	else if (g_map_chenge == 2)
	{
		src.m_top = 0.0f;
		src.m_left = 1000.0f;
		src.m_right = 1600.0f;
		src.m_bottom = 600.0f;
	}
	else if (g_map_chenge == 3)
	{
		src.m_top = 600.0f;
		src.m_left = 800.0f;
		src.m_right = 800.0f;
		src.m_bottom = 600.0f;
	}
	else if (g_map_chenge == 4)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 640.0f;
		src.m_bottom = 269.0f;
	}
	//描画
	dst.m_top = 0.0f;
	dst.m_left = 0.0f + m_x1;
	dst.m_right = 800.0f + m_x1;
	dst.m_bottom = 600.0f;
	Draw::Draw(3, &src, &dst, c, 0.0f);

}