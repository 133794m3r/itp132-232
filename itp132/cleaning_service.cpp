#include <iostream>
/*
* Cleaning service thing.
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/
int main(){
	const char small_rooms_price=25;
	const char large_room_price=35;
	const double sales_tax=0.06;
	const expiry=30;
	double total_costs=0.0
	std::cout << "Estimate for cleaning service\r\nNumber of small rooms: ";
	std::cin >> small_rooms;
	std::cout << "Number of large rooms: ";
	std::cin >> large_rooms;
	std::cout << "What is the sales tax in your state(hit enter for default value): ";
	std::cin >> local_tax;
	
	if(local_tax == ''){
		local_tax=sales_tax
	}
	
	std::cout "Price per large room: $" << large_room_price << std::endl;
	std::cout "Price per small room: $" << small_room_price << std::endl;
	total_cost=((small_room_price*small_rooms)+(large_room_price*large_rooms))*(1+local_tax)
	std::cout << "Cost: $" << total_cost << std::endl;
	std::cout << "It is valid for " << expiry << " days.";
	
	return 0;
}