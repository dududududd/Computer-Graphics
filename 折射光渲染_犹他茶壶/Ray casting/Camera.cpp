#include "pch.h"
#include "Camera.h"

Camera::Camera(void)
	:eye(0.0,0.0,500.0), lookat(0.0), up(0.0, 1.0, 0.0),
	u(1.0,0.0,0.0), v(0.0,1.0,0.0), w(0.0,0.0,1.0), exposure_time(1.0)
{

}

Camera::~Camera(void)
{

}

void Camera::compute_uvw(void)
{
	w = eye - lookat;
	w.Normalize();
	u = up ^ w;
	u.Normalize();
	v = w ^ u;

	if (eye.x == lookat.x&&eye.z == lookat.z&&lookat.y < eye.y)//相机垂直向下观察
	{
		u = Vector3D(0, 0, 1);
		v = Vector3D(1, 0, 0);
		w = Vector3D(0, 1, 0);
	}
	if (eye.x == lookat.x&&eye.z == lookat.z&&lookat.y > eye.y)//相机垂直向上观察
	{
		u = Vector3D(1, 0, 0);
		v = Vector3D(0, 0, 1);
		w = Vector3D(0, -1, 0);
	}
}

void Camera::set_eye(const Point3D& p)
{
	this->eye = p;
}

void Camera::set_lookat(const Point3D& p)
{
	this->lookat = p;
}

void Camera::set_up(const Vector3D& u)
{
	this->up = u;
}

void Camera::set_exposure_time(const float t)
{
	this->exposure_time = t;
}