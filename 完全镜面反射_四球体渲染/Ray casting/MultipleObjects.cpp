#include "pch.h"
#include "MultipleObjects.h"

#include"World.h"

MultipleObjects::MultipleObjects(void)
	:Tracer()
{

}

MultipleObjects::MultipleObjects(World* _worldPtr)
	: Tracer(_worldPtr)
{

}

MultipleObjects::~MultipleObjects(void)
{

}

RGBColor MultipleObjects::trace_ray(const Ray& ray)const
{
	ShadeRec sr(world_ptr->hit_objects(ray));

	if (sr.hit_an_object)
		return(sr.color);
	else
	{
		return(world_ptr->background_color);//不碰取的是背景颜色
	}
}//该函数运行结束之后返回到World类之中

RGBColor MultipleObjects::trace_ray(const Ray& ray, const int depth)const
{
	ShadeRec sr(world_ptr->hit_objects(ray));

	if (sr.hit_an_object)
		return(sr.color);
	else
	{
		return(world_ptr->background_color);//不碰取的是背景颜色
	}
}//该函数运行结束之后返回到World类之中