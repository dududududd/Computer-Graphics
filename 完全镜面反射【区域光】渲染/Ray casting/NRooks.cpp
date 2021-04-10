#include "pch.h"
#include "NRooks.h"

NRooks::NRooks(void)
	:Sampler()
{

}

NRooks::NRooks(const int num_samples)
	: Sampler()
{
	this->num_samples = num_samples;
	generate_samples();
}

NRooks::~NRooks(void)
{

}

void NRooks::generate_samples(void)//预先在 n*n的像素网格中生成主对角线的n个像素
{
	//沿主对角线生成样本

	for (int p = 0; p < num_sets; p++)
	{
		for (int j = 0; j < num_samples; j++)
		{
			Point2D pv;
			pv.x = (j + (float)rand()*1.0 / (float)RAND_MAX) / num_samples;
			pv.y = (j + (float)rand()*1.0 / (float)RAND_MAX) / num_samples;
			samples.push_back(pv);
		}
	}
	shuffle_x_coordinates();
	shuffle_y_coordinates();
}

void NRooks::shuffle_x_coordinates(void)//使用洗牌算法来混乱X坐标
{
	for (int p = 0; p < num_sets; p++)//num_sets是预先存储的样本集，一般就是83。
	{
		for (int i = 0; i < num_samples - 1; i++)
		{
			int target = rand() % num_samples + p * num_samples;
			float temp = samples[i + p * num_samples + 1].x;
			samples[i + p * num_samples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
	}
}

void NRooks::shuffle_y_coordinates(void)//使用洗牌算法来混乱Y坐标
{
	for (int p = 0; p < num_sets; p++)
	{
		for (int i = 0; i < num_samples - 1; i++)
		{
			int target = rand() % num_samples + p * num_samples;
			float temp = samples[i + p * num_samples + 1].y;
			samples[i + p * num_samples + 1].y = samples[target].y;
			samples[target].y = temp;
		}
	}
}