//使用するヘッダーファイル
#include"GameHead.h"
#include"CObjStick.h"
#include"GameL\DrawTexture.h"
#include"GameL\HitBoxManager.h"


//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjStick::CObjStick(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjStick::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;

	Hits::SetHitBox(this, m_x, m_y, 50, 50, ELEMENT_MAGIC, OBJ_STICK, 1);
}

//アクション
void CObjStick::Action()
{
	 
}

