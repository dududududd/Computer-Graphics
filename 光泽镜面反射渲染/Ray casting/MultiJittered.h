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
说明：
关于generate_samples()函数，我按照书籍的源码来抄写的，目前思路欠缺，等有更好的方法会回来修改。
*/