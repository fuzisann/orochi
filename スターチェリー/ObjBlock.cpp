//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\SceneObjManager.h"

#include"GameHead.h"
#include"ObjBlock.h"
#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;


CObjBlock::CObjBlock(int map[19][100])
{
	//マップデータコピー
	memcpy(m_map, map, sizeof(int)*(19 * 100));
}

//イニシャライズ
void CObjBlock::Init()
{
	m_scroll = 0.0f;
	m_scroll_map = 0.0f;
	float m_x1 = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 0;

	m_ani_max_time = 15;
}


//アクション
void CObjBlock::Action()
{
	//主人公の位置を取得
	CObjHero*hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//敵の位置を取得
	CObjEnemy1*enemy1 = (CObjEnemy1*)Objs::GetObj(OBJ_ENEMY_FIRST);
	CObjEnemy2*enemy2 = (CObjEnemy2*)Objs::GetObj(OBJ_ENEMY_SECOND);
	/*float hx = hero->GetX();
	float hy = hero->GetY();*/
	////後方スクロールライン
	if (hx < 80)
	{
		hero->SetX(80);           //主人公はラインを超えないようにする
		m_scroll -= hero->GetVX(); //主人公が本来動くべき分の値をm_scrollに加える

	}

	//前方スクロールライン
	if (hx > 300)
	{
		hero->SetX(300);           //主人公はラインを超えないようにする
		m_scroll -= hero->GetVX(); //主人公が本来動くべき分の値をm_scrollに加える

	}


	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//敵(雑魚)出現
			if (m_map[i][j] == 3)
			{
				//3があれば敵(アジ)を出現
				
				CObjEnemy1* obje1 = new CObjEnemy1(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(obje1, OBJ_ENEMY_FIRST, 112);

				//出現場所の値を0にする
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 4)
			{
				//4があれば敵(イワシ)を出現
				CObjEnemy2* obje2 = new CObjEnemy2(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(obje2, OBJ_ENEMY_SECOND, 112);
	
				//出現場所の値を0にする
				m_map[i][j] = 0;
			}

			//ゴールブロック出現
			if (m_map[i][j] == 5)
			{
				CObjgoalblock* ends = new CObjgoalblock(j*ALL_BLOCK_SIZE, i*ALL_BLOCK_SIZE);
				Objs::InsertObj(ends, OBJ_GOAL_BLOCK, 11);
				m_map[i][j] = 0;
			}

			//歯車出現
			if (m_map[i][j] == 6)
			{
				CObjgear* gears = new CObjgear(j*ALL_BLOCK_SIZE, i*ALL_BLOCK_SIZE);
				Objs::InsertObj(gears, OBJ_GEAR, 11);
				m_map[i][j] = 0;
			}

			
			//ボス出現
			if (m_map[i][j] == 7)
			{
				//7があればボス(カメ)を出現
				if (g_map_chenge == 0) {
					/*CObjBoss1* objb1 = new CObjBoss1(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
					Objs::InsertObj(objb1, OBJ_BOSS_FIRST, 112);*/
				}

				//出現場所の値を0にする
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 8)
			{
				//8があればボス(リュウグウノツカイ)を出現
				if (g_map_chenge == 0) {
					/*CObjBoss2* objb2 = new CObjBoss2(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
					Objs::InsertObj(objb2, OBJ_BOSS_SECOND, 112);*/
				}

				//出現場所の値を0にする
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 9)
			{
				//9があればボス(サメ(乙姫))を出現
				if (g_map_chenge == 0) {
					/*CObjBoss3* objb3 = new CObjBoss3(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
					Objs::InsertObj(objb3, OBJ_BOSS_THIRD, 112);*/
				}

				//出現場所の値を0にする
				m_map[i][j] = 0;
			}
		}
	}
}

