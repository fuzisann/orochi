//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL\Audio.h"

#include "ObjMain.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMain::Init()
{
	
}

//�A�N�V����
void CObjMain::Action()
{

}

//�h���[
void CObjMain::Draw()
{
	
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	hero_hp = hero->GetHP();	//��l������HP�̏����擾

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	wchar_t HP[128];

	//�؂���ʒu�̐ݒ�
	src.m_top = 50.0f *  m_posture - 1;	 //������-1
	src.m_left = 0.0f + (AniData[m_ani_frame] * 48);
	src.m_right = 48.0f + (AniData[m_ani_frame] * 48);
	src.m_bottom = 50.0f * (m_posture + 1) - 3;//������-3

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 50.0f + m_px;
	dst.m_bottom = 50.0f + m_py;

	Draw::Draw(17, &src, &dst, c, 0.0f);
	
	/*swprintf_s(HP, L"HP %d", hero_hp);
	Font::StrDraw(HP, GAME_HP_POS_X, GAME_HP_POS_Y, GAME_HP_FONT_SIZE, c);//HP��\��*/

}