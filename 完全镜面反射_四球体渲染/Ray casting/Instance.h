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
	GeometricObject* object_ptr;//Ҫ�任�Ķ���
	Matrix inv_matrix;//��任����
	bool transform_the_texture;//�Ƿ�任����
	static Matrix forward_matrix;//�任����
	BBox bbox;//�任����İ�Χ��
};
/*
˵����
1.����transform_texture()���ڽ���������任����
2.hit()��������Ϊһ���ŽӺ���������ת�����ߵľֲ����������Ҳ���������ض����Ƿ��ѱ�ת����
���⣬hit()��������ת�����߲�������һ������Զ���Ϊconst���͡�����Ҳ��һ�ֽϺõ���Ʒ�����
���hit()�����ı��˵�ǰ���ߣ�����World::hit_objects()�Լ�����Compound::hit()���޷�����������
ͬһ���߽���ȫ��������в��ԡ��ڸú�����������*��������������ط�ʽ�����㡢�������������ߡ�double���ͱ���������֮�����˼��㡣
ͬʱ��hit()������������Ƕ�׵�ʵ�������󣬴洢�������Ϊ��һ��ʵ�������󡪡�����ڽ�ģ�������ʮ�ֹؼ���
����������£�Instance::hit()��ʵ�ֵݹ���ã�ֱ������δ�任���󡣣�δ�任�����п����԰����ѱ任�������
�κ�����任��������������һ���ĵݹ���ã����ڸ����ݹ����֮ǰ����ǰ���߽��Խ����ķ�ʽʵ����任���������գ�
�任��ģ��ұ任������ࣩ���߽���δ�任��������ཻ���ԡ�
*/