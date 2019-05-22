//�g�p����w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameL\WinInputs.h"
#include"GameL\SceneManager.h"
#include"GameL\SceneObjManager.h"

#include"GameHead.h"
#include"ObjBlock.h"
#include"GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

bool Hit_wall = false;
bool Hit_wall_r = false;
bool m_up = false;

CObjBlock::CObjBlock(int map[50][150])
{
	//�}�b�v�f�[�^�R�s�[
	memcpy(m_map, map, sizeof(int)*(50 * 150));
}

void CObjBlock::Setwall(bool type)
{
	if(type == true)
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 150; j++)
			{
				if (m_map[i][j] == 13)
					m_map[i][j] = 0;
			}
		}
}

/*void CObjBlock::Setswitch(bool type)
{
	if (type == true)
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				if (m_map[i][j] == 10)
					m_map[i][j] = 0;
			}
		}
}*/

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	m_scroll = 0.0f;
	m_scroll_map = 0.0f;
	float m_x1 = 0.0f;

	m_scrollx = 0.0f;
	m_scrolly = 0.0f;

	m_ani_time = 0;
	m_ani_frame = 0;

	m_ani_max_time = 15;
}


//�A�N�V����
void CObjBlock::Action()
{
	//��l���̈ʒu���擾
	CObjHero*hero = (CObjHero*)Objs::GetObj(COBJ_HERO);
	//float hx = hero->GetX();
	//float hy = hero->GetY();

	//�G�̈ʒu���擾
	CObjEnemy1*enemy1 = (CObjEnemy1*)Objs::GetObj(OBJ_ENEMY_FIRST);
	CObjEnemy2*enemy2 = (CObjEnemy2*)Objs::GetObj(OBJ_ENEMY_SECOND);

	CObjBoss1*boss1 = (CObjBoss1*)Objs::GetObj(OBJ_BOSS_FIRST);
	CObjBoss2*boss2 = (CObjBoss2*)Objs::GetObj(OBJ_BOSS_SECOND);

	/*float hx = hero->GetX();
	float hy = hero->GetY();*/
	////����X�N���[�����C��
	/*if (hx < 80)
	{
		hero->SetX(80);           //��l���̓��C���𒴂��Ȃ��悤�ɂ���
		m_scroll -= hero->GetVX(); //��l�����{�������ׂ����̒l��m_scroll�ɉ�����

	}

	//�O���X�N���[�����C��
	if (hx > 300)
	{
		hero->SetX(300);           //��l���̓��C���𒴂��Ȃ��悤�ɂ���
		m_scroll -= hero->GetVX(); //��l�����{�������ׂ����̒l��m_scroll�ɉ�����

	}*/
	if (Hit_wall == false)
	{
		//���̃X�N���[�����C��
		{
			hero->SetX(80);				//��l���̓��C���𒴂��Ȃ��悤�ɂ���
			m_scrollx -= hero->GetVX();	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
		}
		//�E�̃X�N���[�����C��
		{
			hero->SetX(250);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
			m_scrollx -= hero->GetVX();	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
		}
	}
		//��̃X�N���[�����C��
		{
			hero->SetY(0);				//��l���̓��C���𒴂��Ȃ��悤�ɂ���
			m_scrolly -= hero->GetVY();	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
		}
		//���̃X�N���[�����C��
		{
			hero->SetY(375);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
			m_scrolly -= hero->GetVY();	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
		}
	

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			//�G(�G��)�o��
			if (m_map[i][j] == 3)
			{
				//3������ΓG(�A�W)���o��
				
				CObjEnemy1* obje1 = new CObjEnemy1(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(obje1, OBJ_ENEMY_FIRST, 112);

				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 4)
			{
				//4������ΓG(�C���V)���o��
				CObjEnemy2* obje2 = new CObjEnemy2(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(obje2, OBJ_ENEMY_SECOND, 112);
	
				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;
			}

			//�S�[���u���b�N�o��
			if (m_map[i][j] == 5)
			{
				CObjgoalblock* ends = new CObjgoalblock(j*ALL_BLOCK_SIZE, i*ALL_BLOCK_SIZE);
				Objs::InsertObj(ends, OBJ_GOAL_BLOCK, 11);
				m_map[i][j] = 0;
			}

			//���ԏo��
			if (m_map[i][j] == 6)
			{
				CObjgear* gears = new CObjgear(j*ALL_BLOCK_SIZE, i*ALL_BLOCK_SIZE);
				Objs::InsertObj(gears, OBJ_GEAR, 11);
				m_map[i][j] = 0;
			}

			
			//�{�X�o��
			if (m_map[i][j] == 7)
			{
				//7������΃{�X(�J��)���o��
				
				CObjBoss1* objb1 = new CObjBoss1(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(objb1, OBJ_BOSS_FIRST, 112);
			

				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 8)
			{
				//8������΃{�X(�����E�O�E�m�c�J�C)���o��
				
				CObjBoss2* objb2 = new CObjBoss2(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(objb2, OBJ_BOSS_SECOND, 112);

				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 9)
			{
				//9������΃{�X(�T��(���P))���o��
				
				CObjBoss3* objb3 = new CObjBoss3(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(objb3, OBJ_BOSS_THIRD, 112);

				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;
			}

			if (m_map[i][j] == 10)
			{
				//10�������ChangeSwitch���o��
				CObjChangeSwitch* objds = new CObjChangeSwitch(j * ALL_BLOCK_SIZE, i * ALL_BLOCK_SIZE);
				Objs::InsertObj(objds, OBJ_CHANGESWITCH, 11);
				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;

			}
			if (m_map[i][j] == 11)
			{
				//11�������ChangeGate1���o��
				CObjChangeGate1* objds = new CObjChangeGate1(j * ALL_BLOCK_SIZE, i * ALL_BLOCK_SIZE);
				Objs::InsertObj(objds, OBJ_CHANGEGATE, 11);
				
				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;
			}
			if (m_map[i][j] == 15)
			{
				//15������ΓG(���񂱂�)���o��
				CObjEnemy3* obje3 = new CObjEnemy3(j*ALL_ENEMY_SIZE, i*ALL_ENEMY_SIZE);
				Objs::InsertObj(obje3, OBJ_ENEMY_THIRD, 112);

				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;
			}
			/*if (m_map[i][j] == 12)
			{
				
				//12�������ChangeGate2���o��
				CObjChangeGate2* objds = new CObjChangeGate2(j * ALL_BLOCK_SIZE, i * ALL_BLOCK_SIZE);
				Objs::InsertObj(objds, OBJ_CHANGEGATE, 11);
				
				//�o���ꏊ�̒l��0�ɂ���
				m_map[i][j] = 0;
			}*/
			
		}
	}
}

//�h���[
void CObjBlock::Draw()
{

	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float bl[4] = { 0.8f,0.8f,0.8f,1.0f };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu


	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{

			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = ALL_BLOCK_SIZE;
			src.m_bottom = ALL_BLOCK_SIZE;

			//�u���b�N�摜�\��
			if (m_map[i][j] == 1 || m_map[i][j] == 13)
			{
				if (g_map_chenge == 0) {

					//�\���ʒu�̐ݒ�
					dst.m_top = i * ALL_BLOCK_SIZE + m_scrolly;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scrollx;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
				else if (g_map_chenge == 1) {

					//�\���ʒu�̐ݒ�
					dst.m_top = i * ALL_BLOCK_SIZE + m_scrolly;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scrollx;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
				else if (g_map_chenge == 2) {

					//�\���ʒu�̐ݒ�
					dst.m_top = i * ALL_BLOCK_SIZE + m_scrolly;
					dst.m_left = j * ALL_BLOCK_SIZE + m_scrollx;
					dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
					dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

					Draw::Draw(2, &src, &dst, c, 0.0f);
				}
			}

			//�u���b�N�摜�\��
			if (m_map[i][j] == 2)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top = i*ALL_BLOCK_SIZE + m_scrolly;
				dst.m_left = j*ALL_BLOCK_SIZE + m_scrollx;
				dst.m_right = dst.m_left + ALL_BLOCK_SIZE;
				dst.m_bottom = dst.m_top + ALL_BLOCK_SIZE;

				Draw::Draw(2, &src, &dst, bl, 0.0f);
			}
		}
	}
}

//BlockHit�֐�
//�����P    float * x           :������s��object��X�ʒu
//�����Q    float * y           :������s��object��Y�ʒu
//�����R    bool     scroll_on  :������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
//�����S    bool *   up         :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T    bool *   down       :�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U    bool *   left       :�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V    bool *   right      :�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W    float * vx          :���E���莞�̔����ɂ��ړ������E�͂̒l�ς��ĕԂ�
//�����X    float * vy          :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l�ς��ĕԂ�
//�����P�O  int * bt            :���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHit(
	float *x, float *y, bool scroll_on,
	bool*up, bool*down, bool*left, bool*right,
	float *vx, float*vy, int *bt
)
{
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//���ǂɐG�ꂽ���̕`��ύX������
	Hit_wall = false;

	Hit_wall_r = false;

	m_up = false;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*32.0f;
				float by = i*32.0f;

				//�X�N���[���̉e��
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scrollx) + 64.0f > bx) && (*x + (-scrollx) < bx + 32.0f) 
				 && (*y + (-scrolly) + 64.0f > by) && (*y + (-scrolly) < by + 32.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scrollx)) - bx+16;
					float rvy = (*y + (-scrolly)) - by+16;

					//���������߂�
					float len = sqrt(rvx*rvx + rvy*rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r*180.0f / 3.14f;

					if (r < 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 55.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right = true;//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
							*x = bx + 32.0f + (scrollx);//�u���b�N�̈ʒu+��l���̕�
							*vx = 0.5f;//����
							Hit_wall = false;
							Hit_wall_r = false;

							//�}�b�v��2������΂�����
							if (m_map[i][j] == 2)
							{
								*x= bx + 31.0f + (scrollx);//�u���b�N�̈ʒu-��l���̕�
								if (*vy > 0.0f)
									*vy = 0.0f;//���������ߔ����Ȃ�
								*vx = 0.0f;
								Hit_wall = true;

								Audio::Start(5);

								//�E�L�[���͂ŗ����
								if (Input::GetVKey(VK_RIGHT) == true)
								{
									*vx = 0.5f;//����
									Hit_wall = false;
									Hit_wall_r = false;
								}

								if (Input::GetVKey(VK_UP) == true)
								{
									Hit_wall = false;
									Hit_wall_r = true;
									*vx = 0.5f;//����
									*vy = -3.0f;
								}
							}

						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l���̉��̕������Փ˂��Ă���
							*y = by - 64.0f + (scrolly);//�u���b�N�̈ʒu-��l���̕�
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;//��l���̉E�̕������Փ˂��Ă���
							*x = bx - 64.0f + (scrollx);//�u���b�N�̈ʒu-��l���̕�
							*vx = -0.5f;//����
							Hit_wall = false;
							Hit_wall_r = false;

							//�}�b�v��2������΂�����
							if (m_map[i][j] == 2)
							{
								*x = bx - 63.0f + (scrollx);//�u���b�N�̈ʒu-��l���̕�
								*vx = 0.0f;//���������ߔ����Ȃ�
							
								if(*vy>0.0f)
									*vy = 0.0f;//���������ߔ����Ȃ�
								Hit_wall = true;

								Audio::Start(5);

								//���L�[���͂ŗ����
								if (Input::GetVKey(VK_LEFT) == true)
								{
									Hit_wall = false;
									Hit_wall_r = false;
									*vx = -0.5f;//����
								}

								if (Input::GetVKey(VK_UP) == true)
								{
									Hit_wall = false;
									Hit_wall_r = true;
									*vx = -0.5f;//����
									*vy = -3.0f;
								}

							}
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;//��l���̏�̕������Փ˂��Ă���
							*y = by + 32.0f + (scrolly);//�u���b�N�̈ʒu+��l���̕�
							//m_up = false;

							//*vx = 0.0f;
							if (*vy < 0)
							{
								*vy = 0.0f;
							}

							//�}�b�v��2������΂�����
							if (m_map[i][j] == 2)
							{
								*y = by + 29.0f + (scrolly);//�u���b�N�̈ʒu+��l���̕�
								*vy = 0.0f;//���������ߔ����Ȃ�

								//m_up = true;
								Audio::Start(5);

								//���L�[���͂ŗ����
								if (Input::GetVKey(VK_DOWN) == true)
								{
									*vy = 0.5f;//����
									//m_up = false;
								}

								/*if (Input::GetVKey(VK_UP) == true)
								{
									Hit_wall = false;
									*vx = -0.5f;//����
									*vy = -3.0f;
								}*/
							}
						}
					}
				}
			}
		}
	}
}


