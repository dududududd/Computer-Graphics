#pragma once

#include"GeometricObject.h"
#include"Matrix.h"

class Instance:public GeometricObject
{
public:

	Instance(void);

	Instance(GeometricObject* obj_ptr);

	Instance(const Instance& instance);

	Instance& operator=(const Instance& rhs);

	~Instance(void);

	virtual bool shadow_hit(const Ray& ray, float& t)const;

	virtual bool hit(const Ray& ray, double& t, ShadeRec& sr)const;

	void set_object(GeometricObject* obj_ptr);

	void transform_texture(const bool transform);

	virtual void compute_bounding_box(void);

	virtual BBox get_bounding_box(void);

	virtual BBox set_bounding_box(void);

	virtual Material* get_material(void)const;

	virtual void set_material(Material* material_ptr);

	void translate(const Vector3D& trans);

	void translate(const double dx, const double dy, const double dz);

	void scale(const Vector3D& s);

	void scale(const double a, const double b, const double c);

	virtual void rotate_x(const double theta);

	virtual void rotate_y(const double theta);

	virtual void rotate_z(const double theta);

	void shear(const Matrix& s);

private:
	GeometricObject* object_ptr;//要变换的对象
	Matrix inv_matrix;//逆变换矩阵
	bool transform_the_texture;//是否变换纹理
	static Matrix forward_matrix;//变换矩阵
	BBox bbox;//变换对象的包围盒
};
/*
说明：
1.函数transform_texture()用于将纹理绑定至变换对象
2.hit()函数可视为一类桥接函数，用于转换光线的局部副本对象且并不测试相关对象是否已被转换。
另外，hit()函数并不转换光线参数，这一类参数皆定义为const类型——这也是一种较好的设计方案。
如果hit()函数改变了当前光线，函数World::hit_objects()以及函数Compound::hit()将无法正常工作，
同一光线将于全部对象进行测试。在该函数中体现了*运算符的四种重载方式：顶点、方向向量、法线、double类型变量与向量之间的左乘计算。
同时，hit()函数还适用于嵌套的实例化对象，存储对象可以为另一个实例化对象——这对于建模的灵活性十分关键。
在这种情况下，Instance::hit()将实现递归调用，直至发现未变换对象。（未变换对象中可能仍包含已变换的组件，
任何组件变换操作均会引发新一级的递归调用）。在各级递归调用之前，当前光线将以渐进的方式实现逆变换操作。最终，
变换后的（且变换次数最多）光线将与未变换对象进行相交测试。
*/