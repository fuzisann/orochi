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
#include "SceneMenu.h"
#include "GameHead.h"

//コンストラクタ
CSceneMenu::CSceneMenu()
{

}

//デストラクタ
CSceneMenu::~CSceneMenu()
{

}

//初期化メソッド
void CSceneMenu::InitScene()
{

	//背景オブジェクト作成
	CObjMenu* om1 = new CObjMenu();
	Objs::InsertObj(om1, OBJ_MENU, 1);

}
//実行中メソッド
void CSceneMenu::Scene()
{

}