#include "GameController.h"

GameController::GameController()
	:outerRot{ {0,1,2},{3,7,11},{15,14,13},{12,8,4} },
	innerRot{ 5,6,10,9 }
{

}

GameController::~GameController() {

}

void GameController::RotateObj(unsigned int (&input)[16]) {
	unsigned int tmp[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if(i<3)
				tmp[outerRot[i][j]] = input[outerRot[i + 1][j]];
			else
				tmp[outerRot[i][j]] = input[outerRot[0][j]];
		}
		if (i<3)
			tmp[innerRot[i]] = input[innerRot[i+1]];
		else
			tmp[innerRot[i]] = input[innerRot[0]];
	}
	std::memcpy(input, tmp, 16*sizeof(unsigned int));
}


