//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"

#include "GameHead.h"
#include "ObjMenu.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMenu::Init()
{
	choose = 0;
	m_time = 10;
}

//アクション
void CObjMenu::Action()
{
	if (Input::GetVKey(VK_UP) == true)
	{
		choose = 0;
	}
	if (Input::GetVKey(VK_DOWN) == true)
	{
		choose = 1;
	}

	if (choose == 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{

			if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneMain());
				m_key_flag = false;
			}
		}
		else
		{
			m_key_flag = true;
		}
	}
	if (choose == 1)
	{
		if (Input::GetVKey(VK_BACK) == true)
		{
			Scene::SetScene(new CSceneTitle());
			m_key_flag = false;
		}
	}
}
//ドロー
void CObjMenu::Draw()

{
	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

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
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(4, &src, &dst, c, 0.0f);

	float b[4] = { 1,1,1,1 };

	Font::StrDraw(L"メニュー", 230, 100, 90, c);

	if(choose==0)
		Font::StrDraw(L"◇ゲームに戻る", GAME_BACK_X -40,GAME_BACK_Y, GAME_DOBLE_FONT, c);
	else
		Font::StrDraw(L"ゲームに戻る", GAME_BACK_X, GAME_BACK_Y, GAME_DOBLE_FONT, c);
	if (choose == 1)
		Font::StrDraw(L"◇タイトルに戻る", TITLE_BACK_X -40, TITLE_BACK_Y, GAME_DOBLE_FONT, c);
	else
		Font::StrDraw(L"タイトルに戻る", TITLE_BACK_X, TITLE_BACK_Y, GAME_DOBLE_FONT, c);
}
