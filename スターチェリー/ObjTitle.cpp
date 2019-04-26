//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjTitle.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

int g_map_chenge = 0;//マップ変更
int block2 = 0;

//イニシャライズ
void CObjTitle::Init()
{
	m_key_flag = false;
	choose = 0;
	m_time = 10;

	//ゲーム実行して一回のみ
	static bool init_point = false;
	if (init_point == false)
	{

		//ロード
		Save::Open();//同フォルダ「UserData」からデータ取得

		init_point = true;
	}

	Save::Seve();//UserDataの情報フォルダ「UserData」を作成
}

//アクション
void CObjTitle::Action()
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
				Scene::SetScene(new CSceneMain());
				g_px = 64.0f;
				g_py = 450.0f;
				m_time = 20;

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
			exit(1);
		}
	}
}

//ドロー
void CObjTitle::Draw()
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
	dst.m_right = 1600.0f;
	dst.m_bottom = 920.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(3, &src, &dst, c, 0.0f);

	float b[4] = { 1,1,1,1 };

	//タイトル
	Font::StrDraw(L"スターチェリー", 30, 125, 60, b);

		if(choose==0)
			Font::StrDraw(L"◇はじめる", GAME_START_POS_X - 55, GAME_START_POS_Y, GAME_START_FONT_SIZE, b);
		else
			Font::StrDraw(L"はじめる", GAME_START_POS_X, GAME_START_POS_Y, GAME_START_FONT_SIZE, b);

		if(choose==1)
			Font::StrDraw(L"◇おわる", GAME_EXIT_POS_X - 55, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, b);
		else
			Font::StrDraw(L"おわる", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, b);
}