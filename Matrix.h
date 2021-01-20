#pragma once
#include <algorithm>

/*
	Klasa pomocnicza wykorzystywana do tworzeniad dwuwymiarowej tablicy
*/
class Matrix
{
	int* data;
	long long sizeX;
	long long sizeY;
public:
	Matrix();
	~Matrix();

	void initMatrix(long long size1, long long size2);
	void set_element(long long x, long long y, int value);
	int at_element(long long x, long long y);
	int size1();
	int size2();

};

