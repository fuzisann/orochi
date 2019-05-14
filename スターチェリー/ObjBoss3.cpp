//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"ObjBoss3.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

extern bool m_start_boss;

CObjBoss3::CObjBoss3(float x, float y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjBoss3::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f; //�E����0.0f,������1,0f

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[��������������

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	m_boss_hp = 10;     //�G�̃q�b�g�|�C���g(�ő�10)
	m_damage = 3;

	m_time_die = 0;

	m_move = false;		//true=�E false=��

	m_do_f = false;//�ːi�t���O

	//block�Ƃ̒Ǔˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_del = false;

	m_inputf = true;	// true = ���͉�	false = ���͕s��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 200, 100, ELEMENT_ENEMY, OBJ_BOSS_THIRD, 1);
}

//�A�N�V����
void CObjBoss3::Action()
{
	//���C
	m_vx += -(m_vx * 0.098);
	//m_vy += -(m_vy * 0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//�_�~�[
	int d;
	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHitBoss3(&m_px, &m_py, false,
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

	//input�t���O���I���̎��Ɉړ����\�ɂ���
	if (m_inputf == true)
	{
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

	//�ːi�s��
	if (m_do_f == true)
	{
		m_dotime++;
		if (m_dotime > 40)
		{
			m_vx *= 5;
			m_vy *= 5;
			if (m_dotime == 100)
			{
				m_do_f = false;
				m_dotime = 0;
			}
		}
		else
		{
			m_vx = 0;
			m_vy = 0;
		}
	}



	//�U�����󂯂���̗͂����炷
	//��l����ATTACK�n���Ƃ̓����蔻��
	if (hit->CheckElementHit(ELEMENT_ATTACK) == true)
	{
		//�m�b�N�o�b�N����
		if (m_posture == 0.0f)
		{
			m_vy = -10;
			m_vx += 15;
		}
		if (m_posture == 1.0f)
		{
			m_vy = -10;
			m_vx -= 15;
		}
		m_time_d = 30;	//�G�̖��G���Ԃ��Z�b�g
		m_boss_hp -= 1;	//�G�̗̑͂����炷
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}

	if (m_del == false && m_boss_hp <= 0)
	{
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		block->Setwall(true);
		m_time_die = 30;
		m_inputf = false;	//�����𐧌�
		m_del = true;
		m_time_dead = 80;	//���S���Ԃ��Z�b�g
	}

	/*if (m_time_die > 0)
	{
		m_time_die--;
		if (m_time_die <= 0)
		{
			Scene::SetScene(new CSceneClear());
			m_time_die = 0;
		}
	}*/

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollX(), m_py - 50 + block->GetScrollY());

	if (m_del == true)
	{
		hit->SetInvincibility(true);	//���G�ɂ���
		m_eff_flag = true;			//�摜�؂�ւ��p�t���O
		m_speed_power = 0.0f;			//�������~�߂�

	}

	if (m_time_dead > 0)
	{
		m_time_dead--;
		if (m_time_dead <= 0)
		{
			this->SetStatus(false);		//�摜�̍폜
			Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X�̍폜
			m_time_dead = 0;
			m_start_boss = true;
			Scene::SetScene(new CSceneClear());
		}
	}
}
//�h���[
void CObjBoss3::Draw()
{
	int AniData[4] =
	{
		0,1,2,3,
	};

	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�u���b�N���������Ă���
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py - 50 + pb->GetScrollY();
	dst.m_left = (200.0f * m_posture) + m_px + pb->GetScrollX();
	dst.m_right = (200 - 200.0f *m_posture) + m_px + pb->GetScrollX();
	dst.m_bottom = 100.0f + m_py - 50 + pb->GetScrollY();

	//�G�̏�Ԃŕ`���ύX
	if (m_del == true)
	{

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 200.0f;
		src.m_bottom = 100.0f;

		if (m_eff_flag == true)
			Draw::Draw(12, &src, &dst, c, 0.0f);
	}
	else
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 200;
		src.m_right = 200.0f + AniData[m_ani_frame] * 200;
		src.m_bottom = 100.0f;

		//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
		if (m_time_d > 0) {
			Draw::Draw(12, &src, &dst, a, 0.0f);
		}
		else {
			Draw::Draw(12, &src, &dst, c, 0.0f);
		}
	}
}