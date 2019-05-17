//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include"GameL\DrawTexture.h"
#include"GameL\SceneObjManager.h"
#include"GameL\DrawTexture.h"
#include"GameL\DrawFont.h"
#include"GameL\UserData.h"
#include"GameL\DrawFont.h"
#include"GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

extern bool m_m_change;

//�g�p�w�b�_�[
#include"SceneMain.h"
#include"GameHead.h"
#include"ObjArrow.h"


//�R���X�g���N�^
CSceneMain::CSceneMain()
{
	//ooo//
}

//�e�X�g���N�^
CSceneMain::~CSceneMain()
{

}


//���������\�b�h
void CSceneMain::InitScene()
{
	//Font�쐬
	Font::SetStrTex(L"0123456789���b");

	//�O���f�[�^�̓ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p; //�X�e�[�W���|�C���^�[
	int size;              //�X�e�[�W���̑傫��

	if (g_map_chenge == 0)
	{
		p = Save::ExternalDataOpen(L"stage1 (����).csv", &size);//�O���f�[�^�ǂݍ���
	}
	else if (g_map_chenge == 1)
	{
		p = Save::ExternalDataOpen(L"�V�X�e�[�W2.csv", &size);//�O���f�[�^�ǂݍ���
	}
	else if (g_map_chenge == 2)
	{
		p = Save::ExternalDataOpen(L"�V�X�e�[�W3.csv", &size);//�O���f�[�^�ǂݍ���
	}
	/*else if (g_map_chenge == 3)
	{
		p = Save::ExternalDataOpen(L"map9-6.csv", &size);//�O���f�[�^�ǂݍ���
	}
	else if (g_map_chenge == 4)
	{
		p = Save::ExternalDataOpen(L"map10-4.csv", &size);//�O���f�[�^�ǂݍ���
	}*/

	int map[50][150];
	int count = 1;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			if(w>=10)
				count += 3;
			else
				count += 2;
		}
	}

	//Font�쐬
	Font::SetStrTex(L"0123456789���b");
	
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^�i576x384�s�N�Z���j
	Draw::LoadImage(L"��l��3.png", 0, TEX_SIZE_512);

	if (g_map_chenge == 0)
	{
		//�w�i�摜�ǂݍ���
		Draw::LoadImage(L"�P�X�e�[�W�w�i.png", 3, TEX_SIZE_1024);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�X�e�[�W1�u���b�N.png", 2, TEX_SIZE_512);

		//�G�摜�ǂݍ���
		Draw::LoadImage(L"����������.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V������.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"���񂱂�.png", 10, TEX_SIZE_512);//�e�X�g�p
		Draw::LoadImage(L"�J��.png", 12, TEX_SIZE_512);
		Draw::LoadImage(L"�A�W(���S�p).png", 13, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V(���S�p).png", 14, TEX_SIZE_512);
		Draw::LoadImage(L"�J��(���S�p).png", 15, TEX_SIZE_512);

		//�̗͂̓ǂݍ���
		Draw::LoadImage(L"�̗̓Q�[�W�t��.png", 17, TEX_SIZE_512);

		//���摜�ǂݍ���
		Draw::LoadImageW(L"��.png", 16, TEX_SIZE_512);
	}
	else if (g_map_chenge == 1)
	{
		//�w�i�摜�ǂݍ���
		Draw::LoadImage(L"�Q�X�e�[�W�w�i.png", 3, TEX_SIZE_1024);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�X�e�[�W2�u���b�N.png", 2, TEX_SIZE_512);
		//�G�摜�ǂݍ���
		Draw::LoadImage(L"����������.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V������.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"���񂱂�����.png", 10, TEX_SIZE_512);
		Draw::LoadImage(L"�����E�O�E�m�c�J�C�@������.png", 12, TEX_SIZE_512);
		Draw::LoadImage(L"�A�W(���S�p).png", 13, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V(���S�p).png", 14, TEX_SIZE_512);
		Draw::LoadImage(L"�����E�O�E�m�c�J�C(���S�p).png", 15, TEX_SIZE_512);
		//Draw::LoadImage(L"���񂱂�(���S�p).png", 16, TEX_SIZE_512);

		//���摜�ǂݍ���
		Draw::LoadImageW(L"��.png", 16, TEX_SIZE_512);
	}
	else if (g_map_chenge == 2)
	{
		//�w�i�摜�ǂݍ���
		Draw::LoadImage(L"�R�X�e�[�W�w�i.png", 3, TEX_SIZE_1024);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�X�e�[�W3�u���b�N.png", 2, TEX_SIZE_512);
		//�G�摜�ǂݍ���
		Draw::LoadImage(L"����������.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V������.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"���񂱂�����.png", 10, TEX_SIZE_512);
		Draw::LoadImage(L"���P�T��.png", 12, TEX_SIZE_512);
		Draw::LoadImage(L"�A�W(���S�p).png", 13, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V(���S�p).png", 14, TEX_SIZE_512);

		Draw::LoadImageW(L"��.png", 16, TEX_SIZE_512);
	}

	//���{��摜(1�X�e�[�W�ڃS�[���p)
	Draw::LoadImage(L"���{��1.png", 5, TEX_SIZE_512);

	Draw::LoadImage(L"��l���̗�.png", 20, TEX_SIZE_512);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero(map);   //��l���I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, COBJ_HERO, 30);//�������l���I�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

	//�w�i�I�u�W�F�N�g�쐬
	C0bjBackground * back = new C0bjBackground();
	Objs::InsertObj(back, OBJ_BACKGROUND, 1);
	
	//block�I�u�W�F�N�g�쐬
	CObjBlock* objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 9);

	//�G�I�u�W�F�N�g�쐬
	/*CObjEnemy1* obje1 = new CObjEnemy1();
	Objs::InsertObj(obje1, OBJ_ENEMY_FIRST, 10);*/

	/*CObjEnemy2* obje2 = new CObjEnemy2();
	Objs::InsertObj(obje2, OBJ_ENEMY_SECOND, 10);*/

	CObjMain* objm = new CObjMain();
	Objs::InsertObj(objm, OBJ_MAIN, 120);

	//�I�[�f�B�I�ǂݍ���
	if (g_map_chenge == 0)
	{
		//���y�ǂݍ���
		Audio::LoadAudio(0, L"�X�e�[�W1BGM.wav", BACK_MUSIC);
		//�{�����[��1.5
		//float f = Audio::VolumeMaster(-0.3);

	}
	else if (g_map_chenge == 1)
	{
		//���y�ǂݍ���
		Audio::LoadAudio(0, L"�X�e�[�W2BGM.wav", BACK_MUSIC);
		//�{�����[��1.5
		//float f = Audio::VolumeMaster(-0.3);
	}
	else if (g_map_chenge == 2)
	{
		//���y�ǂݍ���
		Audio::LoadAudio(0, L"�X�e�[�W3BGM.wav", BACK_MUSIC);
		//�{�����[��1.5
		//float v = Audio::VolumeMaster(-0.1);
	}

	Audio::LoadAudio(1, L"���U����.wav", EFFECT);
	Audio::LoadAudio(2, L"�W�����v��.wav", EFFECT);
	Audio::LoadAudio(3, L"�_���[�W��(��l��).wav", EFFECT);
	Audio::LoadAudio(4, L"�_���[�W��(�G).wav", EFFECT);
	Audio::LoadAudio(5, L"�Ђ�����.wav", EFFECT);

	Audio::LoadAudio(6, L"�{�X��BGM.wav",BACK_MUSIC);

	float f = Audio::VolumeMaster(-0.2);

	Audio::Start(0);
}


//���s�����\�b�h
void CSceneMain::Scene()
{
	//�`�F���W�X�C�b�`�̏����擾
	CObjChangeSwitch* change = (CObjChangeSwitch*)Objs::GetObj(OBJ_CHANGESWITCH);

	if (m_m_change == false)
	{
		//���C�����y�X�g�b�v
		Audio::Stop(0);
		//�{�X���y�X�^�[�g
		Audio::Start(6);
		m_m_change = true;
	}
}