#pragma once

#include"Material.h"

//�Է������
class Emissive:public Material
{
public:
	Emissive(void);

	~Emissive(void);

	void scale_radiance(const float _ls);//���÷��䷶Χ

	void set_ce(const float r, const float g, const float b);//���÷�����ɫ

	virtual RGBColor get_Le(ShadeRec& sr)const;//��÷����

	virtual RGBColor shade(ShadeRec& sr);//����

	virtual RGBColor area_light_shade(ShadeRec& sr);//��������

	virtual RGBColor path_shade(ShadeRec& sr);

private:
	float ls;//�����������(����ϵ��)
	RGBColor ce;//�Է�����ɫֵ
};
/*
˵����
1.shade()����ʹ���Է�����ʿ����������͵Ĺ��߸��������ʹ�á����⣬����
��������������淨��λ��ͬһ��ʱ����������������Le=lsCe�������������غ�ɫֵ��
�˴��������Է�����ɫֵ�Լ�ͬ�Է��䷽ʽ���ս�ʹ�Է���������Ϊ�̶���ɫ״̬��
*/
/*
˵���������Է���������ǿ���������������ԣ�
1.�������ԣ�����Ҫ������������ܹ�����⣨��������Ϊ�˼򻯲�δ���Ƿ��䣬���ԴӶ���Ƕ���˵�䲻�ܱ����������
2.��Դ���ԣ��ܹ�����⣬���ӹ�Դ�Ƕ�����ʱ�����ܷ�������������������ܹ������������
*/
/*
ע�⣺�Է�����ʵķ���������λ�úͷ������йصģ���������Ϊ�˼򻯣�������λ�úͷ����޹ء�
*/

