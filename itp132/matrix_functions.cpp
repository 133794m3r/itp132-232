#include <iostream>
#include "matrix_functions.hxx"
/*
* Just showing templates that's all.
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/



//the main function
int main() {
	int i;
	//the int arrays.
	int a[4]={0,0,0,0};
	int b[4]={1,2,3,4};
	//resulting heap object.
	int *r;
	
	//float version.
	float c[4]={2,3,4,5};
	float d[4]={0.1,0.1,0.1,0.1};
	//the result.
	float *r2;
	
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