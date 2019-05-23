//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBubble.h"
#include "ObjBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBubble::CObjBubble(float x, float y)
{
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjBubble::Init()
{
	m_vx    = -1.0f;
	m_vy    =  0.0f;
	m_event = 0;
	time2   = 0;
	//�����蔻��phitBox�쐬
	Hits::SetHitBox(this, m_px, m_py, 15, 15, ELEMENT_ENEMY, OBJ_BUBBLE, 1);
}

//�A�N�V����
void CObjBubble::Action()
{

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�x�N�g���̒��������߂�
	float r = 0.0f;
	r = m_vx*m_vx + m_vy*m_vy;
	r = sqrt(r);

	//������0���ǂ������ׂ�
	if (r == 0.0f)
	{
		;//0�Ȃ牽�����Ȃ�
	}
	else
	{
		//���K�����s��
		m_vx = 1.0f / r*m_vx;
		m_vy = 1.0f / r*m_vy;
	}
	check = false;

	//�C�x���g1�@�����
	if (m_event == 1)
	{
		//���x�t����B
		m_vx = -5.5f;
		m_vy = 0.0f;
	}

	//�C�x���g0�@��Ђ������ł�B
	/*if (m_event == 0)
	{
		//���x�t����B
		m_vx = 0.0f;
		m_vy = 0.0f;
		time2 += 1.0f;
		m_c = false;
		if (time2 >= 100)
		{
			m_event = 1;
			time2 = 0;
		}
	}*/

	//�ړ��x�N�g�������W�ɉ��Z����
	m_x += m_vx;
	m_y += m_vy;

	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y+16);

	//HitBox�̈ʒu��ύX	
	hit->SetPos(m_x + block->GetScrollX(), m_y+8 + block->GetScrollY());

	//�u���b�N�ɓ�����ƍ폜
	/*if (m_hit_right == true || m_hit_left == true
	 || m_hit_up == true || m_hit_down == true)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}*/


	//��ʊO�ɏo����|���j�����鏈��
	/*if (m_x + block->GetScrollX() > 800.0f ||
		m_x + block->GetScrollX() < -45.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}*/

	//�G�Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		//��l�����G�Ƃǂ̊p�x�������Ă��邩���m�F
		HIT_DATA**hit_data;           //�����������ׂ̍��ȏ������邽�߂̍\����
		hit_data = hit->SearchObjNameHit(COBJ_HERO);//hit_data�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

		for (int i = 0; i < hit->GetCount(); i++)
		{
			//�G�̍��E�ɓ���������
			float r = 0;
			for (int i = 0; i < 10; i++)
			{
				if (hit_data[i] != nullptr) {
					r = hit_data[i]->r;
				}
			}
			if (m_c==true)
			{
				this->SetStatus(false);
				Hits::DeleteHitBox(this);
			}
		}
	}

	//�u���b�N�Ƃ̓����蔻����s
	/*Objwall* pd = (Objwall*)Objs::GetObj(OBJ_WALL);
	if (pd != nullptr)
	{
		pd->wallHit(&m_x, &m_y, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type
		);
	}*/
}

//�h���[
void CObjBubble::Draw()
{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 15.0f;
	src.m_bottom = 15.0f;

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f   +m_y + block->GetScrollY();
	dst.m_left   =  0.0f   +m_x + block->GetScrollX();
	dst.m_right  = 15.0f   +m_x + block->GetScrollX();
	dst.m_bottom = 15.0f   +m_y + block->GetScrollY();

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(18, &src, &dst, c, 0.0f);
}
