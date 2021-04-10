#pragma once
#include"RGBColor.h"
class ShadeRec;

class Material
{
public:

	Material(void);

	virtual~Material(void);

	virtual RGBColor shade(ShadeRec& sr);

	virtual RGBColor area_light_shade(ShadeRec& sr);//区域光照函数

	virtual RGBColor get_Le(ShadeRec& sr)const;

	//virtual RGBColor path_shade(ShadeRec& sr);

public:
	bool shadows;//用于设置材质阴影选项
};