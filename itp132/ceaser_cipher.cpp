/*
* Super simple Ceaser Cipher using the for each operator in C++.
* Macarthur Inbody 2020-04-25
*/
#include <iostream>
typdef unsigned char uint8;

int main() {
  std::string input="";
  std::string out="";
  int shift = 0;
  uint8 mode=0;
  
  std::cout << "Welcome to the ceaser shifter!\r\nSelect whether you want to \r\n1:Encrypt\r\n2:Decrypt\r\n";
  std::cin >> mode;
  
  std::cout << "\r\nEnter the shift you'd like to use(1-26): ";
  std::cin >> shift;
  
  std::cout << "\r\nEnter the string to encrypt/decrypt: ";  
  std::getline(std::cin >> std::ws, input);
  
  shift=(shift>26)?shift%26:shift;
  
  shift*=((mode == '1')?1:-1);
  std::cout << input << std::endl;
  
  for(char x:input){
 
	if(x>=65 && x<=90){
		x+=shift;
	  if(x>=90)
		x=(x-90)+65;
	}
	else if(x>=97 && x<=122){
		x+=shift;	
	  if(x>=122)
		x=(x-122)+65;
	}
	out+=x;
  }
  std::cout << std::endl << out << std::endl;
}