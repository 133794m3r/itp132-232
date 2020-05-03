#include <iostream>
#include <vector>
#include "accounts.h"
//this'll be a simple trading game. Buy an item for a price, then see if you want to seell it. 
//costs'll be randomized each day. Goal is to have the maximum amount of money in the end.
typedef std::vector<Item *> vector_ptr_item;
typedef std::vector<int *> vector_ptr_int;
void update_prices(void){
	
}
void update_amounts(void){
	
}
void print_items(vector_ptr_item &items){
	int i=0;
	
	for(Item *current:items){
		if(i>0)
			std::cout << ",";
		std::cout << current->get_name();
	}
	std::cout << std::endl;
}
int main(){
	std::string username;
	double starting_balance=1000.0;
	vector_ptr_item items = { new Item("Tuna Fish", 10.5), new Item("Bunch of Bananas", 3.7), new Item("Barrel of Oil", 100.35),new Item("Wuhan Bat Soup",66.6)};
	std::cout << "Please enter your name: ";
	getline(std::cin, username);
	Account *user = new Account(username,starting_balance);
	Inventory *user_inventory=new Inventory(items.size());
	std::cout << "Welcome to the Trading simulator. You will play for 3 days. The goals is to end up with the maximum money at the end of it.\r\nYou start off with $1000.0\r\n Each day there will be a list of items to buy at the start, then a list of items that people want to buy. Both will have a price listed beside them along with how many of them there are. At the end of the game any unsold items will be automatically sold for the final sale price and added to your final total" << std::endl;
	std::cout << user->get_name() << " " << user->get_balance() << std::endl;
	
	print_items(items);
	return 0;
}