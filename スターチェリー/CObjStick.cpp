//�g�p����w�b�_�[�t�@�C��
#include"GameHead.h"
#include"CObjStick.h"
#include"GameL\DrawTexture.h"
#include"GameL\HitBoxManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjStick::CObjStick(float x, float y)
{
	m_x=x;
	m_y=y;
}

//�C�j�V�����C�Y
void CObjStick::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hero_x = 0.0f;
	m_hero_y = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 0;

	Hits::SetHitBox(this, m_x, m_y, 50, 50, ELEMENT_MAGIC, OBJ_STICK, 1);
}

//�A�N�V����
void CObjStick::Action()
{
	//��l���̏����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
		m_hero_x = hero->GetX();
		m_hero_y = hero->GetY();
	

}
//�h���[
void CObjStick::Draw()

{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 909.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1600.0f;
	dst.m_bottom = 920.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(4, &src, &dst, c, 0.0f);

}
