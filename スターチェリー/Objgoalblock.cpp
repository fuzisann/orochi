//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\HitBoxManager.h"

#include"GameHead.h"
#include"Objgoalblock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjgoalblock::CObjgoalblock(float x, float y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjgoalblock::Init()
{
	/*m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[��������������
	m_ani_max_time =15;  //�A�j���[�V�����Ԋu��*/

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 77, 85, ELEMENT_FIELD, OBJ_GOAL_BLOCK, 1);

}

//�A�N�V����
void CObjgoalblock::Action()
{
	/*m_ani_time += 1;
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}*/

	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//��l���Ɠ������Ă��邩�m�F
	if (hit->CheckElementHit(ELEMENT_PLAYER) == true)
	{
		Scene::SetScene(new CSceneStageClear());
	}

	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBox�̈ʒu��ύX	
	hit->SetPos(m_px + 165 +block->GetScrollX(),m_py + 269 + block->GetScrollY());
}
//�h���[
void CObjgoalblock::Draw()
{
	int AniData[5] =
	{
		0,1,2,3,4
	};

	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 32.0f;
	src.m_left = 10.0f;
	src.m_right = 393.0f;
	src.m_bottom = 370.0f;
	
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�\���ʒu�̐ݒ�
	dst.m_top  = 32.0f  + m_py + block->GetScrollY();
	dst.m_left = 10.0f  + m_px + block->GetScrollX();
	dst.m_right = 393.0f  + m_px + block->GetScrollX();
	dst.m_bottom = 370.0f + m_py - 12  + block->GetScrollY();

	Draw::Draw(5, &src, &dst, c, 0.0f);

}