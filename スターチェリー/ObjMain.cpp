//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL\Audio.h"

#include "ObjMain.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjMain::Init()
{
	
}

//アクション
void CObjMain::Action()
{

}

//ドロー
void CObjMain::Draw()
{
	
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	hero_hp = hero->GetHP();	//主人公からHPの情報を取得

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置


	wchar_t HP[128];

	
	//画面上部のメニュー画面

	swprintf_s(HP, L"HP %d", hero_hp);
	Font::StrDraw(HP, GAME_HP_POS_X, GAME_HP_POS_Y, GAME_HP_FONT_SIZE, c);//HPを表示

}