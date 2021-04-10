#include "pch.h"
#include "Instance.h"

#include"Constants.h"
#include"World.h"


Matrix Instance::forward_matrix;//初始化静态变换矩阵

Instance::Instance(void)
	:GeometricObject(),object_ptr(nullptr),
	inv_matrix(),bbox(),transform_the_texture(true)
{
	this->forward_matrix.set_identity();//将变换矩阵初始化为单位矩阵
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

//只有在将实例放入网格时才调用此函数
//它将始终从构建函数调用
void Instance::compute_bounding_box(void)
{
	// 首先获取对象未变换的BBox

	BBox object_bbox = object_ptr->get_bounding_box();


	// 现在将仿射变换应用于长方体
	// 我们必须对原始长方体的所有8个顶点应用变换
	// 然后计算出新的最小值和最大值

	// 将八个顶点构造为三维点：

	Point3D v[8];

	v[0].x = object_bbox.x0; v[0].y = object_bbox.y0; v[0].z = object_bbox.z0;
	v[1].x = object_bbox.x1; v[1].y = object_bbox.y0; v[1].z = object_bbox.z0;
	v[2].x = object_bbox.x1; v[2].y = object_bbox.y1; v[2].z = object_bbox.z0;
	v[3].x = object_bbox.x0; v[3].y = object_bbox.y1; v[3].z = object_bbox.z0;

	v[4].x = object_bbox.x0; v[4].y = object_bbox.y0; v[4].z = object_bbox.z1;
	v[5].x = object_bbox.x1; v[5].y = object_bbox.y0; v[5].z = object_bbox.z1;
	v[6].x = object_bbox.x1; v[6].y = object_bbox.y1; v[6].z = object_bbox.z1;
	v[7].x = object_bbox.x0; v[7].y = object_bbox.y1; v[7].z = object_bbox.z1;


	// 使用前向矩阵变换这些值

	v[0] = forward_matrix * v[0];
	v[1] = forward_matrix * v[1];
	v[2] = forward_matrix * v[2];
	v[3] = forward_matrix * v[3];
	v[4] = forward_matrix * v[4];
	v[5] = forward_matrix * v[5];
	v[6] = forward_matrix * v[6];
	v[7] = forward_matrix * v[7];


	// 由于前向矩阵是一个静态变量，我们现在必须将其设置为单位矩阵
	// 这将为下一个实例对象正确设置它

	forward_matrix.set_identity();


	// 计算最小值

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

	// 计算最大值

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

	// 为包围盒指定值

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
	Matrix inv_translation_matrix;//临时逆平移矩阵

	inv_translation_matrix.m[0][3] = -trans.x;
	inv_translation_matrix.m[1][3] = -trans.y;
	inv_translation_matrix.m[2][3] = -trans.z;

	inv_matrix = inv_matrix * inv_translation_matrix;

	Matrix translation_matrix;//临时平移矩阵

	translation_matrix.m[0][3] = trans.x;
	translation_matrix.m[1][3] = trans.y;
	translation_matrix.m[2][3] = trans.z;

	forward_matrix = translation_matrix * forward_matrix;
}

void Instance::translate(const double dx, const double dy, const double dz)
{
	Matrix inv_translation_matrix;//临时逆平移矩阵

	inv_translation_matrix.m[0][3] = -dx;
	inv_translation_matrix.m[1][3] = -dy;
	inv_translation_matrix.m[2][3] = -dz;

	inv_matrix = inv_matrix * inv_translation_matrix;//后乘逆平移矩阵

	Matrix translation_matrix;//临时平移矩阵

	translation_matrix.m[0][3] = dx;
	translation_matrix.m[1][3] = dy;
	translation_matrix.m[2][3] = dz;

	forward_matrix = translation_matrix * forward_matrix;
}

void Instance::scale(const Vector3D & s)
{
	Matrix inv_scaling_matrix;//临时逆缩放矩阵

	inv_scaling_matrix.m[0][0] = 1.0 / s.x;
	inv_scaling_matrix.m[1][1] = 1.0 / s.y;
	inv_scaling_matrix.m[2][2] = 1.0 / s.z;

	inv_matrix = inv_matrix * inv_scaling_matrix;

	Matrix scaling_matrix;//临时缩放矩阵

	scaling_matrix.m[0][0] = s.x;
	scaling_matrix.m[1][1] = s.y;
	scaling_matrix.m[2][2] = s.z;

	forward_matrix = scaling_matrix * forward_matrix;
}

void Instance::scale(const double a, const double b, const double c)
{
	Matrix inv_scaling_matrix;//临时逆缩放矩阵

	inv_scaling_matrix.m[0][0] = 1.0 / a;
	inv_scaling_matrix.m[1][1] = 1.0 / b;
	inv_scaling_matrix.m[2][2] = 1.0 / c;

	inv_matrix = inv_matrix * inv_scaling_matrix;

	Matrix scaling_matrix;//临时缩放矩阵

	scaling_matrix.m[0][0] = a;
	scaling_matrix.m[1][1] = b;
	scaling_matrix.m[2][2] = c;

	forward_matrix = scaling_matrix * forward_matrix;
}

void Instance::rotate_x(const double theta)
{
	double sin_theta = sin(theta*PI_ON_180);
	double cos_theta = cos(theta*PI_ON_180);

	Matrix inv_x_rotation_matrix;//关于X轴的临时逆旋转矩阵

	inv_x_rotation_matrix.m[1][1] = cos_theta;
	inv_x_rotation_matrix.m[1][2] = sin_theta;
	inv_x_rotation_matrix.m[2][1] = -sin_theta;
	inv_x_rotation_matrix.m[2][2] = cos_theta;

	inv_matrix = inv_matrix * inv_x_rotation_matrix;

	Matrix x_rotation_matrix;//关于X轴的临时旋转矩阵

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

	Matrix inv_y_rotation_matrix;//关于Y轴的临时逆旋转矩阵	

	inv_y_rotation_matrix.m[0][0] = cos_theta;
	inv_y_rotation_matrix.m[0][2] = -sin_theta;
	inv_y_rotation_matrix.m[2][0] = sin_theta;
	inv_y_rotation_matrix.m[2][2] = cos_theta;

	inv_matrix = inv_matrix * inv_y_rotation_matrix;

	Matrix y_rotation_matrix;//关于Y轴的临时旋转矩阵	

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

	Matrix inv_z_rotation_matrix;//关于Z轴的临时逆旋转矩阵	

	inv_z_rotation_matrix.m[0][0] = cos_theta;
	inv_z_rotation_matrix.m[0][1] = sin_theta;
	inv_z_rotation_matrix.m[1][0] = -sin_theta;
	inv_z_rotation_matrix.m[1][1] = cos_theta;

	inv_matrix = inv_matrix * inv_z_rotation_matrix;

	Matrix z_rotation_matrix;//关于Z轴的临时旋转矩阵	

	z_rotation_matrix.m[0][0] = cos_theta;
	z_rotation_matrix.m[0][1] = -sin_theta;
	z_rotation_matrix.m[1][0] = sin_theta;
	z_rotation_matrix.m[1][1] = cos_theta;

	forward_matrix = z_rotation_matrix * forward_matrix;
}

void Instance::shear(const Matrix & s)
{
	Matrix inverse_shearing_matrix;//逆剪切矩阵

	//判别式

	double d = 1.0 - s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2] - s.m[2][1] * s.m[1][2]
		+ s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];

	//对角线

	inverse_shearing_matrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	inverse_shearing_matrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	inverse_shearing_matrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	inverse_shearing_matrix.m[3][3] = d;

	//第一行

	inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];

	//第二行

	inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];

	//第三行

	inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2];

	//除以判别式

	inverse_shearing_matrix = inverse_shearing_matrix / d;

	inv_matrix = inv_matrix * inverse_shearing_matrix;

	forward_matrix = s * forward_matrix;
}