//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"


#include"GameHead.h"
#include"CObjHero.h"
#include"GameL\Audio.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

float g_px;//= 64.0f;
float g_py;//= 450.0f;
extern bool Hit_wall;
extern bool Hit_wall_r;
extern bool m_up;
extern bool m_start_boss;

//�C�j�V�����C�Y
void CObjHero::Init()
{

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f; //�E����0.0f,������1,0f

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[��������������

	m_ani_time_r = 0;
	m_ani_frame_r = 0;  //�Î~�t���[��������������
	m_ani_max_time_r = 4;  //�A�j���[�V�����Ԋu��

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;	//����ł���u���b�N�̎��

	m_hero_hp = 30;     //��l���̍ő�HP(�ő�30)

	m_speed_power = 0.5f;//�ʏ푬�x
	m_ani_max_time = 4;  //�A�j���[�V�����Ԋu��

	m_time = 31;

	m_del = false;

	m_sword_delay = 0;
	m_swordwidth = 0.0f; //�\�[�h��

	m_inputf = true;	// true = ���͉�	false = ���͕s��

	m_inputw = false;	// false = ���͉�	true = ���͕s��

	m_up = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, g_px, g_py,64,64, ELEMENT_PLAYER, COBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	//HP��0�ȉ��̎��ɃQ�[���I�[�o�[�Ɉڍs����
	if (m_del == false && m_hero_hp <= 0)
	{
		m_del = true;
		m_inputf = false;	//�L�[���͂𐧌�
		m_time_dead = 80;	//���S���Ԃ��Z�b�g
	}

	m_speed_power = 0.5f;

	//input�t���O���I���̏ꍇ���͂��\�ɂ���
	if (m_inputf == true)
	{
		if(m_inputw == false)
		{

		//Z�L�[�ŋߐ�(��)�U��
			if (Input::GetVKey('Z') == true)
			{
				if (m_sword_delay == 0)
				{
					//��l���̌����ɂ���čU�����������ݒ�
					if (m_posture == 0.0f) {
						m_swordwidth = 70.0f;
					}
					else if (m_posture == 1.0f) {
						m_swordwidth = -30.0f;
					}

					//���ōU��
					CObjHeroSword* objsb = new CObjHeroSword(m_px + m_swordwidth, m_py + 32.0f);//���I�u�W�F�N�g(�퓬)�쐬
					Objs::InsertObj(objsb, OBJ_SWORD, 100);		//��������I�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

					//�a����
					Audio::Start(1);

					m_sword_delay = 20;
				}
			}
		}
		if (m_sword_delay > 0)
		{
			m_sword_delay--;
			if (m_sword_delay <= 0)
				m_sword_delay = 0;
		}

		//�W�����v
		if (m_up == false)
		{
			if (Input::GetVKey(VK_UP) == true)
			{
				if (m_hit_down == true && m_time == 0)
				{
					m_vy = -17;	//�����l�F-13
					//g_py += m_vy;

					Audio::Start(2);

				}
			}
		}
		
		if (m_time > 0) {
			m_time--;
			if (m_time <= 0) {
				m_time = 0;
			}
		}

		else if (m_ani_frame >= 4)
		{
			m_ani_frame = 0;
			m_ani_time = 0;
		}
		else if (m_ani_frame_r >= 8)
		{
			m_ani_frame_r = 0;
			m_ani_time_r = 0;
		}

		if (Input::GetVKey(VK_RIGHT) == true)
		{
			m_vx += m_speed_power;
			m_posture = 0.0f;
			m_ani_time += 1;
		}
		else if (Input::GetVKey(VK_LEFT) == true)
		{
			m_vx -= m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else
		{
			m_ani_frame = 0;   //�L�[���͂������ꍇ�Î~�t���[���ɂ���
			m_ani_time = 0;
		}

		if (Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_RIGHT) == true)
		{
			m_ani_time_r += 1;
		}
		else if (Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_LEFT) == true)
		{
			m_ani_time_r += 1;
		}
		else
		{
			m_ani_frame_r = 0;   //�L�[���͂������ꍇ�Î~�t���[���ɂ���
			m_ani_time_r = 0;
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

		if (m_ani_time_r > m_ani_max_time_r)
		{
			m_ani_frame_r += 1;
			m_ani_time_r = 0;
		}
		if (m_ani_frame_r == 8)
		{
			m_ani_frame_r = 0;
		}

		//�ړ��x�N�g���̐��K��
		//UnitVec(&m_vx, &m_vy);

	//���C
	m_vx += -(m_vx * 0.098);
	m_vy += -(m_vy * 0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);

	//�ʒu�̍X�V
	g_px += m_vx;
	g_py += m_vy;

	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&g_px, &g_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//HitBox�̈ʒu��ύX	
	hit->SetPos(g_px, g_py);

	//�����蔻����s���I�u�W�F�N�g���Q
	int data_base[3] =
	{
		ELEMENT_ENEMY,
	};
	//�I�u�W�F�N�g���Q�Ɠ����蔻��s���B�������Ă���΃m�b�N�o�b�N
	for (int i = 0; i < 6; i++)
	{
		if (hit->CheckElementHit(data_base[i]) == true)
		{
			HIT_DATA** hit_date;							//�����������ׂ̍��ȏ������邽�߂̍\����
			hit_date = hit->SearchElementHit(data_base[i]);	//hit_date�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

			float r = 0;
			for (int i = 0; i < 10; i++) {
				if (hit_date[i] != nullptr) {
					r = hit_date[i]->r;
				}
			}
			//�p�x�ŏ㉺���E�𔻒�
			//if ((r < 45 && r >= 0) || r > 315)
			if (r > 90 && r < 270)
			{
				m_vy =  -5;		//�E
				m_vx += 6;
			}
			else
			{
				m_vy =   -5;		//��
				m_vx -=  6;
			}

			Audio::Start(3);	//�_���[�W��
			m_time_d = 80;		//���G���Ԃ��Z�b�g
			hit->SetInvincibility(true);	//���G�I��

			//�G�ɓ������HP�����炷
			if (hit->CheckObjNameHit(OBJ_ENEMY_FIRST) != nullptr)
			{
				CObjEnemy1* ene1 = (CObjEnemy1*)Objs::GetObj(OBJ_ENEMY_FIRST);
				m_damage = ene1->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_ENEMY_SECOND) != nullptr)
			{
				CObjEnemy2* ene2 = (CObjEnemy2*)Objs::GetObj(OBJ_ENEMY_SECOND);
				m_damage = ene2->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_ENEMY_THIRD) != nullptr)
			{
				CObjEnemy3* ene3 = (CObjEnemy3*)Objs::GetObj(OBJ_ENEMY_THIRD);
				m_damage = ene3->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_BOSS_FIRST) != nullptr)
			{
				CObjBoss1* boss1 = (CObjBoss1*)Objs::GetObj(OBJ_BOSS_FIRST);
				m_damage = boss1->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_BOSS_SECOND) != nullptr)
			{
				CObjBoss2* boss2 = (CObjBoss2*)Objs::GetObj(OBJ_BOSS_SECOND);
				m_damage = boss2->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_BOSS_THIRD) != nullptr)
			{
				CObjBoss3* boss3 = (CObjBoss3*)Objs::GetObj(OBJ_BOSS_THIRD);
				m_damage = boss3->GetDMG();
				m_hero_hp -= m_damage;
			}
			if (hit->CheckObjNameHit(OBJ_BUBBLE) != nullptr)
			{
				CObjBubble* bubble = (CObjBubble*)Objs::GetObj(OBJ_BUBBLE);
				m_damage = bubble->GetDMG();
				m_hero_hp -= m_damage;
			}

			//�G�̍U���ɂ����HP��0�ȉ��ɂȂ����ꍇ
			if (m_hero_hp <= 0)
				m_hero_hp = 0;	//HP��0�ɂ���

		}

	}

	if (hit->CheckElementHit(ELEMENT_MYSTERY) == true)
	{
		//��l�����u���b�N�Ƃǂ̊p�x�œ������Ă���̂����m�F
		HIT_DATA** hit_date;							//�����������ׂ̍��ȏ������邽�߂̍\����
		hit_date = hit->SearchElementHit(ELEMENT_MYSTERY);	//hit_date�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������
		for (int i = 0; i < hit->GetCount(); i++)
		{
			float r = hit_date[i]->r;
			if ((r < 45 && r >= 0) || r > 315)
			{
				m_vx = -0.15f; //�E
			}
			if (r > 45 && r < 135)
			{
				m_vy = 0.15f;//��
			}
			if (r > 135 && r < 225)
			{
				m_vx = 0.15f;//��
			}
			if (r > 225 && r < 315)
			{
				m_vy = -0.15f; //��
			}
		}
	}



	if (m_del == true)
	{
		hit->SetInvincibility(true);	//���G�ɂ���
		m_eff_flag = true;			//�摜�؂�ւ��p�t���O
		m_speed_power = 0.0f;			//�������~�߂�

	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
			hit->SetInvincibility(false);	//���G�I�t
		}
	}

	if (m_time_dead > 0)
	{
		m_time_dead--;
		if (m_time_dead <= 0)
		{
			Scene::SetScene(new CSceneOver());
			m_time_dead = 0;
			m_start_boss = true;
		}
	}
}

