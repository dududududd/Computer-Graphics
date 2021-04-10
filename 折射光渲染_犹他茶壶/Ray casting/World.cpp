#include "pch.h"
#include "World.h"

#include"PinHole.h"
#include"Ambient.h"
#include"PointLight.h"

const double World::kHugeValue = 1.0E10;

World::World(void)
	:vp(), background_color(0.0), tracer_ptr(nullptr),
	camera_ptr(nullptr),ambient_ptr(nullptr)/*,eye(0.0),d(0.0)*/
{

}

World::~World(void)
{
	int object_length = objects.size();
	for (int i = 0; i < object_length ; i++)
	{
		if (objects[i]->material != nullptr)
		{
			delete objects[i]->material;
			objects[i]->material = nullptr;
		}
		if (objects[i])
		{
			delete objects[i];
			objects[i] = nullptr;
		}
	}
	objects.erase(objects.begin(), objects.end());

	int lights_length = lights.size();
	for (int i = 0; i < lights_length; ++i)
	{
		delete lights[i];
		lights[i] = nullptr;
	}
	lights.erase(lights.begin(), lights.end());

	delete camera_ptr; camera_ptr = nullptr;
	delete ambient_ptr; ambient_ptr = nullptr;
	delete tracer_ptr; tracer_ptr = nullptr;
	delete vp.sampler_ptr;//视平面
}

World::World(const World& _world)
	:vp(_world.vp), background_color(_world.background_color),
	tracer_ptr(_world.tracer_ptr), pDC(_world.pDC),
	camera_ptr(_world.camera_ptr),ambient_ptr(_world.ambient_ptr)
	/*,eye(_world.eye),d(_world.d)*/
{

}

World& World::operator=(const World& _world)
{
	if (this == &_world)
		return(*this);
	else
	{
		this->vp = _world.vp;
		this->background_color = _world.background_color;
		this->tracer_ptr = _world.tracer_ptr;
		this->pDC = _world.pDC;
		this->camera_ptr = _world.camera_ptr;
		this->ambient_ptr = _world.ambient_ptr;
		/*this->eye = _world.eye;
		this->d = _world.d;*/
		return(*this);
	}
}

