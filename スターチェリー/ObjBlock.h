#pragma once
//使用するヘッダー
#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include"GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

#define ALL_BLOCK_SIZE (32.0f)

//オブジェクト：ブロック＆背景
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[50][150]);
	~CObjBlock() {};
	void Init();   //イ二シャライズ
	void Action();	//アクション
	void Draw();    //ドロー

	void SetScrollX(float sx) { m_scrollx = sx; }
	void SetScrollY(float sy) { m_scrolly = sy; }
	//float GetScroll() { return m_scroll; }
	float GetScrollX() { return m_scrollx; }
	float GetScrollY() { return m_scrolly; }

	void Setwall(bool type = true);//隠し通路セット関数
	//void Setswitch(bool type = true);

	//ブロックの当たり判定
	void BlockHit(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//ブロックの当たり判定(敵)
	void BlockHitEne(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//ブロックの当たり判定(ボス1)
	void BlockHitBoss1(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//ブロックの当たり判定(ボス2)
	void BlockHitBoss2(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//ブロックの当たり判定(ボス2)
	void BlockHitBoss3(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);


private:
	void BlockDraw(float x, float y, RECT_F*dst, float c[]);
	int m_map[50][150]; //マップ情報

	float m_scroll;     //左右スクロール用
	float m_scroll_map;
	float x, y;

	float m_scrollx;		//左右スクロール用
	float m_scrolly;

	int m_ani_time;
	int m_ani_frame;
	int m_ani_max_time;
};
