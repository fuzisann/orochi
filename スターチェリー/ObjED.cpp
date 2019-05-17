//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "SceneMain.h"

#include "GameHead.h"
#include "ObjED.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjED::Init()
{
	m_y = 0.0;
	m_key_flag = true;
}

//アクション
void CObjED::Action()
{


}
//ドロー
void CObjED::Draw()
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
	Font::StrDraw(L"いくつもの苦難を乗り越え見事サメを倒した主人公は、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 400, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"サメの口の中に乙姫様らしき影がある事を知り、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 450, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"サメの口の中から乙姫様を引きずり出しました。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 500, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"主人公は安全な場所まで乙姫様を運び、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 600, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"竜宮城の外に主人公は助けを呼びに行きました。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 650, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"その後乙姫様は、竜宮城の皆に助けられました。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 700, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"暴れていたサメが倒れたことで、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 800, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"竜宮城で操られていた魚たちが続々と意識を取り戻しました。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 850, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"主人公はこの時以来、乙姫様を助けた英雄として、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 950, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"竜宮城に名が知れ渡るようになり、", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1000, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"乙姫様専属の付き人として竜宮城で暮らすようになりました。", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1050, GAME_CLEAR_FONT_SIZE, p);
	
	Font::StrDraw(L"ＥＮＤ", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1200, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"※Enterキーでタイトルへ※", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1300, GAME_CLEAR_FONT_SIZE, p);

	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}