#ifndef CRYPTO_MATH_HEADER
#define CRYPTO_MATH_HEADER
#include <cmath>
template <typename T> gcd_fast(T a, T b, T *x, T *y){
	if(a == 0){
		*x=0;
		*y=1;
		return b;
	}
	T x1,y1;
	T gcd = gcd_fast((a+b)%a, a, &x1, &y1);
	//std::cout <<"gcd:" << gcd << " a:" << a << " b:" << b << " x:" << *x << " y:" << *y << std::endl;
	*x=y1-(b/a) * x1;
	*y=x1;
	return gcd;
}

template <typename T> mod_inv(T a, T mod){
	T gcd=0;
	T x=0;
	T y=0;
	
	int sign_a = (a < 0)?-1:1;
	int sign_mod = (mod < 0)?-1:1;
	a*=sign_a;
	mod*=sign_mod;
	
	gcd=gcd_fast(a,mod,&x,&y);
	if((gcd != 1) && (gcd != -1)){
		throw std::invalid_argument("The gcd between a and the modulus must be either 1 or -1");
	}
	
	if((sign_a < 0) && (sign_mod < 0))
		return -1*((x+mod)%mod);
	else
		return x % mod;


}
template <typename T> *small_prime_factor(T n){
		//the first 20 primes is more than enough for the demo we're doing.
		//as one of the primes from n has to be one of these primes since NCL likes
		//small numbers.
		int primes[20]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71}
		int remainder=0;
		int i=0;
		T p=0;
		T q=0;
		T *two_factors=new T[2];
		
		for(i=0;i<11;i++){
			remainder=n%primes[i];
			if(remainder == 0){
				q=n/primes[i];
				p=n/q;
			}
		}
		two_factors[0]=p;
		two_factors[1]=q;
		return two_factors;
}

template <typename T> fast_lcm(T a,T b){
	T lcm=0;
	T gcd=0;
	T x=0;
	T y=0;
	if(a == 0 || b == 0)
		return 0;
	else if(a == 1)
		return b;
	else if(b == 1)
		return a;
	gcd=egcd(a,b,&x,&y);
	lcm=(a/gcd)*b;
	return lcm;
}
template <typename T> factor
#endif