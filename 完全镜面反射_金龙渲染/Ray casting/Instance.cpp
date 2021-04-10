#include "pch.h"
#include "Instance.h"

#include"Constants.h"
#include"World.h"


Matrix Instance::forward_matrix;//��ʼ����̬�任����

Instance::Instance(void)
	:GeometricObject(),object_ptr(nullptr),
	inv_matrix(),bbox(),transform_the_texture(true)
{
	this->forward_matrix.set_identity();//���任�����ʼ��Ϊ��λ����
}

Instance::Instance(GeometricObject * obj_ptr)
	:GeometricObject(),object_ptr(obj_ptr),
	inv_matrix(),/*bbox(),*/transform_the_texture(true)
{
	this->forward_matrix.set_identity();
	bbox = get_bounding_box();
}

Instance::Instance(const Instance & instance)
	:GeometricObject(instance),inv_matrix(instance.inv_matrix),
	transform_the_texture(instance.transform_the_texture)
{

}

Instance & Instance::operator=(const Instance & rhs)
{
	if (this == &rhs)
		return(*this);
	else
	{
		this->object_ptr = rhs.object_ptr;
		this->inv_matrix = rhs.inv_matrix;
		this->transform_the_texture = rhs.transform_the_texture;
		this->bbox = rhs.bbox;
	}

}

Instance::~Instance(void)
{
	if (object_ptr)
	{
		delete object_ptr;
		object_ptr = nullptr;
	}
}

bool Instance::shadow_hit(const Ray & ray, float & t) const
{
	Ray inv_ray(ray);
	inv_ray.o = inv_matrix * inv_ray.o;
	inv_ray.d = inv_matrix * inv_ray.d;

	if (object_ptr->shadow_hit(inv_ray, t))
	{
		return(true);
	}
	return(false);
}

bool Instance::hit(const Ray & ray, double & t, ShadeRec & sr) const
{
	Ray inv_ray(ray);
	inv_ray.o = inv_matrix * inv_ray.o;
	inv_ray.d = inv_matrix * inv_ray.d;

	if (object_ptr->hit(inv_ray, t, sr))
	{
		sr.normal = inv_matrix * sr.normal;
		sr.normal.Normalize();

		if (object_ptr->get_material())
		{
			material = object_ptr->get_material();
		}

		if (!transform_the_texture)
		{
			sr.local_hit_point = ray.o + t * ray.d;
		}

		return(true);
	}
	return(false);
}

void Instance::set_object(GeometricObject * obj_ptr)
{
	this->object_ptr = obj_ptr;
}

void Instance::transform_texture(const bool transform)
{
	this->transform_the_texture = transform;
}

