//STLデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include"GameL\DrawTexture.h"
#include"GameL\SceneObjManager.h"
#include"GameL\DrawTexture.h"
#include"GameL\DrawFont.h"
#include"GameL\UserData.h"
#include"GameL\DrawFont.h"
#include"GameL\Audio.h"
//使用するネームスペース
using namespace GameL;


//使用ヘッダー
#include"SceneMain.h"
#include"GameHead.h"
#include"ObjArrow.h"


//コンストラクタ
CSceneMain::CSceneMain()
{

}

//テストラクタ
CSceneMain::~CSceneMain()
{

}


//初期化メソッド
void CSceneMain::InitScene()
{
	//Font作成
	Font::SetStrTex(L"0123456789分秒");

	//外部データの読み込み（ステージ情報）
	unique_ptr<wchar_t> p; //ステージ情報ポインター
	int size;              //ステージ情報の大きさ

	if (g_map_chenge == 0)
	{
		p = Save::ExternalDataOpen(L"ステージ1完成.csv", &size);//外部データ読み込み
	}
	else if (g_map_chenge == 1)
	{
		p = Save::ExternalDataOpen(L"ステージ2完成.csv", &size);//外部データ読み込み
	}
	else if (g_map_chenge == 2)
	{
		p = Save::ExternalDataOpen(L"マップ3.csv", &size);//外部データ読み込み
	}
	/*else if (g_map_chenge == 3)
	{
		p = Save::ExternalDataOpen(L"map9-6.csv", &size);//外部データ読み込み
	}
	else if (g_map_chenge == 4)
	{
		p = Save::ExternalDataOpen(L"map10-4.csv", &size);//外部データ読み込み
	}*/

	int map[19][100];
	int count = 1;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			if(w>=10)
				count += 3;
			else
				count += 2;
		}
	}

	//Font作成
	Font::SetStrTex(L"0123456789分秒");
	
	//外部グラフィックファイルを読み込み0番に登録（576x384ピクセル）
	Draw::LoadImage(L"主人公１.png", 0, TEX_SIZE_512);

	if (g_map_chenge == 0)
	{
		//背景画像読み込み
		Draw::LoadImage(L"１ステージ背景.png", 3, TEX_SIZE_1024);
		//ブロック画像読み込み
		Draw::LoadImage(L"ブロック1.png", 2, TEX_SIZE_512);
		Draw::LoadImage(L"ひっつくブロック.png", 4, TEX_SIZE_512);

		//チェンジスイッチ＆ゲート画像読み込みテスト
		Draw::LoadImage(L"雲ブロック.png", 6, TEX_SIZE_512);
		Draw::LoadImage(L"氷ブロック.png", 7, TEX_SIZE_512);

		//敵画像読み込み
		Draw::LoadImage(L"あじ完成版.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ完成版.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"カメ.png", 12, TEX_SIZE_512);

		//歯車画像読み込みテスト
		Draw::LoadImage(L"歯車1.5.png", 10, TEX_SIZE_512);

		Draw::LoadImage(L"歯車4.png", 11, TEX_SIZE_512);

		//体力の読み込み
		Draw::LoadImage(L"体力ゲージフル.png", 17, TEX_SIZE_512);
		Draw::LoadImage(L"体力ゲージフル.png", 18, TEX_SIZE_512);
		Draw::LoadImage(L"体力ゲージフル.png", 19, TEX_SIZE_512);

		//剣画像読み込み
		Draw::LoadImageW(L"剣.png", 16, TEX_SIZE_512);
	}
	else if (g_map_chenge == 1)
	{
		//背景画像読み込み
		//Draw::LoadImage(L"２ステージ背景.png", 3, TEX_SIZE_1024);
		//ブロック画像読み込み
		Draw::LoadImage(L"ステージ2ブロック.png", 2, TEX_SIZE_512);
		Draw::LoadImage(L"ひっつくブロック.png", 4, TEX_SIZE_512);
		//敵画像読み込み
		Draw::LoadImage(L"あじ完成版.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ完成版.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"リュウグウノツカイ　完成版.png", 12, TEX_SIZE_512);
		//剣画像読み込み
		Draw::LoadImageW(L"剣.png", 16, TEX_SIZE_512);
		/*//背景画像読み込み
		Draw::LoadImage(L"map.jpg", 3, TEX_SIZE_1024);
		//マップ2　ブロック画像読み込み
		Draw::LoadImage(L"brock5.png", 1, TEX_SIZE_512);
		//針罠読み込み
		Draw::LoadImage(L"blockobj2.png", 4, TEX_SIZE_512);*/
	}
	else if (g_map_chenge == 2)
	{
		//背景画像読み込み
		Draw::LoadImage(L"３ステージ背景.png", 3, TEX_SIZE_1024);
		//ブロック画像読み込み
		Draw::LoadImage(L"ステージ3ブロック.png", 2, TEX_SIZE_512);
		Draw::LoadImage(L"ひっつくブロック.png", 4, TEX_SIZE_512);
		//敵画像読み込み
		Draw::LoadImage(L"あじ完成版.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ完成版.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"乙姫.png", 12, TEX_SIZE_512);
		//剣画像読み込み
		Draw::LoadImageW(L"剣.png", 16, TEX_SIZE_512);
		/*//背景画像読み込み
		Draw::LoadImage(L"氷の洞窟2.jpg", 3, TEX_SIZE_1024);
		//マップ7　ブロック画像読み込み
		Draw::LoadImage(L"氷ブロック.png", 1, TEX_SIZE_512);
		//マップ7　ブロック画像読み込み
		Draw::LoadImage(L"氷ブロック2.png", 6, TEX_SIZE_512);
		//氷柱罠読み込み
		Draw::LoadImage(L"氷柱ブロック.png",7, TEX_SIZE_512);*/
	}
	/*else if (g_map_chenge == 3) 
	{
		//背景画像読み込み
		Draw::LoadImage(L"雲の上ステージ.jpg", 3, TEX_SIZE_1024);
		//マップ9　ブロック画像読み込み
		Draw::LoadImage(L"雲ブロック.png", 1, TEX_SIZE_512);
		//マップ9　ブロック画像読み込み
		Draw::LoadImage(L"雲ブロック.png", 9, TEX_SIZE_512);
	}
	else if (g_map_chenge == 4)
	{
		//マップ10  背景画像読み込み
		Draw::LoadImage(L"ラストステージ.gif", 3, TEX_SIZE_1024);
		//マップ10　ブロック画像読み込み
		Draw::LoadImage(L"ラストステージブロック.png", 1, TEX_SIZE_512);
		//マップ10　ブロック画像読み込み
		Draw::LoadImage(L"氷ブロック2.png", 6, TEX_SIZE_512);
		//マップ10  氷柱罠読み込み
		Draw::LoadImage(L"氷柱ブロック.png", 7, TEX_SIZE_512);
		//マップ10　ブロック画像読み込み
		Draw::LoadImage(L"ひび割れブロック.png", 8, TEX_SIZE_512);
		//マップ10　ブロック画像読み込み
		Draw::LoadImage(L"落ちる石ブロック.png", 9, TEX_SIZE_512);
	}*/
	
	//ゴール
	Draw::LoadImage(L"efe.png", 5, TEX_SIZE_512);

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero(map);   //主人公オブジェクト作成
	Objs::InsertObj(obj, COBJ_HERO, 30);//作った主人公オブジェクトをオブジェクトマネージャーに登録

	//背景オブジェクト作成
	C0bjBackground * back = new C0bjBackground();
	Objs::InsertObj(back, OBJ_BACKGROUND, 1);
	
	//blockオブジェクト作成
	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 9);

	//敵オブジェクト作成
	/*CObjEnemy1* obje1 = new CObjEnemy1();
	Objs::InsertObj(obje1, OBJ_ENEMY_FIRST, 10);*/

	/*CObjEnemy2* obje2 = new CObjEnemy2();
	Objs::InsertObj(obje2, OBJ_ENEMY_SECOND, 10);*/

	CObjMain* objm = new CObjMain();
	Objs::InsertObj(objm, OBJ_MAIN, 120);

	/*if (g_map_chenge == 0)
	{
		//音楽読み込み
		Audio::LoadAudio(0, L"moristage.wav", BACK_MUSIC);
		//ボリューム1.5
		float f = Audio::VolumeMaster(1.5);
	}
	else if (g_map_chenge == 1)
	{
		//音楽読み込み
		Audio::LoadAudio(0, L"洞窟.wav", BACK_MUSIC);
		//ボリューム1.5
		float v = Audio::VolumeMaster(1.5);
	}
	else if (g_map_chenge == 2)
	{
		//音楽読み込み
		Audio::LoadAudio(0, L"map7.wav", BACK_MUSIC);
		//ボリューム1.5
		float v = Audio::VolumeMaster(1.5);
	}
	else if (g_map_chenge == 3)
	{
		//音楽読み込み
		Audio::LoadAudio(0, L"map9BGM.wav", BACK_MUSIC);
		//ボリューム1.5
		float v = Audio::VolumeMaster(1.5);
	}
	else if (g_map_chenge == 4)
	{
		//音楽読み込み
		Audio::LoadAudio(0, L"ラストステージ.wav", BACK_MUSIC);
		//ボリューム1.5
		float v = Audio::VolumeMaster(1.5);
	}
	Audio::LoadAudio(1, L"jump01.wav", EFFECT);
	//ボリューム1.5
	float v = Audio::VolumeMaster(1.0);

	//音楽スタート
	Audio::Start(0);
	*/

}


//実行中メソッド
void CSceneMain::Scene()
{

}