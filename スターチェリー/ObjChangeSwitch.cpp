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

bool m_delete = true;
bool m_change = true;
bool m_start_boss = true;
bool m_m_change = true;


CObjChangeSwitch::CObjChangeSwitch(float x, float y)
{
	m_px = x;		//位置
	m_py = y;
}

//イニシャライズ
void CObjChangeSwitch::Init()
{
	m_change = true;	//画像切り替え
	m_time = 0;
	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_FIELD, OBJ_CHANGESWITCH, 1);
}

//アクション
void CObjChangeSwitch::Action()
{
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	//主人公と当たっているか確認
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		//CObjChangeGate1* change = (CObjChangeGate1*)Objs::GetObj(OBJ_CHANGEGATE);
		//m_change = change->GetCHANGE();
		
		m_change = false;
		m_delete = false;
		m_start_boss = false;
		m_m_change = false;
		//hit->SetInvincibility(true);	//無敵オン
		//m_time = 100;
	}


	if (m_delete == false)
	{
		//自身を削除
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		m_delete = true;
	}


	/*if (m_time > 0)
	{
		m_time--;
		if (m_time <= 0)
		{
			m_time = 0;
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}*/
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollX(), m_py + block->GetScrollY());

}

//ドロー
void CObjChangeSwitch::Draw()
{

}


