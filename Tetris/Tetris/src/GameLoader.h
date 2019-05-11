#pragma once
#include<vector>
#include<iostream>

struct mapdata {
	std::vector<float>* position;
	std::vector<unsigned int>* indices;
};

class GameLoader {
private:
	unsigned int width;
	unsigned int height;
	unsigned int mapsize;
	 int cubesize;
	std::vector<float> tempVb;
	std::vector<unsigned int>tempindices;
public:
	unsigned int Map[300];
	unsigned int TmpMap[300];
	GameLoader();
	~GameLoader();
	void UpdateMap(const unsigned int* input);
	mapdata BuildMap();
};