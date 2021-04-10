#include "pch.h"
#include "Matrix.h"

Matrix::Matrix(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				m[i][j] = 1.0;
			else
			{
				m[i][j] = 0.0;
			}
		}
	}
}

Matrix::Matrix(const Matrix& mat)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = mat.m[i][j];
		}
	}
}

Matrix::~Matrix(void)
{

}

Matrix& Matrix::operator=(const Matrix& rhs)
{
	if (this == &rhs)
		return(*this);
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = rhs.m[i][j];
			}
		}
		return(*this);
	}
}

Matrix Matrix::operator*(const Matrix& mat)const
{
	Matrix product;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			double sum = 0.0;
			for (int k = 0; k < 4; k++)
			{
				sum += m[i][k] * mat.m[k][j];
			}
			product.m[i][j] = sum;
		}
	}
	return(product);
}

Matrix Matrix::operator/(const double d)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = m[i][j] / d;
		}
	}
	return(*this);
}

void Matrix::set_identity(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				m[i][j] = 1.0;
			else
			{
				m[i][j] = 0.0;
			}
		}
	}
}