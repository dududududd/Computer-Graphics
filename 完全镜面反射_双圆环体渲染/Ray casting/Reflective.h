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
˵����
����Reflective::shade()�������ú����Եݹ�ķ�ʽ����trace_ray()������
��ʹ��shade()������Whitted::trac_ray()���ٴα��ݹ���ã����ڲ����ں�����������ã�
��������ݹ��������Ϊһ����ʽ���á����ǵ�trace_ray()�������ݹ���ã�
����߲���Ӧ����Ϊ"Ray ray"��������"const Ray& ray",��Ȼ���߸��Ӹ�Ч��
����trace_ray()�����ĸ���ջ֡����Ҫ������Ĺ��߸������ݣ�����˴��б�Ҫʹ��ֵ���ݡ�
������ʱ�̣��ݹ�ջ��������max_depth()���˴˲�ͬ�Ĺ��ߡ������ý��ʺ��ڹ���Ͷ����㡣
*/