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

extern bool m_m_change;

//使用ヘッダー
#include"SceneMain.h"
#include"GameHead.h"
#include"ObjArrow.h"


//コンストラクタ
CSceneMain::CSceneMain()
{
	//ooo//
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
		p = Save::ExternalDataOpen(L"stage1 (完成).csv", &size);//外部データ読み込み
	}
	else if (g_map_chenge == 1)
	{
		p = Save::ExternalDataOpen(L"新ステージ2.csv", &size);//外部データ読み込み
	}
	else if (g_map_chenge == 2)
	{
		p = Save::ExternalDataOpen(L"新ステージ3.csv", &size);//外部データ読み込み
	}
	/*else if (g_map_chenge == 3)
	{
		p = Save::ExternalDataOpen(L"map9-6.csv", &size);//外部データ読み込み
	}
	else if (g_map_chenge == 4)
	{
		p = Save::ExternalDataOpen(L"map10-4.csv", &size);//外部データ読み込み
	}*/

	int map[50][150];
	int count = 1;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
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
	Draw::LoadImage(L"主人公3.png", 0, TEX_SIZE_512);

	if (g_map_chenge == 0)
	{
		//背景画像読み込み
		Draw::LoadImage(L"１ステージ背景.png", 3, TEX_SIZE_1024);
		//ブロック画像読み込み
		Draw::LoadImage(L"ステージ1ブロック.png", 2, TEX_SIZE_512);

		//敵画像読み込み
		Draw::LoadImage(L"あじ完成版.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ完成版.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"あんこう.png", 10, TEX_SIZE_512);//テスト用
		Draw::LoadImage(L"カメ.png", 12, TEX_SIZE_512);
		Draw::LoadImage(L"アジ(死亡用).png", 13, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ(死亡用).png", 14, TEX_SIZE_512);
		Draw::LoadImage(L"カメ(死亡用).png", 15, TEX_SIZE_512);

		//体力の読み込み
		Draw::LoadImage(L"体力ゲージフル.png", 17, TEX_SIZE_512);

		//剣画像読み込み
		Draw::LoadImageW(L"剣.png", 16, TEX_SIZE_512);
	}
	else if (g_map_chenge == 1)
	{
		//背景画像読み込み
		Draw::LoadImage(L"２ステージ背景.png", 3, TEX_SIZE_1024);
		//ブロック画像読み込み
		Draw::LoadImage(L"ステージ2ブロック.png", 2, TEX_SIZE_512);
		//敵画像読み込み
		Draw::LoadImage(L"あじ完成版.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ完成版.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"あんこう完成.png", 10, TEX_SIZE_512);
		Draw::LoadImage(L"リュウグウノツカイ　完成版.png", 12, TEX_SIZE_512);
		Draw::LoadImage(L"アジ(死亡用).png", 13, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ(死亡用).png", 14, TEX_SIZE_512);
		Draw::LoadImage(L"リュウグウノツカイ(死亡用).png", 15, TEX_SIZE_512);
		//Draw::LoadImage(L"あんこう(死亡用).png", 16, TEX_SIZE_512);

		//剣画像読み込み
		Draw::LoadImageW(L"剣.png", 16, TEX_SIZE_512);
	}
	else if (g_map_chenge == 2)
	{
		//背景画像読み込み
		Draw::LoadImage(L"３ステージ背景.png", 3, TEX_SIZE_1024);
		//ブロック画像読み込み
		Draw::LoadImage(L"ステージ3ブロック.png", 2, TEX_SIZE_512);
		//敵画像読み込み
		Draw::LoadImage(L"あじ完成版.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ完成版.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"あんこう完成.png", 10, TEX_SIZE_512);
		Draw::LoadImage(L"乙姫サメ.png", 12, TEX_SIZE_512);
		Draw::LoadImage(L"アジ(死亡用).png", 13, TEX_SIZE_512);
		Draw::LoadImage(L"イワシ(死亡用).png", 14, TEX_SIZE_512);

		Draw::LoadImageW(L"剣.png", 16, TEX_SIZE_512);
	}

	//竜宮城画像(1ステージ目ゴール用)
	Draw::LoadImage(L"竜宮城1.png", 5, TEX_SIZE_512);

	Draw::LoadImage(L"主人公体力.png", 20, TEX_SIZE_512);

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

	//オーディオ読み込み
	if (g_map_chenge == 0)
	{
		//音楽読み込み
		Audio::LoadAudio(0, L"ステージ1BGM.wav", BACK_MUSIC);
		//ボリューム1.5
		//float f = Audio::VolumeMaster(-0.3);

	}
	else if (g_map_chenge == 1)
	{
		//音楽読み込み
		Audio::LoadAudio(0, L"ステージ2BGM.wav", BACK_MUSIC);
		//ボリューム1.5
		//float f = Audio::VolumeMaster(-0.3);
	}
	else if (g_map_chenge == 2)
	{
		//音楽読み込み
		Audio::LoadAudio(0, L"ステージ3BGM.wav", BACK_MUSIC);
		//ボリューム1.5
		//float v = Audio::VolumeMaster(-0.1);
	}

	Audio::LoadAudio(1, L"剣攻撃音.wav", EFFECT);
	Audio::LoadAudio(2, L"ジャンプ音.wav", EFFECT);
	Audio::LoadAudio(3, L"ダメージ音(主人公).wav", EFFECT);
	Audio::LoadAudio(4, L"ダメージ音(敵).wav", EFFECT);
	Audio::LoadAudio(5, L"ひっつく音.wav", EFFECT);

	Audio::LoadAudio(6, L"ボス戦BGM.wav",BACK_MUSIC);

	float f = Audio::VolumeMaster(-0.2);

	Audio::Start(0);
}


//実行中メソッド
void CSceneMain::Scene()
{
	//チェンジスイッチの情報を取得
	CObjChangeSwitch* change = (CObjChangeSwitch*)Objs::GetObj(OBJ_CHANGESWITCH);

	if (m_m_change == false)
	{
		//メイン音楽ストップ
		Audio::Stop(0);
		//ボス音楽スタート
		Audio::Start(6);
		m_m_change = true;
	}
}