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

	Point3D eye;//�ӵ�
	Point3D lookat;//�۲��
	Vector3D up;//UP����
	Vector3D u, v, w;//����������
	float exposure_time;//�ع�ʱ��
};
/*
˵��:
1.�ں�����һ�����ͳ�Ա����exposure_time�ı�Ҫ�ԡ���ǰ���ñ���ֵ����Camera���Ĭ��
���캯�����趨ΪĬ��ֵ1.0��
2.��Ȼ�ɶ���������趨�����С��Ĭ��ֵ���������ڸ��Ե�build()�����ñ���eye��lookat�Լ�d��
��Ƚ϶��ԣ�����up��exposure_time�Լ�zoom��Ӧ����Ϊ��ԭĬ��ֵ��������Ϊ��������ͼ��Ż�ʹ�����Ĭ��ֵ��
*/

