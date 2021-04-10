#pragma once

#include"Sampler.h"

class Hammersley :public Sampler
{
public:
	Hammersley(void);
	Hammersley(const int num_samples);

	~Hammersley(void);

private:
	double phi(int j);//针对整数j的、基数为2的根反函数
	virtual void generate_samples(void);
};
