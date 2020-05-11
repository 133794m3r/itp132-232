#include <iostream>
#include "matrix.hxx"
/*
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
* Matrix Class Module Test Program
*/
int main() {
	int row=2;
	int col=2;
	//Matrix mat1(2,2,1);
	//std::cout << "mat1" << std::endl;
	//Matrix<int> result(row,col,0);
	int i=0;
	int j=0;
	int k=0;
	matrix_int mat1(col,row,0);

	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			mat1(i,j)=(k++);
		}
	}

	std::cout << "test_mat=[";
	for(i=0;i<row;i++){
		std::cout << "[";
		for(j=0;j<col;j++){
			std::cout << mat1(i,j);
			if(j < col-1)
				std::cout << ",";
		}
		std::cout << "]";
		if(i < row-1)
			std::cout << ",";	
	}
	std::cout << "];" << std::endl;
	
	row=2;
	col=2;

	matrix_int mat2(col,row,5);
	matrix_int result(2,2,0);

	std::cout << "mat2=[";
	for(i=0;i<col;i++){
		std::cout << "[";
		for(j=0;j<row;j++){
			std::cout << mat2(i,j);
			if(j < row-1)
				std::cout << ",";
		}
		std::cout << "]";
		if(i < col-1)
			std::cout << ",";	
	}
	std::cout << "];" << std::endl;	
	
	result=mat1-mat2;
	std::cout << "result=[";
	for(i=0;i<row;i++){
		std::cout << "[";
		for(j=0;j<col;j++){
			std::cout << result(i,j);
			if(j < col-1)
				std::cout << ",";
	}
		std::cout << "]";

		if(i < row-1)
		std::cout << ",";	
	}
	std::cout << "];" << std::endl;
	
	result=result+10;
	std::cout << "result=[";
	for(i=0;i<row;i++){
		std::cout << "[";
		for(j=0;j<col;j++){
			std::cout << result(i,j);
			if(j < col-1)
				std::cout << ",";
	}
		std::cout << "]";
		if(i < row-1)
			std::cout << ",";	
	}
	std::cout << "];" << std::endl;	
	std::cout << result << std::endl;

	matrix_double det_mat(2,2,0);
	k=1;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			det_mat(i,j)=(k+=2);
		}
	}
	std::cout << "det_matrix" << std::endl << det_mat << std::endl;
	double the_determinant=det_mat.det();
	std::cout << the_determinant << std::endl;
	double arr[4]={7,11,8,11};
	std::cout << "Hill Cipher Tests" << std::endl;
	matrix_double hill2(arr,2,2);
	std::cout << "K == "<< std::endl << hill2 << std::endl << std::endl;
	std::cout << "det(K) = ";
	std::cout << hill2.det() << std::endl << std::endl;
	std::cout << "adj(K) == " << std::endl;
	std::cout << hill2.adj() << std::endl << std::endl;
	std::cout << "[K]^-1 = [d]^-1 * adj(K) == " << std::endl;
	std::cout << hill2.inv_mod(26) << std::endl;

	return 0;
}