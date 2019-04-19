//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"CObjHero.h"
#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

float g_px = 64.0f;
float g_py = 450.0f;

//イニシャライズ
void CObjHero::Init()
{

	m_vx = 0.0f;    //移動ベクトル
	m_vy = 0.0f;
	m_posture = 1.0f; //右向き0.0f,左向き1,0f

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期化する

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;	//踏んでいるブロックの種類

	m_hero_hp = 100;     //主人公のヒットポイント

	m_speed_power = 0.5f;//通常速度
	m_ani_max_time = 4;  //アニメーション間隔幅

	m_time = 31;

	m_sword_delay = 0;
	m_swordwidth = 0.0f; //ソード幅

	//当たり判定用のHitBoxを作成
	Hits::SetHitBox(this, g_px, g_py,64,64, ELEMENT_PLAYER, COBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//HPが0以下の時にゲームオーバーにする
	if (m_hero_hp <= 0)
	{
		Scene::SetScene(new CSceneOver());
	}

	//落下によるゲームオーバー＆リスタート
	if (g_py > 1000.0f)
	{
		//場外に出たらリスタート
		Scene::SetScene(new CSceneOver());
	}

	m_speed_power = 0.5f;

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
			//Audio::Start(0);

			m_sword_delay = 20;
		}
	}
	if (m_sword_delay > 0)
	{
		m_sword_delay--;
		if (m_sword_delay <= 0)
			m_sword_delay = 0;
	}

	//ジャンプ
	if (Input::GetVKey(VK_UP) == true)
	{
		if (m_hit_down == true && m_time == 0)
		{
			m_vy = -30;	//初期値：-13
			g_py += m_vy;

			//Audio::Start(1);

		}

	}
	if (m_time > 0) {
		m_time--;
		if (m_time <= 0) {
			m_time = 0;
		}
	}


	/*if (m_ani_frame == 1)
	{
	m_ani_frame = 0;
	m_ani_time = 0;
	}*/

	else if (m_ani_frame >= 4)
	{
		m_ani_frame = 0;
		m_ani_time = 0;
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
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//主人公機が領域外行かない処理
	if (g_px + 64.0f > 800.0f)
	{
		g_px = 800.0f - 64.0f;

	}

	CObjBlock*b = (CObjBlock*)Objs::GetObj(COBJ_HERO);
	//後方スクロールライン
	if (g_px < 80)
	{
		g_px = 80;
		b->SetScroll(b->GetScroll());
	}

	//前方スクロールライン
	if (g_px > 350)
	{
		g_px = 350;
		b->SetScroll(b->GetScroll());
	}
	//摩擦
	m_vx += -(m_vx*0.098);

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
				m_vy = -5;		//右
				m_vx += 10;
			}
			else
			{
				m_vy = -5;		//左
				m_vx -= 10;
			}
			m_time_d = 80;		//無敵時間をセット
			hit->SetInvincibility(true);	//無敵オン

			//敵
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


			//敵の攻撃によってHPが0以下になった場合
			if (m_hero_hp <= 0)
				m_hero_hp = 0;	//HPを0にする


			//if (r > 135 && r < 225 || r < 135)
			/*if (r > 90 && r < 270)
			{
			m_vy = -5;		//右
			m_vx += 25;
			}
			//if ((r < 45 && r >= 0) || r > 315 || (r > 45 || r < 90 ))
			else
			{
			m_vy = -5;		//左
			m_vx -= 25;
			}*/

			/*//敵と当たっているか確認
			if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
			{
			//主人公と敵がどの角度で当たっているかを確認
			HIT_DATA** hit_data;
			hit_data = hit->SearchObjNameHit(OBJ_ENEMY);

			//敵の左右に当たったら
			float r = hit_data[0]->r;
			if ((r < 45 && r >= 0) || r > 315)
			{
			m_vx = -5.0f;//左に移動させる
			}
			if (r > 135 && r < 225)
			{
			m_vy = -5.0f;//右に移動させる
			}
			if (r >= 225 && r > 315)
			{
			//敵の移動方向を主人公の位置に加算
			m_vx += ((CObjEnemy1*)hit_data[0]->o)->GetVX();
			//頭に乗せる処理
			if (m_vy < -1.0f)
			{
			//ジャンプしてる場合は下記の影響を出ないようにする
			}
			else
			{
			//主人公が敵の頭に乗っているので、Yvecは0にして落下させない
			//また、地面に当たっている判定にする
			m_vy = 0.0f;
			m_hit_down = true;
			}

			}
			}*/
		}

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
}

//ドロー
void CObjHero::Draw()
{
	int AniData[5] =
	{
		0,1,2,3,0,
	};

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置
	
    //切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + g_py;
	dst.m_left = (64.0f*m_posture) + g_px;
	dst.m_right = (64 - 64.0f*m_posture) + g_px;
	dst.m_bottom = 64.0f + g_py;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写

	if (m_time_d > 0) {
		Draw::Draw(0, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	

}