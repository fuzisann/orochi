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


//�g�p�w�b�_�[
#include"SceneMain.h"
#include"GameHead.h"
#include"ObjArrow.h"


//�R���X�g���N�^
CSceneMain::CSceneMain()
{

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
		p = Save::ExternalDataOpen(L"�X�e�[�W1����.csv", &size);//�O���f�[�^�ǂݍ���
	}
	else if (g_map_chenge == 1)
	{
		p = Save::ExternalDataOpen(L"�X�e�[�W2����.csv", &size);//�O���f�[�^�ǂݍ���
	}
	else if (g_map_chenge == 2)
	{
		p = Save::ExternalDataOpen(L"�}�b�v3.csv", &size);//�O���f�[�^�ǂݍ���
	}
	/*else if (g_map_chenge == 3)
	{
		p = Save::ExternalDataOpen(L"map9-6.csv", &size);//�O���f�[�^�ǂݍ���
	}
	else if (g_map_chenge == 4)
	{
		p = Save::ExternalDataOpen(L"map10-4.csv", &size);//�O���f�[�^�ǂݍ���
	}*/

	int map[19][100];
	int count = 1;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 100; j++)
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
	Draw::LoadImage(L"��l���P.png", 0, TEX_SIZE_512);

	if (g_map_chenge == 0)
	{
		//�w�i�摜�ǂݍ���
		Draw::LoadImage(L"�P�X�e�[�W�w�i.png", 3, TEX_SIZE_1024);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�u���b�N1.png", 2, TEX_SIZE_512);
		Draw::LoadImage(L"�Ђ����u���b�N.png", 4, TEX_SIZE_512);

		//�`�F���W�X�C�b�`���Q�[�g�摜�ǂݍ��݃e�X�g
		Draw::LoadImage(L"�_�u���b�N.png", 6, TEX_SIZE_512);
		Draw::LoadImage(L"�X�u���b�N.png", 7, TEX_SIZE_512);

		//�G�摜�ǂݍ���
		Draw::LoadImage(L"����������.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V������.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"�J��.png", 12, TEX_SIZE_512);

		//���ԉ摜�ǂݍ��݃e�X�g
		Draw::LoadImage(L"����1.5.png", 10, TEX_SIZE_512);

		Draw::LoadImage(L"����4.png", 11, TEX_SIZE_512);

		//�̗͂̓ǂݍ���
		Draw::LoadImage(L"�̗̓Q�[�W�t��.png", 17, TEX_SIZE_512);
		Draw::LoadImage(L"�̗̓Q�[�W�t��.png", 18, TEX_SIZE_512);
		Draw::LoadImage(L"�̗̓Q�[�W�t��.png", 19, TEX_SIZE_512);

		//���摜�ǂݍ���
		Draw::LoadImageW(L"��.png", 16, TEX_SIZE_512);
	}
	else if (g_map_chenge == 1)
	{
		//�w�i�摜�ǂݍ���
		//Draw::LoadImage(L"�Q�X�e�[�W�w�i.png", 3, TEX_SIZE_1024);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�X�e�[�W2�u���b�N.png", 2, TEX_SIZE_512);
		Draw::LoadImage(L"�Ђ����u���b�N.png", 4, TEX_SIZE_512);
		//�G�摜�ǂݍ���
		Draw::LoadImage(L"����������.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V������.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"�����E�O�E�m�c�J�C�@������.png", 12, TEX_SIZE_512);
		//���摜�ǂݍ���
		Draw::LoadImageW(L"��.png", 16, TEX_SIZE_512);
		/*//�w�i�摜�ǂݍ���
		Draw::LoadImage(L"map.jpg", 3, TEX_SIZE_1024);
		//�}�b�v2�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"brock5.png", 1, TEX_SIZE_512);
		//�j㩓ǂݍ���
		Draw::LoadImage(L"blockobj2.png", 4, TEX_SIZE_512);*/
	}
	else if (g_map_chenge == 2)
	{
		//�w�i�摜�ǂݍ���
		Draw::LoadImage(L"�R�X�e�[�W�w�i.png", 3, TEX_SIZE_1024);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�X�e�[�W3�u���b�N.png", 2, TEX_SIZE_512);
		Draw::LoadImage(L"�Ђ����u���b�N.png", 4, TEX_SIZE_512);
		//�G�摜�ǂݍ���
		Draw::LoadImage(L"����������.png", 8, TEX_SIZE_512);
		Draw::LoadImage(L"�C���V������.png", 9, TEX_SIZE_512);
		Draw::LoadImage(L"���P.png", 12, TEX_SIZE_512);
		//���摜�ǂݍ���
		Draw::LoadImageW(L"��.png", 16, TEX_SIZE_512);
		/*//�w�i�摜�ǂݍ���
		Draw::LoadImage(L"�X�̓��A2.jpg", 3, TEX_SIZE_1024);
		//�}�b�v7�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�X�u���b�N.png", 1, TEX_SIZE_512);
		//�}�b�v7�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�X�u���b�N2.png", 6, TEX_SIZE_512);
		//�X��㩓ǂݍ���
		Draw::LoadImage(L"�X���u���b�N.png",7, TEX_SIZE_512);*/
	}
	/*else if (g_map_chenge == 3) 
	{
		//�w�i�摜�ǂݍ���
		Draw::LoadImage(L"�_�̏�X�e�[�W.jpg", 3, TEX_SIZE_1024);
		//�}�b�v9�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�_�u���b�N.png", 1, TEX_SIZE_512);
		//�}�b�v9�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�_�u���b�N.png", 9, TEX_SIZE_512);
	}
	else if (g_map_chenge == 4)
	{
		//�}�b�v10  �w�i�摜�ǂݍ���
		Draw::LoadImage(L"���X�g�X�e�[�W.gif", 3, TEX_SIZE_1024);
		//�}�b�v10�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"���X�g�X�e�[�W�u���b�N.png", 1, TEX_SIZE_512);
		//�}�b�v10�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�X�u���b�N2.png", 6, TEX_SIZE_512);
		//�}�b�v10  �X��㩓ǂݍ���
		Draw::LoadImage(L"�X���u���b�N.png", 7, TEX_SIZE_512);
		//�}�b�v10�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"�Ђъ���u���b�N.png", 8, TEX_SIZE_512);
		//�}�b�v10�@�u���b�N�摜�ǂݍ���
		Draw::LoadImage(L"������΃u���b�N.png", 9, TEX_SIZE_512);
	}*/
	
	//�S�[��
	Draw::LoadImage(L"efe.png", 5, TEX_SIZE_512);

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

	/*if (g_map_chenge == 0)
	{
		//���y�ǂݍ���
		Audio::LoadAudio(0, L"moristage.wav", BACK_MUSIC);
		//�{�����[��1.5
		float f = Audio::VolumeMaster(1.5);
	}
	else if (g_map_chenge == 1)
	{
		//���y�ǂݍ���
		Audio::LoadAudio(0, L"���A.wav", BACK_MUSIC);
		//�{�����[��1.5
		float v = Audio::VolumeMaster(1.5);
	}
	else if (g_map_chenge == 2)
	{
		//���y�ǂݍ���
		Audio::LoadAudio(0, L"map7.wav", BACK_MUSIC);
		//�{�����[��1.5
		float v = Audio::VolumeMaster(1.5);
	}
	else if (g_map_chenge == 3)
	{
		//���y�ǂݍ���
		Audio::LoadAudio(0, L"map9BGM.wav", BACK_MUSIC);
		//�{�����[��1.5
		float v = Audio::VolumeMaster(1.5);
	}
	else if (g_map_chenge == 4)
	{
		//���y�ǂݍ���
		Audio::LoadAudio(0, L"���X�g�X�e�[�W.wav", BACK_MUSIC);
		//�{�����[��1.5
		float v = Audio::VolumeMaster(1.5);
	}
	Audio::LoadAudio(1, L"jump01.wav", EFFECT);
	//�{�����[��1.5
	float v = Audio::VolumeMaster(1.0);

	//���y�X�^�[�g
	Audio::Start(0);
	*/

}


//���s�����\�b�h
void CSceneMain::Scene()
{

}