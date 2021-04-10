#pragma once

#include"Sampler.h"

class PureRandom:public Sampler
{
public:
	PureRandom(void);
	PureRandom(const int num_samples);
	
	~PureRandom(void);

private:
	virtual void generate_samples(void);
};

