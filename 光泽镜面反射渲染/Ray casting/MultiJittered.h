#pragma once

#include"Maths.h"
#include"Sampler.h"

class MultiJittered:public Sampler
{
public:
	MultiJittered(void);
	MultiJittered(const int num_samples);

	~MultiJittered(void);

private:
	virtual void generate_samples(void);
};
/*
˵����
����generate_samples()�������Ұ����鼮��Դ������д�ģ�Ŀǰ˼·Ƿȱ�����и��õķ���������޸ġ�
*/