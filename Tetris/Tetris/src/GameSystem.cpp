#include "GameSystem.h"

GameSystem::GameSystem()
	:objtype(),gameReset(false),score(0),startpoint(4),objShape{ {5,6,9,10},{4,5,9,10},{6,7,9,10},{1,5,9,10},{2,6,9,10},{2,6,10,14},{5,8,9,10} },
	rotatechecker(false), lastpoint(4), pointerRef{ 0,1,2,3,12,13,14,15,24,25,26,27,36,37,38,39 }, prepointerRef{0,1,2,3,12,13,14,15,24,25,26,27,36,37,38,39}
{
	objtype = rand() % 7;
}
GameSystem::~GameSystem() {

}


void GameSystem::GenerataObj(unsigned int map[300], unsigned int tmpmap[300])
{
	std::memcpy(tmpmap, map, 300 * sizeof(unsigned int));
	bool reset = false;
	int flag = 0;
	unsigned int tmpPoint = startpoint;

	for (int i = 0; i < 4; i++) {
		unsigned int tmp = startpoint + pointerRef[objShape[objtype][i]];
		if (tmpmap[tmp] == 1) {
			if (rotatechecker) {
				if (tmpmap[tmp + 1] == 1 && tmpmap[tmp - 1]) {
					if (tmpmap[tmp - 12] == 0) {
						lastpoint -= 12;
						reset = true;
					}
					else {
						lastpoint -= 12;
					}
				}
				tmpmap[tmp + 1] == 1 ? lastpoint-- : lastpoint++; //bounce back if go in walls
				flag++;
				if (flag >= 2) {
					flag = 0;
					RollBackRotate();
					lastpoint = tmpPoint;
				}
				i = -1;
			}
			else if (startpoint - lastpoint == 12) {
				reset = true;
			}
			else if (startpoint == 4) {
				std::cout << "Game Over!!" << std::endl << "Press Enter To Restart." << std::endl;
				gameReset = true;
			}
			startpoint = lastpoint; //reset moved position
			
		}
	}
	for (int i = 0; i < 4; i++) {
		unsigned int tmp = startpoint + pointerRef[objShape[objtype][i]];
		tmpmap[tmp] = tmpmap[tmp] + 1;
		
	}
	rotatechecker = false;
	if (reset) {
		reset = false;
		CLearStroke(objtype, tmpmap);
		FixObj(map, tmpmap);
		startpoint = 4;
		objtype = rand() % 7;
	}
	std::memcpy(prepointerRef, pointerRef, 16 * sizeof(unsigned int));
	lastpoint = startpoint;
}

void GameSystem::ObjFall(int index)
{
	GameController gamecontroller;
	switch (index) {
	case 2:
		startpoint += 12;
		break;
	case 4:
		startpoint -= 1;
		break;
	case 6:
		startpoint += 1;
		break;
	case 8:
		rotatechecker = true;
		gamecontroller.RotateObj(pointerRef);
		break;
	default:
		break;
	}
	
}
void GameSystem::FixObj(unsigned int map[300], unsigned int tmpmap[300])
{
	std::memcpy(map, tmpmap, 300 * sizeof(unsigned int));
}


void GameSystem::RollBackRotate()
{
	std::memcpy(pointerRef, prepointerRef, 16 * sizeof(unsigned int));
}

void GameSystem::CLearStroke(unsigned int index, unsigned int tmpmap[300])
{
	std::vector<int> storeline;
	bool linecheck = false;
	float multiplier = 1.25f;
	for (int i = 0; i < 4; i++) {
		unsigned int tmp = startpoint + pointerRef[objShape[index][i]];
		int currentline = (float)tmp / 12.0f;
		for (int j = 1; j < 11; j++) {
			if (tmpmap[(currentline * 12) + j] == 0)
				break;
			else if(j==10)
			{
				std::memset(tmpmap+((currentline * 12)+1),0,10*sizeof(unsigned int));
				storeline.push_back((currentline*12)+1);
				multiplier *= storeline.size();
				linecheck = true;
			}
		}
	}
	if (linecheck) {
		score += (40 * multiplier);
		std::cout << "Score: " << score << std::endl;
	}
	std::sort(storeline.begin(), storeline.end());
	int lineindex = storeline.size()-1;
	int movedline = 1;
	while (linecheck) {
		for (int i = 0; i < 10; i++) {
			if (lineindex > 0) {
				if (storeline[lineindex - 1] == (storeline[lineindex] - (movedline * 12))) {
					lineindex--;
					movedline = 1;
				}
			}
			if (tmpmap[(storeline[lineindex] - (movedline*12)) + i] == 1) {
				std::memmove(tmpmap + (storeline[lineindex] + ((storeline.size()-lineindex-movedline) * 12)), tmpmap + (storeline[lineindex] - (movedline * 12)), 10 * sizeof(unsigned int));
				std::memset(tmpmap + (storeline[lineindex] - (movedline * 12)), 0, 10 * sizeof(unsigned int));
				movedline++;
				break;
			}
			else if (i == 9) {
				if (lineindex == 0 && movedline >1) {
					linecheck = false;
				}
				movedline++;
			}
		}
	}

}

