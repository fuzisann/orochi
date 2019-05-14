//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"Objgoalblock.h"

//使用するネームスペース
using namespace GameL;

CObjgoalblock::CObjgoalblock(float x, float y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjgoalblock::Init()
{
	/*m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期化する
	m_ani_max_time =15;  //アニメーション間隔幅*/

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 77, 85, ELEMENT_FIELD, OBJ_GOAL_BLOCK, 1);

}

//アクション
void CObjgoalblock::Action()
{
	/*m_ani_time += 1;
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}*/

	//自身のHitBoxを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//主人公と当たっているか確認
	if (hit->CheckElementHit(ELEMENT_PLAYER) == true)
	{
		Scene::SetScene(new CSceneStageClear());
	}

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBoxの位置を変更	
	hit->SetPos(m_px + 165 +block->GetScrollX(),m_py + 269 + block->GetScrollY());
}
//ドロー
void CObjgoalblock::Draw()
{
	int AniData[5] =
	{
		0,1,2,3,4
	};

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	src.m_top = 32.0f;
	src.m_left = 10.0f;
	src.m_right = 393.0f;
	src.m_bottom = 370.0f;
	
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//表示位置の設定
	dst.m_top  = 32.0f  + m_py + block->GetScrollY();
	dst.m_left = 10.0f  + m_px + block->GetScrollX();
	dst.m_right = 393.0f  + m_px + block->GetScrollX();
	dst.m_bottom = 370.0f + m_py - 12  + block->GetScrollY();

	Draw::Draw(5, &src, &dst, c, 0.0f);

}