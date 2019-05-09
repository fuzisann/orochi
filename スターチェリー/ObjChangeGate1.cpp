//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjChangeGate1.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

extern bool m_change;

CObjChangeGate1::CObjChangeGate1(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_MYSTERY, OBJ_CHANGEGATE, 1);
}

//�C�j�V�����C�Y
void CObjChangeGate1::Init()
{
	m_vx = 0.0f;		//�ړ��x�N�g��
	m_vy = 0.0f;
}

//�A�N�V����
void CObjChangeGate1::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	CObjHero* hero = (CObjHero*)Objs::GetObj(COBJ_HERO);

	//�`�F���W�X�C�b�`�̏����擾
	CObjChangeSwitch* change = (CObjChangeSwitch*)Objs::GetObj(OBJ_CHANGESWITCH);
	//m_change = change->GetCHANGE();

	/*CObjChangeGate1* change = (CObjChangeGate1*)Objs::GetObj(OBJ_CHANGEGATE);
	m_change = change->GetCHANGE();*/

	//�`�F���W�t���O���I���̏ꍇ
	if (m_change == false) {
		
		hit->SetInvincibility(false);	//���G�I�t
	}
	else {
		hit->SetInvincibility(true);	//���G�I��
	}

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollX(), m_py + block->GetScrollY());

}

//�h���[
void CObjChangeGate1::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
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
	dst.m_top = 0.0f + m_py + block->GetScrollY();	//�`��ɑ΂��ăX�N���[���̉e����������
	dst.m_left = 0.0f + m_px + block->GetScrollX();
	dst.m_right = 32.0f + m_px + block->GetScrollX();
	dst.m_bottom = 32.0f + m_py + block->GetScrollY();

	//�`��
	if (m_change == false) {
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}

	/*if (m_change == true) {
		Draw::Draw(2, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(2, &src, &dst, g, 0.0f);
	}*/
}


