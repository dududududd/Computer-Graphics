#pragma once

#include<vector>//vector����
#include"ViewPlane.h"
#include"Sphere.h"
#include"Plane.h"
#include"GeometricObject.h"
#include"Whitted.h"
#include"Maths.h"

class Light;
#include"Camera.h"
class PinHole;

#include"Instance.h"
//#include"Grid.h"
//#include"CBezierPatch.h"
#include"CTeapot.h"
#include"Box.h"
#include"SolidCylinder.h"
#include"CRectangle.h"

#include"Directional.h"
#include"PointLight.h"
#include"AmbientOccluder.h"
#include"AreaLighting.h"
#include"EnvironmentLight.h"
#include"Emissive.h"
#include"AreaLight.h"
#include"PointLight.h"

#include"Matte.h"
#include"Phong.h"
#include"GlossyReflector.h"
#include"Reflective.h"

class World
{
public:
	World(void);//Ĭ�Ϲ��캯��
	~World(void);//��������

	World(const World& _world);//�������캯��
	World& operator=(const World& _world);//��ֵ���������

	void build(void);//������ز���

	void add_object(GeometricObject* object_ptr);//�����Ⱦ����

	void add_light(Light* light_ptr);

	RGBColor max_to_one(const RGBColor& c)const;//��ɫ������1

	RGBColor clamp_to_color(const RGBColor& raw_color)const;//��ɫ������2

	ShadeRec hit_objects(const Ray& ray);//��ȡ�����ײ�������

	//void render_scene(void)const;//��ƽ��Ͷ�������Ⱦ����

	//void render_perspective(void)const;//���ڼ���һ�����ߴ�Խ��������λ��ʱ�������͸��ͼ

	void open_window(const int hres, const int vres)const;//������Ⱦ����

	void display_pixel(const int row, const int column,RGBColor& raw_color)const;//��������

public:
	ViewPlane vp;//��ƽ��
	RGBColor background_color;//������ɫ
	Tracer* tracer_ptr;//������ָ��
	std::vector<GeometricObject*>objects;//��������
	CDC* pDC;//MFC����ͼָ�� 
	static const double kHugeValue;//����Ϊ�����ֵ
	//double eye;//�Ӽ���
	//double d;//��ƽ�����
	Camera* camera_ptr;//���ָ��
	Light* ambient_ptr;
	std::vector<Light*>lights;
};
/*
˵����
1.����open_window(hres,vres)�������������ǿ���һ����Ⱦ���ڣ��������ڱ�������õ���MFC��⣬��û��ʹ�õ��ú�������������
2.�������������Ĺ���Ͷ��������Ⱦ���̣�����Ҫ˵��������ã�
��ShadeRec���������洢�������������ֵ�ġ�
�ڼ��ζ������������洢��������Ļ�����Ϣ�͹���-�����ཻ���Ժ����ġ�
�۸����������������㾭�����ഫ�ݹ����Ķ���Ĳ��ʹ��յġ�
��World���ǵ��������������࣬�佫������������ʵ��һ������ĸ��������൱��main()������
3.����δ�����ص�ļ��ζ������ͣ���������ڼ��ζ���̳в�νṹ�е�����������ͣ���ʵ���˻���hit()�����Ĺ����ӿڡ�
4.�����ͶӰ����render_perspective()ʵ�֣������������е������滻ԭrender_scene()������
5.ambient_ptr��������ָ�������Lightָ�����Ambientָ�룬����Ӧ����Ambient���͵ĸ�ֵ������
6.��World���Ĭ�Ϲ��캯���У�Ambientָ�뽫��ʼ��Ϊָ��ĳһAmbient������ǿ�ָ�롣������Ҫ��Ը����ʶ�������ka������
��Ambient����Ӧ���ڶ��������С����ս��Ϊ������Ҫ����lsʱ��ı�Ĭ����ɫʱ������build()����������Ambient���ա�
*/