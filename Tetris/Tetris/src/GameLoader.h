#pragma once
#include<vector>
#include<iostream>

struct mapdata {
	std::vector<float>* position;//点座標
	std::vector<unsigned int>* indices;//点の接続順
};

class GameLoader {
private:
	unsigned int width;
	unsigned int height;
	unsigned int mapsize;//マップの大きさ
	float colorpool[7][3];
	 int cubesize;//ブロックのテクスチャーの大きさ
	std::vector<float> tempVb;
	std::vector<unsigned int>tempindices;
public:
	unsigned int Map[300];
	unsigned int TmpMap[300];//マップの暫定データ
	GameLoader();
	~GameLoader();
	mapdata BuildMap();
};