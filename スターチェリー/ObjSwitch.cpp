//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjSwitch.h"


//使用するネームスペース
using namespace GameL;


CObjSwitch::CObjSwitch(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjSwitch::Init()
{
	m_change = false;	//画像切り替え
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_FIELD, OBJ_SWITCH, 1);
}

//アクション
void CObjSwitch::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公と当たっているか確認
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		m_change = true;	//描画カラーを変える
		hit->SetInvincibility(true);	//無敵をオンにする
	}
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScroll(), m_py);

}

//ドロー
void CObjSwitch::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,2.0f,0.7f };
	float r[4] = { 3.0f,1.0f,1.0f,1.0f };

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
		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
	else if (m_change == true) {
		Draw::Draw(5, &src, &dst, r, 0.0f);
	}
}


