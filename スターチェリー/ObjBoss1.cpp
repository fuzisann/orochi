//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjBoss1.h"

//使用するネームスペース
using namespace GameL;

extern bool m_start_boss;

CObjBoss1::CObjBoss1(float x, float y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjBoss1::Init()
{
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f; //右向き0.0f,左向き1,0f

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期化する

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	m_enemy_hp = 5;     //敵のヒットポイント(最大5)
	m_damage = 1;

	m_move = true;		//true=右 false=左

	m_change = true;

	//blockとの追突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 100, 55, ELEMENT_ENEMY, OBJ_BOSS_FIRST, 1);
}

//アクション
void CObjBoss1::Action()
{
	//摩擦
	m_vx += -(m_vx * 0.098);
	//m_vy += -(m_vy * 0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//ダミー
	int d;
	//ブロックとの当たり判定実行
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHitBoss1(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;


	//突進行動
	/*if (m_do_f == true)
	{
		m_dotime++;
		if (m_dotime > 40)
		{
			m_vx *= 5;
			m_vy *= 5;
			if (m_dotime == 100)
			{
				m_do_f = false;
				m_dotime = 0;
			}
		}
		else
		{
			m_vx = 0;
			m_vy = 0;
		}
	}*/
	//落下
	/*if (m_py > 1000.0f)
	{
		;
	}*/

	m_speed_power = 0.0f;		//スピードを０にする
	//m_vx = 0.0f;
	//m_vy = 0.0f;

	if (m_start_boss == false)
	{
		m_speed_power = 0.5f;
		m_ani_time = 4;
	}

	//通常速度
	

	/*if (m_change == true) {
		m_change = false;
	}
	else {
		m_change = true;
	}

	if (m_change == false) {
		
	}
	else {
		m_vx = 0;
		m_vy = 0;
	}*/
	

	//ブロック衝突で向き変更
	if (m_hit_left == true)
	{
		m_move = true;
	}
	if (m_hit_right == true)
	{
		m_move = false;
	}

	//方向
	if (m_move == false)
	{
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	else if (m_move == true)
	{
		m_vx -= m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;
	}
	
	/*else
	{
		m_ani_frame = 1;  //静止フレーム
		m_ani_time = 0;
	}*/

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//攻撃を受けたら体力を減らす
	//主人公とATTACK系統との当たり判定
	if (hit->CheckElementHit(ELEMENT_ATTACK) == true)
	{
		//ノックバック処理
		if (m_posture == 0.0f)
		{
			m_vy = -10;
			m_vx += 15;
		}
		if (m_posture == 1.0f)
		{
			m_vy = -10;
			m_vx -= 15;
		}
		m_time_d = 30;	//敵の無敵時間をセット
		m_enemy_hp -= 1;	//敵の体力を減らす
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}

	if (m_enemy_hp <= 0)
	{
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		block->Setwall(true);
		this->SetStatus(false);		//画像の削除
		Hits::DeleteHitBox(this);	//ヒットボックスの削除
	}

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollX(), m_py + block->GetScrollY());

}
//ドロー
void CObjBoss1::Draw()
{
	int AniData[4] =
	{
		0,1,2,3,
	};

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 100;
	src.m_right = 100.0f + AniData[m_ani_frame] * 100;
	src.m_bottom = 100.0f;
			
	//ブロック情報を持ってくる
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py - 32 + pb->GetScrollY();
	dst.m_left = (100.0f * m_posture) + m_px + pb->GetScrollX();
	dst.m_right = (100 - 100.0f *m_posture) + m_px + pb->GetScrollX();
	dst.m_bottom = 100.0f + m_py - 32 + pb->GetScrollY();
					
	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(12, &src, &dst, c, 0.0f);
		
}