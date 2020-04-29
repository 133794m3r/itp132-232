#include <fstream>
#include <iostream>
#include <algorithm>
#ifdef _WIN32
#include <windows.h>
bool test = SetConsoleMode(GetStdHandle(-11),7);
#endif

char *get_opt_val(char **start, char **end, const std::string &opt){
	char **iter = std::find(start,end,opt);
	return (iter != end && ++iter != end)?*iter:0;
}

bool opt_exists(char **start, char **end, const std::string &opt){
	return std::find(start,end,opt) != end;
}
void print_help(char *prog_name){
	std::cout << prog_name << " is used to do a full shift encoding/decoding on a file." << std::endl;
	std::cout << "Usage: \e[1m" << prog_name;
	std::cout << "\e[0m -i {INPUT_FILE_NAME} -o {OUTPUT_FILE_NAME} -k {SHIFT_TO_USE} -e|d Encode/Decode the input file." << std::endl;
	std::cout << "You must have a space between the flag and option as unix style options are not supported. Also only encoding or decoding is allowed. You can also only encrypt or decrypt the input file." << std::endl;
}

int main(int argc, char **argv){
	//the shift.
	int shift = 0;
	//chosen mode.
	uint8_t mode=0;
	//two bools.
	bool encode=false;
	bool decode=false;
	//pointer to end of the array of options.
	char **end_argv=argv+argc;
	//the string we're going to use to have a c-like string.
	char const *str;
	//the length of the current line.
	unsigned int length=0;
	//current character we're modifying.
	unsigned char character=0;
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
	
	while(getline(input,line)){
		str=line.c_str();
		length=line.length();
		for(int i=0;i<length;i++){
			character=str[i]+shift;
			if(character > 126)
				character=32+(character - 127);
			else if(character < 32)
				character=127 -  (32 - character);
			
			line[i]=character;
		}
		std::cout<< line << std::endl;
		output << line << std::endl;
	}
	input.close();
	output.close();
}