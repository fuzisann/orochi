#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト :背景
class C0bjBackground : public CObj
{
public:
	C0bjBackground() {};
	~C0bjBackground() {};

	void Init();   //イ二シャライズ
	void Action();	//アクション
	void Draw();    //ドロー
private:
	float m_x1;//背景1の位置情報

};