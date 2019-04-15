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
#include"SceneRanking.h"
#include "GameHead.h"

//コンストラクタ
CSceneRanking::CSceneRanking()
{

}

//デストラクタ
CSceneRanking::~CSceneRanking()
{

}

//初期化メソッド
void CSceneRanking::InitScene()
{
	//背景オブジェクト作成
	CObjRanking* or = new CObjRanking();
	Objs::InsertObj(or, OBJ_RANKING, 4);
}
//実行中メソッド
void CSceneRanking::Scene()
{

}