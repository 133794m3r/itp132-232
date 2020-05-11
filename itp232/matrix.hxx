#ifndef MATRIX_CLASS_DEMO
#define MATRIX_CLASS_DEMO
#include <vector>
#include <valarray>
#include "math.h"
template <class T> class Matrix;
template <typename T> std::ostream& operator<<( std::ostream&, const Matrix<T>& );
/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Matrix Class Module
 *
 */

template <class T> class Matrix{
	
	private:
	
	size_t rows;
	size_t cols;
	/*
	 * have to use a vector since C++ doesn't like raw pointers and
	 * I give up trying to make it let me use pointers the way I want to.
	 * thus I'll use this less effecient vector implementation.
	 */
	std::vector<T> array;				
	
	public:
	
//constructor section.
Matrix(size_t _cols=1, size_t _rows=1, T initial_value=0){
		size_t total_elements=_rows*_cols;			
		size_t i=0;
		rows=_rows;
		cols=_cols;
		//reserve the memory necessary to construct the array, thus not having to realloc continously.
		//otherwise each push_back might result in a realloc|| destruct+construct
		array.reserve(total_elements);
		for(i=0;i<total_elements;++i){
			array.push_back(initial_value);				
		}
	}

	//allow them to seed it with a vector of values precomputed.
	Matrix(std::vector<T> &input_array,size_t _cols, size_t _rows){
		//if the input is already a std::vector of normal type just copy it.
		array=input_array;
		cols=_cols;
		rows=_rows;
	}

	//also allow construction with a C style array.
	Matrix(T *input_array,size_t _cols, size_t _rows) {
		cols=_cols;
		rows=_rows;
		size_t total_elements=_cols*_rows;
		size_t i=0;
		//reserve the memory necessary to construct the array, thus not having to realloc continously.
		array.reserve(total_elements);
		for(i=0;i<total_elements;++i){
			array.push_back(input_array[i]);
		}
	}

	Matrix<T> operator=(const Matrix<T> &input){
		//self referential assignment.
		if(this == &input) {
			return *this;
		}
		//otherwise we do the deep copy.
		//we copy the std::vector<T> to the new one.
		array=input.array;
		//same with rows.
		rows=input.rows;
		//same with cols.
		cols=input.cols;
		return *this;
	}


	size_t get_cols() {
		return this->cols;
	}
	
	size_t get_cols() const{
		return this->cols;
	}
	
	size_t get_rows() const{
		return this->rows;
	}
	
	size_t get_rows() {
		return this->rows;
	}
	
	size_t index(size_t x, size_t y) const{
		return x+(rows*y);
	}
	
	T &operator()(const size_t x, const size_t y){
		#ifdef CHECK_RANGE
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x,y);
		#endif	
		return this->array[x+(rows*y)];
	}
	
	const T &operator()(const size_t x, const size_t y) const{
		#ifdef CHECK_RANGE
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x,y);
		#endif			
		return array[x+(rows*y)];
	}
	
	T &operator[](const size_t x){
		#ifdef CHECK_RANGE
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x);
		#endif		
		return this->array[x];
	}
	
	const T &operator[](const size_t x) const{
		#ifdef CHECK_RANGE
		if(x >= rows || y >= cols)
			_index_out_of_bounds("[","]",x);
		#endif			
		return this->array[x];
	}

	T *get_elem(T x,T y){
		T *el;
		el=&array[x+(rows*y)];
		return el;
	}
	
	void _index_out_of_bounds(const std::string  &left_item, const std::string &right_item, const size_t x, const size_t y){
		throw std::invalid_argument("Error: Chosen index is out of bounds. Matrix<T>"+left_item+std::to_string(x)+","+std::to_string(y)+right_item);
	}
	
	void _index_out_of_bounds(const std::string  &left_item, const std::string &right_item, const size_t x){
		throw std::invalid_argument("Error: Chosen index is out of bounds. Matrix<T>"+left_item+std::to_string(x)+right_item);
	}
	
	void _invalid_dim(const std::string &op, const Matrix &other_matrix){
		throw std::invalid_argument("For " + op + " Matrix 1's columns and rows must match Matrix 2's columns and rows.\r\nM1.cols="+std::to_string(cols)+" M1.rows="+std::to_string(rows)+" M2.cols="+std::to_string(other_matrix.rows)+" M2.rows="+std::to_string(other_matrix.cols)+"\r\n");
	}
	
	Matrix<T> operator+(const T &scalar){
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]+scalar;
			}
		}
		return result;
	}
	
	Matrix<T> operator-(const T &scalar){
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]-scalar;
			}
		}
		return result;
	}					

	Matrix<T> operator+(Matrix<T> &other_matrix){
		if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
			_invalid_dim("addition",other_matrix);
		}
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]+other_matrix.array[i+(rows*j)];
			}
		}
		return result;
	}	
	
	Matrix<T> operator-(Matrix<T> &other_matrix){
		if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
			_invalid_dim("subtraction",other_matrix);
		}
		Matrix result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]-other_matrix.array[i+(rows*j)];
			}
		}
		return result;
	}
	
	Matrix<T> &operator+=(const T &scalar) {
		size_t rows=this->rows;
		size_t cols=this->cols;

		for (unsigned i=0; i<rows; i++) {
			for (unsigned j=0; j<cols; j++) {
				this->array[i+(rows*j)] += scalar;
			}
		}

		return *this;
	}
	
	Matrix<T> &operator-=(const T &scalar) {
		size_t rows=this->rows;
		size_t cols=this->cols;

		for (unsigned i=0; i<rows; i++) {
			for (unsigned j=0; j<cols; j++) {
				this->array[i+(rows*j)] -= scalar;
			}
		}

		return *this;
	}
	
	Matrix<T> &operator+=(const Matrix<T> &other_matrix) {
		size_t rows=this->rows;
		size_t cols=this->cols;
		
		if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
			_invalid_dim("addition",other_matrix);
		}

		for (unsigned i=0; i<rows; i++) {
			for (unsigned j=0; j<cols; j++) {
				this->array[i+(rows*j)] += other_matrix.array[i+(rows*j)];
			}
		}

		return *this;
	}
	
	Matrix<T> &operator-=(const Matrix<T> &other_matrix) {
		size_t rows=this->rows;
		size_t cols=this->cols;
		
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

	Matrix<T> operator/(const Matrix<T> &other_matrix){

	}
	
	// Output stream function for matrix
	friend std::ostream& operator<< <T>( std::ostream &, const Matrix<T> &);

	bool lud(double &determinant) {
		Matrix<T> A=Matrix<T>(*this);
		size_t i, j, k;
		std::vector<T> tmp_row;
		double max_matrix, absolute_matrix;
		std::vector<T> P;
		P.reserve(cols-1);
		determinant = T(1);
		
		for (i = 0; i < cols; i++) {
			P.push_back(i);
		}

		for (i = 0; i < cols - 1; i++) {
			max_matrix = abs(A[P[i] * cols + i]);
			size_t i_max = i;
			for (j = i + 1; j < cols; j++) {
				if ((absolute_matrix = abs(A[j] * cols + i)) > max_matrix) {
					max_matrix = absolute_matrix;
					i_max = j;
				}
			}
			if (i_max != i) {
				std::swap(P[i], P[i_max]);
				determinant = -determinant;
			}

			size_t i_pos = P[i] * cols;
			size_t i_pos_i = i_pos+i;
			if (abs(A[i_pos_i]) < epsilon(A[i_pos_i])) {
				return false;
			}
			determinant *= A[i_pos_i];
			for (j = i + 1; j < cols; j++) {
				size_t j_pos = P[j] * cols;
				T a = A[j_pos + i] /= A[i_pos_i];

				for (k = i + 1; k < cols; k++) {
					A[j_pos + k] -= a * A[i_pos + k];
				}
			}
		}

		determinant*= A[P[i]*cols+i];
		return true;
	}
	double _det_small(void){

	}
	
	double _det(void){
		return (array[0]*array[3])-(array[1]*array[2]);
	}
	
	//TODO: Going to have a hard-coded version for when I have a 1x1 or 2x2 matrix as it's easy enough to hard code.
	double det(void){
		if(this->cols != this->rows){
			throw std::invalid_argument( "Matrix<T>::det() Error: Cannot calculate the determinant of a non-square matrix!");
		}
		Matrix<T> tmp_matrix=Matrix<T>(*this);
		double determinant=0;
		//if it's 2x2 I can simply do it w/o having do LUD or any other
		//expensive operations. No reason do all of those extra operations.
		if(cols == 2 && rows == 2)
			determinant=_det();
		if(!lud(determinant))
			determinant=0;

		return determinant;
	}

	_adj(Matrix<T> &matrix){
		std::swap(matrix.array[0],matrix.array[3])
		matrix.array[1]*=-1;
		matrix.array[2]*=-1;
	}
	
	Matrix<T> adj(){
		if(cols != rows)
			throw std::invalid_arugment("Matrix<T>::adj() Error: Cannot calculate Adjugate of a non-square matrix!");
		Matrix<T> result=Matrix<T>(*this);
		if(cols == 2 && rows == 2)
			_adj(result);
		
		
		return result;
	}
	~Matrix();
	
};
template <class T> Matrix<T>::~Matrix(){
	array.clear();
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T> &m){
	//int w = os.width();
	size_t rows=m.rows;
	size_t cols=m.cols;
	os << '[';
	for (size_t i=0; i < rows; i++) {
		os << '[';
		for (size_t j = 0; j < cols; j++) {
			os << m(i, j) << (j == cols - 1 ? "]" : "\t,");
		}
		os << ((i < rows -1)?",":"]");
		os << "\n";
	}
	return os;
}

typedef Matrix<int> matrix_int;
typedef Matrix<double> matrix_double;
#endif