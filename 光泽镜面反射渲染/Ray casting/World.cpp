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
	int num_samples = 16;//完全镜面反射设置
	//int num_samples = 100;//光泽反射设置
	vp.set_samples(num_samples);
	vp.set_max_depth(19);

	//Sampler *sampler_ptr = new MultiJittered(num_samples);

	background_color = RGBColor(0.0);
	tracer_ptr = new Whitted(this);//完全镜面反射设置
	//tracer_ptr = new AreaLighting(this);//光泽反射设置

	Ambient* ambient_ptr1 = new Ambient;
	ambient_ptr1->set_color(RGBColor(0.0));
	ambient_ptr1->scale_radiance(1.0);
	ambient_ptr = ambient_ptr1;

	
	camera_ptr = new PinHole();//声明相机类型
	PinHole* pinhole_ptr = new PinHole;
	pinhole_ptr->set_eye(Point3D(7.5, 3, 9.5));
	pinhole_ptr->set_lookat(Point3D(5, 2.5, 0));
	pinhole_ptr->set_d(400.0);
	pinhole_ptr->compute_uvw();
	camera_ptr = pinhole_ptr;

	// four point lights near the ceiling
	// these don't use distance attenuation

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(10, 10, 0);
	light_ptr1->set_color(RGBColor(1.0));
	light_ptr1->scale_radiance(2.0);
	light_ptr1->shadows = true;
	add_light(light_ptr1);

	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(0, 10, 10);
	light_ptr2->set_color(RGBColor(1.0));
	light_ptr2->scale_radiance(2.0);
	light_ptr2->shadows = true;
	add_light(light_ptr2);

	PointLight* light_ptr3 = new PointLight;
	light_ptr3->set_location(-10, 10, 0);
	light_ptr3->set_color(RGBColor(1.0));
	light_ptr3->scale_radiance(2.0);
	light_ptr3->shadows = true;
	add_light(light_ptr3);

	PointLight* light_ptr4 = new PointLight;
	light_ptr4->set_location(0, 10, -10);
	light_ptr4->set_color(RGBColor(1.0));
	light_ptr4->scale_radiance(2.0);
	light_ptr4->shadows = true;
	add_light(light_ptr4);

	// sphere
	// this is the only reflective object with a direct illumination shading component

	Reflective* reflective_ptr1 = new Reflective;
	reflective_ptr1->set_ka(0.1);
	reflective_ptr1->set_kd(0.4);
	reflective_ptr1->set_cd(RGBColor(0, 0, 1));   	 // blue
	reflective_ptr1->set_ks(0.25);
	reflective_ptr1->set_exp(100.0);
	reflective_ptr1->set_kr(0.85);
	reflective_ptr1->set_cr(RGBColor(0.75, 0.75, 1));  // blue 

	Sphere*	sphere_ptr1 = new Sphere(Point3D(0, 0.5, 0), 4);
	sphere_ptr1->set_material(reflective_ptr1);
	sphere_ptr1->set_bounding_box();
	add_object(sphere_ptr1);


	// the walls, the ceiling, and the floor of the room are defined as planes
	// the shape is a cube

	double room_size = 11.0;

	// floor  (-ve yw)

	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.1);
	matte_ptr1->set_kd(0.50);
	matte_ptr1->set_cd(0.25);     // medium grey

	Plane* floor_ptr = new Plane(Point3D(0, -room_size, 0), Normal(0, 1, 0));
	floor_ptr->set_material(matte_ptr1);
	add_object(floor_ptr);


	// ceiling  (+ve yw)

	Matte* matte_ptr2 = new Matte;
	matte_ptr2->set_ka(0.35);
	matte_ptr2->set_kd(0.50);
	matte_ptr2->set_cd(white);

	Plane* ceiling_ptr = new Plane(Point3D(0, room_size, 0), Normal(0, -1, 0));
	ceiling_ptr->set_material(matte_ptr2);
	add_object(ceiling_ptr);


	// back wall  (-ve zw)

	Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.15);
	matte_ptr3->set_kd(0.60);
	matte_ptr3->set_cd(RGBColor(0.5, 0.75, 0.75));     // cyan

	Plane* backWall_ptr = new Plane(Point3D(0, 0, -room_size), Normal(0, 0, 1));
	backWall_ptr->set_material(matte_ptr3);
	add_object(backWall_ptr);

	// front wall  (+ve zw)

	Matte* matte_ptr4 = new Matte;
	matte_ptr4->set_ka(0.15);
	matte_ptr4->set_kd(0.60);
	matte_ptr4->set_cd(RGBColor(0.5, 0.75, 0.75));

	Plane* frontWall_ptr = new Plane(Point3D(0, 0, room_size), Normal(0, 0, -1));
	frontWall_ptr->set_material(matte_ptr4);
	add_object(frontWall_ptr);

	// left wall  (-ve xw)

	Matte* matte_ptr5 = new Matte;
	matte_ptr5->set_ka(0.15);
	matte_ptr5->set_kd(0.60);
	matte_ptr5->set_cd(RGBColor(0.71, 0.40, 0.20));   // orange

	Plane* leftWall_ptr = new Plane(Point3D(-room_size, 0, 0), Normal(1, 0, 0));
	leftWall_ptr->set_material(matte_ptr5);
	add_object(leftWall_ptr);

	// right wall  (+ve xw)

	Matte* matte_ptr6 = new Matte;
	matte_ptr6->set_ka(0.15);
	matte_ptr6->set_kd(0.60);
	matte_ptr6->set_cd(RGBColor(0.71, 0.40, 0.20));   // orange

	Plane* rightWall_ptr = new Plane(Point3D(room_size, 0, 0), Normal(-1, 0, 0));
	rightWall_ptr->set_material(matte_ptr6);
	add_object(rightWall_ptr);


	// mirrors on the walls
	// the right wall has no mirror

	double mirror_size = 8;  	// the mirror size
	double offset = 1.0;  // the mirror offset from the walls

	// mirror material

	Reflective* reflective_ptr2 = new Reflective;
	reflective_ptr2->set_ka(0);
	reflective_ptr2->set_kd(0);
	reflective_ptr2->set_cd(black);
	reflective_ptr2->set_ks(0);
	reflective_ptr2->set_kr(0.9);
	reflective_ptr2->set_cr(RGBColor(0.9, 1.0, 0.9));  // light green

	// glossy reflector material for the back and front mirrors

	float exp = 25000.0;
	GlossyReflector* glossy_reflector_ptr1 = new GlossyReflector;
	glossy_reflector_ptr1->set_samples(num_samples, exp);
	//glossy_reflector_ptr1->set_sampler(sampler_ptr, exp);
	glossy_reflector_ptr1->set_ka(0.0);
	glossy_reflector_ptr1->set_kd(0.0);
	glossy_reflector_ptr1->set_ks(0.0);
	glossy_reflector_ptr1->set_exp(exp);
	glossy_reflector_ptr1->set_cd(black);
	glossy_reflector_ptr1->set_kr(0.9);
	glossy_reflector_ptr1->set_exponent(exp);
	glossy_reflector_ptr1->set_cr(RGBColor(0.9, 1.0, 0.9));  // light green


	GlossyReflector* glossy_reflector_ptr2 = new GlossyReflector;
	glossy_reflector_ptr2->set_samples(num_samples, exp);
	//glossy_reflector_ptr2->set_sampler(sampler_ptr, exp);
	glossy_reflector_ptr2->set_ka(0.0);
	glossy_reflector_ptr2->set_kd(0.0);
	glossy_reflector_ptr2->set_ks(0.0);
	glossy_reflector_ptr2->set_exp(exp);
	glossy_reflector_ptr2->set_cd(black);
	glossy_reflector_ptr2->set_kr(0.9);
	glossy_reflector_ptr2->set_exponent(exp);
	glossy_reflector_ptr2->set_cr(RGBColor(0.9, 1.0, 0.9));  // light green

	// back wall mirror  (-ve zw)

	Point3D p0;
	Vector3D a, b;

	p0 = Point3D(-mirror_size, -mirror_size, -(room_size - offset));
	a = Vector3D(2.0 * mirror_size, 0, 0);
	b = Vector3D(0, 2.0 * mirror_size, 0);
	Normal n(0, 0, 1);
	CRectangle* rectangle_ptr1 = new CRectangle(p0, a, b, n);
	rectangle_ptr1->set_bounding_box();
	rectangle_ptr1->set_material(reflective_ptr2);//设置完全镜面反射
	//rectangle_ptr1->set_material(glossy_reflector_ptr1);//设置光泽反射
	add_object(rectangle_ptr1);

	Reflective* reflective_ptr3 = new Reflective;
	reflective_ptr3->set_ka(0);
	reflective_ptr3->set_kd(0);
	reflective_ptr3->set_cd(black);
	reflective_ptr3->set_ks(0);
	reflective_ptr3->set_kr(0.9);
	reflective_ptr3->set_cr(RGBColor(0.9, 1.0, 0.9));  // light green

	// front wall mirror  (+ve zw)

	p0 = Point3D(-mirror_size, -mirror_size, +(room_size - offset));
	n = Normal(0, 0, -1);
	CRectangle* rectangle_ptr2 = new CRectangle(p0, a, b, n);
	rectangle_ptr2->set_bounding_box();
	rectangle_ptr2->set_material(reflective_ptr3);//设置完全镜面反射
	//rectangle_ptr2->set_material(glossy_reflector_ptr2);//设置光泽反射
	add_object(rectangle_ptr2);


	Reflective* reflective_ptr4 = new Reflective;
	reflective_ptr4->set_ka(0);
	reflective_ptr4->set_kd(0);
	reflective_ptr4->set_cd(black);
	reflective_ptr4->set_ks(0);
	reflective_ptr4->set_kr(0.9);
	reflective_ptr4->set_cr(RGBColor(0.9, 1.0, 0.9));  // light green

	// left wall mirror  (-ve xw)

	p0 = Point3D(-(room_size - offset), -mirror_size, +mirror_size);
	a = Point3D(0, 0, -2.0 * mirror_size);
	n = Normal(1, 0, 0);
	CRectangle* rectangle_ptr3 = new CRectangle(p0, a, b, n);
	rectangle_ptr3->set_bounding_box();
	rectangle_ptr3->set_material(reflective_ptr4);
	add_object(rectangle_ptr3);


	// horizontal mirror underneath the sphere
	// this has no direct illumination and a lemon color

	Reflective* reflective_ptr5 = new Reflective;
	reflective_ptr5->set_ka(0);
	reflective_ptr5->set_kd(0);
	reflective_ptr5->set_cd(black);
	reflective_ptr5->set_ks(0);
	reflective_ptr5->set_kr(1);
	reflective_ptr5->set_cr(RGBColor(1, 1, 0.5));  // lemon

	double yw = -4.0;   // the yw location of the mirror

	p0 = Point3D(-mirror_size, yw, -mirror_size);
	a = Vector3D(0, 0, 2.0 * mirror_size);
	b = Vector3D(2.0 * mirror_size, 0, 0);
	n = Normal(0, 1, 0);
	CRectangle* rectangle_ptr4 = new CRectangle(p0, a, b, n);
	rectangle_ptr4->set_bounding_box();
	rectangle_ptr4->set_material(reflective_ptr5);
	add_object(rectangle_ptr4);
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