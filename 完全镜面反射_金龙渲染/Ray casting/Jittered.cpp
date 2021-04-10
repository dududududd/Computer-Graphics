#include "pch.h"
#include "Jittered.h"


Jittered::Jittered(void)
	:Sampler()
{
	
}

Jittered::Jittered(const int num_samples)//������������ʼ��Sampler�����������ⲿ����������������generate_samplers()������
	: Sampler()
{
	this->num_samples = num_samples;//������ǰ�棬����num_samples�ֻᱻSampler()����Ϊ1
	generate_samples();//����Ҫд������ᱨ����ʾ��vector�±�Խ��
}

Jittered::~Jittered(void)
{

}

void Jittered::generate_samples(void)//�����Ĳ������ݲ�ͬ�Ĳ���������ǰ����������ֵ��ִ����󷵻�World�ࡿ
{
	int n = (int)sqrt(num_samples);

	for (int p = 0; p < num_sets; p++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				Point2D sp((k + (float)rand()*1.0 / (float)RAND_MAX) / n, (j + (float)rand()*1.0 / (float)RAND_MAX) / n);
				samples.push_back(sp);//��������ѹ����������
			}
		}
	}
}