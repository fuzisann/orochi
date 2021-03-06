//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include"GameHead.h"
#include"ObjBoss3.h"

//使用するネームスペース
using namespace GameL;

extern bool m_start_boss;

CObjBoss3::CObjBoss3(float x, float y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjBoss3::Init()
{
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f; //右向き0.0f,左向き1,0f

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期化する

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	m_boss_hp = 15;     //敵のヒットポイント(最大15)
	m_damage = 4;

	m_time = 0;
	m_time_b = 0;
	m_time_d = 0;

	m_time_die = 0;

	m_move = false;		//true=右 false=左

	m_do_f = false;//突進フラグ

	//blockとの追突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_del = false;

	m_inputf = true;	// true = 入力可	false = 入力不可

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 200, 100, ELEMENT_ENEMY, OBJ_BOSS_THIRD, 1);
}

//アクション
void CObjBoss3::Action()
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
	pb->BlockHitBoss3(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);
	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
	m_speed_power = 0.0f;		//スピードを０にする

	if (m_start_boss == false)
	{
		//通常速度
		m_speed_power = 0.5f;
		m_ani_max_time = 4;

		m_time_b++;

		//突進
		if (m_time >= 0)
		{
			m_time++;

			if (m_time >= 60)
			{
				m_speed_power = 0.0f;

				if (m_time >= 100)
				{
					m_speed_power = 100.0f;
					m_time = 0;
				}
			}
		}

		if (m_time_b > 50)
		{
			m_time_b = 0;
			//オブジェクト作成
			CObjBubble* objbu = new CObjBubble(m_px, m_py);
			Objs::InsertObj(objbu, OBJ_BUBBLE, 100);
			Audio::Start(8);	//音
		}
	}

	//ブロック衝突で向き変更
	if (m_hit_left == true)
	{
		m_move = true;
	}
	if (m_hit_right == true)
	{
		m_move = false;
	}

	//inputフラグがオンの時に移動を可能にする
	if (m_inputf == true)
	{
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
	}

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
		Audio::Start(4);	//ダメージ音
		m_time_d = 30;	//敵の無敵時間をセット
		m_boss_hp -= 1;	//敵の体力を減らす
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}

	if (m_del == false && m_boss_hp <= 0)
	{
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		block->Setwall(true);
		m_time_die = 30;
		m_inputf = false;	//動きを制御
		m_del = true;
		m_time_dead = 80;	//死亡時間をセット
		m_vy += 9.8 / (16.0f);	//自由落下運動
	}

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollX(), m_py - 50 + block->GetScrollY());

	if (m_del == true)
	{
		hit->SetInvincibility(true);	//無敵にする
		m_eff_flag = true;			//画像切り替え用フラグ
		m_speed_power = 0.0f;			//動きを止める
		m_start_boss = true;
	}

	if (m_time_dead > 0)
	{
		m_time_dead--;
		if (m_time_dead <= 0)
		{
			this->SetStatus(false);		//画像の削除
			Hits::DeleteHitBox(this);	//ヒットボックスの削除
			m_time_dead = 0;
			Scene::SetScene(new CSceneClear());
		}
	}
}
//ドロー
void CObjBoss3::Draw()
{
	int AniData[4] =
	{
		0,1,2,3,
	};

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//ブロック情報を持ってくる
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py - 50 + pb->GetScrollY();
	dst.m_left = (200.0f * m_posture) + m_px + pb->GetScrollX();
	dst.m_right = (200 - 200.0f *m_posture) + m_px + pb->GetScrollX();
	dst.m_bottom = 100.0f + m_py - 50 + pb->GetScrollY();

	//敵の状態で描画を変更
	if (m_del == true)
	{

		//切り取り位置の設定
		src.m_top = 100.0f;
		src.m_left = 420.0f;
		src.m_right = 615.0f;
		src.m_bottom = 200.0f;

		if (m_eff_flag == true)
			Draw::Draw(12, &src, &dst, c, 0.0f);
	}
	else
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 200;
		src.m_right = 200.0f + AniData[m_ani_frame] * 200;
		src.m_bottom = 100.0f;

		//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
		if (m_time_d > 0) {
			//切り取り位置の設定
			src.m_top = 100.0f;
			src.m_left = 200.0f;
			src.m_right = 400.0f;
			src.m_bottom = 200.0f;

			Draw::Draw(12, &src, &dst, a, 0.0f);
		}
		else {
			Draw::Draw(12, &src, &dst, c, 0.0f);
		}
	}
}