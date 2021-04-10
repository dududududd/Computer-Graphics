#pragma once

class World;
#include"Point3D.h"
#include"Vector3D.h"

class Camera
{
public:
	Camera(void);

	virtual~Camera(void);

	void compute_uvw(void);

	virtual void render_scene(World& w) = 0;

	void set_eye(const Point3D& p);

	void set_lookat(const Point3D& p);

	void set_up(const Vector3D& u);

	void set_exposure_time(const float t);

protected:

	Point3D eye;//视点
	Point3D lookat;//观察点
	Vector3D up;//UP向量
	Vector3D u, v, w;//正交基向量
	float exposure_time;//曝光时间
};
/*
说明:
1.在后面会进一步解释成员变量exposure_time的必要性。当前，该变量值仅在Camera类的默认
构造函数中设定为默认值1.0。
2.虽然可对相机参数设定任意大小的默认值，但仍需在各自的build()中设置变量eye、lookat以及d。
相比较而言，参数up、exposure_time以及zoom则应保留为其原默认值，这是因为仅有少数图像才会使用其非默认值。
*/

