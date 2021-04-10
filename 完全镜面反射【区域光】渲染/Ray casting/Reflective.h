#pragma once

#include"Phong.h"
#include"PerfectSpecular.h"

class Reflective:public Phong
{
public:

	Reflective(void);

	~Reflective(void);

	void set_kr(const float _kr);

	void set_cr(const RGBColor& _cr);

	virtual RGBColor shade(ShadeRec& sr);

private:

	PerfectSpecular* reflective_brdf;
};
/*
说明：
关于Reflective::shade()函数，该函数以递归的方式调用trace_ray()函数，
这使得shade()函数在Whitted::trac_ray()中再次被递归调用，由于不存在函数的自身调用，
因而上述递归操作可视为一类隐式调用。考虑到trace_ray()函数被递归调用，
其光线参数应定义为"Ray ray"而非引用"const Ray& ray",虽然后者更加高效。
由于trace_ray()函数的各个栈帧均需要其自身的光线副本数据，因而此处有必要使用值传递。
在任意时刻，递归栈中最多包含max_depth()条彼此不同的光线。而引用仅适合于光线投射计算。
*/