//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjEnemy1.h"

//�g�p����l�[���X�y�[�X���wwww
using namespace GameL;

CObjEnemy1::CObjEnemy1(int map[19][100])
{
	//�}�b�v�f�[�^�R�s�[
	memcpy(m_map, map, sizeof(int)*(19 * 100));
}

//�C�j�V�����C�Y
void CObjEnemy1::Init()
{
	m_px = 1050.0f;	//�ʒu
	m_py = 400.0f;
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f; //�E����0.0f,������1,0f

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[��������������

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	m_damage = 1;

	m_move = false;		//true=�E false=��

	//block�Ƃ̒Ǔˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 50, 50, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//�A�N�V����
void CObjEnemy1::Action()
{
	//���C
	m_vx += -(m_vx * 0.098);
	//m_vy += -(m_vy * 0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);
	
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

	//����
	if (m_py > 1000.0f)
	{
		;
	}

	//�ʏ푬�x
	m_speed_power = 0.5f;
	m_ani_max_time = 4;

	//�u���b�N�Փ˂Ō����ύX
	if (m_hit_left == true)
	{
		m_move = true;
	}
	if (m_hit_right == true)
	{
		m_move = false;
	}

	//����
	if (m_move == false)
	{
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	else if (m_move == true)
	{
		m_vx -= m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;
	}
	/*else
	{
		m_ani_frame = 1;  //�Î~�t���[��
		m_ani_time = 0;
	}*/

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}

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
				CObjEnemy1* ene1 = new CObjEnemy1(j*50, i*50);
				Objs::InsertObj(ene1, OBJ_ENEMY, 10);
				m_map[i][j] = 0;
			}
		}
	}
}
//�h���[
void CObjEnemy1::Draw()
{
	int AniData[4] =
	{
		0,1,2,3,
	};

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
			src.m_left = 0.0f + AniData[m_ani_frame] * 50;
			src.m_right = 50.0f + AniData[m_ani_frame] * 50;
			src.m_bottom = 50.0f;

			//�u���b�N���������Ă���
			CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

			if (m_map[i][j] == 6)
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