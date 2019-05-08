#pragma once
//�g�p����w�b�_�[
#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include"GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define ALL_BLOCK_SIZE (32.0f)

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[50][150]);
	~CObjBlock() {};
	void Init();   //�C��V�����C�Y
	void Action();	//�A�N�V����
	void Draw();    //�h���[

	void SetScrollX(float sx) { m_scrollx = sx; }
	void SetScrollY(float sy) { m_scrolly = sy; }
	//float GetScroll() { return m_scroll; }
	float GetScrollX() { return m_scrollx; }
	float GetScrollY() { return m_scrolly; }

	void Setwall(bool type = true);//�B���ʘH�Z�b�g�֐�
	//void Setswitch(bool type = true);

	//�u���b�N�̓����蔻��
	void BlockHit(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//�u���b�N�̓����蔻��(�G)
	void BlockHitEne(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//�u���b�N�̓����蔻��(�{�X1)
	void BlockHitBoss1(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//�u���b�N�̓����蔻��(�{�X2)
	void BlockHitBoss2(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);

	//�u���b�N�̓����蔻��(�{�X2)
	void BlockHitBoss3(
		float*x, float*y, bool scroll_on,
		bool*up, bool*down, bool*left, bool*right,
		float*vx, float*vy, int*bt
	);


private:
	void BlockDraw(float x, float y, RECT_F*dst, float c[]);
	int m_map[50][150]; //�}�b�v���

	float m_scroll;     //���E�X�N���[���p
	float m_scroll_map;
	float x, y;

	float m_scrollx;		//���E�X�N���[���p
	float m_scrolly;

	int m_ani_time;
	int m_ani_frame;
	int m_ani_max_time;
};
