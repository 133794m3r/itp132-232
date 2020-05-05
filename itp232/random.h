#ifndef XOR_RANDOM_LIB
#define XOR_RANDOM_LIB
#ifndef uint64
typedef unsigned long long uint64;
#endif
uint64 XOR_SHIFT_128_STATE[2]={0LL,0LL};
//not going to explain the math behind this. It's up to you figure out on your own.
//i'm done commenting.
unsigned long long splitmix64(uint64 seed){
	uint64 z=(seed+0x9E3779B97F4A7C15LL);
	z=(z^(z>>30))*0xBF58476D1CE4E5B9LL;
	z=(z^(z >> 27))*0x94D049BB133111EBLL;
	return z ^ (z >> 32);
}

void s_xor_128(uint64 seed=0){
	//make the seed be the current time since epoch in milliseconds.
	seed=(seed=0)?(std::chrono::system_clock::now().time_since_epoch()/std::chrono::milliseconds(1)):seed;
	//initalize the state with the seed throught the splitmix64 function.
	XOR_SHIFT_128_STATE[0]=splitmix64(seed);
	//take the seed and modify it by a bit and reuse it again.
	XOR_SHIFT_128_STATE[1]=splitmix64(seed<<1);
}
/*
* templated xorshift128 function.
*
* It's type is based upon what the user passes it.
* Low and high are set to 0 by default so that it can be called with a single argument.
* And that argument will be the highest value with 0 being the low automatically.
* 
*/
template <typename T> T xorshift128(T low=0, T high=0){
	//get the current state.
	uint64 s1=XOR_SHIFT_128_STATE[0];
	uint64 s0=XOR_SHIFT_128_STATE[1];  
	//set the result of the values.
	uint64 result=XOR_SHIFT_128_STATE[0]+XOR_SHIFT_128_STATE[1];
	//set state[0] to s0.
	XOR_SHIFT_128_STATE[0]=s0;
	//set the value of s1 to be s^ (s1 << 23)
	s1 ^= s1 << 23;
	/*
	* We are taking s1 shifting it to the right by 18. 
	* take s0 shift it to the right by 5.
	* Then take s1 xor it with s0.
	* then take that intermediate value and xor it with the (s1 >> 18)
	* then take that value and xor it with (s0 >> 5).
	* finall take that value and set it to the state1.
	* s1 XOR s0 XOR (s1 >> 18) XOR (s0 >> 5)
	*/
	XOR_SHIFT_128_STATE[1]=s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
	//if high is equal to low then set high to low and keep low  as zero.
	if(high == 0 && low != 0){
		high=low;
	}
	/*
	* To make sure that we get a value within the range of the high and low.
	* I have to cast the results of the division of result and UINT64_MAX to a double
	* because otherwise it'll be integer division which'll be between 0 and 1.
	* Then I take that result and multiply it by the range (high-low)
	* Then you add the low value and you now have a value that's between low and high(inclusive)
	*/
	return low+((high-low)*((double)result/ UINT64_MAX));	
}

//non templated version for the full width uint64 always.
//not recommenting this bit.
uint64 xorshift128(void){
	//same as above except we dont' change the values and clamp the range down.
	uint64 s1=XOR_SHIFT_128_STATE[0];
	uint64 s0=XOR_SHIFT_128_STATE[1];  
	uint64 result=XOR_SHIFT_128_STATE[0]+XOR_SHIFT_128_STATE[1];
	XOR_SHIFT_128_STATE[0]=s0;
	s1 ^= s1 << 23;
	XOR_SHIFT_128_STATE[1]=s1;
	XOR_SHIFT_128_STATE[1]=s1 ^ s0 ^ (s1 >> 17) ^ (s0 >> 26);

	return result;
}
#endif