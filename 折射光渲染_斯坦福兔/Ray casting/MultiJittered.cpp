#include "pch.h"
#include "MultiJittered.h"



MultiJittered::MultiJittered(void)
	:Sampler()
{

}

MultiJittered::MultiJittered(const int num_samples)
	: Sampler()
{
	this->num_samples = num_samples;
	generate_samples();
	setup_shuffled_indices();
}

MultiJittered::~MultiJittered(void)
{

}

void MultiJittered::generate_samples(void)
{
	//num_samples��Ҫ��һ��������������
	int n = (int)sqrt((float)num_samples);
	double subcell_width = 1.0 / ((float)num_samples);

	//ʹ��α�����samples���飬�Ա�������
	//��ʼģʽ
	Point2D fill_point;
	for (int j = 0; j < num_samples*num_sets; j++)
	{
		samples.push_back(fill_point);
	}

	//�ڳ�ʼģʽ�зֲ���
	for (int p = 0; p < num_sets; p++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				samples[i*n + j + p * num_samples].x = (i*n + j)*subcell_width + rand_float(0, subcell_width);
				samples[i*n + j + p * num_samples].y = (j*n + i)*subcell_width + rand_float(0, subcell_width);
			}
		}
	}

	//����ƶ�x����
	for (int p = 0; p < num_sets; p++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int k = rand_int(j, n - 1);
				float t = samples[i * n + j + p * num_samples].x;
				samples[i * n + j + p * num_samples].x = samples[i * n + k + p * num_samples].x;
				samples[i * n + k + p * num_samples].x = t;
			}
		}
	}
	//����ƶ�y����
	for (int p = 0; p < num_sets; p++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				int k = rand_int(j, n - 1);
				float t = samples[j * n + i + p * num_samples].y;
				samples[j * n + i + p * num_samples].y = samples[k * n + i + p * num_samples].y;
				samples[k * n + i + p * num_samples].y = t;
			}
		}
	}
}