//BlockHitEne�֐�(�A�W�E�C���V�p)
//�����P    float * x           :������s��object��X�ʒu
//�����Q    float * y           :������s��object��Y�ʒu
//�����R    bool     scroll_on  :������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
//�����S    bool *   up         :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T    bool *   down       :�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U    bool *   left       :�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V    bool *   right      :�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W    float * vx          :���E���莞�̔����ɂ��ړ������E�͂̒l�ς��ĕԂ�
//�����X    float * vy          :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l�ς��ĕԂ�
//�����P�O  int * bt            :���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHitEne(
	float *x, float *y, bool scroll_on,
	bool*up, bool*down, bool*left, bool*right,
	float *vx, float*vy, int *bt
)
{
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*32.0f;
				float by = i*32.0f;

				//�X�N���[���̉e��
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scrollx) + 50.0f > bx) && (*x + (-scrollx) < bx + 32.0f) 
				 && (*y + (-scrolly) + 64.0f > by) && (*y < by + (-scrolly) + 32.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//���������߂�
					float len = sqrt(rvx*rvx + rvy*rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r*180.0f / 3.14f;

					if (r < 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);


					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right = true;//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
							*x = bx + 32.0f + (scrollx);//�u���b�N�̈ʒu+��l���̕�
							*vx = 0.0f;//-VX*�����W��

						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l���̉��̕������Փ˂��Ă���
							*y = by - 50.0f + (scrolly);//�u���b�N�̈ʒu-��l���̕�
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;//��l���̉E�̕������Փ˂��Ă���
							*x = bx - 64.0f + (scrollx);//�u���b�N�̈ʒu-��l���̕�
							*vx = -(*vx)*0.0f;//-VX*�����W��
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;//��l���̏�̕������Փ˂��Ă���
							*y = by + 32.0f + (scrolly);//�u���b�N�̈ʒu+��l���̕�

							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}

//BlockHitEne2�֐�(���񂱂��p)
//�����P    float * x           :������s��object��X�ʒu
//�����Q    float * y           :������s��object��Y�ʒu
//�����R    bool     scroll_on  :������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
//�����S    bool *   up         :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T    bool *   down       :�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U    bool *   left       :�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V    bool *   right      :�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W    float * vx          :���E���莞�̔����ɂ��ړ������E�͂̒l�ς��ĕԂ�
//�����X    float * vy          :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l�ς��ĕԂ�
//�����P�O  int * bt            :���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHitEne2(
	float *x, float *y, bool scroll_on,
	bool*up, bool*down, bool*left, bool*right,
	float *vx, float*vy, int *bt
)
{
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 32.0f;
				float by = i * 32.0f;

				//�X�N���[���̉e��
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scrollx) + 64.0f > bx) && (*x + (-scrollx) < bx + 32.0f) 
				 && (*y + (-scrolly) + 110.0f > by) && (*y < by + (-scrolly) + 32.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//���������߂�
					float len = sqrt(rvx*rvx + rvy * rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r < 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);


					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right = true;//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
							*x = bx + 32.0f + (scrollx);//�u���b�N�̈ʒu+��l���̕�
							*vx = 0.0f;//-VX*�����W��

						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l���̉��̕������Փ˂��Ă���
							*y = by - 110.0f + (scrolly);//�u���b�N�̈ʒu-��l���̕�
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;//��l���̉E�̕������Փ˂��Ă���
							*x = bx - 64.0f + (scrollx);//�u���b�N�̈ʒu-��l���̕�
							*vx = -(*vx)*0.0f;//-VX*�����W��
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;//��l���̏�̕������Փ˂��Ă���
							*y = by + 32.0f + (scrolly);//�u���b�N�̈ʒu+��l���̕�

							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}

