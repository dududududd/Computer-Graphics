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
	std::vector<GeometricObject*>cells;//单元存储在一维数组中
	BBox bbox;//包围盒
	int nx, ny, nz;//x、y和z方向的单元数

	Point3D min_coordinates(void);//计算最小网格坐标
	Point3D max_coordinates(void);//计算最大网格坐标

	Mesh* mesh_ptr;//保存三角形数据
	bool reverse_normal;//某些PLY文件的法线指向内部

	void read_ply_file(char* file_name, const int triangle_type);

	void compute_mesh_normals(void);
};
/*
说明：
1.min_coordinates()函数和max_coordinates()分别用于计算栅格对象的包围盒的P0点和P1点。
但是P0点和P1点并不存储于栅格对象中。
2.min_coordinates()函数中，顶点P0将减去一个kEpsilon值以使栅格稍大于各对象包围盒的并集。
3.cells表示为一个NxNyNz数量的1D数组。
4.没有set_bounding_box函数，因为边界框是在setup_cells中构造的。
*/