//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "SceneMain.h"

#include "GameHead.h"
#include "ObjOP.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjOP::Init()
{
	m_y = 0.0;
	m_key_flag = true;
}

//アクション
void CObjOP::Action()
{
	

}
//ドロー
void CObjOP::Draw()
{
	//描写カラー情報
	float bl[4] = { 0.7f,0.7f,0.7f,1.0f };

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
	Draw::Draw(3, &src, &dst, bl, 0.0f);

	float p[4] = { 1,1,1,1 };

	if (Input::GetVKey(VK_RETURN) == true)
	{
		m_y -= 3.0f;
	}
	else
	{
		m_y -= 0.6f;
	}
	Font::StrDraw(L"～あらすじ～", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 400, 40, p);
	Font::StrDraw(L"ある日、突然サメが竜宮城を乗っ取るために攻めてきました。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 500, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"そのサメを恐れた竜宮城の魚たちは、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 550, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"竜宮城から逃げ出してしまいました。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 600, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"慌てて竜宮城から逃げ出してきた魚たちを見て、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 700, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"主人公は竜宮城で何かが起きている事を感知し、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 750, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"竜宮城に向かうのでした。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 800, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"竜宮城に向かった主人公は、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 900, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"竜宮城から逃げ遅れた魚たちがサメに操られている光景や、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 950, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"サメが竜宮城で暴れている光景を目にしたのでした。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1000, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"※Enterキーで次へ進む※", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1150, GAME_CLEAR_FONT_SIZE, p);

	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneOperation());
	}
}