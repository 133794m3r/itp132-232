/*
* Super simple Caesar Cipher using the for each operator in C++.
* plus it shows functional overloading, pass by reference, address, and value.
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/
#include <iostream>
//to do the typedef requirement.
typedef unsigned char uint8;

//basic shifter function.
//char array as input.
void transform(char *input, unsigned int length, int shift){
	unsigned int i=0;
	unsigned char x;
	//iterate over the string till the end.
	while(i<length){
		x=input[i];
		//if the value is printable uppercase ASCII
		if(x>=65 && x<=90){
			//add the shift.
			x+=shift;
			//if it's greater than 'Z'.
			if(x>=90)
				//handle overflows.
				x=(x-90)+64;
		}
		//else if it's lowercase ascii.
		else if(x>=97 && x<=122){
			//same thing again.
			x+=shift;
			//same if it's greater than 'z'.
			if(x>=122)
				//handle overflow.
				x=(x-122)+96;
		}
		//add the value to the out string.
		input[i++]=x;
	}	

}
//c++ style string input.
void transform(std::string &input, int shift){
	unsigned int i=0;
	
	for(char x:input){
		//x=input[i];
		//if the value is printable uppercase ASCII
		if(x>=65 && x<=90){
			//add the shift.
			x+=shift;
			//if it's greater than 'Z'.
			if(x>=90)
				//handle overflows.
				x=(x-90)+64;
		}
		//else if it's lowercase ascii.
		else if(x>=97 && x<=122){
			//same thing again.
			x+=shift;
			//same if it's greater than 'z'.
			if(x>=122)
				//handle overflow.
				x=(x-122)+96;
		}
		//add the value to the out string.
		input[i++]=x;
	}	

}
int main() {
	//initialize strings(also requirement)
	std::string input="";
	std::string out="";
	//the shift.
	int shift = 0;
	//chosen mode.
	uint8 mode=0;
	
	//tell them the options.
	std::cout << "Welcome to the caesar shifter!\r\nSelect whether you want to \r\n1:Encrypt\r\n2:Decrypt\r\n";
	//read it in.
	std::cin >> mode;
	//prompt for shift.
	std::cout << "\r\nEnter the shift you'd like to use(1-26): ";
	//get the value.
	std::cin >> shift;
	//enter the string.
	std::cout << "\r\nEnter the string to encrypt/decrypt: ";	
	std::getline(std::cin >> std::ws,input);
	//if the shift is greater than we get the absolute value.
	shift=(shift>26 || shift < 0)?shift%26:shift;
	
	//if it's decryption then make the shift negative.
	shift*=((mode == '1')?1:-1);
	
	//output the input string.
	std::cout << input << std::endl;
	
	transform(input,shift);
	//output the final encrypted string.
	std::cout << "Transformed" << std::endl << input << std::endl;
}
