#pragma once

#include"Sampler.h"

class Jittered:public Sampler
{
public:
	Jittered(void);
	Jittered(const int num_samples);

	~Jittered(void);

private:
	virtual void generate_samples(void);
};
/*
˵����
1.generate_samples�������ڵ�λ�����������ɲ����㣬����洢����Ϊ�򵥵ķ�ʽ��ʹ��һά���飬����������������Ԫ�ؽ��з��ʡ�
*/
