//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjEnemy1.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjEnemy1::CObjEnemy1(float x, float y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjEnemy1::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f; //�E����0.0f,������1,0f

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[��������������

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	m_enemy_hp = 3;     //�G�̃q�b�g�|�C���g(�ő�3)(��)
	m_damage = 1;

	m_move = false;		//true=�E false=��

	//block�Ƃ̒Ǔˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 50, 50, ELEMENT_ENEMY, OBJ_ENEMY_FIRST, 1);
}

//�A�N�V����
void CObjEnemy1::Action()
{
	//���C
	m_vx += -(m_vx * 0.098);
	//m_vy += -(m_vy * 0.098);

	
	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

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

	//�U�����󂯂���̗͂����炷
	//��l����ATTACK�n���Ƃ̓����蔻��
	if (hit->CheckElementHit(ELEMENT_ATTACK) == true)
	{
		//�m�b�N�o�b�N����
		if (m_posture == 0.0f)
		{
			//m_vy = -10;
			m_vx += 15;
		}
		if (m_posture == 1.0f)
		{
			//m_vy = -10;
			m_vx -= 15;
		}
		m_time_d = 30;	//�G�̖��G���Ԃ��Z�b�g
		m_enemy_hp -= 1;	//�G�̗̑͂����炷
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}

	if (m_enemy_hp <= 0)
	{
		this->SetStatus(false);		//�摜�̍폜
		Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X�̍폜
	}

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScroll(), m_py);

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

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 50;
	src.m_right = 50.0f + AniData[m_ani_frame] * 50;
	src.m_bottom = 50.0f;
	
	//�u���b�N���������Ă���
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (50.0f * m_posture) + m_px + pb->GetScroll();
	dst.m_right = (50 - 50.0f *m_posture) + m_px + pb->GetScroll();
	dst.m_bottom = 50.0f + m_py;
		
	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(8, &src, &dst, c, 0.0f);

}