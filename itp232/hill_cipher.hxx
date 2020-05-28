/*
 * By Macarthur Inbody <admin-contact@transcendental.us> 2020
 * Licensed AGPLv3
 * Hill Cipher Class
 *
 */

#ifndef _HILL_CIPHER_
#define _HILL_CIPHER_
#include "matrix.hxx"
#include "vectors.hxx"
#include "random.h"
#include <map>
//may end up making it templated to work with bytes also but not sure yet.
//template <typename character>
class Hill{
 private:
	Matrix<char> key;
	//I may do a vector as the alphabet but I'm unsure about this.
	//std::vector<char> alphabet;
	//the default one is the "normal" hill cipher alphabet.
	std::map <char,size_t> alphabet;
	//std::string alphabet;
	//these are all of the default/normal values.
	size_t alphabet_size;
	Matrix<char> decryption_key;
	/*
	* it is the same here. The default chunk size is 2 to make it simpler to work though.
	* basically we have to construct the input text as vectors and then you'd have to go column-wise through the data
	* to reconstruct the output string. By doing it this way we can easily do column by column. Also by doing a size 2
	* I can simply use the vector as a normal form. What I do to find out if I can simply go down it in a standard way is
	* I take the number of columns of the key and compare it with the chunk size. If they are the same then I can do the simpler
	* way of doing it. Otherwise I have to iterate over it in a column-wise method to get back the original data from the matrix.
	*/
	unsigned int chunk_size=2;
 public:
	Hill(const Matrix<char> &_key=Matrix<char>(2,2,1), const std::string &_alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ"){
		if(_key.get_rows() != _key.get_cols()){
			throw std::invalid_argument("The key must be square. Thus rows and columns should be the same! key.rows="
				+std::to_string(_key.get_rows())+"key.cols="+std::to_string(_key.get_cols()));
		}
		//if they didn't provide a key we generate one so that it can be instantly used after constructing the class.
		if(_key[0] == _key[1] && _key[1] == _key[2] && _key[3] == _key[0]){
			//gen_key also creates the decryption key for them too.
			gen_key();
		}
		else {
			key = _key;
			//have to wrap this in a try_catch just incase the key doesn't work.
			decryption_key=key.inv_mod(static_cast<char>(alphabet_size));
		}
		for(size_t i=0;i<_alphabet.size();i++){
			alphabet[_alphabet[i]]=i;
		}
		//alphabet=_alphabet;
		alphabet_size=_alphabet.size();

	}
	//in case they think this is C.
	Hill(const Matrix<char> _key=Matrix<char>(2,2,1), char *_alphabet=NULL,size_t size=0){
		if(_key.get_rows() != _key.get_cols()) {
			throw std::invalid_argument("The key must be square. Thus rows and columns should be the same! key.rows="
										+ std::to_string(_key.get_rows()) + "key.cols=" +
										std::to_string(_key.get_cols()));
		}
		//if they didn't provide a key we generate one so that it can be instantly used after constructing the class.
		if(_key[0] == _key[1] && _key[1] == _key[2] && _key[3] == _key[0]){
			gen_key();
		}
		else{
			key=_key;
			decryption_key=key.inv_mod((char)alphabet_size);
		}
		if(_alphabet==NULL){
			//const char *tmp="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			for(size_t i=0;i<26;i++){
				alphabet[65+i]=i;
			}
			size=26;
		}
		else{
			if(size == 0){
				size=sizeof(_alphabet);
			}
			for(size_t i=0;i<size;i++){
				alphabet[*_alphabet+i]=i;
			}
		}

