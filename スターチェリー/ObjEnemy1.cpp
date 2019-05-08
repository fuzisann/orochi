//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjEnemy1.h"

//使用するネームスペース
using namespace GameL;

CObjEnemy1::CObjEnemy1(float x, float y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjEnemy1::Init()
{
	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 0.0f; //右向き0.0f,左向き1,0f

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期化する

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	m_enemy_hp = 3;     //敵のヒットポイント(最大3)(仮)
	m_damage = 1;

	m_move = false;		//true=右 false=左

	//blockとの追突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 50, 50, ELEMENT_ENEMY, OBJ_ENEMY_FIRST, 1);
}

//アクション
void CObjEnemy1::Action()
{
	//摩擦
	m_vx += -(m_vx * 0.098);
	//m_vy += -(m_vy * 0.098);

	
	//自身のHitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//ダミー
	int d;
	//ブロックとの当たり判定実行
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHitEne(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;


	//通常速度
	m_speed_power = 0.5f;
	m_ani_max_time = 4;

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
			//m_vy = -10;
			m_vx += 15;
		}
		if (m_posture == 1.0f)
		{
			//m_vy = -10;
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
		this->SetStatus(false);		//画像の削除
		Hits::DeleteHitBox(this);	//ヒットボックスの削除
	}

	//ブロック情報を持ってくる
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	hit->SetPos(m_px + block->GetScrollX(), m_py + block->GetScrollY());

}
//ドロー
void CObjEnemy1::Draw()
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
	src.m_left = 0.0f + AniData[m_ani_frame] * 50;
	src.m_right = 50.0f + AniData[m_ani_frame] * 50;
	src.m_bottom = 50.0f;
	
	//ブロック情報を持ってくる
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//表示位置の設定
	dst.m_top = 0.0f + m_py + pb->GetScrollY();
	dst.m_left = (50.0f * m_posture) + m_px + pb->GetScrollX();
	dst.m_right = (50 - 50.0f *m_posture) + m_px + pb->GetScrollX();
	dst.m_bottom = 50.0f + m_py + pb->GetScrollY();
		
	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(8, &src, &dst, c, 0.0f);

}