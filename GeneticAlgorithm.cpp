#include "GeneticAlgorithm.h"
#include <random>
#include <time.h>
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(Matrix* inputMatrix, int townAmount)
{
	townMatrix = inputMatrix;
	this->townAmount = townAmount;
	stopTime = 120;
	populationSize = 400;
	pc = 0.7;
	pm = 0.01;
	bestSolution = new Solution();
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	townMatrix = nullptr;
	bestSolution = nullptr;
}

int GeneticAlgorithm::getCostFromPath(vector<int> path)
{
	int finalCost = 0;
	int previousCity = 0;
	for (int iii = 0; iii < path.size(); iii++) {
		finalCost += townMatrix->at_element(previousCity, path.at(iii));
		previousCity = path.at(iii);
	}
	finalCost += townMatrix->at_element(previousCity, 0);

	return finalCost;
}

Solution GeneticAlgorithm::randomizeSolution()
{
	bool* isVisited = new bool[townAmount];
	Solution solution;
	for (int iii = 0; iii < townAmount - 1; iii++)
		isVisited[iii] = false;

	for (int iii = 0; iii < townAmount - 1; iii++)
	{
		int index;
		do
		{
			index = (rand() % (townAmount - 1)) + 1;
		} while (isVisited[index] == true);

		solution.path.push_back(index);
		isVisited[index] = true;
	}
	solution.cost = this->getCostFromPath(solution.path);

	delete[] isVisited;
	return solution;
}

vector<Solution> GeneticAlgorithm::createStartPopulation()
{
	//cerr << "createStartPopulation\n";
	vector<Solution> population;
	for (int iii = 0; iii < populationSize; iii++) {
		population.push_back(this->randomizeSolution());
	}

	return population;
}

vector<Solution> GeneticAlgorithm::getBreedPopulation(vector<Solution> population)
{
	//cerr << "getBreedPopulation\n";
	vector<Solution> breedPopulation;
	bool* isChosen = new bool[populationSize];
	for (int iii = 0; iii < populationSize; iii++)
		isChosen[iii] = false;

	for (int iii = 0; iii < populationSize / 2; iii++) {

		int parentIndex1;
		do
		{
			parentIndex1 = rand() % populationSize;
		} while (isChosen[parentIndex1] != false);

		int parentIndex2;
		do
		{
			parentIndex2 = rand() % populationSize;
		} while (isChosen[parentIndex2] != false || parentIndex1 == parentIndex2);

		if (population.at(parentIndex1).cost < population.at(parentIndex2).cost) {
			breedPopulation.push_back(population.at(parentIndex1));
			isChosen[parentIndex1] = true;
		}
		else {
			breedPopulation.push_back(population.at(parentIndex2));
			isChosen[parentIndex2] = true;
		}
	}

	delete[] isChosen;
	return breedPopulation;
}

vector<Solution> GeneticAlgorithm::crossover(vector<Solution> breedPopulation)
{
	//cerr << "crossMain\n";
	vector<Solution> childGeneration;
	uniform_real_distribution<double> unif(0, 1);
	default_random_engine re;
	for (int iii = 0; iii < breedPopulation.size(); iii++) {
		if (unif(re) < this->pc) {

			int parentIndex1;
			int parentIndex2;

			do {

				parentIndex1 = rand() % breedPopulation.size();
				parentIndex2 = rand() % breedPopulation.size();

			} while (parentIndex1 == parentIndex2);

			vector<Solution> tempChildren = this->crossoverOX(breedPopulation.at(parentIndex1), breedPopulation.at(parentIndex2));
			childGeneration.push_back(tempChildren.back());
			tempChildren.pop_back();
			childGeneration.push_back(tempChildren.back());
		}
	}

	return childGeneration;
}

vector<Solution> GeneticAlgorithm::crossoverOX(Solution parent1, Solution parent2)
{
	//cerr << "crossOX\n";
	int* child1 = new int[townAmount-1];
	int* child2 = new int[townAmount - 1];

	int crossIndex1;
	int crossIndex2;

	do
	{
		crossIndex1 = rand() % (townAmount-1);
		crossIndex2 = rand() % (townAmount - 1);
	} while (crossIndex1 > crossIndex2 || crossIndex2-crossIndex1 == (townAmount-2));

	bool* isChosen1 = new bool[townAmount-1];
	for (int iii = 0; iii < townAmount - 1; iii++)
		isChosen1[iii] = false;

	bool* isChosen2 = new bool[townAmount - 1];
	for (int iii = 0; iii < townAmount - 1; iii++)
		isChosen2[iii] = false;

	for (int iii = crossIndex1; iii <= crossIndex2; iii++) {
		child1[iii] = parent2.path.at(iii);
		isChosen1[child1[iii]] = true;
		child2[iii] = parent1.path.at(iii);
		isChosen2[child2[iii]] = true;
	}
	//cerr << "here\n";
	for (int iii = crossIndex2+1; iii < townAmount - 1; iii++) {
		//cerr << iii << endl;
		int chosenCity;
		int jjj = iii-1;
		do
		{
			jjj++;
			if (jjj == townAmount - 1)
				jjj = 0;
			chosenCity = parent1.path.at(jjj);
		} while (isChosen1[chosenCity] == true);
		child1[iii] = chosenCity;
		isChosen1[chosenCity] = true;

		jjj = iii - 1;
		do
		{
			jjj++;
			if (jjj == townAmount - 1)
				jjj = 0;
			chosenCity = parent2.path.at(jjj);
		} while (isChosen2[chosenCity] == true);
		child2[iii] = chosenCity;
		isChosen2[chosenCity] = true;
	}
	//cerr << "here2\n";
	for (int iii = 0; iii < crossIndex1; iii++) {
		int chosenCity;
		int jjj = iii - 1;
		do
		{
			jjj++;
			if (jjj == townAmount - 1)
				jjj = 0;
			chosenCity = parent1.path.at(jjj);
		} while (isChosen1[chosenCity] == true);
		child1[iii] = chosenCity;
		isChosen1[chosenCity] = true;

		jjj = iii - 1;
		do
		{
			jjj++;
			if (jjj == townAmount - 1)
				jjj = 0;
			chosenCity = parent2.path.at(jjj);
		} while (isChosen2[chosenCity] == true);
		child2[iii] = chosenCity;
		isChosen2[chosenCity] = true;
	}
	//cerr << "here3\n";
	Solution sol1;
	Solution sol2;
	sol1.path = vector<int>(child1, child1+(townAmount-1));
	sol1.cost = this->getCostFromPath(sol1.path);
	sol2.path = vector<int>(child2, child2 + (townAmount - 1));
	sol2.cost = this->getCostFromPath(sol2.path);

	delete[] child1;
	delete[] child2;

	vector<Solution> returnVector;
	returnVector.push_back(sol1);
	returnVector.push_back(sol2);

	return returnVector;
}

