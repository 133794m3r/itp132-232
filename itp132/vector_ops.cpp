#include <iostream>
#include <vector>
#include <algorithm>
/*
* Just showing vectors that's all.
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/

int main(){
	//I create 2 dynamically sized vectors that are all floats.
	std::vector <float> first_numbers;
	std::vector <float> second_numbers;
	//the current value we're at is a float.
	float current_number=0;
	//the number of numbers
	unsigned int numbers;
	//incrementer
	unsigned int i=0;
	//user input is a string.
	std::string input;
	//prompt the user.
	std::cout << "How many numbers will you be operating on?\r\n";
	
	/*
	* get a line of input. Tell getline to ignore any leading whitespace.
	* then put that value into the input string.
	*/
	getline(std::cin >> std::ws,input);
	//if empty set numbers to be 0. Otherwise cast to integer.
	(input.empty())?numbers=0:numbers=std::atoi(input.c_str());
	
	//if it's zero then warn them and return error code.
	if(numbers==0){
		std::cout << "You have to enter at least 1 number for this to work.";
    return -1;
	}
	
	//create a new vector that's intialized to the size of the number.s
	std::vector <float> third_numbers(numbers);  
	//tell them to enter their vectors.
	std::cout << "Enter your first set of numbers one at a time.\r\n";
	
	//do while loop to get them one by one.
	do{
		//read it into the value.
		std::cin >> current_number;
		//append it to the linked list of vectors at the end.
		first_numbers.push_back(current_number);
		//increment i by one.
		i++;
	}
	while(i<numbers);
  
	//prompt for second set.
	std::cout << "Enter your second set of numbers one at a time.\r\n";
	//reset i to zero.
	i=0;
	
	//do while again and get second set of values.
	do{
		std::cin >> current_number;
		second_numbers.push_back(current_number);
		i++;
	}
	while(i<numbers);

	//ask them for their chosen operator. No division to avoid divide by zero errors.
	std::cout << "Enter your chosen operator +,-,*" << std::endl;
	//get the operator to the input string.
	getline(std::cin >> std::ws,input);
	//no operator chosen.
	if(input.empty()){
		std::cout << "You didn't give any input.\r\n";
		return -1;
	}
	//otherwise we got one.
	else{
		//case switch finding operator chosen.
		switch(input[0]){
		case '+':
			//only commenting once here. Use the transform function to apply the operator on the values. Take the first set of vectors, go to the last one
			//then get the second one starting at the beginning and place the results of each operation in to the third_numbers vector. Add them together.
			std::transform(first_numbers.begin(), first_numbers.end(), second_numbers.begin(), third_numbers.begin(), std::plus<float>());
			//break from the switch.
			break;
		case '-':
			std::transform(first_numbers.begin(), first_numbers.end(), second_numbers.begin(), third_numbers.begin(), std::minus<float>());
			break;
		case '*':
			std::transform(first_numbers.begin(), first_numbers.end(), second_numbers.begin(), third_numbers.begin(), std::multiplies<float>());         
			break;
		//chosen operator wasn't valid.
		default:
			std::cout << "Invalid operator given.\r\n";
			return -1;
		}
	}
	
	//print the full list of results.
	for(i=0;i<numbers;i++){
		//if i is 1 or higher then add a "," to the end of the line.
		if(i>0){
			std::cout << ",";
		}
		//output value at the current index.
		std::cout << third_numbers[i];
	}
	//include newline at the end of the data.
	std::cout << "\r\n";
}