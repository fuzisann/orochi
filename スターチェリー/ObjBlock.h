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
	CObjBlock(int map[19][100]);
	~CObjBlock() {};
	void Init();   //イ二シャライズ
	void Action();	//アクション
	void Draw();    //ドロー

	void SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }
	/*float GetScrollX() { return m_scroll; }
	float GetScrollY() { return m_scroll; }*/

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


private:
	void BlockDraw(float x, float y, RECT_F*dst, float c[]);
	int m_map[19][100]; //マップ情報

	float m_scroll;     //左右スクロール用
	float m_scroll_map;
	float x, y;

	int m_ani_time;
	int m_ani_frame;
	int m_ani_max_time;
};
