// Lab1_Problem3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
Author: Ugonna Nwankwo
Class: ECE4122
Last Date Modified: 9/24/2021

Description: This program takes in the initial reflection’s x location along the AB segment and calculates the number of reflections.

https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
*/


#include <stdlib.h>
#include <math.h>  
#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>

using namespace std;

class Points
{
public:
  double m_x = 0.0;
  double m_y = 0.0;
    
  /*This function calculates the distance between two vectors and takes in the x and y components of the vectors.*/
  double distance(const Points& inPt)
  {
    return sqrt((m_x - inPt.m_x) * (m_x - inPt.m_x) + (m_y - inPt.m_y) * (m_y - inPt.m_y));
  }
};

class LineSegement
{
public:
  Points pt1, pt2;
  double m_length = 0.0;
  double m_normalX = 0.0;
  double m_normalY = 0.0;

  LineSegement() {}

  LineSegement(const Points& coordinate1, const Points& coordinate2) : pt1(coordinate1), pt2(coordinate2)
  {
    m_length = pt1.distance(pt2);
  }

  double getDeltaX() const { return (pt2.m_x - pt1.m_x); }
  double getDeltaY() const { return (pt2.m_y - pt1.m_y); }

  /*This function normalizes the normal vector and takes in the normal vector's x and y components as inputs*/
  void setNormal(double nX, double nY)
  {
    double length = sqrt(nX * nX + nY * nY);
    if (length <= 0.0)
      {
	length = 1.0;
      }
    m_normalX = nX / length;
    m_normalY = nY / length;
  }

  void setPoint1(const Points& pt) { pt1 = pt; }
  void setPoint2(const Points& pt) { pt2 = pt; }

  /*This function calculates the intersection point of the inLine ray and the triangle side. It takes the inputs, inLine Ray and reflectPt, to calculate the intersection point and store it in reflectPt*/
  bool getReflectionPt(const LineSegement& inLine, Points& reflectPt)
  {
       
    /*Triangle side represented in the form a1x + b1y = c1*/
    double a1 = pt2.m_y - pt1.m_y;
    double b1 = pt1.m_x - pt2.m_x;
    double c1 = a1 * (pt1.m_x) + b1 * (pt1.m_y);

    /*Inline Ray represented in the form a2x + b2y = c2*/
    double a2 = inLine.pt2.m_y - inLine.pt1.m_y;
    double b2 = inLine.pt1.m_x - inLine.pt2.m_x;
    double c2 = a2 * (inLine.pt1.m_x) + b2 * (inLine.pt1.m_y);

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0) 
      {
	return false;
      }
    else 
      { 
	/*Calculation of the reflection point*/
	double reflectX = (b2 * c1 - b1 * c2) / determinant;
	double reflectY = (a1 * c2 - a2 * c1) / determinant;
	reflectPt.m_x = reflectX;
	reflectPt.m_y = reflectY;
	return true;
      }
  }

  /*This function gets the reflected ray. It takes inputs, inLine ray, reflectLine ray, and reflectPt to calculate the second point for the reflected ray and store it in reflectPt*/
  bool getReflectedLine(const LineSegement& inLine, LineSegement& reflectLine, Points& reflectPt)
  {
    if (getReflectionPt(inLine, reflectPt))
      {
	// Check if point is inside of the segment
	if (reflectPt.distance(pt1) > m_length || reflectPt.distance(pt2) > m_length)
	  {
	    return false;
	  }
	// The point is inside the segment so check if the y value is less than the cutout section
	if (reflectPt.m_y <= 0.01)
	  {
	    return false;
	  }
	else // Determine the reflected ray
	  {
	    // r = d - 2(d * n)n;
	    // d is the inLine
	    // n is the normal vector of this side
	    // r is the reflectLine
	    double changeX = inLine.getDeltaX();
	    double changeY = inLine.getDeltaY();
	    double dotProduct = (changeX * m_normalX) + (changeY * m_normalY);
	    double reflectX = changeX - (2 * dotProduct * m_normalX);
	    double reflectY = changeY - (2 * dotProduct * m_normalY);
	    double reflectSlope = reflectY / reflectX;
	    double b = reflectPt.m_y - (reflectSlope * reflectPt.m_x);
                
	    reflectLine.setPoint1(reflectPt);
	    reflectLine.pt2.m_x = 12;
	    reflectLine.pt2.m_y = (reflectSlope * 12) + b;
	    reflectLine.m_length = reflectLine.pt1.distance(reflectLine.pt2);

	    return true;
	  }
      }
    else
      {
	return false;
      }
    return false;
  }

};

int main(int argc, char* argv[])
{
  // Make sure the input is valid
  if (atof(argv[1]) == 0) 
    {
      cout << "1" << endl;
      return 1;
    }

  cout.precision(8);
  // Convert to double
  double x = abs(atof(argv[1]));
  double y = sqrt(20.0 * 20.0 - 10.0 * 10.0);
  bool bStillInside = false;

  LineSegement sides[3]; // These are the three sides of the triangle

  // Initialize the 3 sides
  
  sides[0] = { { -10, y }, { 10, y } }; // Side AB
  sides[0].setNormal(0,-1);
  sides[1] = { { 10, y }, { 0, 0 } }; // Side BC
  sides[1].setNormal(-y, 10);
  sides[2] = { { 0, 0 }, { -10, y } }; // Side CA
  sides[2].setNormal(y, 10);

  LineSegement incidentRay = { { 0.0, 0.0 }, { x, y } }; // Initialize the incident ray
  LineSegement reflectedRay;
  Points intersectPt = { x, y };

  unsigned long nNumReflects{ 0 };
  short nReflectedSide = -1; // Top segment is the first 


  std::ofstream outFile("out.csv", std::ofstream::out | std::ofstream::trunc);
  outFile << 0.0 << "," << 0.0 << std::endl;
    do
      {
        bStillInside = false;
        for (int ii = 0; ii < 3; ii++)
	  {
            // Don't want to reflect the beam on the side it just came from
            if (nReflectedSide < 0 || ii != nReflectedSide)
	      {
                if (sides[ii].getReflectedLine(incidentRay, reflectedRay, intersectPt))
		  {
                    // Increment the number of reflections everytime an intersection point is found.
                    nNumReflects++;
                    nReflectedSide = ii;
                    bStillInside = true;
                    outFile << intersectPt.m_x << "," << intersectPt.m_y << std::endl;
                    // Change the side of the triangle to calculate the next intersection point. Update the second point for the reflected ray and swap the incident and reflected rays.
                    sides[(ii + 1) % 3].getReflectionPt(reflectedRay, intersectPt);
                    reflectedRay.setPoint2(intersectPt);
                    incidentRay = reflectedRay;
                    break;
		  }
	      }
	  }

      } while (bStillInside);

    outFile << intersectPt.m_x << "," << intersectPt.m_y << std::endl;
    outFile.close();

    std::cout << nNumReflects << std::endl;
    ofstream output("output3.txt");
    output << nNumReflects << endl;

    return 1;
}
