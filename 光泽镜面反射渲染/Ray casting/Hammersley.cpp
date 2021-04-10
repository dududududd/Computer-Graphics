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

	while (j)//������������Ľ�����������ʵ��int�ͱ����پ���һ��������ΪС��1�ĸ�������Ȼ�󾭹�ǿ������ת����Ϊ0������ѭ��
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