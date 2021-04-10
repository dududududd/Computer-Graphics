#include "pch.h"
#include "Hammersley.h"

Hammersley::Hammersley(void)
	:Sampler()
{

}

Hammersley::Hammersley(const int num_samples)
	: Sampler()
{
	this->num_samples = num_samples;
	generate_samples();
}

Hammersley::~Hammersley(void)
{

}

double Hammersley::phi(int j)
{
	double x = 0.0;
	double f = 0.5;

	while (j)//关于这个函数的结束条件，其实其int型变量再经过一次运算后变为小于1的浮点数，然后经过强制类型转换变为0，结束循环
	{
		x += f * (double)(j % 2);
		j /= 2;
		f *= 0.5;
	}
	return(x);
}

void Hammersley::generate_samples(void)
{
	for (int p = 0; p < num_sets; p++)
	{
		for (int j = 0; j < num_samples; j++)
		{
			Point2D pv((float)j / (float)num_samples, phi(j));
			samples.push_back(pv);
		}
	}
}