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

	virtual void generate_samples(void) = 0; //�ڵ�λ����������������ͼ��

	void setup_shuffled_indices(void);//����������е�����

	void shuffle_samples(void); //���ϴ��ÿ��ģʽ�е�����

	Point2D sample_unit_square(void);//�ڵ�λ�����ϻ�ȡ��һ����Ʒ

	int get_num_samples(void);//��ò����������

	void map_samples_to_unit_disk(void);//ִ��ӳ�����(ͬ��ӳ��)

	Point2D sample_unit_disk(void);//�ڵ�λ�����ϻ�ȡ��һ����Ʒ��ͬ��ӳ�䣩

	void map_samples_to_hemisphere(const float e);//ִ��ӳ�����(���������ӳ��)

	Point3D sample_hemisphere(void);//���ذ������ϵ���һ��������(���������ӳ��)

	void map_samples_to_sphere(void);//ִ��ӳ����㣨�������ӳ�䣩

	Point3D sample_sphere(void);//���������ϵ���һ��������(�������ӳ��)

protected:
	int num_samples;//ģʽ�в��������Ŀ
	int num_sets;//�洢����������ģʽ��������
	std::vector<Point2D>samples;//��λ�������ϵĲ�����
	std::vector<int>shuffled_indices;//ϴ��������������
	std::vector<Point2D>disk_samples;//�洢�����Ĳ�����(ͬ��ӳ��)
	std::vector<Point3D>hemisphere_samples;//�洢3D�㣨���������ӳ�䣩
	std::vector<Point3D>sphere_samples;//�������ӳ��
	unsigned long count;//��ǰʹ�õĲ�������
	int jump;//���������Ծ
};
/*
˵����
1.����ض�����Ҫ�ṩ������ʱ�����ɵ���sample_unit_square����
2.sample_unit_square�����в�����%ȷ��������������λ����ȷ�Ĳ�����Χ֮�ڣ���[0,num_samples*num_sets-1]
3.sample_unit_square�����ش洢�ڲ����������е���һ��������
4.count������ӳ�˵�ǰ�������ȫ������ֵ��
5.sample_unit_square�м��汾�ڵ�һ�ε���ʱ����ʵ��������ʡ�
6.num_sets�����þ���ȥ����������������ؼ�ʹ��ͬһģʽ����Ĭ��ֵ��83��
7.������һ����������Ҫ��ȡԲ�ϵĲ�����ʱ���ɵ���map_samples_to_unit_disk�������Ҿ�����������set_sampler�����Ǻ��ʵĵ��ó�����
8.�ڹ�����ض����ڰ��������ṩ������ʱ������map_samples_to_hemisphere�������ã��һ����ڵ����������set_sampler����Ϊ���øú��������λ�á�
*/
/*
�ǣ����ڿ���ݼ����еĲ��������������ڿ����Ƿ��������ġ����ء�����Ը��֮Ϊ���ڽ����ء����������Ծ���ȷ����Ŀ�������㣬��ôͼ��ı߽�����൱������������Ҳ�ǵ��¾��������ֵ�ֱ��ԭ��
���ǣ��ڲ����У�����ϸ���ڽ����أ�����ϸ��Ϊnum_samples�����������ظ񡱣�Ȼ��Ӷԡ��������ظ񡱽�һ����ײ�������Բ�ͬ�ġ��������ظ񡱽�����ɫ���䣬������ǲ�ȡ���С��������ظ񡱽�����ɫƽ�����㡣
��Ϊ�����ջ���һ�����ء����ԣ��߽����ص���ɫ���ڲ�����ɫ�����в�ͬ�ġ�
���ڳ����е�num_sets�����ã����ǶԲ�����num_samples�����������ظ񡱽���num_sets���ظ�������Ȼ����World�����������ٴ�num_sets*num_samples����������ȡ��16��
�����ڴ�num_sets*num_samples����������ȡ16������Ȼ���п���ÿ��ȡ�õ���ͬһ�ֵ㣬���ǿ��ǵ���С�����¼������Բ����ٸ���Ŀ��ǡ�
*/
/*
˵ʵ���������������Ϸ����Ҳ�û����ȫ��⣬ϣ����������ӹ�������һ����������⡣2020-9-30
*/

