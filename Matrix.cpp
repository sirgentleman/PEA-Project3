#include "Matrix.h"

Matrix::Matrix()
{
	sizeX = 0;
	sizeY = 0;
	data = nullptr;
}

void Matrix::initMatrix(long long size1, long long size2)
{
	data = new int[size1 * size2];
	this->sizeX = size1;
	this->sizeY = size2;
}

Matrix::~Matrix()
{
	delete[] data;
	data = nullptr;
}

void Matrix::set_element(long long x, long long y, int value)
{
	data[(x * sizeY) + y] = value;
}

int Matrix::at_element(long long x, long long y)
{
	return data[(x * sizeY) + y];
}

int Matrix::size1()
{
	return sizeX;
}

int Matrix::size2()
{
	return sizeY;
}