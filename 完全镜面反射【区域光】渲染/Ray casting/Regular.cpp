#include "pch.h"
#include "Regular.h"

Regular::Regular(void)
	:Sampler()
{

}

Regular::Regular(const int num_samples)
	: Sampler()
{
	this->num_samples = num_samples;
	generate_samples();
}

Regular::~Regular(void)
{

}

void Regular::generate_samples(void)
{
	int n = (int)sqrt((float)num_samples);

	for (int j = 0; j < num_sets; j++)
	{
		for (int p = 0; p < n; p++)
		{
			for (int q = 0; q < n; q++)
			{
				Point2D sp((q + 0.5) / n, (p + 0.5) / n);
				samples.push_back(sp);
			}
		}
	}
}