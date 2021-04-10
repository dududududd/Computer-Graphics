#pragma once

#include"BTDF.h"

class PerfectTransmitter:public BTDF
{
public:

	PerfectTransmitter(void);

	virtual~PerfectTransmitter(void);

	void set_kt(const float _kt);

	void set_ior(const float _ior);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt)const;

	//����͸�ӹ��ߵķ��򲢽��䷵��������wt���ҽ������ڷ�ȫ�ڷ���������
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt)const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

	virtual bool tir(const ShadeRec& sr)const;

private:

	float kt;//Kt,͸��ϵ����[0,1]
	float ior;//��
};