//ֻ���ڽ�ʵ����������ʱ�ŵ��ô˺���
//����ʼ�մӹ�����������
void Instance::compute_bounding_box(void)
{
	// ���Ȼ�ȡ����δ�任��BBox

	BBox object_bbox = object_ptr->get_bounding_box();


	// ���ڽ�����任Ӧ���ڳ�����
	// ���Ǳ����ԭʼ�����������8������Ӧ�ñ任
	// Ȼ�������µ���Сֵ�����ֵ

	// ���˸����㹹��Ϊ��ά�㣺

	Point3D v[8];

	v[0].x = object_bbox.x0; v[0].y = object_bbox.y0; v[0].z = object_bbox.z0;
	v[1].x = object_bbox.x1; v[1].y = object_bbox.y0; v[1].z = object_bbox.z0;
	v[2].x = object_bbox.x1; v[2].y = object_bbox.y1; v[2].z = object_bbox.z0;
	v[3].x = object_bbox.x0; v[3].y = object_bbox.y1; v[3].z = object_bbox.z0;

	v[4].x = object_bbox.x0; v[4].y = object_bbox.y0; v[4].z = object_bbox.z1;
	v[5].x = object_bbox.x1; v[5].y = object_bbox.y0; v[5].z = object_bbox.z1;
	v[6].x = object_bbox.x1; v[6].y = object_bbox.y1; v[6].z = object_bbox.z1;
	v[7].x = object_bbox.x0; v[7].y = object_bbox.y1; v[7].z = object_bbox.z1;


	// ʹ��ǰ�����任��Щֵ

	v[0] = forward_matrix * v[0];
	v[1] = forward_matrix * v[1];
	v[2] = forward_matrix * v[2];
	v[3] = forward_matrix * v[3];
	v[4] = forward_matrix * v[4];
	v[5] = forward_matrix * v[5];
	v[6] = forward_matrix * v[6];
	v[7] = forward_matrix * v[7];


	// ����ǰ�������һ����̬�������������ڱ��뽫������Ϊ��λ����
	// �⽫Ϊ��һ��ʵ��������ȷ������

	forward_matrix.set_identity();


	// ������Сֵ

	float x0 = kHugeValue;
	float y0 = kHugeValue;
	float z0 = kHugeValue;

	for (int j = 0; j <= 7; j++) {
		if (v[j].x < x0)
			x0 = v[j].x;
	}

	for (int j = 0; j <= 7; j++) {
		if (v[j].y < y0)
			y0 = v[j].y;
	}

	for (int j = 0; j <= 7; j++) {
		if (v[j].z < z0)
			z0 = v[j].z;
	}

	// �������ֵ

	float x1 = -kHugeValue;
	float y1 = -kHugeValue;
	float z1 = -kHugeValue;

	for (int j = 0; j <= 7; j++) {
		if (v[j].x > x1)
			x1 = v[j].x;
	}

	for (int j = 0; j <= 7; j++) {
		if (v[j].y > y1)
			y1 = v[j].y;
	}

	for (int j = 0; j <= 7; j++) {
		if (v[j].z > z1)
			z1 = v[j].z;
	}

	// Ϊ��Χ��ָ��ֵ

	bbox.x0 = x0;
	bbox.y0 = y0;
	bbox.z0 = z0;
	bbox.x1 = x1;
	bbox.y1 = y1;
	bbox.z1 = z1;
}

BBox Instance::get_bounding_box(void)
{
	return (this->bbox);
}

BBox Instance::set_bounding_box(void)
{
	compute_bounding_box();
	return(get_bounding_box());
}

Material * Instance::get_material(void) const
{
	return(material);
}

void Instance::set_material(Material * material_ptr)
{
	this->material = material_ptr;
}

void Instance::translate(const Vector3D & trans)
{
	Matrix inv_translation_matrix;//��ʱ��ƽ�ƾ���

	inv_translation_matrix.m[0][3] = -trans.x;
	inv_translation_matrix.m[1][3] = -trans.y;
	inv_translation_matrix.m[2][3] = -trans.z;

	inv_matrix = inv_matrix * inv_translation_matrix;

	Matrix translation_matrix;//��ʱƽ�ƾ���

	translation_matrix.m[0][3] = trans.x;
	translation_matrix.m[1][3] = trans.y;
	translation_matrix.m[2][3] = trans.z;

	forward_matrix = translation_matrix * forward_matrix;
}

void Instance::translate(const double dx, const double dy, const double dz)
{
	Matrix inv_translation_matrix;//��ʱ��ƽ�ƾ���

	inv_translation_matrix.m[0][3] = -dx;
	inv_translation_matrix.m[1][3] = -dy;
	inv_translation_matrix.m[2][3] = -dz;

	inv_matrix = inv_matrix * inv_translation_matrix;//�����ƽ�ƾ���

	Matrix translation_matrix;//��ʱƽ�ƾ���

	translation_matrix.m[0][3] = dx;
	translation_matrix.m[1][3] = dy;
	translation_matrix.m[2][3] = dz;

	forward_matrix = translation_matrix * forward_matrix;
}

void Instance::scale(const Vector3D & s)
{
	Matrix inv_scaling_matrix;//��ʱ�����ž���

	inv_scaling_matrix.m[0][0] = 1.0 / s.x;
	inv_scaling_matrix.m[1][1] = 1.0 / s.y;
	inv_scaling_matrix.m[2][2] = 1.0 / s.z;

	inv_matrix = inv_matrix * inv_scaling_matrix;

	Matrix scaling_matrix;//��ʱ���ž���

	scaling_matrix.m[0][0] = s.x;
	scaling_matrix.m[1][1] = s.y;
	scaling_matrix.m[2][2] = s.z;

	forward_matrix = scaling_matrix * forward_matrix;
}

