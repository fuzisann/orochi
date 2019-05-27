//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"


#include"GameHead.h"
#include"CObjHero.h"
#include"GameL\Audio.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

float g_px;//= 64.0f;
float g_py;//= 450.0f;
extern bool Hit_wall;
extern bool Hit_wall_r;
extern bool m_up;
extern bool m_start_boss;

//イニシャライズ
void CObjHero::Init()
{

	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f; //右向き0.0f,左向き1,0f

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期化する

	m_ani_time_r = 0;
	m_ani_frame_r = 0;  //静止フレームを初期化する
	m_ani_max_time_r = 4;  //アニメーション間隔幅

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;	//踏んでいるブロックの種類

	m_hero_hp = 30;     //主人公の最大HP(最大30)

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	m_time = 31;

	m_del = false;

	m_sword_delay = 0;
	m_swordwidth = 0.0f; //ソード幅

	m_inputf = true;	// true = 入力可	false = 入力不可

	m_inputw = false;	// false = 入力可	true = 入力不可

	m_up = false;

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, g_px, g_py,64,64, ELEMENT_PLAYER, COBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//HPが0以下の時にゲームオーバーに移行する
	if (m_del == false && m_hero_hp <= 0)
	{
		m_del = true;
		m_inputf = false;	//キー入力を制御
		m_time_dead = 80;	//死亡時間をセット
	}

	m_speed_power = 0.5f;

	//inputフラグがオンの場合入力を可能にする
	if (m_inputf == true)
	{
		if(m_inputw == false)
		{

		//Zキーで近接(剣)攻撃
			if (Input::GetVKey('Z') == true)
			{
				if (m_sword_delay == 0)
				{
					//主人公の向きによって攻撃する向きを設定
					if (m_posture == 0.0f) {
						m_swordwidth = 70.0f;
					}
					else if (m_posture == 1.0f) {
						m_swordwidth = -30.0f;
					}

					//剣で攻撃
					CObjHeroSword* objsb = new CObjHeroSword(m_px + m_swordwidth, m_py + 32.0f);//剣オブジェクト(戦闘)作成
					Objs::InsertObj(objsb, OBJ_SWORD, 100);		//作った剣オブジェクトをオブジェクトマネージャーに登録

					//斬撃音
					Audio::Start(1);

					m_sword_delay = 20;
				}
			}
		}
		if (m_sword_delay > 0)
		{
			m_sword_delay--;
			if (m_sword_delay <= 0)
				m_sword_delay = 0;
		}

		//ジャンプ
		if (m_up == false)
		{
			if (Input::GetVKey(VK_UP) == true)
			{
				if (m_hit_down == true && m_time == 0)
				{
					m_vy = -17;	//初期値：-13
					//g_py += m_vy;

					Audio::Start(2);

				}
			}
		}
		
		if (m_time > 0) {
			m_time--;
			if (m_time <= 0) {
				m_time = 0;
			}
		}

		else if (m_ani_frame >= 4)
		{
			m_ani_frame = 0;
			m_ani_time = 0;
		}
		else if (m_ani_frame_r >= 8)
		{
			m_ani_frame_r = 0;
			m_ani_time_r = 0;
		}

		if (Input::GetVKey(VK_RIGHT) == true)
		{
			m_vx += m_speed_power;
			m_posture = 0.0f;
			m_ani_time += 1;
		}
		else if (Input::GetVKey(VK_LEFT) == true)
		{
			m_vx -= m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else
		{
			m_ani_frame = 0;   //キー入力が無い場合静止フレームにする
			m_ani_time = 0;
		}

		if (Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_RIGHT) == true)
		{
			m_ani_time_r += 1;
		}
		else if (Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_LEFT) == true)
		{
			m_ani_time_r += 1;
		}
		else
		{
			m_ani_frame_r = 0;   //キー入力が無い場合静止フレームにする
			m_ani_time_r = 0;
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

		if (m_ani_time_r > m_ani_max_time_r)
		{
			m_ani_frame_r += 1;
			m_ani_time_r = 0;
		}
		if (m_ani_frame_r == 8)
		{
			m_ani_frame_r = 0;
		}

		//移動ベクトルの正規化
		//UnitVec(&m_vx, &m_vy);

	//摩擦
	m_vx += -(m_vx * 0.098);
	m_vy += -(m_vy * 0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	//位置の更新
	g_px += m_vx;
	g_py += m_vy;

	//ブロックとの当たり判定実行
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&g_px, &g_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	
	//自身のHitBoxを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//HitBoxの位置を変更	
	hit->SetPos(g_px, g_py);

	//当たり判定を行うオブジェクト情報群
	int data_base[3] =
	{
		ELEMENT_ENEMY,
	};
	//オブジェクト情報群と当たり判定行い。当たっていればノックバック
	for (int i = 0; i < 6; i++)
	{
		if (hit->CheckElementHit(data_base[i]) == true)
		{
			HIT_DATA** hit_date;							//当たった時の細かな情報を入れるための構造体
			hit_date = hit->SearchElementHit(data_base[i]);	//hit_dateに主人公と当たっている他全てのHitBoxとの情報を入れる

			float r = 0;
			for (int i = 0; i < 10; i++) {
				if (hit_date[i] != nullptr) {
					r = hit_date[i]->r;
				}
			}
			//角度で上下左右を判定
			//if ((r < 45 && r >= 0) || r > 315)
			if (r > 90 && r < 270)
			{
				m_vy =  -5;		//右
				m_vx += 6;
			}
			else
			{
				m_vy =   -5;		//左
				m_vx -=  6;
			}

			Audio::Start(3);	//ダメージ音
			m_time_d = 80;		//無敵時間をセット
			hit->SetInvincibility(true);	//無敵オン

			//敵に当たるとHPを減らす
			if (hit->CheckObjNameHit(OBJ_ENEMY_FIRST) != nullptr)
			{
				CObjEnemy1* ene1 = (CObjEnemy1*)Objs::GetObj(OBJ_ENEMY_FIRST);
				m_damage = ene1->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_ENEMY_SECOND) != nullptr)
			{
				CObjEnemy2* ene2 = (CObjEnemy2*)Objs::GetObj(OBJ_ENEMY_SECOND);
				m_damage = ene2->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_ENEMY_THIRD) != nullptr)
			{
				CObjEnemy3* ene3 = (CObjEnemy3*)Objs::GetObj(OBJ_ENEMY_THIRD);
				m_damage = ene3->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_BOSS_FIRST) != nullptr)
			{
				CObjBoss1* boss1 = (CObjBoss1*)Objs::GetObj(OBJ_BOSS_FIRST);
				m_damage = boss1->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_BOSS_SECOND) != nullptr)
			{
				CObjBoss2* boss2 = (CObjBoss2*)Objs::GetObj(OBJ_BOSS_SECOND);
				m_damage = boss2->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_BOSS_THIRD) != nullptr)
			{
				CObjBoss3* boss3 = (CObjBoss3*)Objs::GetObj(OBJ_BOSS_THIRD);
				m_damage = boss3->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_BUBBLE) != nullptr)
			{
				CObjBubble* bubble = (CObjBubble*)Objs::GetObj(OBJ_BUBBLE);
				m_damage = bubble->GetDMG();
				m_hero_hp -= m_damage;
			}

			//敵の攻撃によってHPが0以下になった場合
			if (m_hero_hp <= 0)
				m_hero_hp = 0;	//HPを0にする

		}

	}

	if (hit->CheckElementHit(ELEMENT_MYSTERY) == true)
	{
		//主人公がブロックとどの角度で当たっているのかを確認
		HIT_DATA** hit_date;							//当たった時の細かな情報を入れるための構造体
		hit_date = hit->SearchElementHit(ELEMENT_MYSTERY);	//hit_dateに主人公と当たっている他全てのHitBoxとの情報を入れる
		for (int i = 0; i < hit->GetCount(); i++)
		{
			float r = hit_date[i]->r;
			if ((r < 45 && r >= 0) || r > 315)
			{
				m_vx = -0.15f; //右
			}
			if (r > 45 && r < 135)
			{
				m_vy = 0.15f;//上
			}
			if (r > 135 && r < 225)
			{
				m_vx = 0.15f;//左
			}
			if (r > 225 && r < 315)
			{
				m_vy = -0.15f; //下
			}
		}
	}



	if (m_del == true)
	{
		hit->SetInvincibility(true);	//無敵にする
		m_eff_flag = true;			//画像切り替え用フラグ
		m_speed_power = 0.0f;			//動きを止める

	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
			hit->SetInvincibility(false);	//無敵オフ
		}
	}

	if (m_time_dead > 0)
	{
		m_time_dead--;
		if (m_time_dead <= 0)
		{
			Scene::SetScene(new CSceneOver());
			m_time_dead = 0;
			m_start_boss = true;
		}
	}
}

