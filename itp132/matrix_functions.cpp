#include <iostream>
#include "matrix_functions.h"
/*
* Just a simple templated function showing overloaded functions.
* By Macarhtur Inbody.
*/
typdef unsigned int uint32;


//the main function
int main() {
	int i=0;
	//the int arrays.
	int a[4]={0,0,0,0};
	int b[4]={1,2,3,4};
	//resulting heap object.
	int *r = new int[4];
	
	//float version.
	float c[4]={2,3,4,5};
	float d[4]={0.1,0.1,0.1,0.1};
	//the result.
	float *r2=new float[4];
	
	//get result of ints.
	r=matrix_add(a,b);
	//get result of floats.
	r2=matrix_add(c,d);
	
	//output the results.
	std::cout << "Int Example: [";
	for(i=0;i<4;i++){
		//if we're on the second value+ add a comma.
		if(i > 0)
			std::cout << ",";
		
		std::cout << r[i];
	}
	std::cout << "]" << std::endl;
	
	
	//do the float version.
	std::cout << "Float Example: [";	
	for(i=0;i<4;i++){
		if(i > 0)
			std::cout << ",";
		
		std::cout << r2[i] << std::endl;
	}
	std::cout << "]" << std::endl;
	
	//always return zero.
	return 0;
}