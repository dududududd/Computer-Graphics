#pragma once

#include"Point2D.h"
#include"Point3D.h"
#include<vector>
#include<algorithm>

class Sampler
{
public:
	Sampler(void);

	virtual~Sampler(void);

	virtual void generate_samples(void) = 0; //在单位正方形中生成样本图案

	void setup_shuffled_indices(void);//设置随机排列的索引

	void shuffle_samples(void); //随机洗牌每个模式中的样本

	Point2D sample_unit_square(void);//在单位方格上获取下一个样品

	int get_num_samples(void);//获得采样点的数量

	void map_samples_to_unit_disk(void);//执行映射计算(同心映射)

	Point2D sample_unit_disk(void);//在单位方格上获取下一个样品（同心映射）

	void map_samples_to_hemisphere(const float e);//执行映射计算(半球体采样映射)

	Point3D sample_hemisphere(void);//返回半球体上的下一个采样点(半球体采样映射)

	void map_samples_to_sphere(void);//执行映射计算（球体采样映射）

	Point3D sample_sphere(void);//返回球体上的下一个采样点(球体采样映射)

protected:
	int num_samples;//模式中采样点的数目
	int num_sets;//存储的样本集（模式）的数量
	std::vector<Point2D>samples;//单位正方形上的采样点
	std::vector<int>shuffled_indices;//洗牌样本数组索引
	std::vector<Point2D>disk_samples;//存储新增的采样点(同心映射)
	std::vector<Point3D>hemisphere_samples;//存储3D点（半球体采样映射）
	std::vector<Point3D>sphere_samples;//球体采样映射
	unsigned long count;//当前使用的采样点数
	int jump;//随机索引跳跃
};
/*
说明：
1.当相关对象需要提供采样点时，即可调用sample_unit_square函数
2.sample_unit_square函数中操作符%确保数组索引总是位于正确的操作范围之内，即[0,num_samples*num_sets-1]
3.sample_unit_square将返回存储于采样器对象中的下一个采样点
4.count变量反映了当前采样点的全部数量值。
5.sample_unit_square中级版本在第一次调用时即可实现随机访问。
6.num_sets的作用就是去避免各行中相邻像素间使用同一模式，其默认值是83。
7.当构造一个对象且需要获取圆上的采样点时，可调用map_samples_to_unit_disk函数，且景深代码里面的set_sampler（）是合适的调用场所。
8.在构造相关对象并在半球体上提供采样点时，函数map_samples_to_hemisphere将被调用，且环境遮挡代码里面的set_sampler函数为调用该函数的最佳位置。
*/
/*
记：关于抗锯齿技术中的采样技术，其是在考虑是否击中物体的“像素”，我愿称之为“邻界像素”。当我们以绝对确定的目光来计算，那么图像的边界会是相当清晰分明，这也是导致锯齿现象出现的直接原因。
但是，在采样中，我们细化邻界像素，将其细化为num_samples个“理论像素格”，然后从对“理论像素格”进一步碰撞分析，对不同的“理论像素格”进行颜色分配，最后我们采取所有“理论像素格”进行颜色平均计算。
因为其最终还是一个像素。所以，边界像素的颜色与内部的颜色是略有不同的。
对于程序中的num_sets的作用，其是对产生的num_samples个“理论像素格”进行num_sets次重复采样，然后在World函数中我们再从num_sets*num_samples个采样点中取出16个
，关于从num_sets*num_samples个采样点中取16个，虽然是有可能每次取得的是同一种点，但是考虑到是小概率事件，所以不用再更深的考虑。
*/
/*
说实话，这里的索引混合方法我并没有完全理解，希望到后面添加光泽反射后我会回来重新理解。2020-9-30
*/