//ドロー
void CObjHero::Draw()
{

	int AniData[5] =
	{
		0,1,2,3,0,
	};

	int AniData_r[9] =
	{
		0,1,2,3,4,5,6,7,0,
	};

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };
	

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	
	//表示位置の設定
	dst.m_top = 0.0f + g_py;
	dst.m_left = (64.0f*m_posture) + g_px;
	dst.m_right = (64 - 64.0f*m_posture) + g_px;
	dst.m_bottom = 64.0f + g_py;

	//切り取り位置の設定
	//主人公の状態で描画を変更
	if (m_del == true)
	{
		src.m_top = 64.0f;
		src.m_left = 128.0f;
		src.m_right = 192.0f;
		src.m_bottom = 128.0f;
		if (m_eff_flag == true)
			Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	else
	{
		if (Hit_wall == true) //上る壁に主人公が当たった時
		{
			//剣を持っていない時の主人公が描かれている所を切り取る
			src.m_top = 64.0f;
			src.m_left = 64.0f;
			src.m_right = 128.0f;
			src.m_bottom = 128.0f;

			m_inputw = true;

		}
		else if (Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_LEFT) == true
			 || Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_RIGHT) == true)
		{
			//回転している時の主人公が描かれている所を切り取る
			src.m_top = 128.0f;
			src.m_left = 0.0f + AniData_r[m_ani_frame_r] * 64;
			src.m_right = 64.0f + AniData_r[m_ani_frame_r] * 64;
			src.m_bottom = 192.0f;
			m_inputw = true;
		}
		else //それ以外の時
		{
			//剣を持っている時の主人公が描かれている所を切り取る
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData[m_ani_frame] * 64;
			src.m_right = 64.0f + AniData[m_ani_frame] * 64;
			src.m_bottom = 64.0f;
			m_inputw = false;

		}

		//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写

		if (m_time_d > 0) {
			Draw::Draw(0, &src, &dst, a, 0.0f);
		}
		else {
			Draw::Draw(0, &src, &dst, c, 0.0f);
		}
	}
}