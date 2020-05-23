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
	//the default one is the "normal" hill cipher alphabet.
	std::string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//these are all of the default/normal values.
	size_t alphabet_size=26;
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
		key=_key;
		alphabet=_alphabet;
		alphabet_size=_alphabet.size();
		decryption_key=key.inv_mod(alphabet_size);
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
		alphabet_size=size;
		decryption_key=key.inv_mod(alphabet_size);
	}
	//this isn't the proper way to do it but I'll support it.
	void set_alphabet(const std::string &string_alphabet){
		alphabet=string_alphabet;
		alphabet_size=string_alphabet.size();
		decryption_key=key.inv_mod(alphabet_size);
	}
	void set_alphabet(const char &string_alphabet,size_t size=0){
		if(size == 0){
			size=sizeof(string_alphabet);
		}
		for(size_t i=0;i<size;i++){
			alphabet[i]=string_alphabet[i];
		}
		alphabet_size=size;
		decryption_key=key.inv_mod(alphabet_size);
	}
	//to let them set the key from a string of characters. This'll create the Matrix and re-declare it.
	void set_key(const std::string &string_key){
		size_t size=string_key.size();
		double key_size=std::sqrt(size);
		if(key_size != std::floor(key_size)){
			throw std::invalid_argument("The key must be square. For the key to work it has to be an even square. sqrt(string_length)="
			+std::to_string(key_size)+"floor(sqrt(string_length))="+std::to_string(key_size));
		}
		unsigned int cols=std::lround(key_size);
		key=Matrix<char>(cols,cols,1);
		size_t pos=0;
		size_t index=0;
		for(unsigned int i=0;i<cols;i++){
			for(unsigned int j=0;j<cols;j++){
				//this is insanely ineffecient to do a linear search for _every_ single character. I should utilize a hashtable of the alphabet
				//but I've yet to write my own/explore the STL to see if it has a hashtable template I can utilize. 
				index=alphabet.find(string_key[pos++]);
				if(index == std::string::npos){
					//warn them but don't throw an invalid argument for now. Just make it be the element at index 0.
					std::cout << "Warning. The character \"" << string_key[pos-1] <<"\" was not found." << std::endl;
					index=0;
				}
				//normally it'd be key(i,j) but because I am converting the key from a string of characters I have to set it up as if it was multiple
				//vectors that have 1 column, but rows equal to the chunks size. So to make it fill elements row-wise this little hack has to be done.
				key(j,i)=index;
			}
		}
		chunk_size=cols;
		decryption_key=key.inv_mod(alphabet_size);
	}
	
	void set_key(const char &string_key,const size_t size=0){

	}
};


#endif //_HILL_CIPHER_H