//�h���[
void CObjHero::Draw()
{

	int AniData[5] =
	{
		0,1,2,3,0,
	};

	int AniData_r[9] =
	{
		0,1,2,3,4,5,6,7,0,
	};

	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };
	

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + g_py;
	dst.m_left = (64.0f*m_posture) + g_px;
	dst.m_right = (64 - 64.0f*m_posture) + g_px;
	dst.m_bottom = 64.0f + g_py;

	//�؂���ʒu�̐ݒ�
	//��l���̏�Ԃŕ`���ύX
	if (m_del == true)
	{
		src.m_top = 64.0f;
		src.m_left = 128.0f;
		src.m_right = 192.0f;
		src.m_bottom = 128.0f;
		if (m_eff_flag == true)
			Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	else
	{
		if (Hit_wall == true) //���ǂɎ�l��������������
		{
			//���������Ă��Ȃ����̎�l�����`����Ă��鏊��؂���
			src.m_top = 64.0f;
			src.m_left = 64.0f;
			src.m_right = 128.0f;
			src.m_bottom = 128.0f;

			m_inputw = true;

		}
		else if (Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_LEFT) == true
			 || Input::GetVKey(VK_UP) == true && Input::GetVKey(VK_RIGHT) == true)
		{
			//��]���Ă��鎞�̎�l�����`����Ă��鏊��؂���
			src.m_top = 128.0f;
			src.m_left = 0.0f + AniData_r[m_ani_frame_r] * 64;
			src.m_right = 64.0f + AniData_r[m_ani_frame_r] * 64;
			src.m_bottom = 192.0f;
			m_inputw = true;
		}
		else //����ȊO�̎�
		{
			//���������Ă��鎞�̎�l�����`����Ă��鏊��؂���
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData[m_ani_frame] * 64;
			src.m_right = 64.0f + AniData[m_ani_frame] * 64;
			src.m_bottom = 64.0f;
			m_inputw = false;

		}

		//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��

		if (m_time_d > 0) {
			Draw::Draw(0, &src, &dst, a, 0.0f);
		}
		else {
			Draw::Draw(0, &src, &dst, c, 0.0f);
		}
	}
}