void World::build(void)
{
	/*vp.set_hres(400);
	vp.set_vres(400);*/
	vp.set_pixel_size(1.0);
	int num_samples = 16;
	//int num_samples = 4;
	vp.set_samples(num_samples);
	vp.set_max_depth(4);
	
	//background_color = RGBColor(0.0, 0.3, 0.25);
	background_color = RGBColor(0.3, 0.75, 0.65);

	tracer_ptr = new Whitted(this);

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->set_color(RGBColor(1.0));
	//ambient_ptr->scale_radiance(0.25);
	ambient_ptr->scale_radiance(0.75);
	this->ambient_ptr = ambient_ptr;

	camera_ptr = new PinHole();//声明相机类型
	PinHole* pinhole_ptr = new PinHole;
	pinhole_ptr->set_eye(Point3D(-5, 7.5, 35));
	pinhole_ptr->set_lookat(Point3D(1.25, 3.5, 0));
	//pinhole_ptr->set_d(2400.0);
	pinhole_ptr->set_d(800.0);
	pinhole_ptr->compute_uvw();
	camera_ptr = pinhole_ptr;

	
	// point light 

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(40, 50, 0);
	light_ptr1->set_color(RGBColor(1.0));
	light_ptr1->scale_radiance(1.5);
	light_ptr1->shadows = true;
	add_light(light_ptr1);


	// point light 

	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-10, 20, 10);
	light_ptr2->set_color(RGBColor(1.0));
	light_ptr2->scale_radiance(1.5);
	light_ptr2->shadows = true;
	add_light(light_ptr2);


	// directional light 

	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(Vector3D(-1, 0, 0));
	light_ptr3->set_color(RGBColor(1.0));
	light_ptr3->scale_radiance(1.5);
	light_ptr3->shadows = true;
	add_light(light_ptr3);


	// transparent bunny

	Transparent* glass_ptr = new Transparent;
	glass_ptr->set_ks(0.2);
	glass_ptr->set_exp(2000.0);
	glass_ptr->set_ior(1.5);
	glass_ptr->set_kr(0.1);
	glass_ptr->set_kt(0.9);

	CTeapot* teapot_ptr = new CTeapot;
	teapot_ptr->SetRecursiveNumber(3);
	teapot_ptr->set_bounding_box();
	teapot_ptr->set_material(glass_ptr);
	teapot_ptr->set_point();

	Instance* instance_ptr = new Instance();//实例化茶壶对象并实施仿射变换
	instance_ptr->set_object(teapot_ptr);
	instance_ptr->scale(2);
	instance_ptr->rotate_y(0);
	add_object(instance_ptr);


	// red sphere

	Reflective*	reflective_ptr = new Reflective;
	reflective_ptr->set_ka(0.3);
	reflective_ptr->set_kd(0.3);
	reflective_ptr->set_cd(red);
	reflective_ptr->set_ks(0.2);
	reflective_ptr->set_exp(2000.0);
	reflective_ptr->set_kr(0.25);

	//Sphere* sphere_ptr1 = new Sphere(Point3D(4, 4, -6), 3);
	Sphere* sphere_ptr1 = new Sphere(Point3D(4, 4, -6), 3);
	sphere_ptr1->set_material(reflective_ptr);
	sphere_ptr1->set_bounding_box();
	add_object(sphere_ptr1);

	Reflective*	reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.3);
	reflective_ptr1->set_kd(0.3);
	reflective_ptr1->set_cd(green);
	reflective_ptr1->set_ks(0.2);
	reflective_ptr1->set_exp(2000.0);
	reflective_ptr1->set_kr(0.25);

	Sphere* sphere_ptr2 = new Sphere(Point3D(-4, 4, -6), 3);
	sphere_ptr2->set_material(reflective_ptr1);
	sphere_ptr2->set_bounding_box();
	add_object(sphere_ptr2);

	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.8);
	matte_ptr->set_kd(0.85);
	matte_ptr->set_cd(RGBColor(0.0, 1.0, 1.0));

	Reflective*	reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(0.8);
	reflective_ptr2->set_kd(0.85);
	reflective_ptr2->set_cd(RGBColor(0.45, 0.45, 0.45));
	reflective_ptr2->set_ks(0.2);
	reflective_ptr2->set_exp(2000.0);
	reflective_ptr2->set_kr(0.25);

	// rectangle

	Point3D p0(-20, 0, -100);
	Vector3D a(0, 0, 120);
	Vector3D b(40, 0, 0);

	CRectangle* rectangle_ptr = new CRectangle(p0, a, b);
	rectangle_ptr->set_material(reflective_ptr2);
	rectangle_ptr->set_bounding_box();
	add_object(rectangle_ptr);
}

void World::add_object(GeometricObject* object_ptr)//将对象压入容器中
{
	objects.push_back(object_ptr);
}

void World::add_light(Light* light_ptr)//将光源指针压入容器中
{
	lights.push_back(light_ptr);
}

RGBColor World::max_to_one(const RGBColor & c) const
{
	double max_value = Max(c.r, Max(c.g, c.b));

	if (max_value > 1.0)
		return(c / max_value);
	else
	{
		return(c);
	}
}

RGBColor World::clamp_to_color(const RGBColor & raw_color) const
{
	RGBColor c(raw_color);

	//if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0)
	//{
	//	c.r = 1.0;
	//	c.g = 0.0;
	//	c.b = 0.0;
	//}
	c.r = raw_color.r > 1.0 ? 1.0 : raw_color.r;
	c.g = raw_color.g > 1.0 ? 1.0 : raw_color.g;
	c.b = raw_color.b > 1.0 ? 1.0 : raw_color.b;

	return(c);
}

