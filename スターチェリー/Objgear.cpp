//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"Objgear.h"

//使用するネームスペース
using namespace GameL;

CObjgear::CObjgear(float x, float y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjgear::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期化する
	m_ani_max_time = 15;  //アニメーション間隔幅

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GEAR, OBJ_GEAR, 1);
}

//アクション
void CObjgear::Action()
{

	m_ani_time += 1;
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollX(), m_py - 32 + block->GetScrollY());

}
//ドロー
void CObjgear::Draw()
{
	int AniData[5] =
	{
		0,1,2,3,4
	};

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	// 切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 128;
	src.m_right = 128.0f + AniData[m_ani_frame] * 128;
	src.m_bottom = 128.0f;

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//表示位置の設定
	dst.m_top = 0.0f + m_py-32 + block->GetScrollY();
	dst.m_left = 0.0f + m_px + block->GetScrollX();
	dst.m_right = 64.0f + m_px + block->GetScrollX();
	dst.m_bottom = 64.0f + m_py-32 + block->GetScrollY();

	Draw::Draw(10, &src, &dst, c, 0.0f);


	/*for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//ブロック情報を持ってくる
			CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			if (m_map[i][j] == 4)
			{

				//表示位置の設定
				dst.m_top = 0.0f + m_py;
				dst.m_left = (50.0f * m_posture) + m_px + pb->GetScroll();
				dst.m_right = (50 - 50.0f*m_posture) + m_px + pb->GetScroll();
				dst.m_bottom = 50.0f + m_py;

				//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
				Draw::Draw(8, &src, &dst, c, 0.0f);
			}
		}
	}*/
}