		alphabet_size=size;

	}
	//all of the setters.
	void set_alphabet(const std::string &string_alphabet){
		//alphabet=string_alphabet;
		for(size_t i=0;i<string_alphabet.size();i++){
			alphabet[string_alphabet[i]]=i;
		}
		alphabet_size=string_alphabet.size();
		decryption_key=key.inv_mod((char)alphabet_size);
	}
	//if they like pointers.
	void set_alphabet(const char *string_alphabet=NULL,size_t size=0){
		if(string_alphabet==NULL){
			//const char *tmp="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			for(size_t i=0;i<26;i++){
				alphabet[65+i]=i;
			}
			size=26;
		}
		else{
			if(size == 0){
				size=sizeof(string_alphabet);
			}
			for(size_t i=0;i<size;i++){
				alphabet[*string_alphabet+i]=i;
			}
		}
		alphabet_size=size;
		decryption_key=key.inv_mod((char)alphabet_size);
	}
	//if they want the program to generate the key for them.
	void gen_key(void){
		size_t items=chunk_size*chunk_size;
		//have to seed the PRNG. We call it w/o arguments so that if it's already seeded it won't be reseeded again.
		s_xor_128();
		char maximum=(char)alphabet_size-1;
		Matrix<char> key(chunk_size,chunk_size,1);
		for(size_t i=0;i<items;i++){
			key[i]=xorshift128((char)0,maximum);
		}
		//going to have to figure out how I'm going to loop the generator until I get one that doesn't result in the inv modulus resulting in 0.
		decryption_key=key.inv_mod((char)alphabet_size);
	}
	//to let them set the key from a string of characters. This'll create the Matrix and re-declare it.
	int set_key(const std::string &string_key){
		unsigned int cols;
		int return_code=0;
		std::map <char,size_t>::iterator iterator;
		size_t size=string_key.size();
		if(size == 0 ){
			chunk_size=2;
			gen_key();
			//this is so that I know/or any program using it knows that they literally just used genkey and got out of it.
			//basically if they don't provide anything for the key.
			return_code = -1;
		}
		else {
			double key_size = std::sqrt(size);
			if (key_size != std::floor(key_size)) {
				throw std::invalid_argument(
					"The key must be square. For the key to work it has to be an even square. sqrt(string_length)="
					+ std::to_string(key_size) + "floor(sqrt(string_length))=" + std::to_string(key_size));
			}
			cols = std::lround(key_size);
			key = Matrix<char>(cols, cols, 1);
			chunk_size=cols;
			size_t pos = 0;
			char index;
			for (unsigned int i = 0; i < cols; i++) {
				for (unsigned int j = 0; j < cols; j++) {
					//this is insanely inefficient to do a linear search for _every_ single character. I should utilize a hashtable of the alphabet
					//but I've yet to write my own/explore the STL to see if it has a hashtable template I can utilize.
					//index = alphabet.find(string_key[pos++]);
					iterator=alphabet.find(string_key[pos++]);
					if (iterator == alphabet.end()) {
						//warn them but don't throw an invalid argument for now. Just make it be the element at index 0.
						std::cout << "Warning. The character \"" << string_key[pos - 1]
								  << "\" was not found in the alphabet. Thus we're inserting a 0 in it's place." << std::endl;
						index = 0;
					}
					else{
						index=iterator->second;
					}
					//normally it'd be key(i,j) but because I am converting the key from a string of characters I have to set it up as if it was multiple
					//vectors that have 1 column, but rows equal to the chunks size. So to make it fill elements row-wise this little hack has to be done.
					key(j, i) = index;
				}
			}
		}
		decryption_key=key.inv_mod((char)alphabet_size);
		return return_code;
	}
	//if they are doing it like it was C.
	int set_key(const char *string_key=NULL,size_t size=0){
		int return_code=0;
		if(string_key == NULL){
			//have to make sure that the chunk size is set at 2 for the next function to work properly.
			chunk_size=2;
			//we just generate the key since they didn't provide one.
			gen_key();
			return_code=-1;
		}
		else if(size == 0){
			std::map <char,size_t>::iterator iterator;
			size=sizeof(string_key);
			double key_size = std::sqrt(size);
			if (key_size != std::floor(key_size)) {
				throw std::invalid_argument(
					"The key must be square. For the key to work it has to be an even square. sqrt(string_length)="
					+ std::to_string(key_size) + "floor(sqrt(string_length))=" + std::to_string(key_size));
			}
			unsigned int cols = std::lround(key_size);
			key = Matrix<char>(cols, cols, 1);
			chunk_size=cols;
			size_t pos = 0;
			char index;
			for (unsigned int i = 0; i < cols; i++) {
				for (unsigned int j = 0; j < cols; j++) {
					//this is insanely inefficient to do a linear search for _every_ single character. I should utilize a hashtable of the alphabet
					//but I've yet to write my own/explore the STL to see if it has a hashtable template I can utilize.
					iterator = alphabet.find(string_key[pos++]);
					if (iterator == alphabet.end()) {
						//warn them but don't throw an invalid argument for now. Just make it be the element at index 0.
						std::cout << "Warning. The character \"" << string_key[pos - 1]
								  << "\" was not found in the alphabet. Thus we're inserting a 0 in it's place." << std::endl;
						index = 0;
					}
					else{
						index=iterator->second;
					}
					//normally it'd be key(i,j) but because I am converting the key from a string of characters I have to set it up as if it was multiple
					//vectors that have 1 column, but rows equal to the chunks size. So to make it fill elements row-wise this little hack has to be done.
					key(j, i) = index;
				}
			}
		}
		return return_code;
	}
	//all of the getters that someone would need from the Hill cipher class.
	Matrix<char> get_enc_key(void){
		return this->key;
	}
	Matrix<char> get_encryption_key(void){
		return this->key;
	}
	Matrix<char> get_dec_key(void){
		return this->decryption_key;
	}
	Matrix<char> get_decryption_key(void){
		return this->decryption_key;
	}
	/*
	std::string get_alphabet(void){
		return this->alphabet;
	}
	 */
	size_t get_modulus(void){
		return this->alphabet_size;
	}
	size_t get_chunk_size(void){
		return this->chunk_size;
	}

	//this method will return a vector containing matrices of the input data.
	std::vector<Matrix<char>> chunk_it(const std::string input_data){
		size_t mat_size=chunk_size*chunk_size;
		//this will be modified later to append enough data to make it an even number.
		size_t items=input_data.size()/(mat_size);
		//create our return item.
		std::vector<Matrix<char>> result(items);
		std::map<char,size_t>::iterator iterator;
		char item;
		//loop over the entire input string. For now it's just a string.
		for(size_t i=0;i<items;i++){
			//create my matrix.
			result[i]=Matrix<char>(chunk_size,chunk_size);
			for(size_t j=0;j<chunk_size;j++){
				for(size_t k=0;k<chunk_size;k++){
					//insert into it at the correct spot the correct character.
					//later I'll actually do the lookup part.
					//result[i][k+(j*chunk_size)]=input_data[(i*mat_size)+(j+(k*chunk_size))];
					item=input_data[(i*mat_size)+(j+(k*chunk_size))];
					iterator=alphabet.find(item);
					//if we don't find it we just make it be a zero index and warn them.
					if(iterator == alphabet.end()){
						std::cout << "Warning. The character \"" << item
								  << "\" was not found in the alphabet. Thus we're inserting a 0 in it's place." << std::endl;
						item=0;
					}
					else{
						//otherwise we use the value that we received.
						item=iterator->second;
					}
					//then we assign it to your element as we normally would.
					result[i][k+(j*chunk_size)]=item;
				}
			}
		}
		return result;
	}
	//TODO: Actually make this a function.
	//std::string dechunk_it(std::vector<Matrix<char>> &input_data);
};


#endif //_HILL_CIPHER_H
