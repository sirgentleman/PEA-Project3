#pragma once
#include <vector>
#include "Matrix.h"

using namespace std;

struct Solution {
	vector<int> path;
	int cost;
};

class GeneticAlgorithm
{
	Matrix* townMatrix;
	int townAmount;
	int stopTime;
	int populationSize;
	double pc;
	double pm;
	Solution* bestSolution;

	//
	int getCostFromPath(vector<int> path);
	Solution randomizeSolution();
	vector<Solution> createStartPopulation();
	vector<Solution> getBreedPopulation(vector<Solution> population);
	vector<Solution> crossover(vector<Solution> breedPopulation);
	vector<Solution> crossoverOX(Solution parent1, Solution parent2);
	vector<Solution> mutate(vector<Solution> newPopulation);
	Solution mutateSwap(Solution solution);
	Solution mutateInsert(Solution solution);
	vector<Solution> getNewPopulation(vector<Solution> oldPopulation, vector<Solution> newPopulation);

public:
	GeneticAlgorithm(Matrix* inputMatrix, int townAmount);
	~GeneticAlgorithm();
	void start();

	void printSolution();
	void setStopTime(int timeSec);


};

