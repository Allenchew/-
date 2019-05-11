#pragma once
#include <algorithm>
#include <iostream>

class GameController {
private:
	int outerRot[4][3];
	int innerRot[4];
public:
	GameController();
	~GameController();

	void RotateObj(unsigned int (&input)[16]);
};