//BlockHitBoss1�֐�
//�����P    float * x           :������s��object��X�ʒu
//�����Q    float * y           :������s��object��Y�ʒu
//�����R    bool     scroll_on  :������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
//�����S    bool *   up         :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T    bool *   down       :�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U    bool *   left       :�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V    bool *   right      :�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W    float * vx          :���E���莞�̔����ɂ��ړ������E�͂̒l�ς��ĕԂ�
//�����X    float * vy          :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l�ς��ĕԂ�
//�����P�O  int * bt            :���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHitBoss1(
	float *x, float *y, bool scroll_on,
	bool*up, bool*down, bool*left, bool*right,
	float *vx, float*vy, int *bt
)
{
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 32.0f;
				float by = i * 32.0f;

				//�X�N���[���̉e��
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scrollx) + 100.0f > bx) && (*x + (-scrollx) < bx + 32.0f) && (*y +(scrolly)+ 50.0f > by) && (*y < by + (scrolly) + 32.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//���������߂�
					float len = sqrt(rvx*rvx + rvy * rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r < 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);


					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right = true;//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
							*x = bx + 32.0f + (scrollx);//�u���b�N�̈ʒu+��l���̕�
							*vx = 0.0f;//-VX*�����W��

						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l���̉��̕������Փ˂��Ă���
							*y = by - 50.0f + (scrolly);//�u���b�N�̈ʒu-��l���̕�
							*vy = 0.0f;
							
						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;//��l���̉E�̕������Փ˂��Ă���
							*x = bx - 100.0f + (scrollx);//�u���b�N�̈ʒu-��l���̕�
							*vx = -(*vx)*0.0f;//-VX*�����W��
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;//��l���̏�̕������Փ˂��Ă���
							*y = by + 32.0f + (scrolly);//�u���b�N�̈ʒu+��l���̕�

							/*if (*vy < 0)
							{
								*vy = 0.0f;
							}*/
						}
					}
				}
			}
		}
	}
}


