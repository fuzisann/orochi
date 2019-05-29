//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBubble.h"
#include "ObjBlock.h"
#include "UtilityModule.h"

#include "GameL\Audio.h"

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

	m_damage = 1;

	//�ړ��x�N�g���̐��K��
	UnitVec(&m_vx, &m_vy);

	//�����蔻��phitBox�쐬
	Hits::SetHitBox(this, m_x, m_y, 35, 35, ELEMENT_BUBBLE, OBJ_BUBBLE, 1);
}

//�A�N�V����
void CObjBubble::Action()
{
	//��l���ƖA�Ŋp�x�����
	CObjHero* obj = (CObjHero*)Objs::GetObj(COBJ_HERO);

	CObjBlock*b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l�������݂���ꍇ�A�U���p�x�̌v�Z����
	if (obj != nullptr)
	{
		float x = obj->GetX() - m_x- b->GetScrollX();
		float y = obj->GetY() - m_y- b->GetScrollY();
		float ar = GetAtan2Angle(x, -y);

		//�e�ۂ̌��݂̌����Ă���p�x�����
		float br = GetAtan2Angle(m_vx, -m_vy);

		//��l���@�ƓG�@�p�x�����܂�ɂ��������ꂽ��
		
		if (ar - br > 20)
		{
			//�ړ���������l���@�̕����ɂ���
			m_vx = cos(3.14 / 180 * ar);
			m_vy = -sin(3.14 / 180 * ar);
		}
		
		float yy = m_vy;
		float xx = m_vx;
		float r = 3.14 / 180.0f;	//�p�x�P��
		if (ar < br)
		{
			//�ړ������ɂ�+1��������
			m_vx = xx * cos(r) - yy * sin(r);
			m_vy = yy * cos(r) + xx * sin(r);
		}
		else
		{
			//�ړ������ɂ�-1��������
			m_vx = xx * cos(-r) - yy * sin(-r);
			m_vy = yy * cos(-r) + xx * sin(-r);
		}
		UnitVec(&m_vx, &m_vy);

	}

	//�ړ��x�N�g�������W�ɉ��Z����
	m_x += m_vx * 5.0f;
	m_y += m_vy * 5.0f;

	//HitBox�̓��e���X�V
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu��ύX	
	hit->SetPos(m_x + block->GetScrollX(), m_y + block->GetScrollY());

	//�u���b�N�ɓ�����ƍ폜
	/*if (m_hit_right == true || m_hit_left == true
	 || m_hit_up == true || m_hit_down == true)
	{
		Audio::Start(5);	//��
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;
	}*/

	//��ʊO�ɏo����j�����鏈��
	if (m_x + block->GetScrollX() > 800.0f || m_x + block->GetScrollX() < -45.0f
		&& m_y + block->GetScrollY() > 600.0f || m_y + block->GetScrollY() < 45.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;
	}

	//��l���I�u�W�F�N�g�ƐڐG������U���e�ۍ폜
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		Audio::Start(9);	//��
		hit->SetInvincibility(true);//�����蔻�薳��
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;
	}

	//��������������A�폜
	if (hit->CheckElementHit(ELEMENT_ATTACK) == true)
	{
		Audio::Start(7);	//��
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;
	}

	//���S�ɗ̈�O�ɏo����j������
	/*bool Check = CheckWindow(m_x, m_y, -32.0f, -32.0f, 800.0f, 600.0f);
	if (Check == false)
	{
		this->SetStatus(false);		//���g�ɍ폜���߂��o���B
		Hits::DeleteHitBox(this);	//�G�@�e�ۂ����L����HitBox�ɍ폜����B
	}*/
}

//�h���[
void CObjBubble::Draw()
{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = 35.0f;
	src.m_bottom = 35.0f;

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top    =  0.0f   +m_y + block->GetScrollY();
	dst.m_left   =  0.0f   +m_x + block->GetScrollX();
	dst.m_right  = 35.0f   +m_x + block->GetScrollX();
	dst.m_bottom = 35.0f   +m_y + block->GetScrollY();

	float r = 0.0f;
	//��l���@�ƗU���e�ۂŊp�x�����
	CObjHero* obj = (CObjHero*)Objs::GetObj(COBJ_HERO);

	//��l���@�����݂���ꍇ�A�U���p�x�̌v�Z����
	if (obj != nullptr)
	{
		float x = obj->GetX() - m_x;
		float y = obj->GetY() - m_y;
		r = GetAtan2Angle(x, -y);
	}

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(21, &src, &dst, c, r);
}
