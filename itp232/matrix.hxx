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
		size_t i;
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

	//get columns constantly.
	size_t get_cols() const{
		return this->cols;
	}

	//same with rows.
	size_t get_rows() const{
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
	 * Arithmetic operators.
	 */
	Matrix<T> operator+(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result[i+(this->rows*j)]=this->array[i+(this->rows*j)]+scalar;
			}
		}
		return result;
	}

	Matrix<T> operator*(const T scalar) const{
		size_t i=0,j=0;
		Matrix<T> result(cols,rows,0);
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]*scalar;
			}
		}
		return result;
	}

	Matrix<T> operator-(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]-scalar;
			}
		}
		return result;
	}

	Matrix<T> operator/(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[i+(rows*j)]=this->array[i+(rows*j)]/scalar;
			}
		}
		return result;
	}

	Matrix<T> operator%(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;

		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
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
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
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
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
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
		Matrix result(other_matrix.cols,this->rows,0);
		for(i=0;i<rows;++i){
			for(j=0;j<other_matrix.cols;j++){
				for(k=0;k<rows;k++){
					result.array[(j*other_matrix.rows)+i]+=this->array[(k*rows)+i] * other_matrix.array[(j*other_matrix.rows)+k];
				}
			}
		}
		return result;
	}

	Matrix<T> operator !(void)const{
		Matrix<T> inverted(*this);
		inverted.inv();
		return inverted;
	}

	//division is actually undefined so this is going to be hard to do.
	Matrix<T> operator/(const Matrix<T> &other_matrix) const{
		Matrix<T> tmp=!other_matrix;
		//std::cout << "/" << tmp << other_matrix << "/ " << std::endl;
		return *this * tmp;
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
			_invalid_dim("addition",other_matrix);
		}

		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
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

		for(i=0;i<rows;++i){
			for(j=0;j<other_matrix.cols;j++){
				for(k=0;k<rows;k++){
					this->array[j+(other_matrix.cols*i)]+=this->array[i+(k*rows)] * other_matrix.array[k+(j*other_matrix.rows)];
				}
			}
		}
		return *this;
	}

	Matrix<T> &operator%=(const T &scalar) {
		size_t i=0;
		size_t j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				this->array[i+(rows*j)] %= scalar;
			}
		}
		return *this;
	}
	Matrix<T> &operator/=(const Matrix<T> &other_matrix){
		*this *= !other_matrix;
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

	
	T _det()const{
		std::cout << "_det " << ((array[0]*array[3])-(array[1]*array[2])) << std::endl;
		return (array[0]*array[3])-(array[1]*array[2]);
	}

	T gae(void){
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
		this->array=vec;
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
			};
		}
		T cofact=tmp.det();
		if((max_row+max_col) & 1u )
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


	template <typename U> Matrix<T> inv_mod(U m) const{
		double det_M=this->det();
		Matrix<T> inversed(cols,rows,0);
		double det_inv=0;
		U det=static_cast<U>(floor(det_M));
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
				inversed.array[(i*rows)+j]=mod(det_inv*inversed.array[(i*rows)+j],m);
			}
		}
		return inversed;
	}

	~Matrix();
	T det(void) const;
	Matrix<T> gae_solve() const;
	bool lud(double &determinate);
	bool lud(float &determinant);
	bool lud(std::vector<float> &P, float *determinant);
	bool lud(std::vector<T> &P, double *determinant);
	bool inv(void);
	bool inv_slow();
};