//BlockHitBoss2�֐�
//�����P    float * x           :������s��object��X�ʒu
//�����Q    float * y           :������s��object��Y�ʒu
//�����R    bool     scroll_on  :������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
//�����S    bool *   up         :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T    bool *   down       :�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U    bool *   left       :�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V    bool *   right      :�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W    float * vx          :���E���莞�̔����ɂ��ړ������E�͂̒l�ς��ĕԂ�
//�����X    float * vy          :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l�ς��ĕԂ�
//�����P�O  int * bt            :���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHitBoss2(
	float *x, float *y, bool scroll_on,
	bool*up, bool*down, bool*left, bool*right,
	float *vx, float*vy, int *bt
)
{
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 32.0f;
				float by = i * 32.0f;

				//�X�N���[���̉e��
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scrollx) + 150.0f > bx) && (*x + (-scrollx) < bx + 32.0f) && (*y + (scrolly)+ 50.0f > by) && (*y < by + (scrolly)+ 32.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//���������߂�
					float len = sqrt(rvx*rvx + rvy * rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r < 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);


					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right = true;//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
							*x = bx + 32.0f + (scrollx);//�u���b�N�̈ʒu+��l���̕�
							*vx = 0.0f;//-VX*�����W��

						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l���̉��̕������Փ˂��Ă���
							*y = by - 50.0f + (scrolly);//�u���b�N�̈ʒu-��l���̕�
							*vy = 0.0f;

						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;//��l���̉E�̕������Փ˂��Ă���
							*x = bx - 150.0f + (scrollx);//�u���b�N�̈ʒu-��l���̕�
							*vx = -(*vx)*0.0f;//-VX*�����W��
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;//��l���̏�̕������Փ˂��Ă���
							*y = by + 32.0f + (scrolly);//�u���b�N�̈ʒu+��l���̕�

							/*if (*vy < 0)
							{
								*vy = 0.0f;
							}*/
						}
					}
				}
			}
		}
	}
}


