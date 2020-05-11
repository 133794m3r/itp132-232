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
		//if(this == &input) {
		//	return *this;
		//}
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
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x,y);
		#endif	
		return this->array[x+(rows*y)];
	}
	
	const T &operator()(const size_t x, const size_t y) const{
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x,y);
		#endif			
		return array[x+(rows*y)];
	}
	
	T &operator[](const size_t x){
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x);
		#endif		
		return this->array[x];
	}
	
	const T &operator[](const size_t x) const{
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("[","]",x);
		#endif			
		return this->array[x];
	}

	T *get_elem(T x,T y){
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("::get_elem(",")",x,y);
		#endif	
		T *el;
		el=&array[x+(rows*y)];
		return el;
	}
	
	void _index_out_of_bounds(const std::string  &left_item, const std::string &right_item, const size_t x, const size_t y) const{
		throw std::out_of_range("Error: Chosen index is out of bounds. Matrix<T>"+left_item+std::to_string(x)+","+std::to_string(y)+right_item);
	}
	
	void _index_out_of_bounds(const std::string  &left_item, const std::string &right_item, const size_t x) const{
		throw std::out_of_range("Error: Chosen index is out of bounds. Matrix<T>"+left_item+std::to_string(x)+right_item);
	}
	
	void _invalid_dim(const std::string &op, const Matrix &other_matrix) const{
		throw std::invalid_argument("For " + op + " Matrix 1's columns and rows must match Matrix 2's columns and rows.\r\nM1.cols="+std::to_string(cols)+" M1.rows="+std::to_string(rows)+" M2.cols="+std::to_string(other_matrix.rows)+" M2.rows="+std::to_string(other_matrix.cols)+"\r\n");
	}
	
	Matrix<T> operator+(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]+scalar;
			}
		}
		return result;
	}

	Matrix<T> operator*(const T scalar) const{
		size_t i=0,j=0;
		Matrix<T> result(cols,rows,0);
		for(i=0;i<cols;++i){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]*scalar;
			}
		}
		return result;
	}

	Matrix<T> operator-(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]-scalar;
			}
		}
		return result;
	}					

	Matrix<T> operator+(Matrix<T> const &other_matrix) const{
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
	
	Matrix<T> operator-(const Matrix<T> &other_matrix) const{
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

	Matrix<T> operator*(const Matrix<T> &other_matrix) const{
		if((this->cols != other_matrix.rows)){
			_invalid_dim("multiplication",other_matrix);
		}
		size_t i=0,j=0,k=0;
		Matrix result(this->cols,other_matrix.rows,0);
		for(i=0;i<cols;++i){
			for(j=0;j<other_matrix.cols;j++){
				for(k=0;k<this->cols;k++){
					result.array[(i*other_matrix.cols)+j]+=this->array[(i*this->cols)+k]*other_matrix.array[(k*other_matrix.cols)+j];
				}
			}
		}
		return result;
	}

	Matrix<T> operator%(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;

		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]%scalar;
			}
		}
		return result;
	}

	Matrix<T> &operator+=(const T scalar) {
		size_t i=0;
		size_t j=0;

		for (i=0; i<rows; i++) {
			for (j=0; j<cols; j++) {
				this->array[i+(rows*j)] += scalar;
			}
		}

		return *this;
	}
	
	Matrix<T> &operator-=(const T scalar) {
		size_t i=0;
		size_t j=0;

		for (i=0; i<rows; i++) {
			for (j=0; j<cols; j++) {
				this->array[i+(rows*j)] -= scalar;
			}
		}

		return *this;
	}

	Matrix<T> &operator*=(const T &scalar){
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				this-array[i+(rows*j)]*=scalar;
			}
		}
		return *this;
	};

	Matrix<T> &operator+=(const Matrix<T> &other_matrix) {
		size_t i=0;
		size_t j=0;

		if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
			_invalid_dim("addition",other_matrix);
		}

		for (i=0; i<rows; i++) {
			for (j=0; j<cols; j++) {
				this->array[i+(rows*j)] += other_matrix.array[i+(rows*j)];
			}
		}

		return *this;
	}
	
	Matrix<T> &operator-=(const Matrix<T> &other_matrix) {
		size_t i=0;
		size_t j=0;

		if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
			invalid_dim("addition",other_matrix);
		}

		for (i=0; i<rows; i++) {
			for (j=0; j<cols; j++) {
				this->array[i+(rows*j)] -= other_matrix.array[i+(rows*j)];
			}
		}

		return *this;
	}

	Matrix<T> &operator%=(const T &scalar) {
		size_t i=0;
		size_t j=0;
		for (i=0; i<rows; i++) {
			for (j=0; j<cols; j++) {
				this->array[i+(rows*j)] %= scalar;
			}
		}
		return *this;
	}
	//division is actually undefined so this is going to be hard to do.
	Matrix<T> operator/(const Matrix<T> &other_matrix){

	}
	
	// Output stream function for matrix
	friend std::ostream& operator<< <T>( std::ostream &, const Matrix<T> &);

	bool lud(double &determinant)const{
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
	
	double _det(Matrix<T> &mat)const{
		return (mat.array[0]*mat.array[3])-(mat.array[1]*mat.array[2]);
	}
	
	//TODO: Going to have a hard-coded version for when I have a 1x1 or 2x2 matrix as it's easy enough to hard code.
	double det(void)const{
		if(this->cols != this->rows){
			throw std::invalid_argument( "Matrix<T>::det() Error: Cannot calculate the determinant of a non-square matrix!");
		}
		Matrix<T> tmp_matrix=Matrix<T>(*this);
		double determinant=0;
		//if it's 2x2 I can simply do it w/o having do LUD or any other
		//expensive operations. No reason do all of those extra operations.
		if(cols == 2 && rows == 2)
			determinant=_det(tmp_matrix);
		if(!lud(determinant))
			determinant=0;

		return determinant;
	}

	void _adj(Matrix<T> &matrix)const{
		std::swap(matrix.array[0],matrix.array[3]);
		matrix.array[1]*=-1;
		matrix.array[2]*=-1;
	}

	T cofactor(size_t max_row, size_t max_col) const{
		if(this->rows != this->cols)
			throw std::invalid_argument( "Matrix<T>::cofactor() Error: Cannot calculate the cofactor of a non-square matrix!");
		#ifdef CHECK_RANGE
		if(x >= max_row || y >= max_col)
			_index_out_of_bounds("(",")",max_row,max_col);
		#endif
		size_t i,z,j,y;
		Matrix<T> tmp(rows-1,rows-1);
		for(i=0,z=0;i < rows;i++){
			if(i == max_row)
				continue;
			for(j=0,y=0;j<rows;j++){
				if(j == max_col)
					continue;
				tmp.array[z*(rows-1)+y] = array[i*rows+j];
				y++;
			}
			z++;
		}
		T cofact=tmp.det();
		if((max_row+max_col) & 1 )
			cofact = -cofact;
		return cofact;
	}

	Matrix<T> adj()const{
		if(this->cols != this->rows)
			throw std::invalid_argument("Matrix<T>::adj() Error: Cannot calculate Adjugate of a non-square matrix!");

		Matrix<T> tmp_matrix=Matrix<T>(*this);
		if(tmp_matrix.cols == 2 && tmp_matrix.rows == 2) {
			_adj(tmp_matrix);
		}
		else {

			size_t i = 0, j = 0;
			for (i = 0; i < rows; i++) {
				for (j = 0; j < rows; j++) {
					tmp_matrix.array[(j * rows) + i] = cofactor(i, j);
				}
			}
		}
		return tmp_matrix;
	}
	template <typename U> Matrix<T> inv_mod(U m) const{
		double det_M=this->det();
		Matrix<T> inversed(cols,rows,0);
		double det_inv=0;
		int det=floor(det_M);
		if(det_M == 0)
			throw std::invalid_argument("Matrix is Singular: Determinant is 0. No inversion is possible.");

		inversed=this->adj();
		try{
			det_inv=mod_inv(det,m);
		}
		catch(std::string e){
			std::invalid_argument("Matrix is not invertible (mod "+std::to_string(m)+").");
		}

		size_t i=0,j=0;

		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				inversed.array[i*rows+j]=mod(det_inv*inversed.array[i*rows+j],m);
			}
		}
		return inversed;
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