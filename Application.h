#pragma once
#include "Matrix.h"
#include "GeneticAlgorithm.h"
#include <string>

using namespace std;

class Application
{
	Matrix* inputMatrix;
	int townAmount;
	GeneticAlgorithm* ga;

public:

	Application();
	~Application();

	void showMenu();
	void loadTestFile(string filePath);
	void generateRandomMatrix(int townAmount);
	void printSavedMatrix();
	//void runTests(int cities, int tests);
	//double test(Algorithm* alg);
};

