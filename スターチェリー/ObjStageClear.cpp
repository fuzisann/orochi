//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include"GameL\UserData.h"
#include"SceneMain.h"

#include "GameHead.h"
#include "ObjStageClear.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjStageClear::Init()
{
	choose = 0;
}

//�A�N�V����
void CObjStageClear::Action()
{
	Save::Seve();//UserData�̏��t�H���_�uUserData�v���쐬����;

	if (Input::GetVKey(VK_UP) == true)
	{
		choose = 0;
	}
	if (Input::GetVKey(VK_DOWN) == true)
	{
		choose = 1;
	}

	if (choose == 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{

			if (m_key_flag == true)
			{
				g_px = 64.0f;
				g_py = 500.0f;

				g_map_chenge += 1;
				Scene::SetScene(new CSceneMain());
				m_key_flag = false;
			}
		}
		else
		{
			m_key_flag = true;
		}
	}
	if (choose == 1)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			Scene::SetScene(new CSceneTitle());
			g_map_chenge = 0;//�}�b�v�ύX
			m_key_flag = false;
		}
	}
}
//�h���[
void CObjStageClear::Draw()

{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//��
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 909.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1600.0f;
	dst.m_bottom = 920.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(4, &src, &dst, c, 0.0f);

	float p[4] = { 1,1,1,1 };

	//Font::StrDraw(L"�X�e�[�W�N���A", GAME_CLEAR_X, GAME_CLEAR_Y, GAME_CLEAR_FONT_SIZE, p);

	if (choose == 0)
		Font::StrDraw(L"�����̃X�e�[�W", NEXT_STAGE_YES_X -40, NEXT_STAGE_YES_Y, NEXT_STAGE_YES_FONT_SIZE, p);
	else
		Font::StrDraw(L"���̃X�e�[�W", NEXT_STAGE_YES_X, NEXT_STAGE_YES_Y, NEXT_STAGE_YES_FONT_SIZE, p);
	if (choose == 1)
		Font::StrDraw(L"���^�C�g����", NEXT_STAGE_NO_X - 40, NEXT_STAGE_NO_Y, NEXT_STAGE_NO_FONT_SIZE, p);
	else
		Font::StrDraw(L"�^�C�g����", NEXT_STAGE_NO_X, NEXT_STAGE_NO_Y, NEXT_STAGE_NO_FONT_SIZE, p);
}