#include <iostream>
#include "matrix.hxx"
#include "matrix_test.hxx"
/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Matrix Class Module
 *
 */

//forward declarations.
void test_comparisons();

void test_arithmetic_int();

void test_arithmetic_double();

void test_det();

//the actual driver program to do the testing.  It just calls all of them in order and prints tests.
int main(void) {
	/*
	test_comparisons();
	test_arithmetic_int();
	test_arithematic_double();
	*/
	test_det();
	return 0;
}

/*
 * This function will go through all of the comparison operators to verify that they work.
 */
void test_comparisons() {
	matrix_int least(2, 2, 1);
	matrix_int most(2, 2, 3);
	matrix_int equals_least(2, 2, 1);
	int scalar = 0;
	bool result;
	bool expected;
	std::cout << "Comparison operators " << std::endl;
	result = (least != most);
	expected = true;
	test_print("Matrix A !=(Not Equals) Matrix B", expected, result);
	if (result != expected) {
		test_print_matrix(least, most);
	}
	result = (least == equals_least);
	expected = true;
	test_print("Matrix A ==(Equals) Matrix B", expected, result);
	if (result != expected) {
		test_print_matrix(least, most);
	}
	result = (least >= most);
	expected = false;
	test_print("Matrix A >=Matrix B", expected, result);
	if (result != expected) {
		test_print_matrix(least, most);
	}
	result = (least <= most);
	expected = true;
	test_print("Matrix A <= Matrix B", expected, result);
	if (result != expected) {
		test_print_matrix(least, most);
	}
	result = (least == scalar);
	expected = false;
	test_print("Matrix A == scalar", expected, result);
	if (result != expected) {
		test_print_m_scalar(least, scalar);
	}
	result = (scalar != least);
	expected = true;
	test_print("scalar != Matrix A", expected, result);
	if (result != expected) {
		test_print_m_scalar(scalar, least);
	}
}

void test_arithmetic_int() {
	matrix_int lhs_int(2, 2, 1);
	lhs_int(0, 0) = 1;
	lhs_int(0, 1) = 2;
	lhs_int(1, 0) = 3;
	lhs_int(1, 1) = 4;
	matrix_int rhs_int(2, 2, 1);
	rhs_int(0, 0) = 4;
	rhs_int(0, 1) = 3;
	rhs_int(1, 0) = 2;
	rhs_int(1, 1) = 1;
	std::vector<int> int_vec = {1, 1, 1, 1};
	/*
	 * the result matrices for the basic operations.
	 * Baiscally I do each operation defined seperately, I may change my mind and just redefine the result each and
	 * everytime that we do an operation for the expected result but I don't know yet.
	 */
	matrix_int result_int(2, 2, 1);
	matrix_int expected_int(2, 2, 1);
	int scalar = 10;
	std::cout << "Matrix<int> Arithmetic tests" << std::endl;
	result_int = lhs_int + rhs_int;
	int_vec = {5, 5, 5, 5};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A + Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A + Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int - rhs_int;
	int_vec = {-3, -1, 1, 3};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A - Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A - Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int * rhs_int;
	int_vec = {8, 5, 20, 13};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A * Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A * Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int / rhs_int;
	int_vec = {1, -3, 1, -5};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A / Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A / Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int + scalar;
	int_vec = {11, 12, 13, 14};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A + scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A + scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = scalar + lhs_int;
	if (result_int != expected_int) {
		std::cout << "(scalar + Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(scalar + Matrix A) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int - scalar;
	int_vec = {-9, -8, -7, -6};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A - scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A - scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = scalar - lhs_int;
	if (result_int != expected_int) {
		std::cout << "(scalar - Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(scalar - Matrix A) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int * scalar;
	int_vec = {10, 20, 30, 40};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A * scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A * scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = scalar * lhs_int;
	if (result_int != expected_int) {
		std::cout << "(scalar * Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(scalar * Matrix A) == Matrix C test succeeded" << std::endl;
	}
	//of course this is going to be zero but still have to make sure.
	result_int = lhs_int / scalar;
	int_vec = {0, 0, 0, 0};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A / scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A / scalar) == Matrix C test succeeded" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Matrix<int> inplace arithematic operators" << std::endl;
	result_int = lhs_int;
	result_int += rhs_int;
	int_vec = {5, 5, 5, 5};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Marix A += Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A += Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int -= rhs_int;
	int_vec = {-3, -1, 1, 3};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A -= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A -= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int *= rhs_int;
	int_vec = {8, 5, 20, 13};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A *= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A *= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int /= rhs_int;
	int_vec = {1, -3, 1, -5};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A /= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "Matrix B = " << rhs_int << "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A /= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int += scalar;
	int_vec = {11, 12, 13, 14};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A += scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A += scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int -= scalar;
	int_vec = {-9, -8, -7, -6};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A -= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A -= scalar) == Matrix C test succeeded" << std::endl;
	}
	result_int = lhs_int;
	result_int *= scalar;
	int_vec = {10, 20, 30, 40};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A *= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A *= scalar) == Matrix C test succeeded" << std::endl;
	}
	//of course this is going to be zero but still have to make sure.
	result_int = lhs_int;
	result_int /= scalar;
	int_vec = {0, 0, 0, 0};
	expected_int.set_arr(int_vec);
	if (result_int != expected_int) {
		std::cout << "(Matrix A /= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_int << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_int << std::endl;
		std::cout << "Result = " << result_int << std::endl;
	} else {
		std::cout << "(Matrix A /= scalar) == Matrix C test succeeded" << std::endl;
	}
	std::cout << std::endl;
}

