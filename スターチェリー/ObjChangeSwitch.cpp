//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjChangeSwitch.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;


CObjChangeSwitch::CObjChangeSwitch(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjChangeSwitch::Init()
{
	m_change = false;	//�摜�؂�ւ�
	m_time = 0;
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_FIELD, OBJ_CHANGESWITCH, 1);
}

//�A�N�V����
void CObjChangeSwitch::Action()
{
	/*if (g_battle_flag == true)
	{
		return;
	}*/

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	//��l���Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		if (m_change == true) {
			m_change = false;
		}
		else {
			m_change = true;
		}
		hit->SetInvincibility(true);	//���G�I��
		m_time = 100;
	}
	/*if (m_time > 0)
	{
		m_time--;
		if (m_time <= 0)
		{
			m_time = 0;
			hit->SetInvincibility(false);	//���G�I�t
		}
	}*/
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScroll(), m_py);

}

//�h���[
void CObjChangeSwitch::Draw()
{
	/*if (g_battle_flag == true)
	{
		return;
	}*/

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float g[4] = { 0.0f,1.0f,1.0f,1.0f };
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };



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
	if (m_change == false) {
		Draw::Draw(6, &src, &dst, g, 0.0f);
	}
	else if (m_change == true) {
		Draw::Draw(6, &src, &dst, y, 0.0f);
	}
}


