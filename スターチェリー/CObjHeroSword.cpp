//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "CObjHeroSword.h"
#include "CObjHero.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjHeroSword::CObjHeroSword(float x, float y)
{
	m_x = x;
	m_y = y;
}
//イニシャライズ
void CObjHeroSword::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hero_x = 0.0f;
	m_hero_y = 0.0f;

	m_posture = 0.0f;	//右向き0.0f 左向き1.0f

	//blockとの衝突状態確認
	m_hit_left = false;
	m_hit_right = false;
	m_hit = false;

	//主人公の位向きを取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	m_posture = hero->GetPOS();

	m_ani_frame_x = 0;		//ソードのアニメーション用
	m_ani_frame_y = 0;

	m_time = 0;		//ソードが消える時間

	m_sword_time = 10;	//剣が消える時間

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x + 25, m_y, 50, 50, ELEMENT_ATTACK, OBJ_SWORD, 1);
}

//アクション
void CObjHeroSword::Action()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	m_hero_x = hero->GetX();
	m_hero_y = hero->GetY();

	if (m_hit_left == true)	//左
		m_hit = true;
	if (m_hit_right == true)//右
		m_hit = true;

	if (m_posture == 0.0f) {
		m_ani_frame_y = 0;
	}
	if (m_posture == 1.0f) {
		m_ani_frame_y = 1;
	}

	if (m_posture == 0.0f)
		m_x = m_hero_x + 55;
	else
		m_x = m_hero_x - 35;

	m_y = m_hero_y ;

	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);

	//敵と接触したら剣削除
	if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		//this->SetStatus(false);
		//Hits::DeleteHitBox(this);
		hit->SetInvincibility(true);

	}

	//壁に当たったら消える処理
	if (m_hit == true) {
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}
	//一定の時間で消える処理
	if (m_sword_time > 0) {
		m_sword_time--;
		if (m_sword_time <= 0) {
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}

	if (m_sword_time == 9) {
		m_ani_frame_x = 0;
	}
	else if (m_sword_time == 6) {
		m_ani_frame_x = 1;
	}
	else if (m_sword_time == 3) {
		m_ani_frame_x = 2;
	}


}

//ドロー
void CObjHeroSword::Draw()
{
	//描画カラー情報　R=RED  G=Green  B=Blue A=alpha(透過情報)
	float  c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f + (64.0f * m_ani_frame_y);
	src.m_left = 0.0f + (64.0f * m_ani_frame_x);
	src.m_right = 64.0f + (64.0f * m_ani_frame_x);
	src.m_bottom = 64.0f + (64.0f * m_ani_frame_y);


	//表示位置の設定
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = 50.0f + m_x;
	dst.m_bottom = 50.0f + m_y;

	Draw::Draw(16, &src, &dst, c, 0.0f);
}