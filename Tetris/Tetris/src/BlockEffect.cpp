#include "BlockEffect.h"

BlockEffect::BlockEffect()
	:EndEffect(false)
{
}

BlockEffect::~BlockEffect()
{
}

void BlockEffect::BlockTrans(std::vector<float>& linepointer,std::vector<int>& getindex)
{
	for (int i = 0; i < getindex.size(); i++) {
		for (int j = 0; j < 10; j++) {
			linepointer[((getindex[i]+j) * 32) + 7] -= 0.1f;
			linepointer[((getindex[i]+j) * 32) + 15] -= 0.1f;
			linepointer[((getindex[i]+j) * 32) + 23] -= 0.1f;
			linepointer[((getindex[i]+j) * 32) + 31] -= 0.1f;
		}
	}
	if(linepointer[(getindex[0] * 32) + 7]<0.3f)
		EndEffect = true;
}
