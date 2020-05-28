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
template <typename T> void test_print_matrix(std::string op,Matrix<T> &lhs, Matrix<T> &rhs){
    std::cout << "Matrix A=" << lhs << "Matrix B=" << rhs << std::endl;
}
void test_comparisons(){
    matrix_int test_least(2,2,1);
    matrix_int test_greatest(2,2,3);
    matrix_int test_matrix(2,2,1);
    bool result;
    std::cout << "Comparison operators " << std::endl;
    result=(test_least != test_greatest);
    test_print("!=(Not Equals) ",true,result);
    if(!result){
        test_print_matrix("!=",test_least,test_greatest);
    }
    result=(test_least == test_matrix);
    test_print("==(Not Equals) ",false,result);
    if(!result){
        test_print_matrix("==",test_least,test_greatest);
    }
    result=(test_least >= test_greatest);
    test_print(">=(greater than equals",false,result);
    if(!result){
        test_print_matrix(">=",test_least,test_greatest);
    }
    result=(test_least <= test_greatest);
    test_print("<=(less than equals) ",true,result);
    if(!result){
        test_print_matrix("<=",test_least,test_greatest);
    }
}
int main(){
    test_comparisons();
    return 0;
}