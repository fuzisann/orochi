//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjChangeSwitch.h"


//使用するネームスペース
using namespace GameL;


CObjChangeSwitch::CObjChangeSwitch(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjChangeSwitch::Init()
{
	m_change = false;	//画像切り替え
	m_time = 0;
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_FIELD, OBJ_CHANGESWITCH, 1);
}

//アクション
void CObjChangeSwitch::Action()
{
	/*if (g_battle_flag == true)
	{
		return;
	}*/

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	//主人公と当たっているか確認
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		if (m_change == true) {
			m_change = false;
		}
		else {
			m_change = true;
		}
		hit->SetInvincibility(true);	//無敵オン
		m_time = 100;
	}
	/*if (m_time > 0)
	{
		m_time--;
		if (m_time <= 0)
		{
			m_time = 0;
			hit->SetInvincibility(false);	//無敵オフ
		}
	}*/
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScroll(), m_py);

}

//ドロー
void CObjChangeSwitch::Draw()
{
	/*if (g_battle_flag == true)
	{
		return;
	}*/

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float g[4] = { 0.0f,1.0f,1.0f,1.0f };
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };



	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;	//描画に対してスクロールの影響を加える
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 32.0f + m_px + block->GetScroll();
	dst.m_bottom = 32.0f + m_py;

	//描画
	if (m_change == false) {
		Draw::Draw(6, &src, &dst, g, 0.0f);
	}
	else if (m_change == true) {
		Draw::Draw(6, &src, &dst, y, 0.0f);
	}
}


