//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneStageClear.h"
#include "GameHead.h"

//コンストラクタ
CSceneStageClear::CSceneStageClear()
{

}

//デストラクタ
CSceneStageClear::~CSceneStageClear()
{

}

//初期化メソッド
void CSceneStageClear::InitScene()
{
	//出力させるグラフィックを作成
	if (g_map_chenge == 0)
	{
		Draw::LoadImage(L"ゲームクリア.png", 4, TEX_SIZE_256);
	}
	else if (g_map_chenge == 1)
	{
		Draw::LoadImage(L"ステージクリア2.png", 4, TEX_SIZE_256);
	}

	//背景オブジェクト作成
	CObjStageClear* nk= new CObjStageClear();
	Objs::InsertObj(nk, OBJ_STAGE_CLEAR, 4);

	//音楽読み込み
	Audio::LoadAudio(0, L"ゲームクリアBGM.wav", BACK_MUSIC);
	Audio::LoadAudio(1, L"決定音.wav", EFFECT);

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(-0.1);

	//音楽スタート
	Audio::Start(0);
}
//実行中メソッド
void CSceneStageClear::Scene()
{

}