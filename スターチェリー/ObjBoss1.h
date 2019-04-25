#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g : �{�X
class CObjBoss1 : public CObj
{
	public:
		CObjBoss1(float x, float y);
		~CObjBoss1() {};
		void Init();   //�C��V�����C�Y
		void Action();	//�A�N�V����
		void Draw();    //�h���[

		float GetVX() { return m_vx; }
		int GetDMG() { return m_damage; }//�U���͂��擾

	private:
		int m_map[19][100]; //�}�b�v���
		float m_px;      //�ʒu
		float m_py;
		float m_vx;      //�ړ��x�N�g��
		float m_vy;
		float m_posture; //�p��

		int m_ani_time; //�A�j���[�V�����t���[������Ԋu
		int m_ani_frame;  //�`��t���[��
		int m_dotime;

		int m_enemy_hp;		//�G�̗̑�
		int m_damage;

		int m_time_d;	//�_���[�W���̃J���[�ύX�p�^�C��

		float m_speed_power; //�X�s�[�h�p���[
		float m_ani_max_time;//�A�j���[�V��������Ԋu�ő�l

		//block�Ƃ̏Փˏ�Ԋm�F�p
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;

		//�ړ��̌�������p
		bool m_move;

		//����ł���block�̎�ނ��m�F�p
		//int m_block_type;
		int s;
		int m_time;
		int m_x;
		int m_y;
		bool m_do_f;//�ːi�t���O

		bool m_change;	//�X�C�b�`�̃I���I�t
};

