#pragma once

#include"MultiJittered.h"
#include"Regular.h"

class ViewPlane
{
public:
	ViewPlane(void);//默认构造函数
	ViewPlane(const ViewPlane& vp);//拷贝构造函数
	ViewPlane& operator=(const ViewPlane& vp);//赋值运算符重载

	~ViewPlane(void);//析构函数

	void set_hres(const int h);//设置水平分辨率
	void set_vres(const int v);//设置垂直分辨率
	void set_pixel_size(const float s);//设置像素大小
	void set_gamma(const double g);//设置伽马值及其倒数
	void set_sampler(Sampler* sp);//设置采样器指针
	void set_samples(const int n);//设置采样点的数量值
	void set_max_depth(const float depth);
public:
	int hres;//水平图像分辨率
	int vres;//垂直图像分辨率
	float s;//像素的尺寸
	float gamma;//显示器gamma因素
	float inv_gamma;//gamma值的倒数
	Sampler* sampler_ptr;//指向采样器对象的指针
	int num_samples;//采样数量
	bool show_out_of_gamut;//是否溢色
	float max_depth;//递归深度
};
/*
说明：
1.函数set_sampler(Sampler* sp)并没有对采样器类型做任何要求。
*/