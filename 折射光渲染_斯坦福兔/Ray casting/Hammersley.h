#pragma once

#include"Sampler.h"

class Hammersley :public Sampler
{
public:
	Hammersley(void);
	Hammersley(const int num_samples);

	~Hammersley(void);

private:
	double phi(int j);//�������j�ġ�����Ϊ2�ĸ�������
	virtual void generate_samples(void);
};
