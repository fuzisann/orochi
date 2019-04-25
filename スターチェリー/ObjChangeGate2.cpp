//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjChangeGate2.h"


//使用するネームスペース
using namespace GameL;

//extern bool m_change;


CObjChangeGate2::CObjChangeGate2(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjChangeGate2::Init()
{
	m_vx = 0.0f;		//移動ベクトル
	m_vy = 0.0f;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_MYSTERY, OBJ_CHANGEGATE, 1);
}

//アクション
void CObjChangeGate2::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);
	//チェンジスイッチの情報を取得
	//CObjChangeSwitch* change = (CObjChangeSwitch*)Objs::GetObj(OBJ_CHANGESWITCH);
	//m_change = change->GetCHANGE();

	//チェンジフラグがオンの場合
	if (m_change == true) {
		hit->SetInvincibility(true);	//無敵オン
	}
	else {
		hit->SetInvincibility(false);	//無敵オフ
	}

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScroll(), m_py);
}

//ドロー
void CObjChangeGate2::Draw()
{
	/*if (g_battle_flag == true)
	{
		return;
	}*/
	//描画カラー情報
	float g[4] = { 0.0f,1.0f,1.0f,1.0f };
	float a[4] = { 0.0f,0.0f,0.0f,0.0f };

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
	if (m_change == true) {
		Draw::Draw(7, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(7, &src, &dst, g, 0.0f);
	}
}


