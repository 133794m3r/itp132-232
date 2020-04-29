#include <fstream>
#include <iostream>
#include <algorithm>

//since by default windows doesn't like ANSI escape sequences have to enable all that.
#ifdef _WIN32
#include <windows.h>
//complained that I wasn't capturing the output. So this is just here for that.
bool test = SetConsoleMode(GetStdHandle(-11),7);
#endif

/*
* get the option's value from the original string.
* start is the start of the string, end is the end(both are passed as pointers).
* Then I look for the string I want to to get.
*/
char *get_opt_val(char **start, char **end, const std::string opt){
	//std::find searches the iterable from start to end looking for the "opt" value.
	//if it's found it returns the index, if it's not then it returns end.
	char **iter = std::find(start,end,opt);
	/*
	* Check that iter isn't the same address as the end of the string.
	* If it is then we've failed and didn't find it. Then we increment the pointer
	* making sure that this value is also not the same as the end
	* (because if it is then there's no option for us to get at)
	* If all succeeds then we return a pointer to the start of that string.
	* otherwise we return 0 or NULL.
	*/
	return (iter != end && ++iter != end)?*iter:0;
}

/*
* This just checks to see if the option exists in the search string.
* It returns True if the address of the result of std::find is not the end.
* If it is the end then it returns False.
*/
bool opt_exists(char **start, char **end, const std::string opt){
	//if we find the value we return true. otherwise we return false.
	return std::find(start,end,opt) != end;
}

void print_help(char *prog_name){
	std::cout << prog_name << " is used to do a full shift encoding/decoding on a file." << std::endl;
	std::cout << "Usage: \e[1m" << prog_name;
	std::cout << "\e[0m -i {INPUT_FILE_NAME} -o {OUTPUT_FILE_NAME} -k {SHIFT_TO_USE} -e|d Encode/Decode the input file." << std::endl;
	std::cout << "You must have a space between the flag and option as unix style options are not supported. Also only encoding or decoding is allowed. You can also only encrypt or decrypt the input file." << std::endl;
}

void transform_full(std::string &input, unsigned int length, int shift){
	unsigned int i=0;
	char character=0;
	while(i<length){
		character=input[i]+shift;
		if(character > 126)
			character=32+(character - 127);
		else if(character < 32)
			character=127 -  (32 - character);
			
		input[i++]=character;
	}
}

void transform_full(char *input, unsigned int length, int shift){
	unsigned int i=0;
	char character=0;
	for(char character:input){		
		character=input[i]+shift;
		if(character > 126)
			character=32+(character - 127);
		else if(character < 32)
			character=127 -  (32 - character);
			
		input[i++]=character;
	}
}

int main(int argc, char **argv){
	//the shift.
	int shift = 0;
	//two bools.
	bool encode=false;
	bool decode=false;
	//pointer to end of the array of options.
	char **end_argv=argv+argc;
	//the length of the current line.
	unsigned int length=0;
	//the line of text we're working with.
	std::string line;
	
	//if argc is 1 then no options called.
	if(argc == 1){
		//print help return normal.
		print_help(argv[0]);
		return 0;
	}
	
	//not doing getopt here b/c that's C-like so I'm doing it the hard way.
	//check if help is called.
	if(opt_exists(argv,end_argv,"-h")){
		print_help(argv[0]);
		return 0;
	}
	
	//get the input file string.
	char *ifile = get_opt_val(argv,end_argv,"-i");
	//output file string.
	char *ofile = get_opt_val(argv,end_argv,"-o");
	//the key.
	shift=std::atol(get_opt_val(argv,end_argv,"-k"));
	if(shift == 0){
		std::cout << "You have to specify a key and also it has to not be zero." << std::endl;
		print_help(argv[0]);
	}
	
	shift=(shift>95 || shift < 0)?shift % 96:shift;
	//check to see if both input and output are set.
	if((!ifile) || (!ofile)){
		std::cout << "You didn't specify an input file, an output file or both. if it starts with a \"-\" make sure that you enclose the filename in double quotes(\")." << std::endl;
		print_help(argv[0]);
		return 1;
	}
	//get the mode they chose.
	encode=opt_exists(argv,end_argv,"-e");
	decode=opt_exists(argv,end_argv,"-d");
	//both were seelcted so we've got an error.
	if(encode && decode){
		std::cout << "You can't both encrypt and decrypt. Only one is allowed." << std::endl;
		print_help(argv[0]);
		return 1;
	}
	//otherwise test to see if they didn't select any.
	else if(!(encode) && !(decode)){
		std::cout << "You have to select at least one option." << std::endl;
	}
	//see if it's encoding or decoding mode.
	shift*=(encode)?1:-1;
	//get the input file into a stream.
	std::ifstream input(ifile);
	//same w/ output.
	std::ofstream output(ofile);
	
	//iterate over each line of the input.
	while(getline(input,line)){
		//get the length of the line.
		length=line.length();
		//transform the line.
		transform_full(line,length,shift);
		//write the file after transforming.
		output << line << std::endl;
	}
	//close both file streams b/c windows doesn't like you opening w/o closing.
	input.close();
	output.close();
}