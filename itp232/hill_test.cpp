#include <iostream>
#include <chrono>
#include "hill_cipher.hxx"
int main(){
	std::string cipher_text = "PWQB";
	std::string plain_text = "HILL";
	Hill hill = Hill();
	hill.solve_key(cipher_text,plain_text);
}