#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;


extern float g_px;
extern float g_py;

//�I�u�W�F�N�g : ��l��
class CObjHero : public CObj
{
public:
	CObjHero(int map[19][100]) {};
	~CObjHero() {};
	void Init();   //�C��V�����C�Y
	void Action();	//�A�N�V����
	void Draw();    //�h���[

#define HEROX (64)
#define HEROY (64)

	float GetX() { return g_px; }
	float GetY() { return g_py; }
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }
	int GetBT() { return m_block_type; }
	int GetHP() { return m_hero_hp; }	//��l����HP���擾

	void SetX(float x) { g_px = x; }
	void SetY(float y) { g_py = y; }
	void SetVY(float vy) { m_vy = vy; }
	void SetVX(float vx) { m_vx = vx; }
	void SetBT(int t) { m_block_type = t; }

	void SetUp(bool b) { m_hit_up = b; }
	void SetDown(bool b) { m_hit_down = b; }
	void SetLeft(bool b) { m_hit_left = b; }
	void SetRight(bool b) { m_hit_right = b; }

private:
	int m_map[19][100]; //�}�b�v���
	float m_vx;      //�ړ��x�N�g��
	float m_vy;
	float m_posture; //�p��

	int m_ani_time; //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame;  //�`��t���[��

	int m_hero_hp;	//�̗�(�퓬)
	int m_max_hp;	//HP�̍ő�l

	int m_damage;	//��l�����󂯂�_���[�W�p

	float m_speed_power; //�X�s�[�h�p���[
	float m_speed_pow;   //���Ⴊ�ޑ��x
	float m_ani_max_time;//�A�j���[�V��������Ԋu�ő�l

	int m_time_d;	//�_���[�W���G���ԗp

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//����ł���block�̎�ނ��m�F�p
	int m_block_type;
	int s;
	int m_time;
	int m_x;
	int m_y;
	bool m_key_flag; //�L�[�t���O

};