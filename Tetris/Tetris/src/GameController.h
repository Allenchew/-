#pragma once
#include <algorithm>
#include <iostream>

class GameController {
private:
	int outerRot[4][3]; //ŠO‘¤‚Ì‰ñ“]
	int innerRot[4];//“à‘¤‚Ì‰ñ“]
public:
	GameController();
	~GameController();

	void RotateObj(unsigned int (&input)[16]);//‰ñ“]‚·‚é
};