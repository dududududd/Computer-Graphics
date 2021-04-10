#pragma once

#include"Point2D.h"
#include"World.h"

class PinHole:public Camera
{
public:
	PinHole(void);

	~PinHole(void);

	Vector3D ray_direction(const Point2D& p)const;//计算光线方向

	virtual void render_scene(World& w);

	void set_d(const float dir);

	void set_zoom(const float z);

private:
	float d;//视平面距离
	float zoom;//缩放系数
};
/*
说明：
1.在render_scene()函数中，将针对各像素计算其颜色值L，L表示光线的辐射量。这里，辐射量(度)是光线跟踪器针对各条光线所计算出的一个量值。
2.在全部着色计算的实施过程中，针对同一类函数，参数deoth_in则提供了统一的的接口。
*/

