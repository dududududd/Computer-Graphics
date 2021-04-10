#include "pch.h"
#include "Sampler.h"

double PI = 3.1415926;
const double TWO_PI = 6.2831853071795864769;

Sampler::Sampler(void)
	:num_samples(1), num_sets(83), count(0.0), jump(0)
{
	
}

Sampler::~Sampler(void)
{
	
}

void Sampler::setup_shuffled_indices(void)//混合索引
{
	shuffled_indices.reserve(num_samples*num_sets);
	std::vector<int>indices;

	for (int j = 0; j < num_samples; j++)
	{
		indices.push_back(j);
	}

	for (int p = 0; p < num_sets; p++)
	{
		random_shuffle(indices.begin(), indices.end());
		
		for (int j = 0; j < num_samples; j++)
		{
			shuffled_indices.push_back(indices[j]);
		}
	}
}

void Sampler::shuffle_samples(void)
{
	//这里要写一个洗牌算法来实现索引洗牌
}

Point2D Sampler::sample_unit_square(void)//【第六步：每执行一次，就获取容器中存储的下一个采样点值】
{
	//return(samples[count++ % (num_samples*num_sets)]);//初级版本
	
	/*if(count%num_samples==0)//中级版本

		jump=(rand()%num_sets)*num_samples;

	return(samples[jump + count++%num_samples]);*/

	if (count%num_samples == 0)//高级版本(混合索引)

		jump = (rand() % num_sets)*num_samples;

	return(samples[jump + shuffled_indices[jump + count++%num_samples]]);
}

int Sampler::get_num_samples(void)
{
	return(num_samples);
}

//当构造一个对象且需要获取圆上的采样点时，可调用map_samples_to_unit_disk()函数，而对象函数set_sampler()是合适的调用场所。
void Sampler::map_samples_to_unit_disk(void)
{
	int size = samples.size();
	float r, phi;//极坐标
	Point2D sp;//单元盘上的采样点

	//disk_samples.reserve(size);//预分配出的空间没有被初始化，所以不可访问
	disk_samples.resize(size);//所有的空间都已经初始化了，所以可以直接访问
	for (int j = 0; j < size; j++)
	{
		//将采样点映射到[-1，1]X[-1,1]

		//这里采用了一种取巧的方法，原来的samples的坐标范围为[0,1],要将其转换到[-1,1]，只需对其乘以2然后减1就行
		sp.x = 2.0*samples[j].x - 1.0;
		sp.y = 2.0*samples[j].y - 1.0;

		if (sp.x > -sp.y)//1区和2区
		{
			if (sp.x > sp.y)//1区
			{
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else//2区
			{
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else //3区和4区
		{
			if (sp.x < sp.y)//3区
			{
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else //4区
			{
				r = -sp.y;
				if (sp.y != 0.0)//避免在原点被零除
					phi = 6 - sp.x / sp.y;
				else
				{
					phi = 0.0;
				}
			}
		}
		phi *= PI / 4.0;

		disk_samples[j].x = r * cos(phi);
		disk_samples[j].y = r * sin(phi);
	}
}

Point2D Sampler::sample_unit_disk(void)
{
	if (count%num_samples == 0)//高级版本(混合索引)

		jump = (rand() % num_sets)*num_samples;

	return(disk_samples[jump + shuffled_indices[jump + count++%num_samples]]);
}

void Sampler::map_samples_to_hemisphere(const float e)
{
	int size = samples.size();
	hemisphere_samples.reserve(num_samples*num_sets);

	for (int j = 0; j < size; j++)
	{
		float cos_phi = cos(2.0*PI*samples[j].x);
		float sin_phi = sin(2.0*PI*samples[j].x);
		float cos_theta = pow((1.0 - samples[j].y), 1.0 / (e + 1.0));
		float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;

		hemisphere_samples.push_back(Point3D(pu, pv, pw));
	}
}

Point3D Sampler::sample_hemisphere(void)
{
	if (count%num_samples == 0)

		jump = (rand() % num_sets)*num_samples;

	return(hemisphere_samples[jump + shuffled_indices[jump + count++%num_samples]]);
}

void Sampler::map_samples_to_sphere(void)
{
	float r1, r2;
	float x, y, z;
	float r, phi;

	sphere_samples.reserve(num_samples*num_sets);

	for (int j = 0; j < num_samples*num_sets; j++)
	{
		r1 = samples[j].x;
		r2 = samples[j].y;
		z = 1.0 - 2.0*r1;
		r = sqrt(1.0 - z * z);
		phi = TWO_PI * r2;
		x = r * cos(phi);
		y = r * sin(phi);
		sphere_samples.push_back(Point3D(x, y, z));
	}
}

Point3D Sampler::sample_sphere(void)
{
	if (count%num_samples == 0)

		jump = (rand() % num_sets)*num_samples;

	return(sphere_samples[jump + shuffled_indices[jump + count++%num_samples]]);
}
