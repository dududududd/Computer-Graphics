#pragma once
#include"CBezierPatch.h"
#include"Mesh.h"
#include"GeometricObject.h"

class CTeapot:public GeometricObject
{
public:
	CTeapot(void);
	virtual~CTeapot(void);
	void SetRecursiveNumber(int Renumber);//设置递归深度
	void ReadVertex(void);//读入控制多边形顶点
	void ReadPatch(void);//读入双三次曲面片
	void set_point(void);//绘制整壶
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;
	virtual bool shadow_hit(const Ray& ray, float& tmin)const;
	virtual BBox get_bounding_box(void);
private:
	void DrawRim(void);//壶边
	void DrawBody(void);//壶体
	void DrawHandle(void);//壶柄
	void DrawSpout(void);//壶嘴
	void DrawLid(void);//壶盖
	void DrawBottom(void);//壶底
	void SigleCurvedPatch(void);//绘制一个双三次曲面片
public:
	int Renumber;//递归次数
	Point3D Ver[306];//茶壶总控制点
private:
	Mesh Pat[32];//茶壶总面片
	Point3D Ver3[16];//三维控制点
	CBezierPatch bezier;//bezier曲面片
	BBox bbox;
};
