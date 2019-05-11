#pragma once
#include "GameLoader.h"
#include "GameController.h"

class GameSystem {
private:
	unsigned int objShape[7][4]; // contain pattern of dropping obj
	unsigned int pointerRef[16]; // use to point to map array address
	unsigned int prepointerRef[16];
	unsigned int startpoint; //new generate point
	unsigned int lastpoint; // prev generate point
	unsigned int objtype;
	unsigned int score; // print on console
	bool rotatechecker; // check if rotated
public:
	GameSystem();
	~GameSystem();
	bool gameReset;
	void GenerataObj(unsigned int map[300],unsigned int tmpmap[300]); // use pointer to combine obj and map
	void ObjFall(int index); // make obj auto falling (use rotate)
	void FixObj(unsigned int map[300], unsigned int tmpmap[300]);
	void RollBackRotate();
	void CLearStroke(unsigned int index, unsigned int tmpmap[300]);
};