//ShadeRec World::hit_objects(const Ray& ray)
//{
//	ShadeRec sr(*this);//初始化物体属性
//	double t;
//	double tmin = kHugeValue;
//	int num_objects = objects.size();
//
//	for (int j = 0; j < num_objects; j++)//这里会对碰撞对象进行检测，会取得光线-对象相交测试中的最近碰撞点
//	{
//		if (objects[j]->hit(ray, t, sr) && (t < tmin))//默认是无穷大
//		{
//			sr.hit_an_object = true;//给光线相交测试判断为已发生碰撞
//			tmin = t;
//			sr.color = objects[j]->get_color();//获取与光线碰撞的物体的颜色。
//		}
//	}
//	return(sr);//更新击中的物体的属性
//}//函数运行结束返回到MultipleObjects里面

ShadeRec World::hit_objects(const Ray& ray)
{
	ShadeRec sr(*this);
	double t;
	Normal normal;
	Point3D local_hit_point;
	float tmin = kHugeValue;
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
	{
		if (objects[j]->hit(ray, t, sr) && (t < tmin))
		{
			sr.hit_an_object = true;
			tmin = t;
			sr.material_ptr = objects[j]->get_material();
			sr.hit_point = ray.o + t * ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	}
	if (sr.hit_an_object)
	{
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	return(sr);
}

//void World::render_scene(void)const//这里适用于各类的采样计算
//{
//	RGBColor pixel_color;
//	Ray ray;
//	double zw = 100.0;
//	Point2D sp;//采样点，单位为[0,1]x[0,1]
//	Point2D pp;//像素上的采样点
//
//	open_window(vp.hres, vp.vres);
//	ray.d = Vector3D(0.0, 0.0, -1.0);
//
//	for (int r = 0; r < vp.vres; r++)
//	{
//		for (int c = 0; c < vp.hres; c++)
//		{
//			pixel_color = RGBColor(0.0);
//
//			for (int j = 0; j < vp.num_samples; j++)//每循环一次调用一次sample_unit_square
//			{
//				sp = vp.sampler_ptr->sample_unit_square();//【第五步：使用采样器类指针调用其继承结构中的共有函数sample_unit_square()】
//				pp.x = vp.s*(c - 0.5*vp.hres + sp.x);
//				pp.y = vp.s*(r - 0.5*vp.vres + sp.y);
//				ray.o = Point3D(pp.x, pp.y, zw);
//				pixel_color += tracer_ptr->trace_ray(ray);
//			}
//			pixel_color /= vp.num_samples;//颜色的平均值
//			display_pixel(r, c, pixel_color);
//		}
//	}
//}

/*void World::render_perspective(void)const
{
	RGBColor pixel_color;
	Ray ray;

	open_window(vp.hres, vp.vres);
	ray.o = Point3D(0.0, 0.0, eye);

	for (int r = 0; r < vp.vres; r++)
	{
		for (int c = 0; c < vp.hres; c++)
		{
			ray.d = Vector3D(vp.s*(c - 0.5*(vp.hres - 1.0)), vp.s*(r - 0.5*(vp.vres - 1.0)), -d);
			ray.d.Normalize();
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}
	}
}*/

void World::open_window(const int hres, const int vres)const
{

}

void World::display_pixel(const int row, const int column,RGBColor& raw_color)const
{
	
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)//这里的show_out_of_gamut是用来选择色阶映射算子模式的
		mapped_color = clamp_to_color(raw_color);
	else
	{
		mapped_color = max_to_one(raw_color);
	}
	
	if (vp.gamma != 1.0)
	{
		mapped_color = mapped_color.powc(vp.inv_gamma);
	}

	RGBColor color = 255 * mapped_color;
	pDC->SetPixel(row, column, RGB(color.r, color.g, color.b));
}