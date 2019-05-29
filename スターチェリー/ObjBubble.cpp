//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBubble.h"
#include "ObjBlock.h"
#include "UtilityModule.h"

#include "GameL\Audio.h"

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

	m_damage = 1;

	//移動ベクトルの正規化
	UnitVec(&m_vx, &m_vy);

	//当たり判定用hitBox作成
	Hits::SetHitBox(this, m_x, m_y, 35, 35, ELEMENT_BUBBLE, OBJ_BUBBLE, 1);
}

//アクション
void CObjBubble::Action()
{
	//主人公と泡で角度を取る
	CObjHero* obj = (CObjHero*)Objs::GetObj(COBJ_HERO);

	CObjBlock*b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公が存在する場合、誘導角度の計算する
	if (obj != nullptr)
	{
		float x = obj->GetX() - m_x- b->GetScrollX();
		float y = obj->GetY() - m_y- b->GetScrollY();
		float ar = GetAtan2Angle(x, -y);

		//弾丸の現在の向いている角度を取る
		float br = GetAtan2Angle(m_vx, -m_vy);

		//主人公機と敵機角度があまりにもかけ離れたら
		
		if (ar - br > 20)
		{
			//移動方向を主人公機の方向にする
			m_vx = cos(3.14 / 180 * ar);
			m_vy = -sin(3.14 / 180 * ar);
		}
		
		float yy = m_vy;
		float xx = m_vx;
		float r = 3.14 / 180.0f;	//角度１°
		if (ar < br)
		{
			//移動方向にに+1°加える
			m_vx = xx * cos(r) - yy * sin(r);
			m_vy = yy * cos(r) + xx * sin(r);
		}
		else
		{
			//移動方向にに-1°加える
			m_vx = xx * cos(-r) - yy * sin(-r);
			m_vy = yy * cos(-r) + xx * sin(-r);
		}
		UnitVec(&m_vx, &m_vy);

	}

	//移動ベクトルを座標に加算する
	m_x += m_vx * 5.0f;
	m_y += m_vy * 5.0f;

	//HitBoxの内容を更新
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置を変更	
	hit->SetPos(m_x + block->GetScrollX(), m_y + block->GetScrollY());

	//ブロックに当たると削除
	/*if (m_hit_right == true || m_hit_left == true
	 || m_hit_up == true || m_hit_down == true)
	{
		Audio::Start(5);	//音
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;
	}*/

	//画面外に出たら破棄する処理
	if (m_x + block->GetScrollX() > 800.0f || m_x + block->GetScrollX() < -45.0f
		&& m_y + block->GetScrollY() > 600.0f || m_y + block->GetScrollY() < 45.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;
	}

	//主人公オブジェクトと接触したら誘導弾丸削除
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		Audio::Start(9);	//音
		hit->SetInvincibility(true);//当たり判定無効
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;
	}

	//剣が当たったら泡削除
	if (hit->CheckElementHit(ELEMENT_ATTACK) == true)
	{
		Audio::Start(7);	//音
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;
	}

	//完全に領域外に出たら破棄する
	/*bool Check = CheckWindow(m_x, m_y, -32.0f, -32.0f, 800.0f, 600.0f);
	if (Check == false)
	{
		this->SetStatus(false);		//自身に削除命令を出す。
		Hits::DeleteHitBox(this);	//敵機弾丸が所有するHitBoxに削除する。
	}*/
}

//ドロー
void CObjBubble::Draw()
{
	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 35.0f;
	src.m_bottom = 35.0f;

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top    =  0.0f   +m_y + block->GetScrollY();
	dst.m_left   =  0.0f   +m_x + block->GetScrollX();
	dst.m_right  = 35.0f   +m_x + block->GetScrollX();
	dst.m_bottom = 35.0f   +m_y + block->GetScrollY();

	float r = 0.0f;
	//主人公機と誘導弾丸で角度を取る
	CObjHero* obj = (CObjHero*)Objs::GetObj(COBJ_HERO);

	//主人公機が存在する場合、誘導角度の計算する
	if (obj != nullptr)
	{
		float x = obj->GetX() - m_x;
		float y = obj->GetY() - m_y;
		r = GetAtan2Angle(x, -y);
	}

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(21, &src, &dst, c, r);
}
