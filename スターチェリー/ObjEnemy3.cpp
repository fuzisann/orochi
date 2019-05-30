//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include"GameHead.h"
#include"ObjEnemy3.h"

//使用するネームスペース
using namespace GameL;

CObjEnemy3::CObjEnemy3(float x, float y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjEnemy3::Init()
{
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f; //右向き0.0f,左向き1,0f

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期化する

	m_speed_power = 0.15f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	m_enemy_hp = 2;     //敵のヒットポイント(最大2)
	m_damage = 2;

	m_move = false;		//true=右 false=左

	m_del = false;

	m_time_d = 0;

	//blockとの追突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_inputf = true;	// true = 入力可	false = 入力不可

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 100, 80, ELEMENT_ENEMY, OBJ_ENEMY_THIRD, 1);
}

//アクション
void CObjEnemy3::Action()
{
	//主人公の情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	hero_hp = hero->GetHP();	//主人公からHPの情報を取得

	//摩擦
	m_vx += -(m_vx * 0.098f);
	m_vy += -(m_vy * 0.098f);

	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//ダミー
	int d;
	//ブロックとの当たり判定実行
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHitEne2(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//通常速度
	m_speed_power = 0.15f;
	m_ani_max_time = 4;

	//ブロック衝突で向き変更
	if (m_hit_down == true)
	{
		m_move = true;
	}
	if (m_hit_up == true)
	{
		m_move = false;
	}

	//inputフラグがオンの時に移動を可能にする
	if (m_inputf == true)
	{
		//方向
		if (m_move == false)
		{
			m_vy += m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (m_move == true)
		{
			m_vy -= m_speed_power;
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
		Audio::Start(4);	//ダメージ音
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

	//HPが0以下の時に消滅処理に移行する
	if (m_del == false && m_enemy_hp <= 0)
	{
		m_inputf = false;	//動きを制御
		m_del = true;
		m_time_dead = 80;	//死亡時間をセット
		m_vy += 9.8 / (16.0f);	//自由落下運動

		if (g_hero_max_hp < 18)
		{
			g_hero_max_hp += 2;	//敵の撃破時のHP/MP増加
		}
		else if (g_hero_max_hp == 19)
		{
			g_hero_max_hp += 1;	//敵の撃破時のHP/MP増加
		}
		if (hero_hp < 38)
		{
			hero->SetMAXHP(2);		//HPを増やす
		}
		else if (hero_hp == 39)
		{
			hero->SetMAXHP(1);		//HPを増やす
		}
	}

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollX(), m_py + 11 + block->GetScrollY());

	if (m_del == true)
	{
		hit->SetInvincibility(true);	//無敵にする
		m_eff_flag = true;			//画像切り替え用フラグ
		m_speed_power = 0.0f;			//動きを止める

	}

	if (m_time_dead > 0)
	{
		m_time_dead--;
		if (m_time_dead <= 0)
		{
			this->SetStatus(false);		//画像の削除
			Hits::DeleteHitBox(this);	//ヒットボックスの削除
			m_time_dead = 0;
		}
	}
}
//ドロー
void CObjEnemy3::Draw()
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
	dst.m_top = 0.0f + m_py + pb->GetScrollY();
	dst.m_left = (100.0f * m_posture) + m_px + pb->GetScrollX();
	dst.m_right = (100 - 100.0f *m_posture) + m_px + pb->GetScrollX();
	dst.m_bottom = 100.0f + m_py + pb->GetScrollY();

	//敵の状態で描画を変更
	if (m_del == true)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 400.0f;
		src.m_right = 500.0f;
		src.m_bottom = 100.0f;

		if (m_eff_flag == true)
			Draw::Draw(10, &src, &dst, c, 0.0f);
	}
	else
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 100;
		src.m_right = 100.0f + AniData[m_ani_frame] * 100;
		src.m_bottom = 100.0f;

		//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
		if (m_time_d > 0) {
			Draw::Draw(10, &src, &dst, a, 0.0f);
		}
		else {
			Draw::Draw(10, &src, &dst, c, 0.0f);
		}
	}

}