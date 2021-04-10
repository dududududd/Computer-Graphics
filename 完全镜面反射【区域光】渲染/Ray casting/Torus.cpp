#include "pch.h"
#include "Torus.h"

#include"Maths.h"
#include"World.h"

Torus::Torus(void)
	:GeometricObject(),
	a(2.0), b(0.5), bbox(-a - b, a + b, -b, b, -a - b, a + b)
{

}

Torus::Torus(const double _a, const double _b)
	:GeometricObject(),
	a(_a), b(_b), bbox(-a - b, a + b, -b, b, -a - b, a + b)
{
}

Torus::~Torus(void)
{

}

Normal Torus::compute_normal(const Point3D & p) const
{
	Normal normal;
	double param_squared = a * a + b * b;

	double x = p.x;
	double y = p.y;
	double z = p.z;
	double sum_squared = x * x + y * y + z * z;

	normal.x = 4.0 * x * (sum_squared - param_squared);
	normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
	normal.z = 4.0 * z * (sum_squared - param_squared);
	normal.Normalize();

	return (normal);
}

bool Torus::hit(const Ray & ray, double & tmin, ShadeRec & sr) const
{
	if (!bbox.hit(ray))
		return (false);

	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;

	double coeffs[5];	// 四次方程的系数阵
	double roots[4];	// 四次方程的解列

	// 定义四次方程的系数

	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd = 4.0 * a * a;

	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// 常数项
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// t^4系数

	// 求四次方程的根

	int num_real_roots = SolveQuartic(coeffs, roots);

	bool	intersected = false;
	double 	t = kHugeValue;

	if (num_real_roots == 0)  // 光线没有击中圆环
		return(false);

	// 如果有的话，找出比kEpsilon大的最小根 
	// 根数组未排序

	for (int j = 0; j < num_real_roots; j++)
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t)
				t = roots[j];
		}

	if (!intersected)
		return (false);

	tmin = t;
	sr.local_hit_point = ray.o + t * ray.d;
	sr.normal = compute_normal(sr.local_hit_point);

	return (true);
}