//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"Objgear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjgear::Init()
{
	m_px = 1050.0f;	//�ʒu
	m_py = 400.0f;
	m_vy = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[��������������


	m_damage = 1;

	m_move = false;		//true=�E false=��

	//block�Ƃ̒Ǔˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_GEAR, 1);
}

//�A�N�V����
void CObjgear::Action()
{

	//�_�~�[
	int d;
	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHitEne(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{

			if (m_map[i][j] == 6)
			{
				/*CObjEnemy1* ene1 = new CObjEnemy1(j*50, i*50);
				Objs::InsertObj(ene1, OBJ_ENEMY, 10);
				m_map[i][j] = 0;*/
			}
		}
	}
}
//�h���[
void CObjgear::Draw()
{

	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
		{

			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//�u���b�N���������Ă���
			CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			if (m_map[i][j] == 4)
			{

				//�\���ʒu�̐ݒ�
				dst.m_top = 0.0f + m_py;
				dst.m_left = (50.0f * m_posture) + m_px + pb->GetScroll();
				dst.m_right = (50 - 50.0f*m_posture) + m_px + pb->GetScroll();
				dst.m_bottom = 50.0f + m_py;

				//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
				Draw::Draw(8, &src, &dst, c, 0.0f);
			}
		}
	}
}