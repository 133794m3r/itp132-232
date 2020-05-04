#ifndef XOR_RANDOM_LIB
#define XOR_RANDOM_LIB
#ifndef uint64
typedef unsigned long long uint64;
#endif
uint64 XOR_SHIFT_128_STATE[2]={0LL,0LL};
unsigned long long splitmix64(uint64 seed){
	uint64 z=(seed+0x9E3779B97F4A7C15LL);
	z=(z^(z>>30))*0xBF58476D1CE4E5B9LL;
	z=(z^(z >> 27))*0x94D049BB133111EBLL;
	return z ^ (z >> 32);
}
void s_xor_128(uint64 seed=0){
	seed=(std::chrono::system_clock::now().time_since_epoch()/std::chrono::milliseconds(1));
	XOR_SHIFT_128_STATE[0]=splitmix64(seed);
	XOR_SHIFT_128_STATE[1]=splitmix64(seed+1);
}

template <typename T> T xorshift128(T low=0, T high=1){
	uint64 s1=XOR_SHIFT_128_STATE[0];
	uint64 s0=XOR_SHIFT_128_STATE[1];  
	uint64 result=XOR_SHIFT_128_STATE[0]+XOR_SHIFT_128_STATE[1];
	XOR_SHIFT_128_STATE[0]=s0;
	s1 ^= s1 << 23;
	XOR_SHIFT_128_STATE[1]=s1;
	XOR_SHIFT_128_STATE[1]=s1 ^ s0 ^ (s1 >> 17) ^ (s0 >> 26);
	if(low == 0 && high == UINT64_MAX){
		return result;
	}
	else{
		return low+(double(high-low)*((double)result/(double) UINT64_MAX));
	}
}

#endif