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

bool Hit_wall = false;
bool Hit_wall_r = false;
bool m_up = false;

CObjBlock::CObjBlock(int map[50][150])
{
	//マップデータコピー
	memcpy(m_map, map, sizeof(int)*(50 * 150));
}

void CObjBlock::Setwall(bool type)
{
	if(type == true)
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 150; j++)
			{
				if (m_map[i][j] == 13)
					m_map[i][j] = 0;
			}
		}
}

/*void CObjBlock::Setswitch(bool type)
{
	if (type == true)
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (m_map[i][j] == 10)
					m_map[i][j] = 0;
			}
		}
}*/

//イニシャライズ
void CObjBlock::Init()
{
	m_scroll = 0.0f;
	m_scroll_map = 0.0f;
	float m_x1 = 0.0f;

	m_scrollx = 0.0f;
	m_scrolly = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 0;

	m_ani_max_time = 15;
}


//アクション
void CObjBlock::Action()
{
	//主人公の位置を取得
	CObjHero*hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	//float hx = hero->GetX();
	//float hy = hero->GetY();

	//敵の位置を取得
	CObjEnemy1*enemy1 = (CObjEnemy1*)Objs::GetObj(OBJ_ENEMY_FIRST);
	CObjEnemy2*enemy2 = (CObjEnemy2*)Objs::GetObj(OBJ_ENEMY_SECOND);

	CObjBoss1*boss1 = (CObjBoss1*)Objs::GetObj(OBJ_BOSS_FIRST);
	CObjBoss2*boss2 = (CObjBoss2*)Objs::GetObj(OBJ_BOSS_SECOND);

	/*float hx = hero->GetX();
	float hy = hero->GetY();*/
	////後方スクロールライン
	/*if (hx < 80)
	{
		hero->SetX(80);           //主人公はラインを超えないようにする
		m_scroll -= hero->GetVX(); //主人公が本来動くべき分の値をm_scrollに加える

	}

	//前方スクロールライン
	if (hx > 300)
	{
		hero->SetX(300);           //主人公はラインを超えないようにする
		m_scroll -= hero->GetVX(); //主人公が本来動くべき分の値をm_scrollに加える

	}*/
	if (Hit_wall == false)
	{
		//左のスクロールライン
		{
			hero->SetX(80);				//主人公はラインを超えないようにする
			m_scrollx -= hero->GetVX();	//主人公が本来動くべき分の値をm_scrollに加える
		}
		//右のスクロールライン
		{
			hero->SetX(250);			//主人公はラインを超えないようにする
			m_scrollx -= hero->GetVX();	//主人公が本来動くべき分の値をm_scrollに加える
		}
	}
		//上のスクロールライン
		{
			hero->SetY(0);				//主人公はラインを超えないようにする
			m_scrolly -= hero->GetVY();	//主人公が本来動くべき分の値をm_scrollに加える
		}
		//下のスクロールライン
		{
			hero->SetY(375);			//主人公はラインを超えないようにする
			m_scrolly -= hero->GetVY();	//主人公が本来動くべき分の値をm_scrollに加える
		}
	

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
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
				
				CObjBoss1* objb1 = new CObjBoss1(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(objb1, OBJ_BOSS_FIRST, 112);
			

				//出現場所の値を0にする
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 8)
			{
				//8があればボス(リュウグウノツカイ)を出現
				
				CObjBoss2* objb2 = new CObjBoss2(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(objb2, OBJ_BOSS_SECOND, 112);

				//出現場所の値を0にする
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 9)
			{
				//9があればボス(サメ(乙姫))を出現
				
				CObjBoss3* objb3 = new CObjBoss3(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(objb3, OBJ_BOSS_THIRD, 112);

				//出現場所の値を0にする
				m_map[i][j] = 0;
			}

			if (m_map[i][j] == 10)
			{
				//10があればChangeSwitchを出現
				CObjChangeSwitch* objds = new CObjChangeSwitch(j * ALL_BLOCK_SIZE, i * ALL_BLOCK_SIZE);
				Objs::InsertObj(objds, OBJ_CHANGESWITCH, 11);
				//出現場所の値を0にする
				m_map[i][j] = 0;

			}
			if (m_map[i][j] == 11)
			{
				//11があればChangeGate1を出現
				CObjChangeGate1* objds = new CObjChangeGate1(j * ALL_BLOCK_SIZE, i * ALL_BLOCK_SIZE);
				Objs::InsertObj(objds, OBJ_CHANGEGATE, 11);
				
				//出現場所の値を0にする
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 15)
			{
				//15があれば敵(あんこう)を出現
				CObjEnemy3* obje3 = new CObjEnemy3(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(obje3, OBJ_ENEMY_THIRD, 112);

				//出現場所の値を0にする
				m_map[i][j] = 0;
			}
			/*if (m_map[i][j] == 12)
			{
				
				//12があればChangeGate2を出現
				CObjChangeGate2* objds = new CObjChangeGate2(j * ALL_BLOCK_SIZE, i * ALL_BLOCK_SIZE);
				Objs::InsertObj(objds, OBJ_CHANGEGATE, 11);
				
				//出現場所の値を0にする
				m_map[i][j] = 0;
			}*/
			
		}
	}
}

//ドロー
void CObjBlock::Draw()
{

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float bl[4] = { 0.8f,0.8f,0.8f,1.0f };

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置


	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{

			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = ALL_BLOCK_SIZE;
			src.m_bottom = ALL_BLOCK_SIZE;

			//ブロック画像表示
			if (m_map[i][j] == 1 || m_map[i][j] == 13)
			{
				if (g_map_chenge == 0) {

					//表示位置の設定
					dst.m_top = i * ALL_BLOCK_SIZE + m_scrolly;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scrollx;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
				else if (g_map_chenge == 1) {

					//表示位置の設定
					dst.m_top = i * ALL_BLOCK_SIZE + m_scrolly;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scrollx;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
				else if (g_map_chenge == 2) {

					//表示位置の設定
					dst.m_top = i * ALL_BLOCK_SIZE + m_scrolly;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scrollx;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
			}

			//ブロック画像表示
			if (m_map[i][j] == 2)
			{
				//表示位置の設定
				dst.m_top = i*ALL_BLOCK_SIZE + m_scrolly;
				dst.m_left = j*ALL_BLOCK_SIZE + m_scrollx;
				dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
				dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

				Draw::Draw(2, &src, &dst, bl, 0.0f);
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

	//上る壁に触れた時の描画変更初期化
	Hit_wall = false;

	Hit_wall_r = false;

	m_up = false;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j*32.0f;
				float by = i*32.0f;

				//スクロールの影響
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scrollx) + 64.0f > bx) && (*x + (-scrollx) < bx + 32.0f) 
				 && (*y + (-scrolly) + 64.0f > by) && (*y + (-scrolly) < by + 32.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scrollx)) - bx+16;
					float rvy = (*y + (-scrolly)) - by+16;

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
					if (len < 55.0f)
					{
						//角度で上下左右を判定
						if ((r < 45 && r>0) || r > 315)
						{
							//右
							*right = true;//オブジェクトの左の部分が衝突している
							*x = bx + 32.0f + (scrollx);//ブロックの位置+主人公の幅
							*vx = 0.5f;//反発
							Hit_wall = false;
							Hit_wall_r = false;

							//マップに2があればくっつく
							if (m_map[i][j] == 2)
							{
								*x= bx + 31.0f + (scrollx);//ブロックの位置-主人公の幅
								if (*vy > 0.0f)
									*vy = 0.0f;//くっつくため反発なし
								*vx = 0.0f;
								Hit_wall = true;

								Audio::Start(5);

								//右キー入力で離れる
								if (Input::GetVKey(VK_RIGHT) == true)
								{
									*vx = 0.5f;//反発
									Hit_wall = false;
									Hit_wall_r = false;
								}

								if (Input::GetVKey(VK_UP) == true)
								{
									Hit_wall = false;
									Hit_wall_r = true;
									*vx = 0.5f;//反発
									*vy = -3.0f;
								}
							}

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 64.0f + (scrolly);//ブロックの位置-主人公の幅
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 64.0f + (scrollx);//ブロックの位置-主人公の幅
							*vx = -0.5f;//反発
							Hit_wall = false;
							Hit_wall_r = false;

							//マップに2があればくっつく
							if (m_map[i][j] == 2)
							{
								*x = bx - 63.0f + (scrollx);//ブロックの位置-主人公の幅
								*vx = 0.0f;//くっつくため反発なし
							
								if(*vy>0.0f)
									*vy = 0.0f;//くっつくため反発なし
								Hit_wall = true;

								Audio::Start(5);

								//左キー入力で離れる
								if (Input::GetVKey(VK_LEFT) == true)
								{
									Hit_wall = false;
									Hit_wall_r = false;
									*vx = -0.5f;//反発
								}

								if (Input::GetVKey(VK_UP) == true)
								{
									Hit_wall = false;
									Hit_wall_r = true;
									*vx = -0.5f;//反発
									*vy = -3.0f;
								}

							}
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公の上の部分が衝突している
							*y = by + 32.0f + (scrolly);//ブロックの位置+主人公の幅
							//m_up = false;

							//*vx = 0.0f;
							if (*vy < 0)
							{
								*vy = 0.0f;
							}

							//マップに2があればくっつく
							if (m_map[i][j] == 2)
							{
								*y = by + 29.0f + (scrolly);//ブロックの位置+主人公の幅
								*vy = 0.0f;//くっつくため反発なし

								//m_up = true;
								Audio::Start(5);

								//下キー入力で離れる
								if (Input::GetVKey(VK_DOWN) == true)
								{
									*vy = 0.5f;//反発
									//m_up = false;
								}

								/*if (Input::GetVKey(VK_UP) == true)
								{
									Hit_wall = false;
									*vx = -0.5f;//反発
									*vy = -3.0f;
								}*/
							}
						}
					}
				}
			}
		}
	}
}


