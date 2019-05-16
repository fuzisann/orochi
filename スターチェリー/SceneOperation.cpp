//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include"GameL\DrawTexture.h"
#include"GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "SceneMain.h"
#include "GameHead.h"
#include "SceneOperation.h"
#include "ObjOperation.h"

//コンストラクタ
CSceneOperation::CSceneOperation()
{

}

//デストラクタ
CSceneOperation::~CSceneOperation()
{

}

//ゲームメイン初期化メソッド
void CSceneOperation::InitScene()
{
	//出力させる文字のグラフィックを作成
	Draw::LoadImage(L"操作説明.png", 3, TEX_SIZE_1024);

	//オブジェクト作成
	CObjOperation* ope = new CObjOperation();
	Objs::InsertObj(ope, OBJ_OPERATION, 3);

	//音楽情報の読み込み
	Audio::LoadAudio(0, L"決定音.wav", EFFECT);

	//バックミュージックスタート
	float Volume = Audio::VolumeMaster(0.5);
}

//ゲームメイン実行中メソッド
void CSceneOperation::Scene()
{

}