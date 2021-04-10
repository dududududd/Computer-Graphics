#pragma once

#include"MultiJittered.h"
#include"Regular.h"

class ViewPlane
{
public:
	ViewPlane(void);//Ĭ�Ϲ��캯��
	ViewPlane(const ViewPlane& vp);//�������캯��
	ViewPlane& operator=(const ViewPlane& vp);//��ֵ���������

	~ViewPlane(void);//��������

	void set_hres(const int h);//����ˮƽ�ֱ���
	void set_vres(const int v);//���ô�ֱ�ֱ���
	void set_pixel_size(const float s);//�������ش�С
	void set_gamma(const double g);//����٤��ֵ���䵹��
	void set_sampler(Sampler* sp);//���ò�����ָ��
	void set_samples(const int n);//���ò����������ֵ
	void set_max_depth(const float depth);
public:
	int hres;//ˮƽͼ��ֱ���
	int vres;//��ֱͼ��ֱ���
	float s;//���صĳߴ�
	float gamma;//��ʾ��gamma����
	float inv_gamma;//gammaֵ�ĵ���
	Sampler* sampler_ptr;//ָ������������ָ��
	int num_samples;//��������
	bool show_out_of_gamut;//�Ƿ���ɫ
	float max_depth;//�ݹ����
};
/*
˵����
1.����set_sampler(Sampler* sp)��û�жԲ������������κ�Ҫ��
*/