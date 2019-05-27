#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,
	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	COBJ_HERO,
	OBJ_MAIN,
	OBJ_TITLE,
	OBJ_BACKGROUND,
	OBJ_CLEAR,
	OBJ_STAGE_CLEAR,
	OBJ_BLOCK,
	OBJ_OVER,
	OBJ_TIME,
	OBJ_GOAL_BLOCK,
	OBJ_OPERATION,

	OBJ_ENEMY,
	OBJ_ENEMY_FIRST,
	OBJ_ENEMY_SECOND,
	OBJ_ENEMY_THIRD,

	OBJ_BOSS_FIRST,
	OBJ_BOSS_SECOND,
	OBJ_BOSS_THIRD,

	OBJ_STICK,
	OBJ_SWORD,
	OBJ_GEAR,
	OBJ_SWITCH,
	OBJ_CHANGESWITCH,
	OBJ_CHANGEGATE,
	OBJ_BUBBLE,

	OBJ_OP,
	OBJ_ED,
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,
	//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
	ELEMENT_ATTACK,
	ELEMENT_GEAR,
	ELEMENT_MYSTERY,
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^

};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
extern int g_map_chenge;//�}�b�v�ύX
extern int g_m_chenge;//BGM�ύX
extern int block2;
extern bool check;
extern bool m_c;

//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "CObjHero.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjStageClear.h"
#include "ObjClear.h"
#include "Objgoalblock.h"
#include "ObjOver.h"
#include "ObjTitle.h"
#include "ObjOP.h"
#include "ObjED.h"
#include "ObjOperation.h"
#include "ObjEnemy1.h"
#include "ObjEnemy2.h"
#include "ObjEnemy3.h"
#include "ObjMain.h"
#include "CObjStick.h"
#include "CObjHeroSword.h"
#include "ObjBoss1.h"
#include "ObjBoss2.h"
#include "ObjBoss3.h"
#include "ObjSwitch.h"
#include "ObjChangeSwitch.h"
#include "ObjChangeGate1.h"
#include "ObjBubble.h"

//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneStageClear.h"
#include "SceneOver.h"
#include "SceneTitle.h"
#include "SceneOP.h"
#include "SceneED.h"
#include "SceneOperation.h"

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneMain
#define SET_GAME_START CSceneTitle
//-----------------------------------------------