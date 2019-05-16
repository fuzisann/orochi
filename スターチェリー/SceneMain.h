#pragma once
//使用するヘッダーファイル
#include"GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:メイン
class CSceneMain :public CScene
{
	public:
		CSceneMain();
		~CSceneMain();
		void InitScene();//初期化メソッド
		void Scene();    //実行中メソッド

	private:
		//bool m_m_change;//BGM変更
};

