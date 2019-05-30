#pragma once
#include "GameSystem.h"
#include <vector>

class BlockEffect {
private:

public:
	BlockEffect();
	~BlockEffect();

	bool EndEffect;
	void BlockTrans(std::vector<float>& linepointer,std::vector<int>& getindex);
};