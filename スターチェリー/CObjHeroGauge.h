#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g
class CObjHeroGauge : public CObj
{
public:
	CObjHeroGauge() {};
	~CObjHeroGauge() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[

	float Gethp() { return gethp; }
private:

	float gethp;//�̗͖߂�l
	int change;
	int ad;//HP���������p
	int ac;//HP���������p
	int ab;
	int HP;
};