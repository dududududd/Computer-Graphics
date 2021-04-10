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

void NRooks::generate_samples(void)//Ԥ���� n*n�������������������Խ��ߵ�n������
{
	//�����Խ�����������

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

void NRooks::shuffle_x_coordinates(void)//ʹ��ϴ���㷨������X����
{
	for (int p = 0; p < num_sets; p++)//num_sets��Ԥ�ȴ洢����������һ�����83��
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

void NRooks::shuffle_y_coordinates(void)//ʹ��ϴ���㷨������Y����
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