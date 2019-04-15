#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト : ブロック＆背景
class C0bjTime : public CObj
{
public:
	C0bjTime() {};
	~C0bjTime() {};
	void Init();   //イ二シャライズ
	void Action();	//アクション
	void Draw();    //ドロー

	void SetTimeFlag(bool b) { m_flag_time = b; }
private:
	int m_time;  //時間
	bool m_flag_time;//時間計測スタートフラグ
	int timekeeper[9];
	int i = 300;
	float gh_spx = 64.0f;
	float gh_spy = 500.0f;
};