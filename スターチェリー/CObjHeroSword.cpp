//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "CObjHeroSword.h"
#include "CObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHeroSword::CObjHeroSword(float x, float y)
{
	m_x = x;
	m_y = y;
}
//�C�j�V�����C�Y
void CObjHeroSword::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hero_x = 0.0f;
	m_hero_y = 0.0f;

	m_posture = 0.0f;	//�E����0.0f ������1.0f

	//block�Ƃ̏Փˏ�Ԋm�F
	m_hit_left = false;
	m_hit_right = false;
	m_hit = false;

	//��l���̈ʌ������擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	m_posture = hero->GetPOS();

	m_ani_frame_x = 0;		//�\�[�h�̃A�j���[�V�����p
	m_ani_frame_y = 0;

	m_time = 0;		//�\�[�h�������鎞��

	m_sword_time = 10;	//���������鎞��

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x + 25, m_y, 50, 50, ELEMENT_ATTACK, OBJ_SWORD, 1);
}

//�A�N�V����
void CObjHeroSword::Action()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	m_hero_x = hero->GetX();
	m_hero_y = hero->GetY();

	if (m_hit_left == true)	//��
		m_hit = true;
	if (m_hit_right == true)//�E
		m_hit = true;

	if (m_posture == 0.0f) {
		m_ani_frame_y = 0;
	}
	if (m_posture == 1.0f) {
		m_ani_frame_y = 1;
	}

	if (m_posture == 0.0f)
		m_x = m_hero_x + 55;
	else
		m_x = m_hero_x - 35;

	m_y = m_hero_y ;

	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);

	//�G�ƐڐG�����猕�폜
	if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		//this->SetStatus(false);
		//Hits::DeleteHitBox(this);
		hit->SetInvincibility(true);

	}

	//�ǂɓ�������������鏈��
	if (m_hit == true) {
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}
	//���̎��Ԃŏ����鏈��
	if (m_sword_time > 0) {
		m_sword_time--;
		if (m_sword_time <= 0) {
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}

	if (m_sword_time == 9) {
		m_ani_frame_x = 0;
	}
	else if (m_sword_time == 6) {
		m_ani_frame_x = 1;
	}
	else if (m_sword_time == 3) {
		m_ani_frame_x = 2;
	}


}

//�h���[
void CObjHeroSword::Draw()
{
	//�`��J���[���@R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float  c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f + (64.0f * m_ani_frame_y);
	src.m_left = 0.0f + (64.0f * m_ani_frame_x);
	src.m_right = 64.0f + (64.0f * m_ani_frame_x);
	src.m_bottom = 64.0f + (64.0f * m_ani_frame_y);


	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = 50.0f + m_x;
	dst.m_bottom = 50.0f + m_y;

	Draw::Draw(16, &src, &dst, c, 0.0f);
}