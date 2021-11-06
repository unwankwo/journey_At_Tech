// Lab1_Problem2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Author: Ugonna Nwankwo
Class: ECE4122
Last Date Modified: 9/20/2021

Description: This program takes in the number of moves of the ant and calculates how many black tiles are remaining.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

struct ant 
{
  int rows;
  int col;
  int direction;
};

ant langton = 
{
  99, 
  99,
  1
};

int antmap[200][200];
int count = 0;

int main(int argc, char* argv[])
{
  unsigned long input = strtoul(argv[1], NULL, 0);
  
  /*Fills the grid with white squares*/
  for (int i = 0; i < 200; i++) 
    { 
      for (int j = 0; j < 200; j++) 
	{
	  antmap[i][j] = 0;
	}
   }   
 
  /*Changing the direction of the ant*/
  for (unsigned long p = 0; p < input; p++) 
  {
    if(antmap[langton.rows][langton.col] == 0) 
    {
      antmap[langton.rows][langton.col] = 1;
      langton.direction = (langton.direction + 1) % 4; 
      switch (langton.direction) 
      {
      case 0: langton.rows--;
	break;
      case 1: langton.col++;
	break;
      case 2: langton.rows++;
	break;
      case 3: langton.col--;
	break;
      }
    }
    else 
    {
      antmap[langton.rows][langton.col] = 0;
      langton.direction = (langton.direction + 4 - 1) % 4;
      switch (langton.direction) 
      {
      case 0: langton.rows--;
	break;
      case 1: langton.col++;
	break;
      case 2: langton.rows++;
	break;
      case 3: langton.col--;
	break;
      }
    }
  }

  /*Calculates the number of black tiles*/
  for (int i = 0; i < 200; i++)
    {
      for(int j = 0; j < 200; j++)
	{
          if (antmap[i][j] == 1) 
	    {
	      count++;
	    }
	}
    }
  ofstream myfile;
  myfile.open("output2.txt");
  myfile << count;
  myfile.close();
  return 0;
  cout << count << endl;
}
