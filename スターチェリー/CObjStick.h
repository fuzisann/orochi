#pragma once
//�g�p����w�b�_�[
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g:�X�e�B�b�N
class CObjStick :public CObj
{
public:
	CObjStick(float x, float y) ;  //�R���X�g���N�^
	~CObjStick() {};
	void Init();
	void Action();
	void Draw();

private:
	bool m_f = true;
	bool m_x;
	bool m_y;
	int m_ani_time;
	int m_ani_frame;

};

