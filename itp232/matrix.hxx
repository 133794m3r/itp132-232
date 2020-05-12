#ifndef MATRIX_CLASS_DEMO
#define MATRIX_CLASS_DEMO
#include <vector>
#include <valarray>
#include <stdexcept>
#include "math.h"
template <class T> class Matrix;
template <typename T> std::ostream& operator<<( std::ostream&, const Matrix<T>& );
/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Matrix Class Module
 *
 */
//uncomment line below to do out of range checking. This costs perf and since I know i'm within ranges always
//I have it undefined.
//#define _CHECK_RANGE_
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
	//allow assignment operator.
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

	//get columns.
	size_t get_cols() {
		return this->cols;
	}
	//get columns constantly.
	size_t get_cols() const{
		return this->cols;
	}

	//same with rows.
	size_t get_rows() const{
		return this->rows;
	}
	
	size_t get_rows() {
		return this->rows;
	}

	//get the value at an index.
	size_t index(size_t x, size_t y) const{
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x,y);
		#endif
		return this->array[x+(rows*y)];
	}
	//overload function operator to allow them to call it via matrix(i,j). Where i = row, and j = column.
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

	//subscript operator.
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
	/*
	T *get_elem(T x,T y){
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("::get_elem(",")",x,y);
		#endif	
		T *el;
		el=&array[x+(rows*y)];
		return el;
	}
	*/

	//index out of bounds error when doing x,y form.
	void _index_out_of_bounds(const std::string  &left_item, const std::string &right_item, const size_t x, const size_t y) const{
		throw std::out_of_range("Error: Chosen index is out of bounds. Matrix<T>"+left_item+std::to_string(x)+","+std::to_string(y)+right_item);
	}
	//index out of bounds when doing direct access.
	void _index_out_of_bounds(const std::string  &left_item, const std::string &right_item, const size_t x) const{
		throw std::out_of_range("Error: Chosen index is out of bounds. Matrix<T>"+left_item+std::to_string(x)+right_item);
	}
	//invalid dimensions error.
	void _invalid_dim(const std::string &op, const Matrix &other_matrix) const{
		throw std::invalid_argument("For " + op + " Matrix 1's columns and rows must match Matrix 2's columns and rows.\r\nM1.cols="+std::to_string(cols)+" M1.rows="+std::to_string(rows)+" M2.cols="+std::to_string(other_matrix.rows)+" M2.rows="+std::to_string(other_matrix.cols)+"\r\n");
	}

	/**
	 * Arithematic operators.
	 */
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

	Matrix<T> operator/(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]/scalar;
			}
		}
		return result;
	}

	Matrix<T> operator%(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;

		for(i=0;i<cols;i++){
			for(j=0;j<rows;j++){
				result.array[i+(rows*j)]=mod(this->array[i+(rows*j)],scalar);
			}
		}
		return result;
	}

	/**
	 * Below here are the same operators but with matrices.
	 */
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
			throw std::invalid_argument("For Multiplication Matrix 1's columns must match Matrix 2's rows.\r\nM1.cols="+std::to_string(cols)+" M2.cols="+std::to_string(other_matrix.rows)+"\r\n");
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
	//division is actually undefined so this is going to be hard to do.
	Matrix<T> operator/(const Matrix<T> &other_matrix) const{

	}



	/**
	 * The arith&&= operators.
	 *
	 */
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

	Matrix<T> &operator*=(const Matrix<T> &other_matrix){
		if((this->cols != other_matrix.rows)){
			throw std::invalid_argument("For Multiplication Matrix 1's columns must match Matrix 2's rows.\r\nM1.cols="+std::to_string(cols)+" M2.cols="+std::to_string(other_matrix.rows)+"\r\n");
		}
		size_t i=0,j=0,k=0;

		for(i=0;i<cols;++i){
			for(j=0;j<other_matrix.cols;j++){
				for(k=0;k<this->cols;k++){
					this->array[(i*other_matrix.cols)+j]+=this->array[(i*this->cols)+k]*other_matrix.array[(k*other_matrix.cols)+j];
				}
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

	/**
	 * Comparison Operators are below here.
	 *
	 */

	bool operator==(const Matrix<T> &other_matrix) const{
		if((this->cols != other_matrix.cols)||(this->rows != other_matrix.rows)){
			return false;
		}
		size_t i=0,j=0;
		for(i=0;i<this->rows;i++){
			for(j=0;j<this->cols;j++){
				if(std::abs(this->array[i+(rows*j)] - other_matrix.array[i+(rows*j)]) > epsilon(this->array[i+(rows*j)])){
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(const Matrix<T> &other_matrix) const{
		return !( *this == other_matrix );
	}
	
	bool operator<(const Matrix<T> &other_matrix) const{
		if((this->cols != other_matrix.cols)||(this->rows != other_matrix.rows)){
			_invalid_dim(">",other_matrix);
		}
		size_t i=0,j=0;
		for(i=0;i<this->rows;i++){
			for(j=0;j<this->cols;j++){
				if(this->array[i+(rows*j)]>other_matrix.array[i+(rows*j)]){
					return false;
				}
			}
		}
		return true;
	}

	bool operator<=(const Matrix<T> &other_matrix) const{
		return (*this < other_matrix);
	}

	bool operator>(const Matrix<T> &other_matrix) const{
		return !(*this < other_matrix);
	}

	bool operator>=(const Matrix<T> &other_matrix) const{
		return !(*this < other_matrix);
	}

	bool operator==(const T &rhs) const{
		return false;
	}

	bool operator !=(const T &rhs) const{
		return true;
	}

	// Output stream function for matrix
	friend std::ostream& operator<< <T>( std::ostream &, const Matrix<T> &);

	bool lud(double &determinant)const{
		Matrix<T> A=Matrix<T>(*this);
		long long int i, j, k,n=cols;
		std::vector<T> tmp_row;
		double max_matrix, absolute_matrix;
		std::vector<T> P;
		P.reserve(n-1);
		determinant = static_cast<T>(1);
		
		for (i = 0; i < n; i++) {
			P.push_back(i);
		}

		for (i = 0; i < n - 1; i++) {
			max_matrix = std::abs(A[P[i] * n + i]);
			long long int i_max = i;
			for (j = i + 1; j < n; j++) {
				if ((absolute_matrix = std::abs(A[j] * n + i)) > max_matrix) {
					max_matrix = absolute_matrix;
					i_max = j;
				}
			}
			if (i_max != i) {
				std::swap(P[i], P[i_max]);
				determinant = -determinant;
			}

			size_t i_pos = P[i] * n;
			size_t i_pos_i = i_pos+i;
			if (std::abs(A[i_pos_i]) < epsilon(A[i_pos_i])) {
				return false;
			}
			determinant *= A[i_pos_i];
			for (j = i + 1; j < n; j++) {
				size_t j_pos = P[j] * n;
				T a = A[j_pos + i] /= A[i_pos_i];

				for (k = i + 1; k < n; k++) {
					A[j_pos + k] -= a * A[i_pos + k];
				}
			}
		}

		determinant*= A[P[i]*n+i];
		return true;
	}
	
	T _det()const{
		return (array[0]*array[3])-(array[1]*array[2]);
	}

	T gae(void){
		size_t i,j,k;
		size_t swaps=0;
		for(i=0;i<rows-1;i++){
			for(j= i + 1; j < rows; j++){
				if(std::abs(array[i+(i*rows)]) < std::abs(array[j+(i*rows)])){
					swaps++;
					for(k=0;k<cols;k++){
						std::swap(array[i+(k*rows)],array[j+(k*rows)]);
					}
				}
			}
			for(j=i+1;j<rows;j++){
				double tmp=array[j+(i*rows)]/array[i+(i*rows)];
				for(k=0;k<cols;k++){
					array[j+(k*rows)]=array[j+(k*rows)]-tmp*array[i+(k*rows)];
				}
			}
		}
		return swaps;
	}

	T gae(void)const{
		size_t i,j,k;
		size_t swaps=0;
		std::vector<T> vec=this->array;

		for(i=0;i<rows-1;i++){
			for(j=i+1;j<rows;j++){
				if(std::abs(vec[i+(i*rows)]) < std::abs(vec[j+(i*rows)])){
					swaps++;
					for(k=0;k<cols;k++){
						std::swap(vec[i+(k*rows)],vec[j+(k*rows)]);
					}
				}
			}

			for(j=i+1;j<rows;j++){
				double tmp=vec[j+(i*rows)]/vec[i+(i*rows)];
				for(k=0;k<cols;k++){
					vec[j+(k*rows)]=vec[j+(k*rows)]-tmp*vec[i+(k*rows)];
				}
			}
		}
		return swaps;
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

	void _adj(Matrix<T> &mat)const{
		std::swap(mat.array[0],mat.array[3]);
		mat.array[1]*=-1;
		mat.array[2]*=-1;
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

	bool inv(){
		T det_m=this->det();
		if(det_m == 0) {
			throw std::invalid_argument("Matrix is Singular: Determinant is 0. No inversion is possible.");
		}
		Matrix<T> adj_mat(cols,rows,1);
		adj_mat=this->adj();
		size_t i=0,j=0;
		for(i=0;i<cols;i++){
			for(j=0;j<cols;j++){
				this->array[(j*cols)+i] = adj_mat[(j*cols)+i]/det_m;
			}
		}
		return true;
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
	T det(void) const;
};

template <class T> Matrix<T>::~Matrix(){
	array.clear();
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T> &m){
	//int w = os.width();
	size_t rows=m.rows;
	size_t cols=m.cols;
	os << "[";
	for (size_t i=0; i < rows; i++) {
		os << "[";
		for (size_t j = 0; j < cols; j++) {
			os << m(i, j) << (j == cols - 1 ? "]" : "\t,");
		}
		os << ((i < rows -1)? "," : "]");
		os << '\n';
	}
	return os;
}
//I have to break these templates out because the way that I'm going to do integer types.
template <> float Matrix<float>::det(void) const{
	//it has to be a square matrix for this to work.
	if(this->cols != this->rows){
		throw std::invalid_argument( "Matrix<float>::det() Error: Cannot calculate the determinant of a non-square matrix!");
	}
	//if it's 2x2 I can simply do it w/o having do LUD or any other
	//expensive operations. No reason do all of those extra operations.
	if(cols == 2 && rows == 2)
		return _det();
	//otherwise we create our variables to use later.
	//this'll reduce memory used when it can be easily done with some simple math.
	Matrix<float> tmp_matrix=Matrix<float>(*this);
	double determinant=0;
	if(!lud(determinant))
		determinant=0;

	return determinant;
}

template <> double Matrix<double>::det(void) const{
	if(this->cols != this->rows){
		throw std::invalid_argument( "Matrix<double>::det() Error: Cannot calculate the determinant of a non-square matrix!");
	}

	//if it's 2x2 I can simply do it w/o having do LUD or any other
	//expensive operations. No reason do all of those extra operations.
	if(cols == 2 && rows == 2)
		return _det();

	Matrix<double> tmp_matrix=Matrix<double>(*this);
	double determinant=0;
	if(!lud(determinant))
		determinant=0;

	return determinant;
}
//the normal template type is here. I'm going to use gaussian elimination for every other type than double or float.
template <typename T> T Matrix<T>::det(void)const{
	if(this->cols != this->rows){
		throw std::invalid_argument( "Matrix<T>::det() Error: Cannot calculate the determinant of a non-square matrix!");
	}
	Matrix<T> tmp_matrix=Matrix<T>(*this);
	T determinant=0;
	//if it's 2x2 I can simply do it w/o having do LUD or any other
	//expensive operations. No reason do all of those extra operations.
	if(cols == 2 && rows == 2)
		return _det();
	//otherwise we have to gaussian elimination.
	size_t swaps=this->gae();
	size_t i=0;
	for(i=0;i<rows;i++){
		determinant*=array[i+(i*rows)];
	}
	//then we cast it to the type T.
	return static_cast<T>(determinant*pow(-1,swaps));
}
typedef Matrix<int> matrix_int;
typedef Matrix<double> matrix_double;
#endif