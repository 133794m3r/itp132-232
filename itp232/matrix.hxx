#ifndef _MATRIX_CLASS_
#define _MATRIX_CLASS_
#include <vector>
#include <valarray>
#include <stdexcept>
#include "math.hxx"
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
	size_t index(size_t y, size_t x) const{
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x,y);
		#endif
		return this->array[x+(cols*y)];
	}

	//overload function operator to allow them to call it via matrix(i,j). Where i = row, and j = column.
	T &operator()(const size_t y, const size_t x){
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x,y);
		#endif
		return this->array[x+(cols*y)];
	}

	const T &operator()(const size_t y, const size_t x) const{
		#ifdef _CHECK_RANGE_
		if(x >= rows || y >= cols)
			_index_out_of_bounds("(",")",x,y);
		#endif			
		return array[x+(cols*y)];
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
	void _index_out_of_bounds(const std::string	&left_item, const std::string &right_item, const size_t x, const size_t y) const{
		throw std::out_of_range("Error: Chosen index is out of bounds. Matrix<T>"+left_item+std::to_string(x)+","+std::to_string(y)+right_item);
	}
	//index out of bounds when doing direct access.
	void _index_out_of_bounds(const std::string	&left_item, const std::string &right_item, const size_t x) const{
		throw std::out_of_range("Error: Chosen index is out of bounds. Matrix<T>"+left_item+std::to_string(x)+right_item);
	}
	//invalid dimensions error.
	void _invalid_dim(const std::string &op, const Matrix &other_matrix) const{
		throw std::invalid_argument("For " + op + " Matrix 1's columns and rows must match Matrix 2's columns and rows.\r\nM1.cols="+std::to_string(cols)+" M1.rows="+std::to_string(rows)+" M2.cols="+std::to_string(other_matrix.rows)+" M2.rows="+std::to_string(other_matrix.cols)+"\r\n");
	}

	/**
	 * Arithmetic operators.
	 * First are scalars. Then matricies. Finally it's std::vectors.
	 * For scalars I do them first as a this, then as the scalar being on the lhs.
	 */
	Matrix<T> operator+(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result[j+(this->cols*i)]=this->array[j+(this->cols*i)]+scalar;
			}
		}
		return result;
	}
	//friend Matrix<T> operator+(const T scalar,const Matrix<T> rhs);
	Matrix<T> operator*(const T scalar) const{
		size_t i=0,j=0;
		Matrix<T> result(cols,rows,0);
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[j+(this->cols*i)]=this->array[j+(this->cols*i)]*scalar;
			}
		}
		return result;
	}

	Matrix<T> operator-(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[j+(this->cols*i)]=this->array[j+(this->cols*i)]-scalar;
			}
		}
		return result;
	}

	Matrix<T> operator/(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[j+(this->cols*i)]=this->array[j+(this->cols*i)]/scalar;
			}
		}
		return result;
	}

	Matrix<T> operator%(const T scalar) const{
		Matrix<T> result(cols,rows,0);
		size_t i=0,j=0;

		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[j+(this->cols*i)]=mod(this->array[j+(this->cols*i)],scalar);
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
				result.array[j+(this->cols*i)]=this->array[j+(this->cols*i)]+other_matrix.array[j+(this->cols*i)];
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
				result.array[j+(this->cols*i)]=this->array[j+(this->cols*i)]-other_matrix.array[j+(this->cols*i)];
			}
		}
		return result;
	}

	Matrix<T> operator*(const Matrix<T> &other_matrix) const{
		if((this->cols != other_matrix.rows)){
			throw std::invalid_argument("For Multiplication Matrix 1's columns must match Matrix 2's rows.\r\nM1.cols="+std::to_string(cols)+" M2.rows="+std::to_string(other_matrix.rows)+"\r\n");
		}
		size_t i=0,j=0,k=0;
		Matrix result(other_matrix.cols,this->rows,0);
		for(i=0;i<rows;++i){
			for(j=0;j<other_matrix.cols;j++){
				for(k=0;k<rows;k++){
					result.array[(j*other_matrix.cols)+i]+=this->array[(k*this->cols)+i] * other_matrix.array[(j*other_matrix.cols)+k];
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
	 * The same but with std::vectors.
	 */
	 //+ and - aren't really defined when it comes to vectors really.
	 /*
	Matrix<T> operator+(std::vector<T> const &rhs) const{
		if((cols != rhs.size())||(rows != rhs.size())){
			_invalid_dim("addition",rhs);
		}
		Matrix<T> result(cols,rows,0);

		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[j+(this->cols*i)]=this->array[j+(this->cols*i)]+rhs[j+(this->cols*i)];
			}
		}
		return result;
	}

	Matrix<T> operator-(std::vector<T> const &rhs) const{
		if((cols != rhs.cols)||(rows != rhs.rows)){
			_invalid_dim("subtraction",rhs);
		}
		Matrix result(cols,rows,0);
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[j+(this->cols*i)]=this->array[j+(this->cols*i)]-rhs[j+(this->cols*i)];
			}
		}
		return result;
	}
*/
	Matrix<T> operator*(std::vector<T> const &rhs) const{
		if((this->cols != rhs.size())){
			throw std::invalid_argument("For Multiplication Matrix 1's columns must match Matrix 2's rows.\r\nM1.cols="+std::to_string(cols)+" M2.rows="+std::to_string(rhs.size())+"\r\n");
		}
		size_t i=0,j=0;
		Matrix result(1,this->rows,0);
		for(i=0;i<rows;++i){
			for(j=0;j<cols;j++){
				result.array[i]+=this->array[j+(i*this->cols)] * rhs[j];
			}
		}
		return result;
	}
	Matrix<T> operator/(const std::vector<T> &rhs) const{
		std::vector<T> tmp=rhs;
		for(size_t i=0;i<rhs.size();i++){
			tmp=1.0/rhs[i];
		}
		return *this * tmp;
	}

	/**
	 * The arith&&= operators.
	 * scalars first. Then matrices. Then finally with std::vectors.
	 */
	Matrix<T> &operator+=(const T scalar) {
		size_t i=0;
		size_t j=0;

		for(i=0; i<rows; i++) {
			for(j=0; j<cols; j++) {
				this->array[j+(this->cols*i)] += scalar;
			}
		}

		return *this;
	}
	
	Matrix<T> &operator-=(const T scalar) {
		size_t i=0;
		size_t j=0;

		for(i=0; i<rows; i++) {
			for(j=0; j<cols; j++) {
				this->array[j+(this->cols*i)] -= scalar;
			}
		}

		return *this;
	}

	Matrix<T> &operator*=(const T &scalar){
		size_t i=0,j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				this-array[j+(this->cols*i)]*=scalar;
			}
		}
		return *this;
	}

	Matrix<T> &operator%=(const T &scalar) {
		size_t i=0;
		size_t j=0;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				this->array[j+(this->cols*i)] %= scalar;
			}
		}
		return *this;
	}

	Matrix<T> &operator+=(const Matrix<T> &other_matrix) {
		size_t i=0;
		size_t j=0;

		if((cols != other_matrix.cols)||(rows != other_matrix.rows)){
			_invalid_dim("addition",other_matrix);
		}

		for(i=0; i<rows; i++) {
			for(j=0; j<cols; j++) {
				this->array[j+(this->cols*i)] += other_matrix.array[j+(this->cols*i)];
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
				this->array[j+(this->cols*i)] -= other_matrix.array[j+(this->cols*i)];
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
					this->array[j+(other_matrix.cols*i)]+=this->array[i+(k*this->cols)] * other_matrix.array[k+(j*other_matrix.cols)];
				}
			}
		}
		return *this;
	}

	Matrix<T> &operator/=(const Matrix<T> &other_matrix){
		*this *= !other_matrix;
		return *this;
	}
	
	/**
	 * Comparison Operators are below here. They're implemented because I may just use them in the future and I'd rather
	 * have them implemented now rather than having to do it later.
	 */

	bool operator==(const Matrix<T> &other_matrix) const{
		if((this->cols != other_matrix.cols)||(this->rows != other_matrix.rows)){
			return false;
		}
		size_t i=0,j=0;
		for(i=0;i<this->rows;i++){
			for(j=0;j<this->cols;j++){
				if(std::abs(this->array[j+(this->cols*i)] - other_matrix.array[j+(this->cols*i)]) > epsilon(this->array[j+(this->cols*i)])){
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
				if(this->array[j+(this->cols*i)]>other_matrix.array[j+(this->cols*i)]){
					return false;
				}
			}
		}
		return true;
	}

	bool operator<=(const Matrix<T> &other_matrix) const{
		return(*this < other_matrix);
	}

	bool operator>(const Matrix<T> &other_matrix) const{
		return !(*this < other_matrix);
	}

	bool operator>=(const Matrix<T> &other_matrix) const{
		return !(*this < other_matrix);
	}
	//compared against a scalar it's always going to be false.
	bool operator==(const T &rhs) const{
		return false;
	}
	bool operator !=(const T &rhs) const{
		return true;
	}
	bool operator >=(const T &rhs) const{
		return false;
	}
	bool operator <=(const T &rhs) const{
		return false;
	}
	// Output stream function for matrix
	friend std::ostream& operator<< <T>( std::ostream &, const Matrix<T> &);
	
	T _det()const{
		std::cout << "_det " <<((array[0]*array[3])-(array[1]*array[2])) << std::endl;
		return(array[0]*array[3])-(array[1]*array[2]);
	}

	T gae(void){
		size_t i,j,k;
		size_t swaps=0;
		std::vector<T> vec=this->array;

		for(i=0;i<rows-1;i++){
			for(j=i+1;j<rows;j++){
				if(std::abs(vec[i+(i*this->cols)]) < std::abs(vec[j+(i*this->cols)])){
					swaps++;
					for(k=0;k<cols;k++){
						std::swap(vec[i+(k*this->cols)],vec[j+(k*this->cols)]);
					}
				}
			}

			for(j=i+1;j<rows;j++){
				double tmp=vec[j+(i*this->cols)]/vec[i+(i*this->cols)];
				for(k=0;k<cols;k++){
					vec[j+(k*this->cols)]=vec[j+(k*this->cols)]-tmp*vec[i+(k*this->cols)];
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
				if(std::abs(vec[i+(i*this->cols)]) < std::abs(vec[j+(i*this->cols)])){
					swaps++;
					for(k=0;k<cols;k++){
						std::swap(vec[i+(k*this->cols)],vec[j+(k*this->cols)]);
					}
				}
			}

			for(j=i+1;j<rows;j++){
				double tmp=vec[j+(i*this->cols)]/vec[i+(i*this->cols)];
				for(k=0;k<cols;k++){
					vec[j+(k*this->cols)]=vec[j+(k*this->cols)]-tmp*vec[i+(k*this->cols)];
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
				tmp.array[z*(rows-1)+y] = array[i*this->cols+j];
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
			for(i = 0; i < rows; i++) {
				for(j = 0; j < rows; j++) {
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
		if(det == 0)
			throw std::invalid_argument("Matrix is Singular: Determinant is 0. No inversion is possible.");

		inversed=this->adj();
		try{
			det_inv=mod_inv(det,m);
		}
		catch(std::string &e){
			std::invalid_argument("Matrix is not invertible(mod "+std::to_string(m)+").");
		}

		size_t i=0,j=0;

		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				inversed.array[(i*this->cols)+j]=mod(det_inv*inversed.array[(i*this->cols)+j],m);
			}
		}
		return inversed;
	}

	Matrix<T> mul_mod(const T scalar, const T modulus) const{
		size_t i=0,j=0;
		Matrix<T> result(cols,rows,0);
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				result.array[j+(this->cols*i)]=mod(this->array[j+(this->cols*i)]*scalar,modulus);
			}
		}
		return result;
	}

	~Matrix();
	T det(void) const;
	Matrix<T> solve_gae() const;
	bool lud(double &determinate);
	bool lud(std::vector<size_t> &P);
	bool inv(void);
	bool inv_slow();
	bool solve(const std::vector<T> &right_side,std::vector<T> &solution) const;
	bool solve(const Matrix<T> &right_side, Matrix<T> &solution) const;
	bool solve_lud(const std::vector<T> &right_side,std::vector<T> &solution) const;
	bool solve_lud(const Matrix<T> &right_side, Matrix<T> &solution) const;
	void lud_backsub(const std::vector<size_t> &partition, const std::vector<T> &right_side,std::vector<T> &solution) const;
};

template <class T> Matrix<T>::~Matrix(){
	this->array.clear();
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T> &m){
	//int w = os.width();
	size_t rows=m.rows;
	size_t cols=m.cols;
	os << "[";
	for(size_t i=0; i < rows; i++) {
		os << "[";
		for(size_t j = 0; j < cols; j++) {
			os << m(i, j) <<(j == cols - 1 ? "]" : "\t,");
		}
		os <<((i < rows -1)? "," : "]");
		os << '\n';
	}
	return os;
}
/*
template <typename T> Matrix<T> Matrix<T>::operator+(T scalar,const Matrix<T> rhs){
	Matrix<T> result(rhs.cols,rhs.rows,0);
	size_t i=0,j=0;
	for(i=0;i<rhs.rows;i++){
		for(j=0;j<rhs.cols;j++){
			result[j+(rhs.cols*i)]=rhs[j+(rhs.cols*i)]+scalar;
		}
	}
	return result;
}
 */
/*
 * since I need to also support the basic operators as if they were _normal_ I have to define them like so.
 * i'm basically overloading the global operator instead of having it be part of the class. First is the arithematic operators.
 * then it's the comparison ones.
 */
template <typename T> Matrix<T> operator+(const T scalar, const Matrix<T> rhs){
	//no reason to redefine the whole function again. Why not just reuse my already defined code. This codebase is large
	// enough already.
	return rhs+scalar;
}
template <typename T> Matrix<T> operator-(const T scalar, const Matrix<T> rhs){
	return rhs-scalar;
}
template <typename T> Matrix<T> operator*(const T scalar, const Matrix<T> rhs){
	return rhs*scalar;
}
template <typename T> Matrix<T> operator/(const T scalar, const Matrix<T> rhs){
	return rhs/scalar;
}
//then the comparison operators.
template <typename T> bool operator==(const T scalar, const Matrix<T> rhs) {
	return false;
}
template <typename T> bool operator !=(const T scalar, const Matrix<T> rhs){
	return true;
}
template <typename T> bool operator >=(const T scalar, const Matrix<T> rhs){
	return false;
}
template <typename T> bool operator <=(const T scalar, const Matrix<T> rhs){
	return false;
}
template<>Matrix<double> Matrix<double>::solve_gae() const{
	if(this->rows < (this->cols -1 )){
		throw std::invalid_argument("Matrix<double>::solve_gae() is impossible! You must have as many rows as you have variables. Rows must equal columns -1. Rows=" + std::to_string(this->rows) + " Cols=" + std::to_string(this->cols) +"\n");
	}
	std::vector<double> vec(this->array);
	std::vector<double> tmp_vars(this->rows);

	size_t i,j,k;
	for (i=0;i<rows;i++) {
		for (k = i + 1; k < rows; k++) {
			if (std::abs(vec[i + (i * cols)]) < std::abs(vec[i + (k * cols)])) {
				for (j = 0; j <= rows; j++) {
					std::swap(vec[j + (i * cols)], vec[j + (k * cols)]);
				}
			}
		}
	}

	for (i=0;i<rows-1;i++){
		for (k=i+1;k<rows;k++){
			double t=vec[i+(k*cols)]/vec[i+(i*cols)];
			for (j=0;j<=rows;j++){
				vec[j+(k*cols)]-=t*vec[j+(i*cols)];
			}
		}
	}

	for (i=rows-1;;i--) {
		tmp_vars[i] = vec[rows + (i * cols)];
		for (j = i + 1; j < rows; j++) {
			if (j != i) {
				tmp_vars[i] -= vec[j + (i * cols)] * tmp_vars[j];
			}
		}
		tmp_vars[i] /= vec[i + (i * cols)];
		if(i==0) break;
	}
	return Matrix<double>(tmp_vars,rows,1);
}

template<typename T> Matrix<T> Matrix<T>::solve_gae()const{
	if(this->rows < (this->cols -1 )){
		throw std::invalid_argument("Matrix<double>::solve_gae() is impossible! You must have as many rows as you have variables. Rows must equal columns -1. Rows=" + std::to_string(this->rows) + " Cols=" + std::to_string(this->cols) +"\n");
	}


	std::vector<double> vec(this->array.begin(), this->array.end());
	std::vector<double> tmp_vars(this->rows);
	size_t i,j,k;
	for (i=0;i<rows;i++) {
		for (k = i + 1; k < rows; k++) {
			if (std::abs(vec[i + (i * cols)]) < std::abs(vec[i + (k * cols)])) {
				for (j = 0; j <= rows; j++) {
					std::swap(vec[j + (i * cols)], vec[j + (k * cols)]);
				}
			}
		}
	}

	for (i=0;i<rows-1;i++){
		for (k=i+1;k<rows;k++){
			double t=vec[i+(k*cols)]/vec[i+(i*cols)];
			for (j=0;j<=rows;j++){
				vec[j+(k*cols)]-=t*vec[j+(i*cols)];
			}
		}
	}

	for (i=rows-1;;i--) {
		tmp_vars[i] = vec[rows + (i * cols)];
		for (j = i + 1; j < rows; j++) {
			if (j != i) {
				tmp_vars[i] -= vec[j + (i * cols)] * tmp_vars[j];
			}
		}
		tmp_vars[i] /= vec[i + (i * cols)];
		if(i==0) break;
	}

	std::vector<T> vars(this->rows);
	for(i=0;i<rows;i++){
		vars[i]=round(tmp_vars[i]);
	}
	return Matrix<T>(vars,rows,1);
}

//this one is for calculating the determinant. Thus the decomposied

template <> bool Matrix<double>::lud(double &determinant){
	
	if(this->rows < (this->cols -1 )){
		throw std::invalid_argument("Matrix<double>::solve_gae() is impossible! You must have as many rows as you have variables. Rows must equal columns -1. Rows=" + std::to_string(this->rows) + " Cols=" + std::to_string(this->cols) +"\n");
	}
	
	size_t i,j,k;
	//this is the maximal value in our array during swapping.
	size_t ip=0;
	double max_matrix,candidate_matrix;
	std::vector<size_t> Partition(this->rows);
	determinant=1.0;
	size_t n = this->rows;

	for(i=0; i < n; i++){
		Partition[i] = i;

	}
	
	for(i=0; i < n-1; i++){
		ip = i;
		max_matrix = fabs(this->array[Partition[i]*n+i]);
		for(j=i+1; j < n; j++){		
			if((candidate_matrix = fabs( this->array[Partition[j]*n+i])) > max_matrix){
				max_matrix = candidate_matrix;
				ip = j;				
			}
		}
		
		if(ip != i){
			std::swap( Partition[i], Partition[ip]);
			determinant= -determinant;
		}

		size_t ipos = Partition[i] * n;

		if(fabs( this->array[ipos+i]) < epsilon( this->array[ipos+i]))
			return false;

		determinant*=this->array[ipos+i];
		for(j=i+1; j < n; j++){
			size_t jpos = Partition[j] * n;
			double a = this->array[jpos+i] /= this->array[ipos+i];

			for(k=i+1; k < n; k++){
				this->array[jpos+k] -= a * this->array[ipos+k];
			}
		}
	}
	determinant*= this->array[Partition[i]*n+i];

	return true;
}

template <> bool Matrix<double>::lud(std::vector<size_t> &Partition){
	size_t i,j,k;
	//this is the maximal value in our array during swapping.
	size_t ip=0;
	double max_matrix,candidate_matrix;

	if(this->rows != this->cols)
		throw std::invalid_argument( "matrix<T>::lud: Non-square matrix!");

	if(this->rows != Partition.size()){
		Partition.resize( this->rows);
	}

	size_t n = this->rows;


	for(i=0; i < n; i++){
		Partition[i] = i;

	}

	for(i=0; i < n-1; i++){
		ip = i;
		max_matrix = abs(this->array[Partition[i]*n+i]);
		for(j=i+1; j < n; j++){		
			if((candidate_matrix = abs( this->array[Partition[j]*n+i])) > max_matrix){
				max_matrix = candidate_matrix;
				ip = j;				
			}
		}
		if(ip != i){	
			std::swap( Partition[i], Partition[ip]);
		}

		size_t ipos = Partition[i] * n;

		if(abs( this->array[ipos+i]) < epsilon( this->array[ipos+i]))
			return false;


		for(j=i+1; j < n; j++){
			size_t jpos = Partition[j] * n;
			double a = this->array[jpos+i] /= this->array[ipos+i];

			for(k=i+1; k < n; k++){
				this->array[jpos+k] -= a * this->array[ipos+k];
			}
		}
	}

	return true;
}
template <typename T> bool Matrix<T>::lud(double &determinant){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<T>::lud(): LUD doesn't work on a non-square matrix!");
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
template <typename T> bool Matrix<T>::lud(std::vector<size_t> &P){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<float>::lud(): LUD doesn't work on a	non-square matrix!");
	}
	
	std::vector<double> vec(this->array.begin(),this->array.end());
	Matrix<double> tmp_matrix(vec,this->cols,this->rows);
	size_t i=0;
	tmp_matrix.lud(P);
	size_t max=(this->cols);
	for(i=0;i<(max*max);i++){
		this->array[i]=static_cast<T>(floor(tmp_matrix[i]));

	}
	return true;
}
//I have to break these templates out because the way that I'm going to do integer types.

//this inversion takes ~O(2/3(n**3)+(1.709*(n**3))) iterations.
template <> bool Matrix<double>::inv(){
	if(this->rows != this->cols){
		throw std::invalid_argument("matrix<double>::inv(): Can't invert a non-square matrix.");
	}
	long long int i, j, k,n=static_cast<long long int>(this->cols),i_pos=0,j_pos=0;
	long long int i_max=0;
	std::vector<double> P(cols);
	//size_t j_pos,i_pos;
	for(i=0; i < n; i++)
		P[i] = i;

	for(i=0; i < n; i++){
		double ta,tb;
		double a=0.0;
		i_pos = i * n;
		i_max = i;
		ta = std::abs( this->array[i_pos + i]);
		for(j=i + 1; j < n; j++){;
			if((tb = std::abs(this->array[j * n + i])) > ta){
				ta = tb;
				i_max = j;
			}
		}
		if(ta < epsilon( a))
			return false;

		if(i_max != i){
			std::swap(P[i], P[i_max]);
			for(j_pos=i_max*n, j=0; j < n; j++){
				std::swap(this->array[i_pos + j], this->array[j_pos + j]);;
			}
		}

		a = 1.0 / this->array[i_pos + i];
		this->array[i_pos + i] = double(1);

		for(j=0; j < n; j++){;
			this->array[i_pos+j] *= a;
		}

		for(j=0; j < n; j++){;
			if(j != i){
				j_pos = j * n;
				a = this->array[j_pos + i];
				this->array[j_pos + i] = double(0);
				for(k=0; k < n; k++){;
					this->array[j_pos+k] -= a * this->array[i_pos+k];
				}
			}
		}
	}

	for(i=0; i < n; i++){;
		if(i != P[i]){
			k = i + 1;
			while(i != P[k])
				k++;
			for(j=0; j < n; j++){
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
template <> void Matrix<double>::lud_backsub(const std::vector<size_t> &partition, const std::vector<double> &v,std::vector<double> &s) const{
	size_t i,j,k,ip;
	bool nonzero = false;
	size_t n=this->rows;
	for(k=0,i=0; i < n; i++)
	{
		ip = partition[i];
		s[i] = v[ip];

		if(nonzero)
		{
			ip *= n;
			for(j=k; j < i; j++)
				s[i] -= this->array[ip+j] * s[j];
		}
		else if(s[i] != 0.0)
		{
			k = i;
			nonzero = true;
		}
	}
	for(i=n-1; ; i--)
	{
		ip = partition[i] * n;
		for(j=i+1; j < n; j++)
			s[i] -= this->array[ip+j] * s[j];
		s[i] /= this->array[ip+i];
		if(i == 0) break;
	}
}

template <typename T> void Matrix<T>::lud_backsub(const std::vector<size_t> &Partition, const std::vector<T> &values,std::vector<T> &solution) const{
	
	std::vector<double> vec(this->array.begin(),this->array.end());
	Matrix<double> tmp_matrix(vec,this->cols,this->rows);
	tmp_matrix.lud_backsub(Partition,values,solution);
}

template <> bool Matrix<double>::solve(const std::vector<double> &values,std::vector<double> &solution) const{
	Matrix<double> tmp = *this;
	std::vector<size_t> Partition(this->rows);
	if(tmp.lud(Partition)){
		tmp.lud_backsub(Partition,values,solution);
		return true;
	}
	return false;
}

template <typename T> bool Matrix<T>::solve(const std::vector<T> &values, std::vector<T> &solution) const{
	std::vector<double> vec(this->array.begin(),this->array.end());
	Matrix<double> tmp_matrix(vec,this->cols,this->rows);
	return tmp_matrix.solve(values,solution);
}
//this'll be modified to basically read in a file's line later on.
//but for now it's just here as a placeholder.
std::vector<Matrix<char>> __chunk_it(const std::string input_data){
	size_t chunk_size=2;
	size_t mat_size=chunk_size*chunk_size;
	//this will be modified later to append enough data to make it an even number.
	size_t items=input_data.size()/(mat_size);
	//create our return item.
	std::vector<Matrix<char>> result(items);
	//loop over the entire input string. For now it's just a string.
	for(size_t i=0;i<items;i++){
		//create my matrix.
		result[i]=Matrix<char>(chunk_size,chunk_size);
		for(size_t j=0;j<chunk_size;j++){
			for(size_t k=0;k<chunk_size;k++){
				//insert into it at the correct spot the correct character.
				//later I'll actually do the lookup part.
				result[i][k+(j*chunk_size)]=input_data[(i*mat_size)+(j+(k*chunk_size))];
			}
		}
	}
	return result;
}
typedef Matrix<char> matrix_char;
typedef Matrix<int> matrix_int;
typedef Matrix<unsigned int> matrix_uint;
typedef Matrix<double> matrix_double;
typedef Matrix<float> matrix_float;
typedef Matrix<long long int> matrix_long;
typedef Matrix<unsigned long long> matrix_ulong;
#endif //_MATRIX_CLASS_