//ドロー
void CObjBlock::Draw()
{

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置


	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = ALL_BLOCK_SIZE;
			src.m_bottom = ALL_BLOCK_SIZE;

			//ブロック画像表示
			if (m_map[i][j] == 1)
			{
				if (g_map_chenge == 0) {

					//表示位置の設定
					dst.m_top = i * ALL_BLOCK_SIZE;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scroll;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
				else if (g_map_chenge == 1) {

					//表示位置の設定
					dst.m_top = i * ALL_BLOCK_SIZE;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scroll;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
				else if (g_map_chenge == 2) {

					//表示位置の設定
					dst.m_top = i * ALL_BLOCK_SIZE;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scroll;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
			}

			//ブロック画像表示
			if (m_map[i][j] == 2)
			{
				//表示位置の設定
				dst.m_top = i*ALL_BLOCK_SIZE;
				dst.m_left = j*ALL_BLOCK_SIZE + m_scroll;
				dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
				dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

				Draw::Draw(4, &src, &dst, c, 0.0f);
			}
		}
	}
}

//BlockHit関数
//引数１    float * x           :判定を行うobjectのX位置
//引数２    float * y           :判定を行うobjectのY位置
//引数３    bool     scroll_on  :判定を行うobjectはスクロールの影響与えるかどうか（true=与える　false=与えない）
//引数４    bool *   up         :上下左右判定の上部分に当たっているかどうかを返す
//引数５    bool *   down       :上下左右判定の下部分に当たっているかどうかを返す
//引数６    bool *   left       :上下左右判定の左部分に当たっているかどうかを返す
//引数７    bool *   right      :上下左右判定の右部分に当たっているかどうかを返す
//引数８    float * vx          :左右判定時の反発による移動方向・力の値変えて返す
//引数９    float * vy          :上下判定時による自由落下運動の移動方向・力の値変えて返す
//引数１０  int * bt            :下部分判定時、特殊なブロックのタイプを返す
//判定を行うobjectとブロック64×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
void CObjBlock::BlockHit(
	float *x, float *y, bool scroll_on,
	bool*up, bool*down, bool*left, bool*right,
	float *vx, float*vy, int *bt
)
{
	//衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j*32.0f;
				float by = i*32.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 32.0f) && (*y + 64.0f > by) && (*y < by + 32.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

					//長さを求める
					float len = sqrt(rvx*rvx + rvy*rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r*180.0f / 3.14f;

					if (r < 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					


					//lenがある一定の長さのより短い場合判定に入る
					if (len < 88.0f)
					{
						//角度で上下左右を判定
						if ((r < 45 && r>0) || r > 315)
						{
							//右
							*right = true;//オブジェクトの左の部分が衝突している
							*x = bx + 32.0f + (scroll);//ブロックの位置+主人公の幅
							*vx = 0.0f;//-VX*反発係数

							if (m_map[i][j] == 2)
							{
								*x = bx + 30.0f + (scroll);//ブロックの位置-主人公の幅
							}

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 64.0f;//ブロックの位置-主人公の幅
							*vy = 0.0f;
							/*if (m_map[i][j] == 6)
							{
								block2 = 1;
							}
							else
							{
								block2 = 0;
							}*/
							if (m_map[i][j] == 2)
							{
								//Audio::Start(1);
								//Scene::SetScene(new CSceneOver());
							}
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 64.0f + (scroll);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.0f;//-VX*反発係数

							if (m_map[i][j] == 2)
							{
								*x = bx - 62.0f + (scroll);//ブロックの位置-主人公の幅
							}
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公の上の部分が衝突している
							*y = by + 32.0f;//ブロックの位置+主人公の幅
	
							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}


//BlockHitEne関数
//引数１    float * x           :判定を行うobjectのX位置
//引数２    float * y           :判定を行うobjectのY位置
//引数３    bool     scroll_on  :判定を行うobjectはスクロールの影響与えるかどうか（true=与える　false=与えない）
//引数４    bool *   up         :上下左右判定の上部分に当たっているかどうかを返す
//引数５    bool *   down       :上下左右判定の下部分に当たっているかどうかを返す
//引数６    bool *   left       :上下左右判定の左部分に当たっているかどうかを返す
//引数７    bool *   right      :上下左右判定の右部分に当たっているかどうかを返す
//引数８    float * vx          :左右判定時の反発による移動方向・力の値変えて返す
//引数９    float * vy          :上下判定時による自由落下運動の移動方向・力の値変えて返す
//引数１０  int * bt            :下部分判定時、特殊なブロックのタイプを返す
//判定を行うobjectとブロック64×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
void CObjBlock::BlockHitEne(
	float *x, float *y, bool scroll_on,
	bool*up, bool*down, bool*left, bool*right,
	float *vx, float*vy, int *bt
)
{
	//衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j*32.0f;
				float by = i*32.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scroll) + 50.0f > bx) && (*x + (-scroll) < bx + 32.0f) && (*y + 64.0f > by) && (*y < by + 32.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

					//長さを求める
					float len = sqrt(rvx*rvx + rvy*rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r*180.0f / 3.14f;

					if (r < 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);


					//lenがある一定の長さのより短い場合判定に入る
					if (len < 88.0f)
					{
						//角度で上下左右を判定
						if ((r < 45 && r>0) || r > 315)
						{
							//右
							*right = true;//オブジェクトの左の部分が衝突している
							*x = bx + 32.0f + (scroll);//ブロックの位置+主人公の幅
							*vx = 0.0f;//-VX*反発係数

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 50.0f;//ブロックの位置-主人公の幅
							*vy = 0.0f;
							if (m_map[i][j] == 6)
							{
								block2 = 1;
							}
							else
							{
								block2 = 0;
							}
							if (m_map[i][j] == 2)
							{
								//Audio::Start(1);
								//Scene::SetScene(new CSceneOver());
							}
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 64.0f + (scroll);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.0f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公の上の部分が衝突している
							*y = by + 32.0f;//ブロックの位置+主人公の幅

							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}

void CObjBlock::BlockDraw(float x, float y, RECT_F *dst, float c[])
{

}