//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjChangeGate2.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//extern bool m_change;


CObjChangeGate2::CObjChangeGate2(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjChangeGate2::Init()
{
	m_vx = 0.0f;		//�ړ��x�N�g��
	m_vy = 0.0f;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_MYSTERY, OBJ_CHANGEGATE, 1);
}

//�A�N�V����
void CObjChangeGate2::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	//�`�F���W�X�C�b�`�̏����擾
	//CObjChangeSwitch* change = (CObjChangeSwitch*)Objs::GetObj(OBJ_CHANGESWITCH);
	//m_change = change->GetCHANGE();

	//�`�F���W�t���O���I���̏ꍇ
	if (m_change == true) {
		hit->SetInvincibility(true);	//���G�I��
	}
	else {
		hit->SetInvincibility(false);	//���G�I�t
	}

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScroll(), m_py);
}

//�h���[
void CObjChangeGate2::Draw()
{
	/*if (g_battle_flag == true)
	{
		return;
	}*/
	//�`��J���[���
	float g[4] = { 0.0f,1.0f,1.0f,1.0f };
	float a[4] = { 0.0f,0.0f,0.0f,0.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 32.0f + m_px + block->GetScroll();
	dst.m_bottom = 32.0f + m_py;

	//�`��
	if (m_change == true) {
		Draw::Draw(7, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(7, &src, &dst, g, 0.0f);
	}
}


