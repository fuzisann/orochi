#pragma once
//使用するヘッダーファイル
#include"GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト:ゲームクリア
class CObjClear : public CObj
{
public:
	CObjClear() {};
	~CObjClear() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:
	bool m_key_flag;//キーフラグ
	float m_and;		//透明度処理用
	bool m_andf;		//透明度処理用フラグ
	int choose;
};