template <class T> Matrix<T>::~Matrix(){
	this->array.clear();
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

template<>Matrix<double> Matrix<double>::gae_solve() const{
		size_t i,j,k;
		long long l;
		std::vector<double> vec(this->array);
		std::vector<double> tmp_vars(this->rows);
		for(i=0;i<rows-1;i++){
			for(j=i+1;j<rows;j++){
				if(std::abs(vec[i+(i*rows)]) < std::abs(vec[j+(i*rows)])){
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

	for(l=rows-1;0<=l;l--){
		tmp_vars[l] = vec[l+(rows*this->rows)];
		for(j=i+1;j<rows;j++){
			tmp_vars[l] -= vec[l+(j*rows)] * tmp_vars[j];
		}

		tmp_vars[l] = tmp_vars[l]/vec[l+(l*rows)];
	}
		
	return Matrix<double>(tmp_vars,rows,1);
}

template<>Matrix<float>	Matrix<float>::gae_solve()const{
	size_t i,j,k;
	long long l;

		std::vector<float> vec(this->array);
		std::vector<float> tmp_vars(this->rows);

		for(i=0;i<rows-1;i++){
			for(j=i+1;j<rows;j++){
				if(std::abs(vec[i+(i*rows)]) < std::abs(vec[j+(i*rows)])){
					for(k=0;k<cols;k++){
						std::swap(vec[i+(k*rows)],vec[j+(k*rows)]);
					}
				}
			}
			for(j=i+1;j<rows;j++){
				float tmp=vec[j+(i*rows)]/vec[i+(i*rows)];
				for(k=0;k<cols;k++){
					vec[j+(k*rows)]= vec[j + (k * rows)] - tmp * vec[i + (k * rows)];
				}
			}
		}

	for(l=rows-1;0<=l;l--){
		tmp_vars[l] = vec[l+(rows*this->rows)];
		for(j=i+1;j<rows;j++){
			tmp_vars[l] -= vec[l+(j*rows)] * tmp_vars[j];
		}

		tmp_vars[l] = tmp_vars[l]/vec[l+(l*rows)];
	}
		
		return Matrix<float>(tmp_vars,rows,1);
}

template<typename T> Matrix<T> Matrix<T>::gae_solve()const{
	size_t i,j,k;
	long long l;
	std::vector<double> vec(this->array.begin(), this->array.end());
	std::vector<double> tmp_vars(this->rows);
	for(i=0;i<rows-1;i++){
		for(j=i+1;j<rows;j++){
			if(std::abs(vec[i+(i*rows)]) < std::abs(vec[j+(i*rows)])){
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

	for(l=rows-1;0<=l;l--){
		tmp_vars[l] = vec[l+(rows*this->rows)];
		for(j=i+1;j<rows;j++){
			tmp_vars[l] -= vec[l+(j*rows)] * tmp_vars[j];
		}

		tmp_vars[l] = tmp_vars[l]/vec[l+(l*rows)];
	}

	std::vector<T> vars(this->rows);

	for(i=0;i<rows;i++){
		vars[i]=round(tmp_vars[i]);
	}
	return Matrix<T>(vars,rows,1);
}
//this one is for calculating the determinant. Thus the decomposied 
template <> bool Matrix<double>::lud(double &determinant){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<double>::lud(): LUD doesn't work on a  non-square matrix!");
	}

	long long int i, j, k,n=static_cast<long long int>(this->cols);
	double max_matrix, absolute_matrix;
	std::vector<double> P(cols);
	determinant = 1.0;
	for (i = 0; i < n; i++) {
		P[i]=i;
	}

	for (i = 0; i < n; i++) {
		max_matrix = std::abs(this->array[P[i] * n + i]);
		long long int i_max = i;
		for (j = i + 1; j < n; j++) {
			if ((absolute_matrix = std::abs(this->array[j] * n + i)) > max_matrix) {
				max_matrix = absolute_matrix;
				i_max = j;
			}
		}
		if (i_max != i) {
			std::swap(P[i], P[i_max]);
			determinant = -determinant;
		}

		size_t i_pos = static_cast<size_t>(P[i] * n);
		if (std::abs(this->array[i_pos+i]) < epsilon(this->array[i_pos+i])) {
			return false;
		}
		determinant *= this->array[i_pos+i];
		for (j = i + 1; j < n; j++) {
			size_t j_pos = static_cast<size_t>(P[j] * n);
			double a = this->array[j_pos + i] /= this->array[i_pos+i];
			for (k = i + 1; k < n; k++) {
				this->array[j_pos + k] -= a * this->array[i_pos + k];
			}
		}
	}
	i--;
	determinant*= this->array[P[i]*n+i];

	return true;
}
//this one still lets you maybe calculate the determinant
template <> bool Matrix<double>::lud(std::vector<double> &P,double *ptr_det){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<double>::lud(): LUD doesn't work on a  non-square matrix!");
	}

	long long int i, j, k,n=static_cast<long long int>(this->cols);
	double max_matrix, absolute_matrix;
	if(P.size() != this->cols)
		P.resize(cols);
	
	if(ptr_det != NULL)
		*ptr_det = 1.0;
	
	for (i = 0; i < n; i++) {
		P[i]=i;
	}

	for (i = 0; i < n; i++) {
		max_matrix = std::abs(this->array[P[i] * n + i]);
		long long int i_max = i;
		for (j = i + 1; j < n; j++) {
			if ((absolute_matrix = std::abs(this->array[j] * n + i)) > max_matrix) {
				max_matrix = absolute_matrix;
				i_max = j;
			}
		}
		if (i_max != i) {
			std::swap(P[i], P[i_max]);
			if(ptr_det != NULL)			
				*ptr_det = -(*ptr_det);
		}

		size_t i_pos = static_cast<size_t>(P[i] * n);
		if (std::abs(this->array[i_pos+i]) < epsilon(this->array[i_pos+i])) {
			return false;
		}
		if(ptr_det != NULL)
			*ptr_det *= this->array[i_pos+i];
		
		for (j = i + 1; j < n; j++) {
			size_t j_pos = static_cast<size_t>(P[j] * n);
			double a = this->array[j_pos + i] /= this->array[i_pos+i];
			for (k = i + 1; k < n; k++) {
				this->array[j_pos + k] -= a * this->array[i_pos + k];
			}
		}
	}
	

	i--;
	if(ptr_det != NULL)
		*ptr_det *= this->array[P[i]*n+i];

	return true;
}
template <> bool Matrix<float>::lud(float &determinant){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<float>::lud(): LUD doesn't work on a  non-square matrix!");
	}
	long long int i, j, k,n=static_cast<long long int>(this->cols);
	std::vector<float> tmp_row;
	float max_matrix, absolute_matrix;
	std::vector<float> P(cols);
	determinant = 1.0f;
	for (i = 0; i < n; i++) {
		P.push_back(i);
	}

	for (i = 0; i < n; i++) {
		max_matrix = std::abs(this->array[P[i] * n + i]);
		long long int i_max = i;
		for (j = i + 1; j < n; j++) {
			if ((absolute_matrix = std::abs(this->array[j] * n + i)) > max_matrix) {
				max_matrix = absolute_matrix;
				i_max = j;
			}
		}
		if (i_max != i) {
			std::swap(P[i], P[i_max]);
			determinant = -determinant;
		}

		size_t i_pos = static_cast<size_t>(P[i] * n);
		if (std::abs(this->array[i_pos+i]) < epsilon(this->array[i_pos+i])) {
			return false;
		}
		determinant *= this->array[i_pos+i];
		for (j = i + 1; j < n; j++) {
			size_t j_pos = static_cast<size_t>(P[j] * n);
			float a = this->array[j_pos + i] /= this->array[i_pos+i];
			for (k = i + 1; k < n; k++) {
				this->array[j_pos + k] -= a * this->array[i_pos + k];
			}
		}
	}

	determinant*= this->array[P[i]*n+i];
	return true;
}
template <> bool Matrix<float>::lud(std::vector<float> &P,float *ptr_det){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<float>::lud(): LUD doesn't work on a  non-square matrix!");
	}

	long long int i, j, k,n=static_cast<long long int>(this->cols);
	float max_matrix, absolute_matrix;
	if(P.size() != this->cols)
		P.resize(this->cols);
	
	if(ptr_det != NULL)
		*ptr_det = 1.0;
	
	for (i = 0; i < n; i++) {
		P[i]=i;
	}

	for (i = 0; i < n; i++) {
		max_matrix = std::abs(this->array[P[i] * n + i]);
		long long int i_max = i;
		for (j = i + 1; j < n; j++) {
			if ((absolute_matrix = std::abs(this->array[j] * n + i)) > max_matrix) {
				max_matrix = absolute_matrix;
				i_max = j;
			}
		}
		
		if (i_max != i) {
			std::swap(P[i], P[i_max]);
			if(ptr_det != NULL)			
				*ptr_det = -(*ptr_det);
		}

		size_t i_pos = static_cast<size_t>(P[i] * n);
		if (std::abs(this->array[i_pos+i]) < epsilon(this->array[i_pos+i])) {
			return false;
		}
		if(ptr_det != NULL)
			*ptr_det *= this->array[i_pos+i];
		
		for (j = i + 1; j < n; j++) {
			size_t j_pos = static_cast<size_t>(P[j] * n);
			double a = this->array[j_pos + i] /= this->array[i_pos+i];
			for (k = i + 1; k < n; k++) {
				this->array[j_pos + k] -= a * this->array[i_pos + k];
			}
		}
	}
	i--;
	if(ptr_det != NULL)
		*ptr_det *= this->array[P[i]*n+i];
	
	return true;
}
template <typename T> bool Matrix<T>::lud(double &determinant){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<T>::lud(): LUD doesn't work on a  non-square matrix!");
	}

	std::vector<double> vec(this->array.begin(),this->array.end());
	Matrix<double> tmp_matrix(vec,this->cols,this->rows);
	tmp_matrix.lud(determinant);
	size_t i=0;
	size_t max=(this->cols);
	for(i=0;i<(max*max);i++){
		this->array[i]=static_cast<T>(floor(tmp_matrix[i]));

	}
	return true;
}
template <typename T> bool Matrix<T>::lud(std::vector<T> &P,double *ptr_det){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<float>::lud(): LUD doesn't work on a  non-square matrix!");
	}
	
	std::vector<double> vec(this->array.begin(),this->array.end());
	Matrix<double> tmp_matrix(vec,this->cols,this->rows);
	size_t i=0;
	tmp_matrix.lud(P,ptr_det);
	size_t max=(this->cols);
	for(i=0;i<(max*max);i++){
		this->array[i]=static_cast<T>(floor(tmp_matrix[i]));

	}
	return true;
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
	float determinant=0.0f;
	if(!tmp_matrix.lud(determinant))
		determinant=0.0f;

	return determinant;
}

//this inversion takes ~O(2/3(n**3)+(1.709*(n**3))) iterations.
template <> bool Matrix<double>::inv(){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<double>::inv(): Can't invert a non-square matrix.");
	}
	long long int i, j, k,n=static_cast<long long int>(this->cols),i_pos=0,j_pos=0;
	long long int i_max=0;
	std::vector<double> P(cols);
	//size_t j_pos,i_pos;
	for (i=0; i < n; i++)
		P[i] = i;

	for (i=0; i < n; i++){
		double ta,tb;
		double a(0);
		i_pos = i * n;
		i_max = i;
		ta = std::abs( this->array[i_pos + i]);
		for (j=i + 1; j < n; j++){;
			if ((tb = std::abs(this->array[j * n + i])) > ta){
				ta = tb;
				i_max = j;
			}
		}
		if (ta < epsilon( a))
			return false;

		if (i_max != i){
			std::swap(P[i], P[i_max]);
			for (j_pos=i_max*n, j=0; j < n; j++){
				std::swap(this->array[i_pos + j], this->array[j_pos + j]);;
			}
		}

		a = double(1) / this->array[i_pos + i];
		this->array[i_pos + i] = double(1);

		for (j=0; j < n; j++){;
			this->array[i_pos+j] *= a;
		}

		for (j=0; j < n; j++){;
			if (j != i){
				j_pos = j * n;
				a = this->array[j_pos + i];
				this->array[j_pos + i] = double(0);
				for (k=0; k < n; k++){;
					this->array[j_pos+k] -= a * this->array[i_pos+k];
				}
			}
		}
	}

	for (i=0; i < n; i++){;
		if (i != P[i]){
			k = i + 1;
			while (i != P[k])
				k++;
			for (j=0; j < n; j++){
				std::swap(this->array[j * n + i], this->array[j * n + k]);
			}
			std::swap(P[i], P[k]);
		}
	}
	
	return true;
}