void test_arithematic_double() {
	matrix_double lhs_dbl(2, 2, 1.0);
	lhs_dbl(0, 0) = 1.4;
	lhs_dbl(0, 1) = 2.3;
	lhs_dbl(1, 0) = 3.2;
	lhs_dbl(1, 1) = 4.1;
	matrix_double rhs_dbl(2, 2, 1.0);
	rhs_dbl(0, 0) = 4.1;
	rhs_dbl(0, 1) = 3.2;
	rhs_dbl(1, 0) = 2.3;
	rhs_dbl(1, 1) = 1.4;
	std::vector<double> dbl_vec = {1.0, 1.0, 1.0, 1.0};
	matrix_double result_dbl(2, 2, 1.0);
	matrix_double expected_dbl(2, 2, 1.0);
	double scalar = 10.5;

	std::cout << "Matrix<double> Arithmetic tests" << std::endl;
	result_dbl = lhs_dbl + rhs_dbl;
	dbl_vec = {5.5, 5.5, 5.5, 5.5};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A + Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A + Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl + scalar;
	dbl_vec = {11.9, 12.8, 13.7, 14.6};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A + scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A + scalar) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = scalar + lhs_dbl;
	if (result_dbl != expected_dbl) {
		std::cout << "(scalar + Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(scalar + Matrix A) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl - rhs_dbl;
	dbl_vec = {-2.7, -0.9, 0.9, 2.7};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A - Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A - Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl - scalar;
	dbl_vec = {-9.1, -8.2, -7.3, -6.4};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A - scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A - scalar) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = scalar - lhs_dbl;
	if (result_dbl != expected_dbl) {
		std::cout << "(scalar - Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(scalar - Matrix A) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl * rhs_dbl;
	dbl_vec = {11.03, 7.7, 22.55, 15.98};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A * Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A * Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl * scalar;
	dbl_vec = {14.7, 24.15, 33.6, 43.05};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A * scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A * scalar) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = scalar * lhs_dbl;
	if (result_dbl != expected_dbl) {
		std::cout << "(scalar * Matrix A) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(scalar * Matrix A) == Matrix C test succeeded" << std::endl;
	}

	//we have to round it because it's a repeating fraction.
	result_dbl = matrix_round(lhs_dbl / rhs_dbl);
	dbl_vec = {2.0556, -3.0556, 3.0556, -4.0556};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A / Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A / Matrix B) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = matrix_round(lhs_dbl / scalar);
	dbl_vec = {0.1333, 0.2190, 0.3048, 0.3905};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A / scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A / scalar) == Matrix C test succeeded" << std::endl;
	}
	std::cout << std::endl;


	std::cout << "Matrix<dbl> inplace arithematic operators" << std::endl;
	result_dbl = lhs_dbl;
	result_dbl += rhs_dbl;
	dbl_vec = {5.5, 5.5, 5.5, 5.5};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Marix A += Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A += Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl;
	result_dbl += scalar;
	dbl_vec = {11.9, 12.8, 13.7, 14.6};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A += scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A += scalar) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl;
	result_dbl -= rhs_dbl;
	dbl_vec = {-2.7, -0.9, 0.9, 2.7};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A -= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A -= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl;
	result_dbl -= scalar;
	dbl_vec = {-9.1, -8.2, -7.3, -6.4};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A -= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A -= scalar) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl;
	result_dbl *= rhs_dbl;
	dbl_vec = {11.03, 7.7, 22.55, 15.98};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A *= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A *= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl;
	result_dbl *= scalar;
	dbl_vec = {14.7, 24.15, 33.6, 43.05};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A *= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A *= scalar) == Matrix C test succeeded" << std::endl;
	}

	result_dbl = lhs_dbl;
	result_dbl /= rhs_dbl;
	result_dbl = matrix_round(result_dbl);
	dbl_vec = {2.0556, -3.0556, 3.0556, -4.0556};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A /= Matrix B) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "Matrix B = " << rhs_dbl << "Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A /= Matrix B) == Matrix C test succeeded" << std::endl;
	}
	result_dbl = lhs_dbl;
	result_dbl /= scalar;
	result_dbl = matrix_round(result_dbl);
	dbl_vec = {0.1333, 0.2190, 0.3048, 0.3905};
	expected_dbl.set_arr(dbl_vec);
	if (result_dbl != expected_dbl) {
		std::cout << "(Matrix A /= scalar) == Matrix C test failed" << std::endl;
		std::cout << "Matrix A = " << lhs_dbl << "scalar = " << scalar << std::endl <<
				  " Matrix C = " << expected_dbl << std::endl;
		std::cout << "Result = " << result_dbl << std::endl;
	} else {
		std::cout << "(Matrix A /= scalar) == Matrix C test succeeded" << std::endl;
	}

	std::cout << std::endl;
}

