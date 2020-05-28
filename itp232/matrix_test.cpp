#include <iostream>
#include "matrix.hxx"

/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Matrix Class Module
 *
 */
template <typename T> void test_print(std::string input,T expected,T result){
    if(expected != result){
        std::cout << input << " test failed" << std::endl;
    }
    else{
        std::cout << input << " test succeeded." << std::endl;
    }
}
template <typename T> void test_print_matrix(Matrix<T> &lhs, Matrix<T> &rhs){
    std::cout << "Matrix A=" << lhs << "Matrix B=" << rhs << std::endl;
}
template <typename T,typename U> void test_print_m_scalar(Matrix<T> &lhs, U &rhs){
    std::cout << "Matrix A " << lhs << "scalar=" << rhs << std::endl;
}

template <typename T,typename U> void test_print_m_scalar(U &lhs,Matrix<T> &rhs){
std::cout << "scalar=" << rhs << "Matrix A " << lhs  << std::endl;
}
/*
 * This function will go through all of the comparison operators to verify that they work.
 */
void test_comparisons(){
    matrix_int least(2, 2, 1);
    matrix_int most(2, 2, 3);
    matrix_int equals_least(2, 2, 1);
    int scalar=0;
    bool result;
    bool expected;
    std::cout << "Comparison operators " << std::endl;
    result=(least != most);
    expected=true;
    test_print("Matrix A !=(Not Equals) Matrix B",expected,result);
    if(result != expected){
        test_print_matrix(least, most);
    }
    result=(least == equals_least);
    expected=true;
    test_print("Matrix A ==(Equals) Matrix B",expected,result);
    if(result != expected){
        test_print_matrix(least, most);
    }
    result=(least >= most);
    expected=false;
    test_print("Matrix A >=Matrix B",expected,result);
    if(result != expected){
        test_print_matrix(least, most);
    }
    result=(least <= most);
    expected=true;
    test_print("Matrix A <= Matrix B",expected,result);
    if(result != expected){
        test_print_matrix(least, most);
    }
    result=(least == scalar);
    expected=false;
    test_print("Matrix A == scalar",expected,result);
    if(result != expected){
        test_print_m_scalar(least,scalar);
    }
    result=(scalar != least);
    expected=true;
    test_print("scalar != Matrix A",expected,result);
    if(result != expected){
        test_print_m_scalar(scalar,least);
    }
}
int main(){
    test_comparisons();
    return 0;
}