template <> bool Matrix<float>::inv(){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<float>::inv(): Can't invert a non-square matrix.");
	}
	
	long long int i, j, k,n=static_cast<long long int>(this->cols),i_pos=0,j_pos=0;
	long long int i_max=0;
	std::vector<float> P(cols);
	for (i=0; i < n; i++)
		P[i] = i;

	for (i=0; i < n; i++){
		double ta,tb;
		double a(0);
		i_pos = i * n;
		i_max = i;
		
		ta = std::abs( this->array[i_pos + i]);
		for (j=i + 1; j < n; j++){;
			if ((tb = std::abs(this->array[j * n + i])) > ta){
				ta = tb;
				i_max = j;
			}
		}
		if (ta < epsilon( a))
			return false;

		if (i_max != i){
			std::swap(P[i], P[i_max]);
			for (j_pos=i_max*n, j=0; j < n; j++){
				std::swap(this->array[i_pos + j], this->array[j_pos + j]);;
			}
		}

		a = double(1) / this->array[i_pos + i];
		this->array[i_pos + i] = double(1);

		for (j=0; j < n; j++){;
			this->array[i_pos+j] *= a;
		}

		for (j=0; j < n; j++){;
			if (j != i){
				j_pos = j * n;
				a = this->array[j_pos + i];
				this->array[j_pos + i] = double(0);
				for (k=0; k < n; k++){;
					this->array[j_pos+k] -= a * this->array[i_pos+k];
				}
			}
		}
	}

	for (i=0; i < n; i++){;
		if (i != P[i]){
			k = i + 1;
			while (i != P[k])
				k++;
			for (j=0; j < n; j++){
				std::swap(this->array[j * n + i], this->array[j * n + k]);
			}
			std::swap(P[i], P[k]);
		}
	}
	
	return true;
}
//for all other types we have to first cast to a double then we can use that version.
template <typename T> bool Matrix<T>::inv(){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<float>::inv(): Can't invert a non-square matrix.");
	}	
	//we create a vector so that we can then cast to a double.
	//to keep precision this has to be done.
	std::vector<double> vec(this->array.begin(),this->array.end());
	//then we allocate the matrix.
	Matrix<double> tmp_matrix(vec,this->cols,this->rows);
	tmp_matrix.inv();
	size_t max=this->cols*this->rows;
	size_t i=0;
	for(i=0;i<max;i++){
		this->array[i]=static_cast<T>(floor(tmp_matrix[i]));

	}
	return true;
}