//BlockHitEne関数(アジ・イワシ用)
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
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j*32.0f;
				float by = i*32.0f;

				//スクロールの影響
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scrollx) + 50.0f > bx) && (*x + (-scrollx) < bx + 32.0f) 
				 && (*y + (-scrolly) + 64.0f > by) && (*y < by + (-scrolly) + 32.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

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
							*x = bx + 32.0f + (scrollx);//ブロックの位置+主人公の幅
							*vx = 0.0f;//-VX*反発係数

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 50.0f + (scrolly);//ブロックの位置-主人公の幅
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 64.0f + (scrollx);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.0f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公の上の部分が衝突している
							*y = by + 32.0f + (scrolly);//ブロックの位置+主人公の幅

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

//BlockHitEne2関数(あんこう用)
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
void CObjBlock::BlockHitEne2(
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
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 32.0f;
				float by = i * 32.0f;

				//スクロールの影響
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scrollx) + 64.0f > bx) && (*x + (-scrollx) < bx + 32.0f) 
				 && (*y + (-scrolly) + 110.0f > by) && (*y < by + (-scrolly) + 32.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//長さを求める
					float len = sqrt(rvx*rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

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
							*x = bx + 32.0f + (scrollx);//ブロックの位置+主人公の幅
							*vx = 0.0f;//-VX*反発係数

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 110.0f + (scrolly);//ブロックの位置-主人公の幅
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 64.0f + (scrollx);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.0f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公の上の部分が衝突している
							*y = by + 32.0f + (scrolly);//ブロックの位置+主人公の幅

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

//BlockHitBoss1関数
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
void CObjBlock::BlockHitBoss1(
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
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 32.0f;
				float by = i * 32.0f;

				//スクロールの影響
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scrollx) + 100.0f > bx) && (*x + (-scrollx) < bx + 32.0f) && (*y +(scrolly)+ 50.0f > by) && (*y < by + (scrolly) + 32.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//長さを求める
					float len = sqrt(rvx*rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

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
							*x = bx + 32.0f + (scrollx);//ブロックの位置+主人公の幅
							*vx = 0.0f;//-VX*反発係数

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 50.0f + (scrolly);//ブロックの位置-主人公の幅
							*vy = 0.0f;
							
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 100.0f + (scrollx);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.0f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公の上の部分が衝突している
							*y = by + 32.0f + (scrolly);//ブロックの位置+主人公の幅

							/*if (*vy < 0)
							{
								*vy = 0.0f;
							}*/
						}
					}
				}
			}
		}
	}
}


