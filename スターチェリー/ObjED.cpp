//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "SceneMain.h"

#include "GameHead.h"
#include "ObjED.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjED::Init()
{
	m_y = 0.0;
	m_key_flag = true;
}

//�A�N�V����
void CObjED::Action()
{


}
//�h���[
void CObjED::Draw()
{
	//�`�ʃJ���[���
	float bl[4] = { 0.7f,0.7f,0.7f,1.0f };

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
	Draw::Draw(3, &src, &dst, bl, 0.0f);

	float p[4] = { 1,1,1,1 };

	if (Input::GetVKey(VK_RETURN) == true)
	{
		m_y -= 3.0f;
	}
	else
	{
		m_y -= 0.6f;
	}
	Font::StrDraw(L"�������̋������z�������T����|������l���́A", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 400, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"�T���̌��̒��ɉ��P�l�炵���e�����鎖��m��A", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 450, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"�T���̌��̒����牳�P�l����������o���܂����B", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 500, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"��l���͈��S�ȏꏊ�܂ŉ��P�l���^�сA", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 600, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"���{��̊O�Ɏ�l���͏������Ăтɍs���܂����B", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 650, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"���̌㉳�P�l�́A���{��̊F�ɏ������܂����B", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 700, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"�\��Ă����T�����|�ꂽ���ƂŁA", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 800, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"���{��ő����Ă��������������X�ƈӎ������߂��܂����B", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 850, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"��l���͂��̎��ȗ��A���P�l���������p�Y�Ƃ��āA", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 950, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"���{��ɖ����m��n��悤�ɂȂ�A", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1000, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"���P�l�ꑮ�̕t���l�Ƃ��ė��{��ŕ�炷�悤�ɂȂ�܂����B", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1050, GAME_CLEAR_FONT_SIZE, p);
	
	Font::StrDraw(L"�d�m�c", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1200, GAME_CLEAR_FONT_SIZE, p);
	Font::StrDraw(L"��Enter�L�[�Ń^�C�g���ց�", GAME_CLEAR_X, GAME_CLEAR_Y + m_y + 1300, GAME_CLEAR_FONT_SIZE, p);

	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}