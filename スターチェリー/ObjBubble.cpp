//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBubble.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

CObjBubble::CObjBubble(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjBubble::Init()
{
	m_vx    = -1.0f;
	m_vy    =  0.0f;
	m_event = 0;
	time2   = 0;
	//当たり判定用hitBox作成
	Hits::SetHitBox(this, m_px, m_py, 15, 15, ELEMENT_ENEMY, OBJ_BUBBLE, 1);
}

//アクション
void CObjBubble::Action()
{

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//ベクトルの長さを求める
	float r = 0.0f;
	r = m_vx*m_vx + m_vy*m_vy;
	r = sqrt(r);

	//長さが0かどうか調べる
	if (r == 0.0f)
	{
		;//0なら何もしない
	}
	else
	{
		//正規化を行う
		m_vx = 1.0f / r*m_vx;
		m_vy = 1.0f / r*m_vy;
	}
	check = false;

	//イベント1　矢が発射
	if (m_event == 1)
	{
		//速度付ける。
		m_vx = -5.5f;
		m_vy = 0.0f;
	}

	//イベント0　矢がひょっこりでる。
	/*if (m_event == 0)
	{
		//速度付ける。
		m_vx = 0.0f;
		m_vy = 0.0f;
		time2 += 1.0f;
		m_c = false;
		if (time2 >= 100)
		{
			m_event = 1;
			time2 = 0;
		}
	}*/

	//移動ベクトルを座標に加算する
	m_x += m_vx;
	m_y += m_vy;

	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y+16);

	//HitBoxの位置を変更	
	hit->SetPos(m_x + block->GetScrollX(), m_y+8 + block->GetScrollY());

	//ブロックに当たると削除
	/*if (m_hit_right == true || m_hit_left == true
	 || m_hit_up == true || m_hit_down == true)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}*/


	//画面外に出たら弓矢を破棄する処理
	/*if (m_x + block->GetScrollX() > 800.0f ||
		m_x + block->GetScrollX() < -45.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}*/

	//敵と当ったているか確認
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		//主人公が敵とどの角度当ったているかを確認
		HIT_DATA**hit_data;           //当たった時の細かな情報を入れるための構造体
		hit_data = hit->SearchObjNameHit(COBJ_HERO);//hit_dataに主人公と当たっている他全てのHitBoxとの情報を入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			//敵の左右に当たったら
			float r = 0;
			for (int i = 0; i < 10; i++)
			{
				if (hit_data[i] != nullptr) {
					r = hit_data[i]->r;
				}
			}
			if (m_c==true)
			{
				this->SetStatus(false);
				Hits::DeleteHitBox(this);
			}
		}
	}

	//ブロックとの当たり判定実行
	/*Objwall* pd = (Objwall*)Objs::GetObj(OBJ_WALL);
	if (pd != nullptr)
	{
		pd->wallHit(&m_x, &m_y, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type
		);
	}*/
}

//ドロー
void CObjBubble::Draw()
{
	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 15.0f;
	src.m_bottom = 15.0f;

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//表示位置の設定
	dst.m_top    =  0.0f   +m_y + block->GetScrollY();
	dst.m_left   =  0.0f   +m_x + block->GetScrollX();
	dst.m_right  = 15.0f   +m_x + block->GetScrollX();
	dst.m_bottom = 15.0f   +m_y + block->GetScrollY();

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(18, &src, &dst, c, 0.0f);
}
