#pragma once

#include"Ray.h"
#include"RGBColor.h"

class World;

class Tracer
{
public:
	Tracer(void);//Ĭ�Ϲ��캯��

	Tracer(World* _world_ptr);//���캯��

	Tracer(const Tracer& tracer);//�������캯��

	Tracer& operator=(const Tracer& tracer);//��ֵ���������

	virtual~Tracer(void);//����������

	virtual RGBColor trace_ray(const Ray& ray)const;//���߸���������
	
	virtual RGBColor trace_ray(const Ray ray, const int depth)const;

	virtual RGBColor trace_ray(const Ray ray, float& tmin, const int depth)const;

protected:
	World* world_ptr;//Worldָ�룬���ڷ��ʳ����еļ��ζ���ͱ�����ɫ
};
/*
˵����
1.������Ϊ���࣬����������Ӧ������Ϊ����������
2.��Ϊ���ݳ�Ա����ָ�������������Ҫд���������캯�����͡���ֵ��������ء���
3.��Ϊ������Ϊ���࣬���ݳ�Ա�ķ�������д�ɱ�����
4.����tmin������trace_ray()����������ʵ�ֻ���Dielectric���ʵ���ɫ���˼��㡣
5.depth��������ģ�ⷴ���Լ�͸���ȡ�
*/
