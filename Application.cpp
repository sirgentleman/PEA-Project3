#include "Application.h"
#include <fstream>
#include <iostream>
#include <random>
#include <time.h>

Application::Application()
{
	inputMatrix = nullptr;

	showMenu();
}

Application::~Application()
{
	delete inputMatrix;
	delete ga;
}

void Application::showMenu()
{
	while (true)
	{
		cout << "MENU GLOWNE\n";
		cout << "1. Zaladuj plik testowy\n";
		cout << "2. Wyswietl zaladowana macierz\n";
		cout << "3. Zmien poczatkowe ustawienia\n";
		cout << "4. Start GA\n";
		cout << "5. Testy\n";

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cout << "Podaj nazwe pliku: ";
			string fileName;
			cin >> fileName;
			this->loadTestFile(fileName);
			ga = new GeneticAlgorithm(inputMatrix, townAmount);
			break;
		}
		case 2:
		{
			this->printSavedMatrix();
			break;
		}
		case 3:
		{
			cout << "NIEZROBIONE\n";
			break;
		}
		case 4:
		{
			cout << "Maksymalny czas wykonania: ";
			int maxTime;
			cin >> maxTime;
			ga->setStopTime(maxTime);
			ga->start();
			ga->printSolution();
			break;
		}
		case 5:
		{
			break;
		}
		}
	}
}

void Application::loadTestFile(string filePath)
{
	ifstream testFile(filePath);

	if (testFile.is_open())
	{
		string buffer;
		getline(testFile, buffer);
		townAmount = stoi(buffer);
		inputMatrix = new Matrix();
		inputMatrix->initMatrix(townAmount, townAmount);

		for (int iii = 0; iii < townAmount; iii++)
		{
			for (int jjj = 0; jjj < townAmount; jjj++)
			{
				int value;
				testFile >> value;
				inputMatrix->set_element(iii, jjj, value);
			}

		}
	}
}


void Application::generateRandomMatrix(int townAmount)
{
	delete inputMatrix;
	inputMatrix = nullptr;
	this->townAmount = townAmount;
	inputMatrix = new Matrix();
	inputMatrix->initMatrix(townAmount, townAmount);
	srand(time(NULL));
	for (int iii = 0; iii < townAmount; iii++)
	{
		for (int jjj = 0; jjj < townAmount; jjj++)
		{
			if (iii == jjj)
				inputMatrix->set_element(iii, jjj, 0);
			else
				inputMatrix->set_element(iii, jjj, rand() % 100 + 1);
		}
	}
}

void Application::printSavedMatrix()
{
	for (int iii = 0; iii < townAmount; iii++)
	{
		for (int jjj = 0; jjj < townAmount; jjj++)
			cout << inputMatrix->at_element(iii, jjj) << " ";
		cout << endl;
	}
}