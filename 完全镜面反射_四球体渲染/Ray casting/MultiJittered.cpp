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
	//num_samples需要是一个完美的正方形
	int n = (int)sqrt((float)num_samples);
	double subcell_width = 1.0 / ((float)num_samples);

	//使用伪点填充samples数组，以便在设置
	//初始模式
	Point2D fill_point;
	for (int j = 0; j < num_samples*num_sets; j++)
	{
		samples.push_back(fill_point);
	}

	//在初始模式中分布点
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

	//随机移动x坐标
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
	//随机移动y坐标
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