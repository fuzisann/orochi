//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjChangeGate1.h"


//使用するネームスペース
using namespace GameL;

extern bool m_change;

CObjChangeGate1::CObjChangeGate1(float x, float y)
{
	m_px = x;		//位置
	m_py = y;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_MYSTERY, OBJ_CHANGEGATE, 1);
}

//イニシャライズ
void CObjChangeGate1::Init()
{
	m_vx = 0.0f;		//移動ベクトル
	m_vy = 0.0f;
}

//アクション
void CObjChangeGate1::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);

	//チェンジスイッチの情報を取得
	CObjChangeSwitch* change = (CObjChangeSwitch*)Objs::GetObj(OBJ_CHANGESWITCH);
	//m_change = change->GetCHANGE();

	/*CObjChangeGate1* change = (CObjChangeGate1*)Objs::GetObj(OBJ_CHANGEGATE);
	m_change = change->GetCHANGE();*/

	//チェンジフラグがオンの場合
	if (m_change == false) {
		
		hit->SetInvincibility(false);	//無敵オフ
	}
	else {
		hit->SetInvincibility(true);	//無敵オン
	}

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollX(), m_py + block->GetScrollY());

}

//ドロー
void CObjChangeGate1::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
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
	dst.m_top = 0.0f + m_py + block->GetScrollY();	//描画に対してスクロールの影響を加える
	dst.m_left = 0.0f + m_px + block->GetScrollX();
	dst.m_right = 32.0f + m_px + block->GetScrollX();
	dst.m_bottom = 32.0f + m_py + block->GetScrollY();

	//描画
	if (m_change == false) {
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	/*if (m_change == true) {
		Draw::Draw(2, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(2, &src, &dst, g, 0.0f);
	}*/
}