Solution GeneticAlgorithm::mutateSwap(Solution solution) {
	//cerr << "mutateSwap\n";
	int index1, index2;
	do
	{
		index1 = rand() % (townAmount - 1);
		index2 = rand() % (townAmount - 1);

	} while (index1 == index2);

	swap(solution.path.at(index1), solution.path.at(index2));

	solution.cost = getCostFromPath(solution.path);

	return solution;
}

Solution GeneticAlgorithm::mutateInsert(Solution solution) {
	int index1, index2;
	do
	{
		index1 = rand() % (townAmount - 1);
		index2 = rand() % (townAmount - 1);

	} while (index1 == index2);

	vector<int> newPath;

	for (int iii = 0; iii < townAmount - 1; iii++) {
		if (iii == index1) {
			newPath.push_back(solution.path.at(index2));
			newPath.push_back(solution.path.at(iii));
			continue;
		}
		else if(iii != index2)
			newPath.push_back(solution.path.at(iii));
	}

	solution.path = newPath;
	solution.cost = getCostFromPath(solution.path);

	return solution;
}

vector<Solution> GeneticAlgorithm::mutate(vector<Solution> newPopulation)
{
	//cerr << "mutate\n";
	vector<Solution> mutatedPopulation;
	uniform_real_distribution<double> unif(0, 1);
	default_random_engine re;

	for (int iii = 0; iii < newPopulation.size(); iii++) {
		if (unif(re) < this->pm) {
			mutatedPopulation.push_back(mutateInsert(newPopulation.at(iii)));
		}
		else
			mutatedPopulation.push_back(newPopulation.at(iii));
	}

	return mutatedPopulation;
}

bool compareSolutions(Solution sol1, Solution sol2) {
	return (sol1.cost < sol2.cost);
}

vector<Solution> GeneticAlgorithm::getNewPopulation(vector<Solution> oldPopulation, vector<Solution> newPopulation) {

	vector<Solution> population;
	//sort(oldPopulation.begin(), oldPopulation.end(), compareSolutions);
	population.insert(population.begin(), oldPopulation.begin(), oldPopulation.end());
	//sort(newPopulation.begin(), newPopulation.end(), compareSolutions);
	population.insert(population.end(), newPopulation.begin(), newPopulation.end());
	sort(population.begin(), population.end(), compareSolutions);

	vector<Solution> returnPopulation;
	returnPopulation.insert(returnPopulation.begin(), population.begin(), population.begin() + populationSize);

	return returnPopulation;
}

void GeneticAlgorithm::start()
{
	vector<Solution> mainPopulation = createStartPopulation();
	sort(mainPopulation.begin(), mainPopulation.end(), compareSolutions);
	copy(mainPopulation.begin(), mainPopulation.begin() + 1, bestSolution);

	time_t startTime = time(NULL);
	while (true) {

		cerr << bestSolution->cost << endl;
		if (time(NULL) >= startTime + stopTime)
		{
			return;
		}

		vector<Solution> selectedPopulation = this->getBreedPopulation(mainPopulation);
		
		vector<Solution> childPopulation = this->crossover(selectedPopulation);
		childPopulation = this->mutate(childPopulation);

		mainPopulation = getNewPopulation(mainPopulation, childPopulation);
		
		if(mainPopulation.at(0).cost < bestSolution->cost)
			copy(mainPopulation.begin(), mainPopulation.begin() + 1, bestSolution);
	}
}


void GeneticAlgorithm::printSolution() {
	cout << "\nFINAL COST: " << bestSolution->cost << "\nFINAL PATH: 0 ->";
	for (int iii = 0; iii < townAmount - 1; iii++)
	{
		cout << bestSolution->path.at(iii) << " -> ";
	}
	cout << " 0\n";
}

void GeneticAlgorithm::setStopTime(int timeSec) {
	this->stopTime = timeSec;
}
