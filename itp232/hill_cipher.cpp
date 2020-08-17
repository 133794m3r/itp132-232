#include <iostream>
#include <chrono>
#include "matrix.hxx"
#include "hill_cipher.hxx"
/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Hill Cipher Tester
 *
 */
int main(){
	Hill hill_instance;
	hill_instance = Hill();
	std::cout << hill_instance.get_enc_key() << std::endl;
}