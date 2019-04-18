//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"Objgear.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjgear::Init()
{
	m_px = 1050.0f;	//位置
	m_py = 400.0f;
	m_vy = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期化する


	m_damage = 1;

	m_move = false;		//true=右 false=左

	//blockとの追突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_GEAR, 1);
}

//アクション
void CObjgear::Action()
{

	//ダミー
	int d;
	//ブロックとの当たり判定実行
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHitEne(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{

			if (m_map[i][j] == 6)
			{
				/*CObjEnemy1* ene1 = new CObjEnemy1(j*50, i*50);
				Objs::InsertObj(ene1, OBJ_ENEMY, 10);
				m_map[i][j] = 0;*/
			}
		}
	}
}
//ドロー
void CObjgear::Draw()
{

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	for (int i = 0; i < 19; i++)
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
	}
}