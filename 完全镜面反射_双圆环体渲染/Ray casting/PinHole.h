#pragma once

#include"Point2D.h"
#include"World.h"

class PinHole:public Camera
{
public:
	PinHole(void);

	~PinHole(void);

	Vector3D ray_direction(const Point2D& p)const;//������߷���

	virtual void render_scene(World& w);

	void set_d(const float dir);

	void set_zoom(const float z);

private:
	float d;//��ƽ�����
	float zoom;//����ϵ��
};
/*
˵����
1.��render_scene()�����У�����Ը����ؼ�������ɫֵL��L��ʾ���ߵķ����������������(��)�ǹ��߸�������Ը����������������һ����ֵ��
2.��ȫ����ɫ�����ʵʩ�����У����ͬһ�ຯ��������deoth_in���ṩ��ͳһ�ĵĽӿڡ�
*/

