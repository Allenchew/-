#include "GameLoader.h"
#include<algorithm>


GameLoader::GameLoader() //to initiate game
	:width(12), height(25), mapsize(width*height), cubesize(20), tempVb(), tempindices(), TmpMap{0},
	Map{
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,
	},
	colorpool{
		{1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f},
		{1.0f,1.0f,0.0f},
		{0.0f,1.0f,1.0f},
		{1.0f,0.0f,1.0f},
		{0.5f,0.5f,0.5f},
	}
{
	
}

GameLoader::~GameLoader()
{

}

mapdata GameLoader::BuildMap()
{
	mapdata input;
	tempVb.clear();
	tempindices.clear();
	input.position = &tempVb;
	input.indices = &tempindices;
	unsigned int sizecount = 0;
	for (int i = 0; i < mapsize; i++) {
		int incrementX = (i > width-1) ? i % width : i;
		int incrementY = height-(int)((float)i / width);
		if (TmpMap[i] >= 1) {
			float position[] = {
				 (incrementX*cubesize),-cubesize +(incrementY * cubesize),0.0f,0.0f,
				 colorpool[TmpMap[i] - 1][0],colorpool[TmpMap[i] - 1][1],colorpool[TmpMap[i] - 1][2],1.0f,
				 (incrementX * cubesize),(incrementY * cubesize),0.0f,1.0f,
				 colorpool[TmpMap[i] - 1][0],colorpool[TmpMap[i] - 1][1],colorpool[TmpMap[i] - 1][2],1.0f,
				 cubesize  + (incrementX * cubesize), (incrementY *cubesize),1.0f,1.0f,
				 colorpool[TmpMap[i] - 1][0],colorpool[TmpMap[i] - 1][1],colorpool[TmpMap[i] - 1][2],1.0f,
				 cubesize  + (incrementX * cubesize), -cubesize+(incrementY * cubesize),1.0f,0.0f,
				 colorpool[TmpMap[i] - 1][0],colorpool[TmpMap[i] - 1][1],colorpool[TmpMap[i] - 1][2],1.0f,
			};
			unsigned int indices[] = {
				0 + (sizecount * 4),1 + (sizecount * 4),2 + (sizecount * 4),
				2 + (sizecount * 4),3 + (sizecount * 4),0 + (sizecount * 4),
			};
			tempVb.insert(tempVb.end(), &position[0], &position[32]);
			tempindices.insert(tempindices.end(), &indices[0], &indices[6]);
			
			sizecount++;
		}
	}
	return input;
}

