#ifndef CRYPTO_MATH_HEADER
#define CRYPTO_MATH_HEADER

template <typename T> egcd(T a, T b, T *x, T *y){
	if(a == 0){
		*x=0;
		*y=1;
		return b;
	}
	T x1,y1;
	T gcd = egcd((a+b)%a, a, &x1, &y1);
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
	
	gcd=egcd(a,mod,&x,&y);
	if((gcd != 1) && (gcd != -1)){
		throw std::invalid_argument("The gcd between a and the modulus must be either 1 or -1");
	}
	
	if((sign_a < 0) && (sign_mod < 0))
		return -1*((x+mod)%mod);
	else
		return x % mod;


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
#endif