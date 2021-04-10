#include "pch.h"
#include "ViewPlane.h"

ViewPlane::ViewPlane(void)
	:hres(50), vres(50), s(1.0),
	gamma(1.0), inv_gamma(1.0),sampler_ptr(nullptr),
	num_samples(1), show_out_of_gamut(false), max_depth(0)
{

}

ViewPlane::ViewPlane(const ViewPlane& vp)
	:hres(vp.hres), vres(vp.vres), s(vp.s),
	gamma(vp.gamma), inv_gamma(vp.inv_gamma),
	sampler_ptr(vp.sampler_ptr),show_out_of_gamut(vp.show_out_of_gamut),
	num_samples(vp.num_samples), max_depth(vp.max_depth)
{

}

ViewPlane& ViewPlane::operator=(const ViewPlane& vp)
{
	if (this == &vp)
		return(*this);
	else
	{
		this->hres = vp.hres;
		this->vres = vp.vres;
		this->s = vp.s;
		this->gamma = vp.gamma;
		this->inv_gamma = vp.inv_gamma;
		this->sampler_ptr = vp.sampler_ptr;
		this->num_samples = vp.num_samples;
		this->max_depth = max_depth;
		return(*this);
	}
}

ViewPlane::~ViewPlane(void)
{
	//if (sampler_ptr) {
	//	delete sampler_ptr;
	//	sampler_ptr = nullptr;
	//}
}

void ViewPlane::set_hres(const int h)
{
	this->hres = h;
}

void ViewPlane::set_vres(const int v)
{
	this->vres = v;
}

void ViewPlane::set_pixel_size(const float s)
{
	this->s = s;
}

void ViewPlane::set_gamma(const double g)
{
	this->gamma = g;
	this->inv_gamma = 1.0 / gamma;
}

void ViewPlane::set_sampler(Sampler* sp)//【第二步：将传入的sp指针进行调用操作】
{
	if (sampler_ptr)//防止指针未初始化带来的危险
	{
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	num_samples = sp->get_num_samples();//获取采样点数量
	sampler_ptr = sp;//将sp指针赋值给sampler_ptr指针
}

//在默认情况下使用多重抖动采样；当采样数量为1时转变为均匀采样，并在各像素中心处设置相应的采样点
void ViewPlane::set_samples(const int n)
{
	num_samples = n;

	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (num_samples > 1)
		sampler_ptr = new MultiJittered(num_samples);
	else
	{
		sampler_ptr = new Regular(1);
	}
}

void ViewPlane::set_max_depth(const float depth)
{
	this->max_depth = depth;
}
