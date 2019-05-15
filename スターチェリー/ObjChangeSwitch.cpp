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

bool m_delete = true;
bool m_change = true;
bool m_start_boss = true;
bool m_m_change = true;


CObjChangeSwitch::CObjChangeSwitch(float x, float y)
{
	m_px = x;		//�ʒu
	m_py = y;
}

//�C�j�V�����C�Y
void CObjChangeSwitch::Init()
{
	m_change = true;	//�摜�؂�ւ�
	m_time = 0;
	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_FIELD, OBJ_CHANGESWITCH, 1);
}

//�A�N�V����
void CObjChangeSwitch::Action()
{
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	//��l���Ɠ������Ă��邩�m�F
	if (hit->CheckObjNameHit(COBJ_HERO) != nullptr)
	{
		//CObjChangeGate1* change = (CObjChangeGate1*)Objs::GetObj(OBJ_CHANGEGATE);
		//m_change = change->GetCHANGE();
		
		m_change = false;
		m_delete = false;
		m_start_boss = false;
		m_m_change = false;
		//hit->SetInvincibility(true);	//���G�I��
		//m_time = 100;
	}


	if (m_delete == false)
	{
		//���g���폜
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		m_delete = true;
	}


	/*if (m_time > 0)
	{
		m_time--;
		if (m_time <= 0)
		{
			m_time = 0;
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}
	}*/
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollX(), m_py + block->GetScrollY());

}

//�h���[
void CObjChangeSwitch::Draw()
{

}


