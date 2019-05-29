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

	
	//��ʏ㕔�̃��j���[���

	Draw::Draw(17, &src, &dst, c, 0.0f);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 48.0f;
	dst.m_right = 80.0f;
	dst.m_bottom = 36.0f;
	Draw::Draw(20, &src, &dst, c, 0.0f);
	
	//HP��\��
	
	swprintf_s(HP, L"HP�@�~%d", hero_hp, 15);
	Font::StrDraw(HP, GAME_HP_POS_X, GAME_HP_POS_Y, 37, c);
	if (hero_hp < 10)
	{
		swprintf_s(HP, L"/", hero_hp, 15);
		Font::StrDraw(HP, 129, GAME_HP_POS_Y, 37, c);
		swprintf_s(HP, L"%d", 20 + g_hero_max_hp, 15);
		Font::StrDraw(HP, 144, 10, 27, c);
	}
	else
	{
		swprintf_s(HP, L"/", hero_hp, 15);
		Font::StrDraw(HP, 148, GAME_HP_POS_Y, 37, c);
		swprintf_s(HP, L"%d", 20 + g_hero_max_hp, 15);
		Font::StrDraw(HP, 163, 10, 27, c);
	}

}