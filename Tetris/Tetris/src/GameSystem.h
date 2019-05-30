#pragma once
#include "GameLoader.h"
#include "GameController.h"
#include "BlockEffect.h"

class GameSystem {
private:
	unsigned int objShape[7][4]; // contain pattern of dropping obj�@�u���b�N�̔z�u�f�[�^
	unsigned int pointerRef[16]; // use to point to map array address�@�}�b�v���̃u���b�N�̔z�u�|�C���g
	unsigned int prepointerRef[16]; //�u���b�N�̔z�u�|�C���g����O�ɖ߂�
	unsigned int startpoint; //new generate point�@�u���b�N�z�u�̎Q�ƃ|�C���g
	unsigned int lastpoint; // prev generate point�@��O�̎Q�ƃ|�C���g
	unsigned int objtype; //��������u���b�N�̃C���f�b�N�X
	unsigned int objcolor;
	unsigned int score; // print on console�@�_��
	bool rotatechecker; // check if rotated�@��]�������ǂ���
	std::vector<int> storeline;
	
public:
	GameSystem();
	~GameSystem();
	bool GameReset; //�Q�[���I�[�o�[����
	bool ClearEffect;
	std::vector<int>outputindex;
	void GenerateObj(unsigned int map[300],unsigned int tmpmap[300]); // use pointer to combine obj and map�@�����蔻��ƃ}�b�v�X�V
	void ObjFall(int index); // make obj auto falling (use rotate)�@�u���b�N�̗���
	void FixObj(unsigned int map[300], unsigned int tmpmap[300]); //�ړ��ł���u���b�N���}�b�v�ɏ�������
	void RollBackRotate(); //��]��������
	void ColliderCheck(unsigned int index, unsigned int tmpmap[300]);
	void Scoring();
	void CLearStroke( unsigned int tmpmap[300]); //�s���N���A
	void MoveLine(unsigned int map[300],unsigned int tmpmap[300]);
	void ProgressIndex(int input,unsigned int tmpmap[300]);

};