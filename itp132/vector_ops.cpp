#include <iostream>
#include <vector>
#include <algorithm>
/*
* Macarthur Inbody 2020-04-25
* Simple vector program. Will add,subtract, or multiply 2 lists of numbers.
*/

int main(){
	std::vector <float> first_numbers;
	std::vector <float> second_numbers;

	float current_number=0;
	unsigned int numbers;
	unsigned int i=0;
  int *op;
	std::string input;
	std::cout << "How many numbers will you be operating on?\r\n";
	getline(std::cin,input);
	(input.empty())?numbers=0:numbers=std::atoi(input.c_str());
	if(numbers==0){
		std::cout << "You have to enter at least 1 number for this to work.";
    return -1;
	}
	std::vector <float> third_numbers(numbers);  

	std::cout << "Enter your first set of numbers one at a time.\r\n";
	do{
		std::cin >> current_number;
		first_numbers.push_back(current_number);
    i++;
	}
	while(i<numbers);
  
	std::cout << "Enter your second set of numbers one at a time.\r\n";
  i=0;

	do{
		std::cin >> current_number;
		second_numbers.push_back(current_number);
    i++;
	}
	while(i<numbers);

  std::cout << "Enter your chosen operator +,-,*" << std::endl;
  std::cin.ignore();
  getline(std::cin,input);

  if(input.empty()){
    std::cout << "You didn't give any input.\r\n";
    return -1;
  }
  else{
    switch(input[0]){
      case '+':
	      std::transform (first_numbers.begin(), first_numbers.end(), second_numbers.begin(), third_numbers.begin(), std::plus<float>());
        break;
      case '-':
	      std::transform (first_numbers.begin(), first_numbers.end(), second_numbers.begin(), third_numbers.begin(), std::minus<float>());
        break;
      case '*':
	      std::transform (first_numbers.begin(), first_numbers.end(), second_numbers.begin(), third_numbers.begin(), std::multiplies<float>());         
        break;
      default:
        std::cout << "Invalid operator given.\r\n";
        return -1;
    }
  }

	for(i=0;i<numbers;i++){
    if(i>0){
      std::cout << ",";
    }
		std::cout << third_numbers[i];
	}
	std::cout << "\r\n";
}