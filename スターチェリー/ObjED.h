#pragma once
//使用するヘッダーファイル
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//描画関係の定数

#define GAME_CLEAR_X (50)
#define GAME_CLEAR_Y (150)
#define GAME_CLEAR_FONT_SIZE (25)

//オブジェクト:クリア
class CObjED : public CObj
{
public:
	CObjED() {};
	~CObjED() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	bool m_key_flag;//キーフラグ
	float m_y;
};