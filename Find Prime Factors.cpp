// Lab1_Problem1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Author: Ugonna Nwankwo
Class: ECE4122
Last Date Modified: 9/20/2021

Description: This program takes in a number and finds the prime factors.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

bool GetPrimeFactors(const unsigned long ulInputNumber, string &strOutput);

int main(int argc, char* argv[])
{
  unsigned long input = strtoul(argv[1], NULL, 0);
  /*unsigned long input = 25;*/
  string output = "";
  GetPrimeFactors(input, output);
  ofstream myfile;
  myfile.open("output1.txt");
  myfile << output;
  myfile.close();
  return 0;
}

/*This function takes in the input number and an empty string and outputs true after the prime factors have been found*/
bool GetPrimeFactors(const unsigned long ulInputNumber, string &strOutput)
{
  /*loops through to find prime factors including duplicates*/
  unsigned long number = ulInputNumber;
  for (unsigned long i = 2; i <= ulInputNumber; i++) 
    {
      for (int j = 0; number%i == 0; j++) 
	{
	  strOutput = strOutput + to_string(i) + ",";
	  number = number/i;
	}
    }
  /*Checks the edge cases for the input*/
  if (ulInputNumber > 4294967295 || ulInputNumber <= 1)
    {
      strOutput = "No prime factors";
      cout << strOutput << endl;
    }
  else
    {
      strOutput.pop_back();
      cout << strOutput << endl;    
    }
  return true;
}
