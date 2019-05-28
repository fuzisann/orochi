//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include"GameHead.h"
#include"ObjBoss2.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

extern bool m_start_boss;

CObjBoss2::CObjBoss2(float x, float y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjBoss2::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f; //�E����0.0f,������1,0f

	m_time = 0;

	m_time_ud = 0;

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[��������������

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	m_boss_hp = 5;     //�G�̃q�b�g�|�C���g(�ő�5)
	m_damage = 2;

	m_time_die = 0;

	m_move = false;		//true=�E false=��

	m_del = false;

	//block�Ƃ̒Ǔˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_inputf = true;	// true = ���͉�	false = ���͕s��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 150, 75, ELEMENT_ENEMY, OBJ_BOSS_SECOND, 1);
}

//�A�N�V����
void CObjBoss2::Action()
{
	//���C
	m_vx += -(m_vx * 0.098);
	m_vy += -(m_vy * 0.098);

	//���R�����^��
	//m_vy += 9.8 / (16.0f);

	//���g��HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//�_�~�[
	int d;
	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHitBoss2(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	m_speed_power = 0.0f;		//�X�s�[�h���O�ɂ���

	if (m_start_boss == false)
	{
		//�ʏ푬�x
		m_speed_power = 0.5f;
		m_ani_max_time = 4;

		m_time++;

		if (m_time > 80)
		{
			m_time = 0;
			//�I�u�W�F�N�g�쐬
			CObjBubble* objbu = new CObjBubble(m_px, m_py);
			Objs::InsertObj(objbu, OBJ_BUBBLE, 100);
		}
	}

	//�u���b�N�Փ˂Ō����ύX
	/*if (m_hit_left == true)
	{
		m_move = true;
	}
	if (m_hit_right == true)
	{
		m_move = false;
	}*/

	if (m_hit_down == true)
	{
		m_move = true;
	}
	if (m_hit_up == true)
	{
		m_move = false;
	}

	//input�t���O���I���̎��Ɉړ����\�ɂ���
	if (m_inputf == true)
	{
		//����
		if (m_move == false)
		{
			m_vy += m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (m_move == true)
		{
			m_vy -= m_speed_power;
			m_posture = 0.0f;
			m_ani_time += 1;
		}
	}

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
			//m_vx += 15;
		}
		if (m_posture == 1.0f)
		{
			//m_vy = -10;
			//m_vx -= 15;
		}
		Audio::Start(4);	//�_���[�W��
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

	//HP��0�ȉ��̎��ɏ��ŏ����Ɉڍs����
	if (m_del == false && m_boss_hp <= 0)
	{
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		block->Setwall(true);
		m_time_die = 30;
		m_inputf = false;	//�����𐧌�
		m_del = true;
		m_time_dead = 80;	//���S���Ԃ��Z�b�g
		m_vy += 9.8 / (16.0f);	//���R�����^��
	}

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	hit->SetPos(m_px + block->GetScrollX(), m_py -32 + block->GetScrollY());

	if (m_del == true)
	{
		hit->SetInvincibility(true);	//���G�ɂ���
		m_eff_flag = true;			//�摜�؂�ւ��p�t���O
		m_speed_power = 0.0f;			//�������~�߂�
		m_start_boss = true;
	}

	if (m_time_dead > 0)
	{
		m_time_dead--;
		if (m_time_dead <= 0)
		{
			this->SetStatus(false);		//�摜�̍폜
			Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X�̍폜
			m_time_dead = 0;
			Scene::SetScene(new CSceneStageClear());
		}
	}

}
//�h���[
void CObjBoss2::Draw()
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
	dst.m_top = 0.0f + m_py - 32 + pb->GetScrollY();
	dst.m_left = (150.0f * m_posture) + m_px + pb->GetScrollX();
	dst.m_right = (150 - 150.0f *m_posture) + m_px + pb->GetScrollX();
	dst.m_bottom = 100.0f + m_py - 32 + pb->GetScrollY();

	//�G�̏�Ԃŕ`���ύX
	if (m_del == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 20.0f;
		src.m_left = 820.0f;
		src.m_right = 1020.0f;
		src.m_bottom = 110.0f;

		if (m_eff_flag == true)
			Draw::Draw(15, &src, &dst, c, 0.0f);
	}
	else
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 150;
		src.m_right = 150.0f + AniData[m_ani_frame] * 150;
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