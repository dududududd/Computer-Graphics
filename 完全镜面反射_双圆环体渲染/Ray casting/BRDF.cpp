#include "pch.h"
#include "BRDF.h"

BRDF::BRDF(void)
	:sampler_ptr(nullptr)
{

}

BRDF::BRDF(const BRDF& brdf)
	:sampler_ptr(brdf.sampler_ptr)
{

}

BRDF& BRDF::operator=(const BRDF& brdf)
{
	if (this == &brdf)
		return(*this);
	else
	{
		this->sampler_ptr = brdf.sampler_ptr;
		return(*this);
	}
}

BRDF::~BRDF(void)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}
}