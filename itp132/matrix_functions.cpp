#include <iostream>
#include "matrix_functions.h"
/*
* Just a simple templated function showing overloaded functions.
* By Macarhtur Inbody.
*/
typdef unsigned int uint32;




//the main function
int main() {
  int a[4]={0,0,0,0};
  int b[4]={1,2,3,4};
  int *r = new int[4];
  
  float c[4]={2,3,4,5};
  float d[4]={0.1,0.1,0.1,0.1};
  float *r2=new float[4];
  
  r=matrix_add(a,b);
  r2=matrix_add(c,d);
  int i=0;
  for(i=0;i<4;i++){
    std::cout << r[i] << std::endl;
  }
  
  for(i=0;i<4;i++){
    std::cout << r2[i] << std::endl;
  }
}