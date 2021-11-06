// Lab2_Problem2.cpp 
/*
Author: Ugonna Nwankwo
Class: ECE4122
Last Date Modified: 10/11/2021

Description: Numerical Integration
This program uses OpenMP to compute an integral using the midpoint rule. The program takes a single command line argument that is the 
number of subdivisions (N) to use in the calculations. The program outputs to a text file Lab2Prob2.txt the estimation of the integral, 
overwriting any previous results.

*/
#include <iostream>
#include <stdio.h> 
#include <thread>
#include <math.h>
#include <omp.h>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[])
{ 

  int N = strtoul(argv[1], NULL, 0);
  double mx;
  double fx;
  double sum;
  double dist = log(2)/7;
  double numb = dist/N;

//find the integral of F(x) using midpoint rule.
  #pragma omp parallel for reduction(+:sum)
      for (int i = 0; i < N; ++i) 
      { 
        mx = (numb)/2 + i*(numb); //this is the midpoint
        fx = 14 * (exp(7*mx));
        sum += fx * (numb);
      }

  ofstream myfile;
  myfile.open("Lab2Prob2.txt");
  myfile << fixed;
  myfile << setprecision(6);
  myfile << sum;
  myfile.close();     
  return 0;
}