#ifndef MATRIX_CLASS_DEMO
#define MATRIX_CLASS_DEMO
#include <vector>
#include <valarray>
#include "math.h"
template <class T> class Matrix;
template <typename T> std::ostream& operator<<( std::ostream&, const Matrix<T>& );
//template <typename T>T det(Matrix<T>&);
//template <typename scalar_type> bool lud(Matrix<scalar_type> &A,scalar_type &determinant);
template <class T> class Matrix{
	private:
		unsigned long rows;
		unsigned long cols;
		//have to use a vector since C++ doesn't like raw pointers and
		//I give up trying to make it let me use pointers the way I want to.
		//thus I'll use this less effecient vector implementation.
		std::vector<T> array;				
	public:	
		Matrix(unsigned long _cols=1, unsigned long _rows=1, T initial_value=0){
			unsigned long total_elements=_rows*_cols;			
			unsigned long i=0;
			rows=_rows;
			cols=_cols;
			for(i=0;i<total_elements;++i){
				array.push_back(initial_value);				
			}
		}
		unsigned long get_cols() {
		    return this->cols;
		}
		unsigned long get_cols() const{
			return this->cols;
		}
		unsigned long get_rows() const{
			return this->rows;
		}
		unsigned long get_rows() {
		    return this->rows;
		}
		
		size_t index(unsigned long x, unsigned long y) const{
			return x+(rows*y);
		}
		
		T &operator()(const unsigned long x, const unsigned long y){
			return this->array[x+(rows*y)];
		}
		
		const T &operator()(const unsigned long x, const unsigned long y) const{
			return array[x+(rows*y)];
		}
		T &operator[](const size_t x){
		    return this->array[x];
		}
		const T &operator[](const size_t x) const{
		    return this->array[x];
		}
		T *get_elem(T x,T y){
			T *el;
			el=&array[x+(rows*y)];
			return el;
		}

		void invalid_dim(const std::string& op, const Matrix &other_matrix){
			throw std::invalid_argument("For " + op + " Matrix 1's columns and rows must match Matrix 2's columns and rows.\r\nM1.cols="+std::to_string(cols)+" M1.rows="+std::to_string(rows)+" M2.cols="+std::to_string(other_matrix.rows)+" M2.rows="+std::to_string(other_matrix.cols)+"\r\n");
		}
		
		Matrix<T> operator+(const T &scalar){
			Matrix<T> result(cols,rows,0);
			unsigned long i=0,j=0;
			for(i=0;i<cols;i++){
				for(j=0;j<rows;j++){
					result.array[i+(rows*j)]=this->array[i+(rows*j)]+scalar;
				}
			}
			return result;
		}
		
		Matrix<T> operator-(const T &scalar){
			Matrix<T> result(cols,rows,0);
			unsigned long i=0,j=0;
			for(i=0;i<cols;i++){
				for(j=0;j<rows;j++){
					result.array[i+(rows*j)]=this->array[i+(rows*j)]-scalar;
				}
			}
			return result;
		}					

		Matrix<T> operator+(Matrix<T> &other_matrix){
			if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
				invalid_dim("addition",other_matrix);
			}
			Matrix<T> result(cols,rows,0);
			unsigned long i=0,j=0;
			for(i=0;i<cols;i++){
				for(j=0;j<rows;j++){
					result.array[i+(rows*j)]=this->array[i+(rows*j)]+other_matrix.array[i+(rows*j)];
				}
			}
			return result;
		}	
		
		Matrix<T> operator-(Matrix<T> &other_matrix){
			if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
				invalid_dim("subtraction",other_matrix);
			}
			Matrix result(cols,rows,0);
			unsigned long i=0,j=0;
			for(i=0;i<cols;i++){
				for(j=0;j<rows;j++){
					result.array[i+(rows*j)]=this->array[i+(rows*j)]-other_matrix.array[i+(rows*j)];
				}
			}
			return result;
		}
		
		Matrix<T> &operator+=(const T &scalar) {
			unsigned long rows=this->rows;
			unsigned long cols=this->cols;

			for (unsigned i=0; i<rows; i++) {
				for (unsigned j=0; j<cols; j++) {
					this->array[i+(rows*j)] += scalar;
				}
			}

			return *this;
		}
		
		Matrix<T> &operator-=(const T &scalar) {
			unsigned long rows=this->rows;
			unsigned long cols=this->cols;

			for (unsigned i=0; i<rows; i++) {
				for (unsigned j=0; j<cols; j++) {
					this->array[i+(rows*j)] -= scalar;
				}
			}

			return *this;
		}
		
		Matrix<T> &operator+=(const Matrix<T>& other_matrix) {
			unsigned long rows=this->rows;
			unsigned long cols=this->cols;
			
			if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
				invalid_dim("addition",other_matrix);
			}

			for (unsigned i=0; i<rows; i++) {
				for (unsigned j=0; j<cols; j++) {
					this->array[i+(rows*j)] += other_matrix.array[i+(rows*j)];
				}
			}

			return *this;
		}
		
		Matrix<T> &operator-=(const Matrix<T>& other_matrix) {
			unsigned long rows=this->rows;
			unsigned long cols=this->cols;
			
			if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
				invalid_dim("addition",other_matrix);
			}

			for (unsigned i=0; i<rows; i++) {
				for (unsigned j=0; j<cols; j++) {
					this->array[i+(rows*j)] -= other_matrix.array[i+(rows*j)];
				}
			}

			return *this;
		}
		/*
	T determinant(void){
		unsigned long rows=this->rows;
		unsigned long cols=this->cols;
		if(rows != cols)
		T det=1;
		int i;
		int swapCount=gaussElimination(n,n,a);
		for(i=0;i<n;i++){
			det =det*a[i][i];
		}
		return det*pow(-1,swapCount);
	}		
	*/
