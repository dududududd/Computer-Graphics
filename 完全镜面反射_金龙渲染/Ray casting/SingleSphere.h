#pragma once

#include"Tracer.h"

class SingleSphere:public Tracer
{
public:
	SingleSphere(void);//Ĭ�Ϲ��캯��
	SingleSphere(World* _worldPtr);//���캯��
	
	~SingleSphere(void);//��������
	//virtual RGBColor trace_ray(const Ray& ray)const;//���߸���������
};
/*
˵����
1.����̳��Ի���Tracer�࣬����û�����������ݳ�Ա��
2.���๹�캯����Ҫ�Ի������ݳ�Ա���г�ʼ����
*/

