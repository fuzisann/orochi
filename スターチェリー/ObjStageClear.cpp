//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include"GameL\UserData.h"
#include"SceneMain.h"

#include "GameHead.h"
#include "ObjStageClear.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjStageClear::Init()
{
	choose = 0;
}

//アクション
void CObjStageClear::Action()
{
	Save::Seve();//UserDataの情報フォルダ「UserData」を作成する;

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
				g_px = 64.0f;
				g_py = 500.0f;

				g_map_chenge += 1;
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
		if (Input::GetVKey(VK_RETURN) == true)
		{
			Scene::SetScene(new CSceneTitle());
			g_map_chenge = 0;//マップ変更
			m_key_flag = false;
		}
	}
}
//ドロー
void CObjStageClear::Draw()

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
	src.m_right = 1600.0f;
	src.m_bottom = 909.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1600.0f;
	dst.m_bottom = 920.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(4, &src, &dst, c, 0.0f);

	float p[4] = { 1,1,1,1 };

	//Font::StrDraw(L"ステージクリア", GAME_CLEAR_X, GAME_CLEAR_Y, GAME_CLEAR_FONT_SIZE, p);

	if (choose == 0)
		Font::StrDraw(L"◆次のステージ", NEXT_STAGE_YES_X -40, NEXT_STAGE_YES_Y, NEXT_STAGE_YES_FONT_SIZE, p);
	else
		Font::StrDraw(L"次のステージ", NEXT_STAGE_YES_X, NEXT_STAGE_YES_Y, NEXT_STAGE_YES_FONT_SIZE, p);
	if (choose == 1)
		Font::StrDraw(L"◆タイトルへ", NEXT_STAGE_NO_X - 40, NEXT_STAGE_NO_Y, NEXT_STAGE_NO_FONT_SIZE, p);
	else
		Font::StrDraw(L"タイトルへ", NEXT_STAGE_NO_X, NEXT_STAGE_NO_Y, NEXT_STAGE_NO_FONT_SIZE, p);
}