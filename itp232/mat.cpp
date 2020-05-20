#include <iostream>
#include "matrix.hxx"
#include <chrono>
/*
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
* Matrix Class Module Test Program
*/
double microtime(void){
	return std::chrono::system_clock::now().time_since_epoch()/std::chrono::milliseconds(1);
}
std::string equality(bool test){
	return (test)?"true":"false";
}
int main() {
	//int i=0;
	//int j=0;
	double start,end;
	start=microtime();
	/*
	int row=2;
	int col=2;
	//Matrix mat1(2,2,1);
	//std::cout << "mat1" << std::endl;
	//Matrix<int> result(row,col,0);
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

	matrix_int det_mat(3,2,0);
	k=1;
	for(i=0;i<2;i++){
		for(j=0;j<3;j++){
			det_mat(i,j)=(k++);
		}
	}
	std::cout << "det = " << std::endl << mat2 << std::endl;
	std::cout << "det*result=" << std::endl << mat2*result << std::endl;
	std::cout << "det*5=" << std::endl << mat2*5 << std::endl;
	std::cout << "result " << std::endl << result << std::endl;
	mat2*=result;
	std::cout << "mat2 " << mat2 << std::endl;
	std::cout << det_mat << std::endl;
	std::cout << "det_mat*result=" << std::endl << mat2*det_mat << std::endl;
	 */
	/*
	matrix_int a(2,2,1);
	matrix_int b(2,2,1);
	matrix_double c_1(2,2,2);
	matrix_double c_2(2,2,3);
	std::cout << "a \r\n" << a << std::endl;
	std::cout << "b \r\n" << b << std::endl;
	std::cout <<"(a  == b) => " <<  equality(a == b) << std::endl;
	std::cout <<"(a  != b) => " << equality(a != b) << std::endl;
	std::cout << "(a  > b) =>" << equality(a > b) << std::endl;
	std::cout << "(a  < b) => " << equality(a < b ) << std::endl << std::endl;
	std::cout << "c1 \r\n" << c_1 << std::endl;
	std::cout << "c2 \r\n" << c_2 << std::endl;
	std::cout << "(c1 == c2) => " <<  equality(c_1 == c_2) << std::endl;
	std::cout << "(c2 != c2) => " << equality(c_1 != c_2) << std::endl;
	std::cout << "(c2 >  c2) => " << equality(c_1 > c_2) << std::endl;
	std::cout << "(c2 <  c2) => " << equality(c_1 < c_2) << std::endl;
	std::cout << "(c2 >= c2) => " << equality(c_1 >= c_2) << std::endl;
	std::cout << "(c2 <= c2) => " << equality(c_1 <= c_2) << std::endl;
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			c_1(i,j)=((i+1)<<2)+((j+1) << 3);
		}
	}
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			c_2(i,j)=((i+1)<<2)+((j+1) << 4);
		}
	}
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			a(i,j)=((i+1)<<2)+((j+1) << 3);
		}
	}
	std::cout << a << std::endl;
	//std::vector<double> A={-0.625,0.5625,0.375,-0.3125};
	std::vector<double> A={1,2,3,4};
	matrix_double AA(A,2,2);
	//bool res=a.inv();
	std::cout << AA << std::endl;
	std::cout << "c1 " << c_1 << std::endl;
	std::cout << "c2 " << c_2 << std::endl;
	std::cout << "c_1 * AA" << std::endl;
	std::cout << c_1 * AA << std::endl;
	//c_1/=c_2;
	//std::cout << "c_1/=c2" << std::endl;
	//std::cout << c_1 << std::endl;
	 */
	/*
	std::cout << "det_matrix" << std::endl << det_mat << std::endl;
	double the_determinant=det_mat.det();
	std::cout << the_determinant << std::endl;
	 */
	/*
	double hill3_arr[4]={7.0,8.0,11.0,11.0};
	int arr[4]={7,8,11,11};
	std::cout << "Hill Cipher Tests" << std::endl;
	matrix_int hill2(arr,2,2);
	matrix_double hill3(hill3_arr,2,2);
	std::cout << "K == "<< std::endl << hill2 << std::endl << std::endl;
	std::cout << "det(K) = ";
	std::cout << hill2.det() << std::endl << std::endl;
	std::cout << "adj(K) == " << std::endl;
	std::cout << hill2.adj() << std::endl << std::endl;
	std::cout << "[K]^-1 = [d]^-1 * adj(K) == " << std::endl;
	std::cout << hill2.inv_mod(26) << std::endl;
	std::cout << hill2.gae() << std::endl;
	std::cout << hill2 << std::endl;
	std::cout << hill2(0,1) << std::endl;
	 */
	std::vector<int> arr2={3,2,5,2,3,-3,-4,3,1,3,15,14};
	matrix_int gaec1(arr2,4,3);
	matrix_double gaec(3,2,1);
	gaec(0,0)=3;gaec(0,1)=1;gaec(0,2)=15;
	gaec(1,0)=5;gaec(1,1)=1;gaec(1,2)=20;

	std::cout << "Solve for x and y in the following equation. \r\n3x + y = 15\r\n5x + y = 20\r\n";
	//std::cout << gaec << std::endl;
	matrix_double result(2,1,0); result=gaec.solve_gae();
	std::cout << "x=" << result(0,0) << std::endl;
	std::cout << "y=" << result(0,1) << std::endl;
	std::cout << "solve again but this time for x, y and z." << std::endl;
	std::cout <<"3x+2y-4z=3\r\n2x+3y+3z=15\r\n5x-3y+z=14\r\n";
	matrix_int result2(3,1,0);result2=gaec1.solve_gae();
	std::cout << "x=" << result2(0,0) << std::endl;
	std::cout << "y=" << result2(0,1) << std::endl;
	std::cout << "z=" << result2(0,2) << std::endl;

	std::vector<size_t> P={0,0};
	std::vector<size_t> Q={0,0};
	std::vector<double> Solution={0.0,0.0};
	std::vector<double> Vars={15.0,20.0};
	matrix_double ludc(2,2,1);
	ludc(0,0)=3;ludc(0,1)=1;
	ludc(1,0)=5;ludc(1,1)=1;	
	std::cout << ludc * ludc << std::endl;
	double det=0.0;
	double detb=ludc.det();
	matrix_double ludc2=ludc;
	std::cout << "ludc_orig\r\n" << ludc << std::endl;
	ludc2.lud(det);
	std::cout << ludc.lud(Q) << std::endl;
	std::cout << "ludc\r\n" << ludc << std::endl;
	std::cout << "ludc2\r\n" << ludc2 << std::endl;
	ludc.lud_backsub(Q,Vars,Solution);
	std::cout << "Solution " << Solution[0] << ", " << Solution[1] << std::endl;
	std::cout << "ri " << Q[0] << " " << Q[1] << std::endl;
	std::cout << "det " << det << "detb " << detb <<  std::endl;
	//std::cout << gaec.gae(1) << std::endl;
	//std::cout << "gaec1.lud" << std::endl;
/*
	hill2=matrix_int(arr,2,2);

	matrix_double hill3_a=hill3;
	matrix_double hill3_b=hill3;
	std::cout << hill3 << std::endl;
	std::cout << hill2 << std::endl;
	std::cout <<"det "<< hill3.det() << std::endl;
	std::cout <<"inv "<<  hill3.inv() << std::endl;
	std::cout <<"h3" << hill3 << std::endl;
	std::cout << "h2.inv()" << hill2.inv() << std::endl;
	std::cout << "h2" << hill2 << std::endl;
	std::cout << "h3d " << hill3.det() << std::endl;
	hill3_a.lud(deta);
	std::cout << "3a det " << deta << std::endl;
	std::cout << "hill3_a.lud() " << hill3_a << std::endl;
	deta=1.0;
	hill3_b.lud(P);
	std::cout << "3b det" << deta << std::endl;
	std::cout << "hil3_b.lud(P,det) " << hill3_b << std::endl;
 */
	matrix_double gaec2(2,2,1);
	gaec2(0,0)=3;gaec2(0,1)=1;
	gaec2(1,0)=5;gaec2(1,1)=1;
	std::vector<double> rhs={15,20};
	//std::vector<double> Solution(2);
	//std::cout << gaec.solve(rhs,Solution) << std::endl;

	std::cout << "gaec2" << gaec2 << std::endl;
	matrix_double gaec_inv=gaec2;
	gaec_inv.inv();
	matrix_double solution(1,2,1);
	solution(0,0)=15;
	solution(1,0)=20;
	std::cout << "g" << gaec.solve_gae() << std::endl;
	std::cout << "s" << solution << std::endl;
	std::cout << "g_inv" << gaec_inv << std::endl;
	std::cout << "g*g" << gaec_inv * solution << std::endl;
	std::cout << Solution[0] << std::endl;
	std::cout << Solution[1] << std::endl;
	gaec2.lud(P);
	gaec2.lud_backsub(P,rhs,Solution);
	std::cout << "s2" << std::endl;
	std::cout << Solution[0] << std::endl;
	std::cout << Solution[1] << std::endl;

//	int k=1;
//	for(i=0;i<2;i++){
//		for(j=0;j<2;j++){
//			a(i,j)=k+((i+1)<<2)+((j+1) << 3);
//		}
//	}
//	std::cout << a << std::endl;
//	for(i=0;i<2;i++){
//		for(j=0;j<2;j++){
//			std::cout << "a(" << i+1 << "," << j+1 << ")=" << a[i+(j*2)] << std::endl;
//		}
//	}
	end=microtime();
	std::cout <<std::endl <<  "total time" << end-start << std::endl;
	return 0;
}