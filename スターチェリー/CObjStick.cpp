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
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjStick::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;

	Hits::SetHitBox(this, m_x, m_y, 50, 50, ELEMENT_MAGIC, OBJ_STICK, 1);
}

//�A�N�V����
void CObjStick::Action()
{
	 
}

