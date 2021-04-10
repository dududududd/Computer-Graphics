#pragma once
#include"CBezierPatch.h"
#include"Mesh.h"
#include"GeometricObject.h"

class CTeapot:public GeometricObject
{
public:
	CTeapot(void);
	virtual~CTeapot(void);
	void SetRecursiveNumber(int Renumber);//���õݹ����
	void ReadVertex(void);//������ƶ���ζ���
	void ReadPatch(void);//����˫��������Ƭ
	void set_point(void);//��������
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;
	virtual bool shadow_hit(const Ray& ray, float& tmin)const;
	virtual BBox get_bounding_box(void);
private:
	void DrawRim(void);//����
	void DrawBody(void);//����
	void DrawHandle(void);//����
	void DrawSpout(void);//����
	void DrawLid(void);//����
	void DrawBottom(void);//����
	void SigleCurvedPatch(void);//����һ��˫��������Ƭ
public:
	int Renumber;//�ݹ����
	Point3D Ver[306];//����ܿ��Ƶ�
private:
	Mesh Pat[32];//�������Ƭ
	Point3D Ver3[16];//��ά���Ƶ�
	CBezierPatch bezier;//bezier����Ƭ
	BBox bbox;
};
