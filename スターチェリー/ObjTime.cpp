//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\DrawFont.h"
#include"GameL\UserData.h"

#include"GameHead.h"
#include"ObjTime.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void C0bjTime::Init()
{
	m_time = 0;
	m_flag_time = false;
}

//アクション
void C0bjTime::Action()
{
	//主人公の位置を取得
	C0bjHero*hero = (C0bjHero*)Objs::GetObj(COBJ_HERO);

	//スタートブロックを踏んでいるならフラグをオンにする
	if (gh_spx == 64.0f || gh_spy == 500.0f)
	{
		m_flag_time = true;
	}

	//フラグがオンの時、時間を進める
	if (m_flag_time == true)
	{
		m_time++;

		if (timekeeper[i] > m_time)
		{
			timekeeper[i] = m_time;
		}
	}
}

//ドロー
void C0bjTime::Draw()
{
	//m_timeから秒分お求める

	int minute;
	minute= (m_time / 60) % 999; //秒

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	wchar_t str[128];
	//分:秒の値を文字列比
	swprintf_s(str, L"%d秒", ((UserData*)Save::GetData())->minute = minute);//秒の1桁目に0を用意
	Font::StrDraw(str, 10, 10, 20, c);
}



