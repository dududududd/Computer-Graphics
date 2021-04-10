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

RGBColor Emissive::get_Le(ShadeRec& sr) const//��ȡ������ʵķ�������
{
	return(ls*ce);
}

RGBColor Emissive::shade(ShadeRec & sr)
{
	//return RGBColor(0.0);
	if (-sr.normal*sr.ray.d > 0.0)//�ж�����Ƿ񿴵�������
		return(ls*ce);
	else
	{
		return(RGBColor(0.0));
	}
}

RGBColor Emissive::area_light_shade(ShadeRec & sr)
{
	if (sr.normal*sr.ray.d > 0.0)//�ж�����Ƿ񿴵�������
		return(ls*ce);
	else
	{
		return(RGBColor(0.0));
	}
}
/*��Ϊ�Է������Ҳ�Ƕ������������߻����䷢����ײ��⣬��������ײʱ��
�����ж�����Ƿ����ܿ���������յķ����棬�����������Դ�������Ϊģ��ġ�̽�յơ���
������������ʹ���䷢�������ɫ��Ⱦ��������������ʱ���ñ���ɫ��Ⱦ��
*/
/*
��Ҫ˵����
ע�⣺
�����area_light_shade()����������жϣ��Ҹı���sr.normal�ķ��ţ�ȥ���ˡ�-���ţ�
�����ԭ���ǣ��������պ�������յ���ɫ����ǲ�һ���ģ�����
������գ�����������������������ⲿѡ������㣬Emissive��Ҫ����Ϊ��Դ��������ǽ�����ɫ��Ⱦ�ġ�
�������գ���һ���޴�Ŀ��壬���������ڲ������㣬Emissive��Ҫ����Ϊ��Դ�������ڿǽ�����ɫ��Ⱦ�ġ�
*/