// Lab2_Problem2.cpp 
/*
Author: Ugonna Nwankwo
Class: ECE4122
Last Date Modified: 10/14/2021

Description: Ant and seeds
This program detects the number, N, of threads that can be run concurrently on the system being used 
and creates N threads to determine how many steps until all seeds have been dropped in the top row and 
how many total runs it takes for the answer to converge. The program generates an output file called 
ProblemOne.txt.
*/

#include <iostream>
#include <stdio.h> 
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <fstream>
#include <iomanip>
using namespace std;

mutex mtx;
unsigned long long totalSteps;
double totalIterations = 10000000;
const auto numThreads = thread::hardware_concurrency();
void calculateTotalSteps();

//This function calculates the total steps that the ant uses to fill up the first row. The total steps is then stored in a global variable called, totalSteps.
void calculateTotalSteps() 
{
	unsigned antFood = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(antFood);
	
	for (int i = 0; i < totalIterations/numThreads; i++)
	{
		unsigned long long steps = 0;
		bool antmap[5][5] = 
		{
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{1, 1, 1, 1, 1}
		};
		short int antRow = 2;
		short int antCol = 2;
		bool seed = false;

        //runs until the first row is full of seeds.
        while(antmap[0][0] == 0 || antmap[0][1] == 0 || antmap[0][2] == 0 || antmap[0][3] == 0 || antmap[0][4] == 0)
        {
			uniform_int_distribution<int> distribution(0,3);
            int direction = distribution(generator);

            //check for boundary conditions and corners.
            while ((antCol == 0 && direction == 3)  ||
                (antCol == 4 && direction == 1)  ||
                (antRow == 0 && direction == 0)  || 
                (antRow == 4 && direction == 2)) 
            {
                direction = distribution(generator);
            }

            switch (direction)
			{
			   	case 0: antRow--;
				break;
			    case 1: antCol++;
				break;
				case 2: antRow++;
				break;
				case 3: antCol--;
				break;
			}

			steps++;

            if (antRow == 4 && seed == false && antmap[4][antCol] == 1)
			{
				seed = true;
				antmap[4][antCol] = 0;
			}

			else if (antRow == 0 && seed == true && antmap[0][antCol] == 0)
			{
				antmap[0][antCol] = 1;
				seed = false;
			}

        }
		//prevent other threads from writing to totalSteps
    	mtx.lock();
		totalSteps += steps;
		mtx.unlock();
    }
}

int main() 
{
	vector<thread> threads;
    
	for (int i = 0; i < numThreads; i++) 
    {
		threads.push_back(thread(calculateTotalSteps));
	}
	
	for (thread &t : threads) 
    {
		if (t.joinable()) 
		{
			t.join();
		}
	}

	ofstream myfile;
    myfile.open("ProblemOne.txt");
	myfile << fixed;
	myfile << setprecision(6);
    myfile << "Number of threads created: " << numThreads << endl;
	myfile << "Expected number of steps: " << ((double)totalSteps / (double)totalIterations) << endl;
	myfile << "Total number of runs needed for solution convergence: 10000000" << endl;
    myfile.close();
    return 0;

}