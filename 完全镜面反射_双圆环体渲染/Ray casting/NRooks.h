#pragma once

#include"Sampler.h"

class NRooks:public Sampler
{
public:
	NRooks(void);
	NRooks(const int num_samples);

	~NRooks(void);
private:
	virtual void generate_samples(void);
	void shuffle_x_coordinates(void);
	void shuffle_y_coordinates(void);
};

