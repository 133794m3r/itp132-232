/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Hill Cipher Class
 *
 */

#ifndef _HILL_CIPHER_
#define _HILL_CIPHER_
#include "matrix.hxx"
#include <vectors.hxx>
class Hill {
 private:
	Matrix<char> key;
	//I may do a vector as the alphabet but I'm unsure about this.
	//std::vector<char> alphabet;
	std::string alphabet="";
	size_t modulus_value=0;
	Matrix<char> decryption_key;
	unsigned int chunk_size=0;
 public:
	Hill(const Matrix<char> &_key=Matrix<char>(2,2,1), const std::string &_alphabet=""){
		if(_key.get_rows() != _key.get_cols()){
			throw std::invalid_argument("The key must be square. Thus rows and columns should be the same! key.rows="
			+std::to_string(_key.get_rows())+"key.cols="+std::to_string(_key.get_cols()));
		}
		key=_key;
		alphabet=_alphabet;
		modulus_value=_alphabet.size();
		decryption_key=key.inv_mod(modulus_value);
	}
	//in case they think this is C.
	Hill(const Matrix<char> _key=Matrix<char>(2,2,1), const char &_alphabet={0},size_t size=0){
		if(_key.get_rows() != _key.get_cols()){
			throw std::invalid_argument("The key must be square. Thus rows and columns should be the same! key.rows="
										+std::to_string(_key.get_rows())+"key.cols="+std::to_string(_key.get_cols()));
		}
		key=_key;
		if(size == 0){
			size=sizeof(_alphabet);
		}
		alphabet.reserve(size);
		for(size_t i=0;i<size;i++){
			alphabet[i]=_alphabet[i];
		}
		modulus_value=size;
		decryption_key=key.inv_mod(modulus_value);
	}
	//this isn't the proper way to do it but I'll support it.
	void set_alphabet(const std::string &string_alphabet){
		alphabet=string_alphabet;
		modulus_value=string_alphabet.size();
		decryption_key=key.inv_mod(modulus_value);
	}
	void set_alphabet(const char &string_alphabet,size_t size=0){
		if(size == 0){
			size=sizeof(string_alphabet);
		}
		for(size_t i=0;i<size;i++){
			alphabet[i]=string_alphabet[i];
		}
		modulus_value=size;
		decryption_key=key.inv_mod(modulus_value);
	}
	//to let them set the key from a string of characters. This'll create the Matrix and re-declare it.
	void set_key(const std::string &string_key){
		size_t size=string_key.size();
		double key_size=std::sqrt(size);
		if(key_size != std::floor(key_size)){
			throw std::invalid_argument("The key must be square. For the key to work it has to be an even square. sqrt(string_length)="
			+std::to_string(key_size)+"floor(sqrt(string_length))="+std::to_string(key_size));
		}

	}
	void set_key(const char &string_key,const size_t size=0){

	}
};


#endif //_HILL_CIPHER_H
