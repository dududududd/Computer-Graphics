#pragma once

#include"Sampler.h"

class Regular:public Sampler
{
public:
	Regular(void);
	Regular(const int num_samples);

	~Regular(void);

private:
	virtual void generate_samples(void);
};