//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\DrawFont.h"
#include"GameL\UserData.h"
#include"GameHead.h"

#include"ObjRanking.h"
#include"SceneMain.h"



//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjRanking::Init()
{
	m_key_flag = false;
	choose = 1;
	m_time = 5;
	//得点が高い順に並び替えをする
	RankingSort(((UserData*)Save::GetData())->m_ranking);

	//ゲーム実行して一回のみ
	static bool init_point = false;
	if (init_point == false)
	{
		//ロード
		Save::Open();//同フォルダ「UserData」からデータ取得

		 //点数を0にする
		((UserData*)Save::GetData())->minute = ALL_RANKING_SIZE;
		init_point = true;
	}
	//得点の初期化
	((UserData*)Save::GetData())->minute = ALL_RANKING_SIZE;

	//得点が高い順に並び替えをする
	RankingSort(((UserData*)Save::GetData())->m_ranking);

}

//アクション
void CObjRanking::Action()
{
	if (Input::GetVKey(VK_UP) == true && choose > 1 && m_time == 0)
	{
		--choose;
		m_time = 5;
	}
	if (Input::GetVKey(VK_DOWN) == true && choose < 11 && m_time == 0)
	{
		++choose;
		m_time = 5;
	}

	if (m_time > 0) {
		m_time--;
		if (m_time <= 0) {
			m_time = 0;
		}
	}

	if (choose !=0)
	{
		//ボタンが押されたらメインに遷移
		if (Input::GetVKey(VK_BACK) == true)
		{
			if (m_key_flag == true)
			{
				Scene::SetScene(new CSceneTitle());
				//得点の初期化
				((UserData*)Save::GetData())->minute = ALL_RANKING_SIZE;
				m_key_flag = false;
			}
		}
		else
		{
			m_key_flag = true;
		}
	}
	//ランキングリセットの部分と当たり判定
	if (choose==11)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				//ランキング初期化
				for (int i = 0; i < 10; i++)
				{
					((UserData*)Save::GetData())->m_ranking[i] = ALL_RANKING_SIZE;
				}
				m_key_flag = false;
			}
		}
	}
	else
	{
		m_key_flag = true;
	}
}

//ドロー
void CObjRanking::Draw()
{
	float c[4] = { 1,1,1,1 };

	//ランキング
	Font::StrDraw(L"ランキング", RANKING_POS_X, RANKING_POS_Y, RANKING_FONT_SIZE, c);

	//for (int i = 0; i <RANKING_CLASS_MAX; i++)
	//{
	//	wchar_t str[STR_MAX2];
	//	swprintf_s(str, L"%d階層", i + CLASS_INIT);
	//	Font::StrDraw(str, CLASS_POS_X, CLASS_POS_Y + CLASS_INTERVAL *i + 1, CLASS_FONT_SIZE, c);
	//}

	for (int i = 0; i <RANKING_SCORE_MAX; i++)
	{
		wchar_t str[STR_MAX];

		if ((((UserData*)Save::GetData())->m_ranking[i]) ==999)
		{
			swprintf_s(str, L"%d位  0秒", i + SCORE_INIT);
		}
		else
		{
			swprintf_s(str, L"%d位  %d秒", i + SCORE_INIT, ((UserData*)Save::GetData())->m_ranking[i]);
		}
		Font::StrDraw(str, SCORE_POS_X, SCORE_POS_Y + SCORE_INTERVAL*i+1, SCORE_FONT_SIZE, c);
	}

	Font::StrDraw(L"バックスペースでタイトルへ", CLICK_TITLE_GO_X, CLICK_TITLE_GO_Y, TITLE_FONT_SIZE, c);

	//マウスがその位置に行った時の処理
	if (choose == 1)
	    Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y, CLASS_FONT_SIZE,c);

	if (choose == 2)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y +45, CLASS_FONT_SIZE, c);

	if (choose == 3)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y + 90, CLASS_FONT_SIZE, c);

	if (choose == 4)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y + 135, CLASS_FONT_SIZE, c);

	if (choose == 5)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y + 180, CLASS_FONT_SIZE, c);

	if (choose == 6)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y + 225, CLASS_FONT_SIZE, c);

	if (choose == 7)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y + 270, CLASS_FONT_SIZE, c);

	if (choose == 8)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y + 315, CLASS_FONT_SIZE, c);

	if (choose == 9)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y + 360, CLASS_FONT_SIZE, c);

	if (choose == 10)
		Font::StrDraw(L"◇", CLASS_POS_X - 30, CLASS_POS_Y + 400, CLASS_FONT_SIZE, c);

	//ランキングリセット場所
	if (choose == 11)
		Font::StrDraw(L"◇ClickReset", CLICK_RESET_POS_X - 20, CLICK_RESET_POS_Y, CLICK_RESET_FONT_SIZE, c);
	else
		Font::StrDraw(L"ClickReset", CLICK_RESET_POS_X, CLICK_RESET_POS_Y, CLICK_RESET_FONT_SIZE, c);
}
//ランキングソートメゾット
//引数1　int[16] :ランキング用配列
//高順でバブルソートを行う
void CObjRanking::RankingSort(int rank[10])
{
	//値交換用変数
	int w;
	int s;

	//バブルソート
	for (int i = 0; i < 9; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (rank[j] < rank[i])
			{
				//値の交換
				w = rank[i];
				rank[i] = rank[j];
				rank[j] = w;
			}
		}
	}
}
