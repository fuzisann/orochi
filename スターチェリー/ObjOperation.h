#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�E�X�N���b�N�̃��C���J�ځi���񂢁j
#define MOU_START_HIT_X (319)
#define MOU_START_HIT_V (469)
#define MOU_START_HIT_Y (349)
#define MOU_START_HIT_H (399)

#define GAME_START_POS_X (480)
#define GAME_START_POS_Y (350)

#define GAME_EXIT_POS_X (515)
#define GAME_EXIT_POS_Y (460)

#define GAME_START_FONT_SIZE (60)
#define GAME_RANKING_FONT_SIZE (60)
#define GAME_EXIT_FONT_SIZE (60)

//�`��֌W�̒萔
#define TITLE_POS_X (200)
#define TITLE_POS_Y (250)
#define TITLE_FONT_SIZE (40)

#define CLICK_START_POS_X (230)
#define CLICK_START_POS_Y (400)
#define CLICK_START_FONT_SIZE (30)

#define CLICK_RESET_POS_X (680)
#define CLICK_RESET_POS_Y (380)
#define CLICK_RESET_FONT_SIZE (16)

//�I�u�W�F�N�g:�^�C�g��
class CObjOperation :public CObj
{
public:
	CObjOperation() {};
	~CObjOperation() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:
	bool m_key_flag; //�L�[�t���O
	float m_mou_x;  //�}�E�X�̈ʒuX
	float m_mou_y;  //�}�E�X�̈ʒuY
	bool m_mou_r;   //�}�E�X�̉E�{�^��
	bool m_mou_l;   //�}�E�X�̍��{�^��
	bool  m_f;     //�e�۔��ː���p
	float m_and;		//�����x�����p
	bool m_andf;		//�����x�����p�t���O
	int choose;
	int m_time;
};