void test_det() {
	std::vector<int> vec_int = {7, 11, 8, 11};
	matrix_int test_int(vec_int, 2, 2);
	int det = test_int.det();
	int expect_int = -11;
	std::cout << "Int tests." << std::endl;
	std::cout << "2x2 tests." << std::endl;
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " << stringify_matrix(test_int);

	double det2 = 0.0;
	test_int.lud(det2);
	test_print("Lud calculation directly --> test_int.lud(det) == " + std::to_string(expect_int), expect_int, det);

	std::cout << "3x3 tests" << std::endl;
	expect_int = 0;
	vec_int = {3, 5, 7, 13, 15, 17, 22, 24, 26};
	test_int = matrix_int(vec_int, 3, 3);
	det = test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " << stringify_matrix(test_int);

	vec_int = {211,312,415,514,223,213,789,897,978};
	expect_int = 19618908;
	test_int.set_arr(vec_int);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " << stringify_matrix(test_int);

	expect_int=-176;
	vec_int = {3, 5, 7, 11, 19, 21, 22, 27, 31};
	test_int.set_arr(vec_int);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " << stringify_matrix(test_int);

	std::cout << "4x4 tests" << std::endl;
	expect_int = 12;
	vec_int = {0, 1, 3, 5, 5, 3, 1, 0, 0, 4, 6, 8, 8, 6, 2, 0};
	test_int = matrix_int(vec_int, 4, 4);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " << stringify_matrix(test_int);

	expect_int=-1270230;
	vec_int={31, 21, 41, 55, 66, 76, 81, 90, 91, 93, 95, 97, 99, 100, 35, 41};
	test_int.set_arr(vec_int);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " << stringify_matrix(test_int);

	vec_int={51, 51, 41, 55, 66, 76, 81, 90, 91, 93, 95, 97, 103, 200, 351, 411};
	expect_int=965609;
	test_int.set_arr(vec_int);
	det=test_int.det();
	test_print("Matrix A.det() == " + std::to_string(expect_int), expect_int, det);
	if (expect_int != det)
		std::cout << "Matrix A = " << stringify_matrix(test_int);

	return;
}
