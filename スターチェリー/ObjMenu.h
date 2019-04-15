#pragma once
#pragma once
//使用するヘッダーファイル
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//描画関係の定数
#define GAME_BACK_X (250)
#define GAME_BACK_Y (380)

#define TITLE_BACK_X (225)
#define TITLE_BACK_Y (490)

#define GAME_DOBLE_FONT (50)

//オブジェクト:クリア
class CObjMenu : public CObj
{
public:
	CObjMenu() {};
	~CObjMenu() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	bool m_key_flag;//キーフラグ
	int choose;
	int m_time;
};