//BlockHitBoss3�֐�
//�����P    float * x           :������s��object��X�ʒu
//�����Q    float * y           :������s��object��Y�ʒu
//�����R    bool     scroll_on  :������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
//�����S    bool *   up         :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
//�����T    bool *   down       :�㉺���E����̉������ɓ������Ă��邩�ǂ�����Ԃ�
//�����U    bool *   left       :�㉺���E����̍������ɓ������Ă��邩�ǂ�����Ԃ�
//�����V    bool *   right      :�㉺���E����̉E�����ɓ������Ă��邩�ǂ�����Ԃ�
//�����W    float * vx          :���E���莞�̔����ɂ��ړ������E�͂̒l�ς��ĕԂ�
//�����X    float * vy          :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l�ς��ĕԂ�
//�����P�O  int * bt            :���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHitBoss3(
	float *x, float *y, bool scroll_on,
	bool*up, bool*down, bool*left, bool*right,
	float *vx, float*vy, int *bt
)
{
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 32.0f;
				float by = i * 32.0f;

				//�X�N���[���̉e��
				float scrollx = scroll_on ? m_scrollx : 0;
				float scrolly = scroll_on ? m_scrolly : 0;

				//�I�u�W�F�N�g�ƃu���b�N�̓����蔻��
				if ((*x + (-scrollx) + 200.0f > bx) && (*x + (-scrollx) < bx + 32.0f) && (*y + (scrolly)+ 50.0f > by) && (*y < by + (scrolly)+ 32.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scrollx)) - bx;
					float rvy = (*y + (-scrolly)) - by;

					//���������߂�
					float len = sqrt(rvx*rvx + rvy * rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r < 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);


					//len��������̒����̂��Z���ꍇ����ɓ���
					if (len < 88.0f)
					{
						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right = true;//�I�u�W�F�N�g�̍��̕������Փ˂��Ă���
							*x = bx + 32.0f + (scrollx);//�u���b�N�̈ʒu+��l���̕�
							*vx = 0.0f;//-VX*�����W��

						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l���̉��̕������Փ˂��Ă���
							*y = by - 50.0f + (scrolly);//�u���b�N�̈ʒu-��l���̕�
							*vy = 0.0f;

						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;//��l���̉E�̕������Փ˂��Ă���
							*x = bx - 200.0f + (scrollx);//�u���b�N�̈ʒu-��l���̕�
							*vx = -(*vx)*0.0f;//-VX*�����W��
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;//��l���̏�̕������Փ˂��Ă���
							*y = by + 32.0f + (scrolly);//�u���b�N�̈ʒu+��l���̕�

							/*if (*vy < 0)
							{
								*vy = 0.0f;
							}*/
						}
					}
				}
			}
		}
	}
}

void CObjBlock::BlockDraw(float x, float y, RECT_F *dst, float c[])
{

}