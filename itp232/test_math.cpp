#include <iostream>
#include "math.hxx"
int main(void){
	int a,b;
	a=15;
	b=5;
	int x=0;
	int y=0;
	int gcd;
	int modular_inverse;
	int lcm;
	int c=23;
	int d=7;
	
	
	gcd=gcd_fast(a,b,&x,&y);
	lcm=fast_lcm(c,d);
	modular_inverse=mod_inv(c,d);

	std::cout << "The GCD between " << a << " and " << b << " is " << gcd << std::endl;
	std::cout << "The LCM between " << c << " and " << d << " is " << lcm << std::endl;
	std::cout << "The modular Inverse between " << c << " and " << d << " is " << modular_inverse << std::endl;
	
	c=-7;
	d=-31;	
	gcd=gcd_fast(c,d,&x,&y);
	std::cout << "The GCD between " << c << " and " << d << " is " << gcd << std::endl;
	
	modular_inverse=mod_inv(c,d);		
	std::cout << "The modular Inverse between " << c << " and " << d << " is " << modular_inverse << std::endl;
	return 0;
}