//BlockHitBoss2関数
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
void CObjBlock::BlockHitBoss2(
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
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 32.0f;
				float by = i * 32.0f;

				//スクロールの影響
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scrollx) + 150.0f > bx) && (*x + (-scrollx) < bx + 32.0f) && (*y + (scrolly)+ 50.0f > by) && (*y < by + (scrolly)+ 32.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//長さを求める
					float len = sqrt(rvx*rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

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
							*x = bx + 32.0f + (scrollx);//ブロックの位置+主人公の幅
							*vx = 0.0f;//-VX*反発係数

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 50.0f + (scrolly);//ブロックの位置-主人公の幅
							*vy = 0.0f;

						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 150.0f + (scrollx);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.0f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公の上の部分が衝突している
							*y = by + 32.0f + (scrolly);//ブロックの位置+主人公の幅

							/*if (*vy < 0)
							{
								*vy = 0.0f;
							}*/
						}
					}
				}
			}
		}
	}
}


//BlockHitBoss3関数
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
void CObjBlock::BlockHitBoss3(
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
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 32.0f;
				float by = i * 32.0f;

				//スクロールの影響
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//オブジェクトとブロックの当たり判定
				if ((*x + (-scrollx) + 200.0f > bx) && (*x + (-scrollx) < bx + 32.0f) && (*y + (scrolly)+ 50.0f > by) && (*y < by + (scrolly)+ 32.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//長さを求める
					float len = sqrt(rvx*rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

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
							*x = bx + 32.0f + (scrollx);//ブロックの位置+主人公の幅
							*vx = 0.0f;//-VX*反発係数

						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 50.0f + (scrolly);//ブロックの位置-主人公の幅
							*vy = 0.0f;

						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 200.0f + (scrollx);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.0f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公の上の部分が衝突している
							*y = by + 32.0f + (scrolly);//ブロックの位置+主人公の幅

							/*if (*vy < 0)
							{
								*vy = 0.0f;
							}*/
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