//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "GameHead.h"
#include "SceneOver.h"

//実行中メソッド
void CSceneOver::Scene()
{

}

//コンストラクタ
CSceneOver::CSceneOver()
{
}

//デストラクタ
CSceneOver::~CSceneOver()
{
}

//初期化メソッド
void CSceneOver::InitScene()
{
	//出力させる文字のグラフィックを作成
	Draw::LoadImage(L"ゲームオーバー.png", 4, TEX_SIZE_512);

	//背景オブジェクト作成
	CObjOver* go1 = new CObjOver();
	Objs::InsertObj(go1, OBJ_OVER, 4);

	//音楽読み込み
	Audio::LoadAudio(0, L"選択音.wav", EFFECT);
	Audio::LoadAudio(1, L"決定音.wav", EFFECT);
	Audio::LoadAudio(2, L"ゲームオーバーBGM候補.wav", BACK_MUSIC);
	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0.1);

	//音楽スタート
	Audio::Start(2);
}
