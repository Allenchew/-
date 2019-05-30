#pragma once
#include<vector>
#include<iostream>

struct mapdata {
	std::vector<float>* position;//�_���W
	std::vector<unsigned int>* indices;//�_�̐ڑ���
};

class GameLoader {
private:
	unsigned int width;
	unsigned int height;
	unsigned int mapsize;//�}�b�v�̑傫��
	float colorpool[7][3];
	 int cubesize;//�u���b�N�̃e�N�X�`���[�̑傫��
	std::vector<float> tempVb;
	std::vector<unsigned int>tempindices;
public:
	unsigned int Map[300];
	unsigned int TmpMap[300];//�}�b�v�̎b��f�[�^
	GameLoader();
	~GameLoader();
	mapdata BuildMap();
};