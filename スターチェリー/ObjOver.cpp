//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"

#include "GameHead.h"
#include "ObjOver.h"

#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;


extern float g_px;
extern float g_py;

//イニシャライズ
void CObjOver::Init()
{
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
	m_andf2 = false;
}

//アクション
void CObjOver::Action() 
{
	if (Input::GetVKey(VK_UP) == true && choose > 0 && m_time == 0)
	{
		--choose;
		Audio::Start(0);
		m_time = 10;
	}
	if (Input::GetVKey(VK_DOWN) == true && choose < 1 && m_time == 0)
	{
		++choose;
		Audio::Start(0);
		m_time = 10;
	}

	if (m_time > 0) {
		m_time--;
		if (m_time <= 0) {
			m_time = 0;
		}
	}

	if (choose == 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{

			if (m_key_flag == true)
			{
				m_andf = true;
				g_px = 64.0f;
				g_py = 500.0f;
				m_key_flag = false;
				Audio::Start(1);
			}
		}
		else
		{
			m_key_flag = true;
		}
	}
	if (choose == 1)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				m_andf2 = true;
				g_map_chenge = 0;//マップ変更
				Audio::Start(1);
				m_key_flag = false;
			}
		}
		else
		{
			m_key_flag = true;
		}
	}

	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			Scene::SetScene(new CSceneMain());
		}
	}

	if (m_andf2 == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf2 = false;
			Scene::SetScene(new CSceneTitle());
		}
	}
}
//ドロー
void CObjOver::Draw()

{
	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//青
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//黄
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//緑
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

    //切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 702.0f;
	src.m_bottom = 599.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(4, &src, &dst, c, 0.0f);

	float p[4] = { 1,1,1,1 };

	//Font::StrDraw(L"ゲームオーバー", GAME_OVER_X, GAME_OVER_Y, GAME_OVER_FONT_SIZE, p);

	if (choose == 0)
	Font::StrDraw(L"◆やり直す", GAME_YES_X -40	, GAME_YES_Y, GAME_YES_FONT_SIZE, r);
	else
	Font::StrDraw(L"やり直す", GAME_YES_X, GAME_YES_Y, GAME_YES_FONT_SIZE, r);

	if (choose == 1)
	Font::StrDraw(L"◆タイトルに戻る", GAME_NO_X -40, GAME_NO_Y, GAME_NO_FONT_SIZE, r);
	else
	Font::StrDraw(L"タイトルに戻る", GAME_NO_X, GAME_NO_Y, GAME_NO_FONT_SIZE, r);

}