// Output stream function for matrix
//friend std::ostream& operator<<( std::ostream&, const Matrix<T>& );
	friend std::ostream& operator<< <T>( std::ostream &, const Matrix<T> &);

    //friend T gaussian_reduction <T>(const Matrix<T> &);
	template <class U> friend bool lud(Matrix<T> &,T &determinant);
	~Matrix();
		
};
template <class T> Matrix<T>::~Matrix(){
	array.clear();
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T> &m){
	//int w = os.width();
	unsigned long rows=m.rows;
	unsigned long cols=m.cols;
	for (unsigned long i=0; i < rows; i++)
		 for (unsigned long j=0; j < cols; j++)
			os << m(i,j) << (j == cols-1 ? '\n' : '\t');
	 return os;
}


template <typename scalar_type> bool lud(Matrix<scalar_type> &A,double &determinant) {
    size_t i, j, k, l, i_max;
    //size_t i,j,k;
    std::vector<scalar_type> tmp_row;
    //double max_matrix,absolute_matrix;
    double max_matrix, absolute_matrix;
    size_t n = A.get_cols();
    size_t i_pos = 0;
    size_t j_pos = 0;
    std::vector<scalar_type> P;

    determinant = scalar_type(1);
    for (i = 0; i < n; i++) {
        P.push_back(i);
    }

    for (i = 0; i < n - 1; i++) {
        max_matrix = abs(A[P[i] * n + i]);
        i_max = i;
        for (j = i + 1; j < n; j++) {
            if ((absolute_matrix = abs(A[j] * n + i)) > max_matrix) {
                max_matrix = absolute_matrix;
                i_max = j;
            }
        }
        if (i_max != i) {
            std::swap(P[i], P[i_max]);
            determinant = -determinant;
        }

        i_pos = P[i] * n;
        if (abs(A[i_pos + i]) < epsilon(A[i_pos + i])) {
            return false;
        }
        determinant *= A[i_pos + i];
        for (j = i + 1; j < n; j++) {
            size_t j_pos = P[j] * n;
            scalar_type a = A[j_pos + i] /= A[i_pos + i];

            for (k = i + 1; k < n; k++) {
                A[j_pos + k] -= a * A[i_pos + k];
            }
        }
    }
    determinant*= A[P[i]*n+i];
    return true;
}

template <typename T> double det(const Matrix<T> &mat){
    if(mat.get_cols() != mat.get_rows()){
        throw std::invalid_argument( "det(Matrix<T> A): Cannot calculate the determinant of a non-square matrix!");
    }
    Matrix<double> tmp_matrix=mat;
    double determinant=0;
    if(!lud(tmp_matrix,determinant))
    determinant=0;

    return determinant;
}

typedef Matrix<int> matrix_int;
#endif