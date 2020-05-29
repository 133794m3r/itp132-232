#include <iostream>
#include "matrix.hxx"
/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Matrix Class Module
 *
 */

//TODO: Once I can read from files I'll read the matrices to test from from there but for now, it's fine to just do it like this.
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

template <typename T,typename U> void test_print_m_scalar(const U &lhs,const Matrix<T> &rhs){
std::cout << "scalar=" << rhs << "Matrix A " << lhs  << std::endl;
}
template <typename T> void print_matrix(Matrix<T> a,Matrix<T> b){

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
void test_arithmetic_int(){
    matrix_int lhs_int(2, 2, 1);
    lhs_int(0, 0)=1;lhs_int(0, 1)=2;
    lhs_int(1, 0)=3;lhs_int(1, 1)=4;
    matrix_int rhs_int(2, 2, 1);
    rhs_int(0,0)=4;rhs_int(0,1)=3;
    rhs_int(1,0)=2;rhs_int(1,1)=1;
    std::vector<int> int_vec={1,1,1,1};
    /*
     * the result matrices for the basic operations.
     * Baiscally I do each operation defined seperately, I may change my mind and just redefine the result each and
     * everytime that we do an operation for the expected result but I don't know yet.
     */
    matrix_int result_int(2,2,1);
    matrix_int expected_int(2,2,1);
    int scalar=10;
    std::cout << "Matrix<int> Arithmetic tests" << std::endl;
    result_int=lhs_int+rhs_int;
    int_vec={5,5,5,5};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A + Matrix B) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A + Matrix B) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int-rhs_int;
    int_vec={-3,-1,1,3};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A - Matrix B) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A - Matrix B) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int*rhs_int;
    int_vec={8, 5, 20, 13};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A * Matrix B) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A * Matrix B) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int/rhs_int;
    int_vec={1, -3, 1, -5};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A / Matrix B) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A / Matrix B) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int+scalar;
    int_vec={11,12,13,14};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A + scalar) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
        "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A + scalar) == Matrix C test succeeded" << std::endl;
    }
    result_int=scalar+lhs_int;
    if(result_int != expected_int){
        std::cout << "(scalar + Matrix A) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(scalar + Matrix A) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int-scalar;
    int_vec={-9,-8,-7,-6};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A - scalar) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
        " Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A - scalar) == Matrix C test succeeded" << std::endl;
    }
    result_int=scalar-lhs_int;
    if(result_int != expected_int){
        std::cout << "(scalar - Matrix A) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(scalar - Matrix A) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int*scalar;
    int_vec={10,20,30,40};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A * scalar) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  " Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A * scalar) == Matrix C test succeeded" << std::endl;
    }
    result_int=scalar*lhs_int;
    if(result_int != expected_int){
        std::cout << "(scalar * Matrix A) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(scalar * Matrix A) == Matrix C test succeeded" << std::endl;
    }
    //of course this is going to be zero but still have to make sure.
    result_int=lhs_int/scalar;
    int_vec={0,0,0,0};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A / scalar) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  " Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A / scalar) == Matrix C test succeeded" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Matrix<int> inplace arithematic operators" << std::endl;
    result_int=lhs_int;
    result_int+=rhs_int;
    int_vec={5,5,5,5};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Marix A += Matrix B) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A += Matrix B) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int;
    result_int-=rhs_int;
    int_vec={-3,-1,1,3};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A -= Matrix B) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A -= Matrix B) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int;
    result_int*=rhs_int;
    int_vec={8, 5, 20, 13};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A *= Matrix B) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A *= Matrix B) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int;
    result_int/=rhs_int;
    int_vec={1, -3, 1, -5};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A /= Matrix B) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A /= Matrix B) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int;
    result_int+=scalar;
    int_vec={11,12,13,14};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A += scalar) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  "Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A += scalar) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int;
    result_int-=scalar;
    int_vec={-9,-8,-7,-6};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A -= scalar) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  " Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A -= scalar) == Matrix C test succeeded" << std::endl;
    }
    result_int=lhs_int;
    result_int*=scalar;
    int_vec={10,20,30,40};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A *= scalar) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  " Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A *= scalar) == Matrix C test succeeded" << std::endl;
    }
    //of course this is going to be zero but still have to make sure.
    result_int=lhs_int;
    result_int/=scalar;
    int_vec={0,0,0,0};
    expected_int.set_arr(int_vec);
    if(result_int != expected_int){
        std::cout << "(Matrix A /= scalar) == Matrix C test failed" << std::endl;
        std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
                  " Matrix C = " << expected_int << std::endl;
        std::cout << "Result = " << result_int << std::endl;
    }
    else{
        std::cout << "(Matrix A /= scalar) == Matrix C test succeeded" << std::endl;
    }
    std::cout << std::endl;
}
void test_det(){
    return;
}
int main(){
    test_comparisons();
    test_arithmetic_int();
    test_det();
    return 0;
}