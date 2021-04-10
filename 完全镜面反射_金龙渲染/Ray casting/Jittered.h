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
说明：
1.generate_samples函数将在单位正方形内生成采样点，对其存储的最为简单的方式是使用一维数组，并利用索引对数据元素进行访问。
*/
