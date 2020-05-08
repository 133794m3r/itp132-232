#ifndef MATRIX_CLASS_DEMO
#define MATRIX_CLASS_DEMO
#include <vector>

template <class T> class Matrix{
	private:
		unsigned long rows;
		unsigned long cols;
		//have to use a vector since C++ doesn't like raw pointers and
		//I give up trying to make it let me use pointers the way I want to.
		//thus I'll use this less effecient vector implementation.
		std::vector<int> array;				
	public:	
		Matrix(unsigned long _cols=1, unsigned long _rows=1, T initial_value=0){
			unsigned int total_elements=_rows*_cols;			
			unsigned int i=0;
			rows=_rows;
			cols=_cols;
			for(i=0;i<total_elements;++i){
				array.push_back(initial_value);				
			}
		}
		size_t index(unsigned long x, unsigned long y) const{
			return x+(rows*y);
		}
		T &operator()(const unsigned long x, const unsigned long y){
			return this->array[x+(rows*y)];
		}
		T *get_elem(T x,T y){
			T *el;
			el=&array[x+(rows*y)];
			return el;
		}
		void invalid_dim(std::string op, Matrix &other_matrix){
			throw std::invalid_argument("For " + op + " Matrix 1's columns and rows must match Matrix 2's columns and rows.\r\nM1.cols="+std::to_string(cols)+" M1.rows="+std::to_string(rows)+" M2.cols="+std::to_string(other_matrix.rows)+" M2.rows="+std::to_string(other_matrix.cols)+"\r\n");
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
		Matrix operator-(Matrix &other_matrix){
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

		
		~Matrix();
		
};
template <class T> Matrix<T>::~Matrix(){
	array.clear();
}

typedef Matrix<int> matrix_int;
#endif