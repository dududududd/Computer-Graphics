#include "pch.h"
#include "PureRandom.h"

PureRandom::PureRandom(void)
	:Sampler()
{

}

PureRandom::PureRandom(const int num_samples)
	: Sampler()
{
	this->num_samples = num_samples;
	generate_samples();
}

PureRandom::~PureRandom(void)
{

}

void PureRandom::generate_samples(void)
{
	int n = (int)num_samples;
	for (int j = 0; j < num_sets; j++)
	{
		for (int p = 0; p < num_samples; p++)
		{
			Point2D sp((float)rand()*1.0 / (float)RAND_MAX, (float)rand()*1.0 / (float)RAND_MAX);
			samples.push_back(sp);
		}
	}
}