//this inversion takes O((2/3(n**3))+(2*(n**3))) operations or so.
template <typename T> bool Matrix<T>::inv_slow(){
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
template <> double Matrix<double>::det(void) const{
	if(this->cols != this->rows){
		throw std::invalid_argument( "Matrix<double>::det() Error: Cannot calculate the determinant of a non-square matrix!");
	}

	//if it's 2x2 I can simply do it w/o having do LUD or any other
	//expensive operations. No reason do all of those extra operations.
	//if(cols == 2 && rows == 2)
	//	return _det();
	//since it's a const we have to create a matrix to modify.
	Matrix<double> tmp_matrix=Matrix<double>(*this);
	double determinant=0;
	if(!tmp_matrix.lud(determinant))
		determinant=0;

	return determinant;
}
//the normal template type is here. I'm going to use gaussian elimination for every other type than double or float.
template <typename T> T Matrix<T>::det(void)const{

	if(this->cols != this->rows){
		throw std::invalid_argument( "Matrix<double>::det() Error: Cannot calculate the determinant of a non-square matrix!");
	}

	//if it's 2x2 I can simply do it w/o having do LUD or any other
	//expensive operations. No reason do all of those extra operations.
	
	if(cols == 2 && rows == 2)
		return _det();
	
	//we create a vector so that we can then cast to a double.
	//to keep precision this has to be done.
	std::vector<double> vec(this->array.begin(),this->array.end());
	//then we allocate the matrix.
	Matrix<double> tmp_matrix(vec,this->cols,this->rows);
	double determinant=0;
	if(!tmp_matrix.lud(determinant))
		determinant=0;

	return determinant;
}

typedef Matrix<int> matrix_int;
typedef Matrix<unsigned int> matrix_uint;
typedef Matrix<double> matrix_double;
typedef Matrix<float> matrix_float;
typedef Matrix<long long int> matrix_long;
typedef Matrix<unsigned long long> matrix_ulong;
#endif