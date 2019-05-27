#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p�l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�|��
class CObjBubble :public CObj
{
	public :
		CObjBubble(float x,float y);
		~CObjBubble() {};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�h���[

		int GetDMG() { return m_damage; }//�U���͂��擾

	private:
		float m_x ;	//�I�u�W�F�N�g�̈ʒuX
		float m_y ;	//�I�u�W�F�N�g�̈ʒuY
		float m_vx;	//�I�u�W�F�N�g�̈ړ��p�x�N�g��X
		float m_vy;	//�I�u�W�F�N�g�̈ړ��p�x�N�g��Y
		float time2;

		//block�Ƃ̏Փˏ�Ԋm�F�p
		bool m_hit_up;
		bool m_hit_down;
		bool m_hit_left;
		bool m_hit_right;
		int  m_block_type;

		int m_py;
		int m_px;

		int m_time; //�U���^�C�~���O�p
		int m_event;
		bool m_c;

		int m_damage;
};