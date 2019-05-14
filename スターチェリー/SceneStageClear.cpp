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

	//出力させる文字のグラフィックを作成
	Draw::LoadImage(L"ゲームクリア.png", 4, TEX_SIZE_256);

	//背景オブジェクト作成
	CObjStageClear* nk= new CObjStageClear();
	Objs::InsertObj(nk, OBJ_CLEAR, 4);

	//音楽読み込み
	Audio::LoadAudio(0, L"ゲームクリアBGM候補.wav", BACK_MUSIC);

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(-0.1);

	//音楽スタート
	Audio::Start(0);
}
//実行中メソッド
void CSceneStageClear::Scene()
{

}