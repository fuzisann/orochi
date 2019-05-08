//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"Objgear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjgear::CObjgear(float x, float y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjgear::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[��������������
	m_ani_max_time = 15;  //�A�j���[�V�����Ԋu��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GEAR, OBJ_GEAR, 1);
}

//�A�N�V����
void CObjgear::Action()
{

	m_ani_time += 1;
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollX(), m_py - 32 + block->GetScrollY());

}
//�h���[
void CObjgear::Draw()
{
	int AniData[5] =
	{
		0,1,2,3,4
	};

	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	// �؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 128;
	src.m_right = 128.0f + AniData[m_ani_frame] * 128;
	src.m_bottom = 128.0f;

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py-32 + block->GetScrollY();
	dst.m_left = 0.0f + m_px + block->GetScrollX();
	dst.m_right = 64.0f + m_px + block->GetScrollX();
	dst.m_bottom = 64.0f + m_py-32 + block->GetScrollY();

	Draw::Draw(10, &src, &dst, c, 0.0f);


	/*for (int i = 0; i < 19; i++)
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
	}*/
}