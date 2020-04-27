#ifndef MATRIX_FUNC
#define MATRIX_FUNC
//this is only just for a 2x2 matrix.
//this is the non-operator overloaded version showing templates.
template <typename T> T *matrix_add(T *a, T *b){
	uint32 i=0;
	T *c=new T[4];
	c[0]=a[0]+b[0];
	c[1]=a[1]+b[1];
	c[2]=a[2]+b[2];
	c[3]=a[3]+b[3];

	return c;
}

template <typename T> T *matrix_sub(T *a, T *b){
	uint32 i=0;
	T *c=new T[4];
	c[0]=a[0]-b[0];
	c[1]=a[1]-b[1];
	c[2]=a[2]-b[2];
	c[3]=a[3]-b[3];

	return c;
}

#endif