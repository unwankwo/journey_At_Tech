/* ECE 2035 Homework 1-2

Your Name:Ugonna Nwankwo
Date:1/18/19

This is the only file that should be modified for the C implementation
of Homework 1.

This program computes and prints the union of two sets of 
ten integers, SetA and SetB.  It also prints the size of the union.
*/

#include <stdio.h>
#include <stdlib.h>

//DO NOT change the following declaration (you may change the initial value).
int SetA[] = {5, -19, 8, 26, 3, 6, -9, 17, 60, -63};
int SetB[] = {8, 11, -63, 18, 26, 17, 25, 12, -9, 60};
/*
For the grading scripts to run correctly, the above declarations
must be the first lines of code in this file (for this homework
assignment only).  Under penalty of grade point loss, do not change
these lines, except to replace the initial values while you are testing
your code.  

Also, do not include any additional libraries.
 */

int main() {
  //int Size;
  	//Size = [setA,setB];
  	int arr[20];
  	int i;
  	int foundDup = 0;
  	int z;
  	int j;
  	int m;
  	int count = 0;

	for (i=0;i<10;i++) {
  		arr[i] = SetA[i];
  		count++;
  	}

  	for(z=0;z<10;z++) {
  		for(j=0;j<10;j++){
  			if (SetB[z]==arr[j]){
  				foundDup = 1;
  			}	
  		}
  		if (foundDup == 0){
  			arr[count] = SetB[z];
  	        count++;
 		}
 		foundDup = 0;

  	}

  for (m=0;m<count;m++) {
  	printf("%d: %d\n",m,arr[m]);
  }

  printf("Union Set Size: %d\n", count);
  return 0;
}
