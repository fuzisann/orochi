#pragma once
#pragma once
//使用するヘッダーファイル
#include"GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:クリア
class CSceneOver : public CScene
{
public:
	CSceneOver();
	~CSceneOver();
	void InitScene();    //初期化メソッド
	void Scene();        //実行中メソッド
private:
};