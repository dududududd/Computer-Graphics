#pragma once

#include"Compound.h"
#include"Mesh.h"

class Grid:public Compound
{
public:
	Grid(void);

	Grid(Mesh* _meshptr);

	virtual ~Grid(void);

	virtual BBox get_bounding_box(void);

	void setup_cells(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray, float& tmin)const;

	void read_flat_triangles(char* file_name);

	void read_smooth_triangles(char* file_name);

	void tessellate_flat_sphere(const int horizontal_steps, const int vertical_steps);

	void tessellate_smooth_sphere(const int horizontal_steps, const int vertical_steps);

	void reverse_mesh_normals(void);

	void store_material(Material* material, const int index);

private:
	std::vector<GeometricObject*>cells;//��Ԫ�洢��һά������
	BBox bbox;//��Χ��
	int nx, ny, nz;//x��y��z����ĵ�Ԫ��

	Point3D min_coordinates(void);//������С��������
	Point3D max_coordinates(void);//���������������

	Mesh* mesh_ptr;//��������������
	bool reverse_normal;//ĳЩPLY�ļ��ķ���ָ���ڲ�

	void read_ply_file(char* file_name, const int triangle_type);

	void compute_mesh_normals(void);
};
/*
˵����
1.min_coordinates()������max_coordinates()�ֱ����ڼ���դ�����İ�Χ�е�P0���P1�㡣
����P0���P1�㲢���洢��դ������С�
2.min_coordinates()�����У�����P0����ȥһ��kEpsilonֵ��ʹդ���Դ��ڸ������Χ�еĲ�����
3.cells��ʾΪһ��NxNyNz������1D���顣
4.û��set_bounding_box��������Ϊ�߽������setup_cells�й���ġ�
*/