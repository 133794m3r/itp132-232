#ifndef MATRIX_FUNC
#define MATRIX_FUNC
//this is only just for a 2x2 matrix.
//this is the non-operator overloaded version showing templates.

/*
* matrix_add
* Templated function that takes any type and adds the values together
*then it returns the result as a new 4 value array.
*/
template <typename T> T *matrix_add(T *a, T *b){
	uint32 i=0;
	//create a new pointer to an array of the type specified.
	T *c=new T[4];
	//add them all together.
	c[0]=a[0]+b[0];
	c[1]=a[1]+b[1];
	c[2]=a[2]+b[2];
	c[3]=a[3]+b[3];
	//return the value.
	return c;
}
/*
* matrix_sub
* Templated subtraction function. Operates on a 4 value matrix.
* This will return a new set of values.
*/
template <typename T> T *matrix_sub(T *a, T *b){
	uint32 i=0;
	//return the resulting heap.
	T *c=new T[4];
	c[0]=a[0]-b[0];
	c[1]=a[1]-b[1];
	c[2]=a[2]-b[2];
	c[3]=a[3]-b[3];

	return c;
}

#endif