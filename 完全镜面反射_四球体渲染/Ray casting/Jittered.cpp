#include "pch.h"
#include "Jittered.h"


Jittered::Jittered(void)
	:Sampler()
{
	
}

Jittered::Jittered(const int num_samples)//【第三步：初始化Sampler参数，读入外部采样点数量，调用generate_samplers()函数】
	: Sampler()
{
	this->num_samples = num_samples;//必须在前面，否则num_samples又会被Sampler()重置为1
	generate_samples();//必须要写，否则会报错提示：vector下标越界
}

Jittered::~Jittered(void)
{

}

void Jittered::generate_samples(void)//【第四步：根据不同的采样类型提前将采样点求值，执行完后返回World类】
{
	int n = (int)sqrt(num_samples);

	for (int p = 0; p < num_sets; p++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				Point2D sp((k + (float)rand()*1.0 / (float)RAND_MAX) / n, (j + (float)rand()*1.0 / (float)RAND_MAX) / n);
				samples.push_back(sp);//将采样点压入容器当中
			}
		}
	}
}