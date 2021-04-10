#include "pch.h"
#include "Emissive.h"

#include"ShadeRec.h"

Emissive::Emissive(void)
	:Material(),ls(1.0),ce(1.0)
{
}

Emissive::~Emissive(void)
{
}

void Emissive::scale_radiance(const float _ls)
{
	this->ls = _ls;
}

void Emissive::set_ce(const float r, const float g, const float b)
{
	this->ce = RGBColor(r, g, b);
}

RGBColor Emissive::get_Le(ShadeRec& sr) const//获取发光材质的发射辐射度
{
	return(ls*ce);
}

RGBColor Emissive::shade(ShadeRec & sr)
{
	//return RGBColor(0.0);
	if (-sr.normal*sr.ray.d > 0.0)//判断相机是否看到发光面
		return(ls*ce);
	else
	{
		return(RGBColor(0.0));
	}
}

RGBColor Emissive::area_light_shade(ShadeRec & sr)
{
	if (sr.normal*sr.ray.d > 0.0)//判断相机是否看到发光面
		return(ls*ce);
	else
	{
		return(RGBColor(0.0));
	}
}
/*因为自发光对象也是对象，所以主光线会与其发生碰撞检测，当发生碰撞时，
我们判断相机是否是能看到区域光照的发光面，（这里区域光源可以理解为模拟的“探照灯”）
当看到发光面使用其发光材质颜色渲染，当看到背光面时采用背景色渲染。
*/
/*
重要说明：
注意：
这里的area_light_shade()函数里面的判断，我改变了sr.normal的符号，去掉了“-”号，
这里的原因是：环境光照和区域光照的着色情况是不一样的！！！
区域光照，例如球面照明，是球体从外部选择采样点，Emissive是要对作为光源的球体外壳进行着色渲染的。
环境光照，是一个巨大的壳体，其是球体内部采样点，Emissive是要对作为光源的球体内壳进行着色渲染的。
*/