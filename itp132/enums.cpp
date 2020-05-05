#include <iostream>
#include <cmath>
#include <type_traits>
/*
* Enums demo.
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/

//this'll give me a real round function the way that I want.
//basically I overloaded the round fucntion if it's got 2 params I call this one
//otherwise I do standard round.
inline double round( double val,int precision){
		precision=pow(10,precision);
		return round(val*precision)/precision;
}
//I have to have an iterator.
template < typename C, C beginVal, C endVal>
class Iterator {
	typedef typename std::underlying_type<C>::type val_t;
	int val;
	public:
		Iterator(const C & f) : val(static_cast<val_t>(f)) {}
		Iterator() : val(static_cast<val_t>(beginVal)) {}
		Iterator operator++() {
			++val;
			return *this;
		}
		C operator*() { return static_cast<C>(val); }
		Iterator begin() { return *this; } //default ctor is good
		Iterator end() {
			static const Iterator endIter=++Iterator(endVal); // cache it
			return endIter;
		}
		bool operator!=(const Iterator& i) { return val != i.val; }
};
void calculate_weights(double weight,const char *units){
	//simple use of enum. Since it only works with ints
	//I'm making everything 1000x the normal.
	//this enum shows the || arrays.
	enum planets{earth=0,mars=1,moon=2};
	//wow ||.
	const char *planets_str[3]={"Earth","Mars","The Moon"};
	//muchh ||
	double gravity[3]={9.81,3.721,1.622};
	//create my iterator.
	typedef Iterator<planets, planets::earth, planets::moon> planets_iterator;
	//iterate over it.
	for(int cur_planet:planets_iterator()){
		//spit out the information.
		std::cout << "Your weight on " << planets_str[cur_planet] << " is ";
		std::cout << weight/gravity[earth]*gravity[cur_planet];
		std::cout << units <<" ." << std::endl;
	}
}
int main() {

	//get the user's weight.
	float weight;
	std::string line;
	int unit=0;
	enum units{lb=0,kg=1,oz=2,g=3};	
	typedef Iterator<units, units::lb, units::g> units_iterator;
	const char *unit_str[]={"lb","oz","kg","g"};	
	std::cout << "What is your weight: ";
	std::cin >> weight;
	//prompt them for chosen unit.
	std::cout << "What unit would you like?(hit enter for lb)" << std::endl;
	//iterate over the enum.
	for(int cur_unit:units_iterator()){
		std::cout << cur_unit << "=" << unit_str[cur_unit] << " ";
	}
	//new line it.
	std::cout << std::endl;
	//ignore the last bit of white space.
	std::cin.ignore();
	//get the line.
	std::getline(std::cin,line);
	//cast it to an int if it's not empty.
	unit=(line.empty())?0:atol(line.c_str());
	//tell the the unit.
	std::cout << "Your chosen unit is " << unit_str[unit] << std::endl;
	//call the function to calculate weights.
	calculate_weights(weight,unit_str[unit]);
	
	return 0;

}