void Instance::scale(const double a, const double b, const double c)
{
	Matrix inv_scaling_matrix;//��ʱ�����ž���

	inv_scaling_matrix.m[0][0] = 1.0 / a;
	inv_scaling_matrix.m[1][1] = 1.0 / b;
	inv_scaling_matrix.m[2][2] = 1.0 / c;

	inv_matrix = inv_matrix * inv_scaling_matrix;

	Matrix scaling_matrix;//��ʱ���ž���

	scaling_matrix.m[0][0] = a;
	scaling_matrix.m[1][1] = b;
	scaling_matrix.m[2][2] = c;

	forward_matrix = scaling_matrix * forward_matrix;
}

void Instance::rotate_x(const double theta)
{
	double sin_theta = sin(theta*PI_ON_180);
	double cos_theta = cos(theta*PI_ON_180);

	Matrix inv_x_rotation_matrix;//����X�����ʱ����ת����

	inv_x_rotation_matrix.m[1][1] = cos_theta;
	inv_x_rotation_matrix.m[1][2] = sin_theta;
	inv_x_rotation_matrix.m[2][1] = -sin_theta;
	inv_x_rotation_matrix.m[2][2] = cos_theta;

	inv_matrix = inv_matrix * inv_x_rotation_matrix;

	Matrix x_rotation_matrix;//����X�����ʱ��ת����

	x_rotation_matrix.m[1][1] = cos_theta;
	x_rotation_matrix.m[1][2] = -sin_theta;
	x_rotation_matrix.m[2][1] = sin_theta;
	x_rotation_matrix.m[2][2] = cos_theta;

	forward_matrix = x_rotation_matrix * forward_matrix;
}

void Instance::rotate_y(const double theta)
{
	double sin_theta = sin(theta * PI / 180.0);
	double cos_theta = cos(theta * PI / 180.0);

	Matrix inv_y_rotation_matrix;//����Y�����ʱ����ת����	

	inv_y_rotation_matrix.m[0][0] = cos_theta;
	inv_y_rotation_matrix.m[0][2] = -sin_theta;
	inv_y_rotation_matrix.m[2][0] = sin_theta;
	inv_y_rotation_matrix.m[2][2] = cos_theta;

	inv_matrix = inv_matrix * inv_y_rotation_matrix;

	Matrix y_rotation_matrix;//����Y�����ʱ��ת����	

	y_rotation_matrix.m[0][0] = cos_theta;
	y_rotation_matrix.m[0][2] = sin_theta;
	y_rotation_matrix.m[2][0] = -sin_theta;
	y_rotation_matrix.m[2][2] = cos_theta;

	forward_matrix = y_rotation_matrix * forward_matrix;
}

void Instance::rotate_z(const double theta)
{
	double sin_theta = sin(theta * PI / 180.0);
	double cos_theta = cos(theta * PI / 180.0);

	Matrix inv_z_rotation_matrix;//����Z�����ʱ����ת����	

	inv_z_rotation_matrix.m[0][0] = cos_theta;
	inv_z_rotation_matrix.m[0][1] = sin_theta;
	inv_z_rotation_matrix.m[1][0] = -sin_theta;
	inv_z_rotation_matrix.m[1][1] = cos_theta;

	inv_matrix = inv_matrix * inv_z_rotation_matrix;

	Matrix z_rotation_matrix;//����Z�����ʱ��ת����	

	z_rotation_matrix.m[0][0] = cos_theta;
	z_rotation_matrix.m[0][1] = -sin_theta;
	z_rotation_matrix.m[1][0] = sin_theta;
	z_rotation_matrix.m[1][1] = cos_theta;

	forward_matrix = z_rotation_matrix * forward_matrix;
}

void Instance::shear(const Matrix & s)
{
	Matrix inverse_shearing_matrix;//����о���

	//�б�ʽ

	double d = 1.0 - s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2] - s.m[2][1] * s.m[1][2]
		+ s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];

	//�Խ���

	inverse_shearing_matrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	inverse_shearing_matrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	inverse_shearing_matrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	inverse_shearing_matrix.m[3][3] = d;

	//��һ��

	inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];

	//�ڶ���

	inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];

	//������

	inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2];

	//�����б�ʽ

	inverse_shearing_matrix = inverse_shearing_matrix / d;

	inv_matrix = inv_matrix * inverse_shearing_matrix;

	forward_matrix = s * forward_matrix;
}