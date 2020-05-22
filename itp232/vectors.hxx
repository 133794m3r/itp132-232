/**
 * This source file overloads the templated vectors so that I can store this somewhere else.
 * Basically it does, +,-,*,/, and %. No operator equals is included in here.
 * It also does the << operator so that I can print it to the terminal/file so that I can easily debug it.
 *
 */
#include <vector>
#include <stdexcept>
#ifndef VECTORS_HXX
#define VECTORS_HXX
template <typename T> std::vector<T> operator+(const std::vector<T> &lhs, std::vector<T> &rhs){
	size_t lhs_size=lhs.size();
	size_t rhs_size=rhs.size();
	if(lhs_size != rhs_size){
		throw std::invalid_argument("For addition between vectors to work both must be the same size! lhs.size()="
		+std::to_string(lhs_size)+"rhs.size()="+std::to_string(rhs_size)+"\r\n");
	}
	std::vector<T> tmp_vec(lhs_size);
	for(size_t i=0;i<lhs_size;i++){
		tmp_vec[i]=lhs[i]+rhs[i];
	}
	return tmp_vec;
}
template <typename T> std::vector<T> operator-(const std::vector<T> &lhs, std::vector<T> &rhs){
	size_t lhs_size=lhs.size();
	size_t rhs_size=rhs.size();
	if(lhs_size != rhs_size){
		throw std::invalid_argument("For subtraction between vectors to work both must be the same size! lhs.size()="
									+std::to_string(lhs_size)+"rhs.size()="+std::to_string(rhs_size)+"\r\n");
	}
	std::vector<T> tmp_vec(lhs_size);
	for(size_t i=0;i<lhs_size;i++){
		tmp_vec[i]=lhs[i]-rhs[i];
	}
	return tmp_vec;
}
template <typename T> std::vector<T> operator*(const std::vector<T> &lhs, std::vector<T> &rhs){
	size_t lhs_size=lhs.size();
	size_t rhs_size=rhs.size();
	if(lhs_size != rhs_size){
		throw std::invalid_argument("For multiplication between vectors to work both must be the same size! lhs.size()="
									+std::to_string(lhs_size)+"rhs.size()="+std::to_string(rhs_size)+"\r\n");
	}
	std::vector<T> tmp_vec(lhs_size);
	for(size_t i=0;i<lhs_size;i++){
		tmp_vec[i]=lhs[i]*rhs[i];
	}
	return tmp_vec;
}
template <typename T> std::vector<T> operator/(const std::vector<T> &lhs, std::vector<T> &rhs){
	size_t lhs_size=lhs.size();
	size_t rhs_size=rhs.size();
	if(lhs_size != rhs_size){
		throw std::invalid_argument("For division between vectors to work both must be the same size! lhs.size()="
									+std::to_string(lhs_size)+"rhs.size()="+std::to_string(rhs_size)+"\r\n");
	}
	std::vector<T> tmp_vec(lhs_size);
	for(size_t i=0;i<lhs_size;i++){
		tmp_vec[i]=lhs[i]/rhs[i];
	}
	return tmp_vec;
}

template <class T> std::ostream& operator<<(std::ostream& os, const std::vector<T> &m){
	size_t m_size=m.size();
	os << "[";
	for(size_t i=0; i < m.size(); i++) {
		os << m[i]  <<(i == m_size - 1 ? "" : ",");
	}
	os << "]" << std::endl;
	return os;
}
template <class T> std::istream& operator>>(std::istream& is, std::vector<T> &m){
	size_t n=m.size();
	for(size_t i=0;i<n;i++){
		is >> m[i];
	}
	return is;
}
#endif //VECTORS_HXX
