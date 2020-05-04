#include <iostream>
#include "terminal.h"
#include "stock_trader.h"
#include <stdio.h>
//this'll be a simple trading game. Buy an item for a price, then see if you want to seell it. 
//costs'll be randomized each day. Goal is to have the maximum amount of money in the end.


typedef std::vector<Item*> vector_ptr_item;
typedef std::vector<int*> vector_ptr_int;

void print_items(vector_ptr_item &Items){
	int i=0;
		std::cout.precision(2);
		std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	for(Item *current:Items){
		printf("\x1b[%dm%d\x1b[22m:",1,i++);
		std::cout << current->get_name();

		std::cout << " $" << current->get_price();
		std::cout << std::endl;
	}
	//std::cout << std::endl;
}

void update_prices(vector_ptr_item &Items){
	double current_price=0.0f;
	double new_price=0.0f;
	for(Item *current_item:Items){
		current_price=current_item->get_price();
		new_price=to_fixed(current_price*xorshift128(0.85,1.15),2);
		current_item->set_price(new_price);
	}
}

int purchase_item_menu(){
	return 0;
}
int main(){
	//xor128 isn't the best PRNG but it's good enough for this simple exercise.
	s_xor_128();
	std::string username;
	unsigned int current_day=0;
	double starting_balance=1000.0;
	int selection=0;
	int tx_success=0;	
	vector_ptr_item items = { new Item("Tuna Fish", 10.5), new Item("Bunch of Bananas", 3.7),
	new Item("Barrel of Oil", 100.35), new Item("Wuhan Bat Soup",66.6), new Item("Shiny Water Charizard",97.51),
	new Item("Chocolate Chip Cookies Futures",5.31), new Item("Giant Fishstick",13.31), new Item("Signed Photo of Nessie", 3.50)
	};
	unsigned int total_items=items.size();

	std::cout << "Please enter your name: ";
	getline(std::cin, username);
	Account *user = new Account(username,starting_balance);
	Inventory *user_inventory=new Inventory(total_items,items);
	//make sure that the colors are always what I want. White on black.
	std::cout << "\x1b[37;40m";
	std::cout << "\x1b[0;0H";
	std::cout << "\x1b[0J" << "\x1b[0;0H";
	std::cout << "Welcome to the Trading simulator. You will play for 3 days. The goals is to end up with the maximum money at the end of it.\r\nYou start off with $1000.0\r\nEach day there will be a list of items to buy at the start, then a list of items that people want to buy. Both will have a price listed beside them along with how many of them there are. At the end of the game any unsold items will be automatically sold for the final sale price and added to your final total" << std::endl;
	std::cout << "The item of the day is \x1b[1mBolded\x1b[22m and also colored \x1b[93mBright Yellow\x1b[37m. This item is in high demand so the price is SKY HIGH! Also the item no one wants is also \x1b[1mBolded\x1b[22m and it's color is \x1b[31mRed\x1b[37m. That means the item is at a ROCK BOTTOM PRICE! So keep your eyes peeeled for this deals. Remember to sell \x1b[1;93mHIGH\x1b[22;93m and buy \x1b[1;37LOW\x1b[1m if you can!"<< std::endl;
	
	
	for(current_day=0;current_day < 2;current_day++){
		selection=0;
		if(current_day > 0)
			std::cout << "\x1b[10F\x1b[0J";
		while(selection != -1){
			std::cout << "Welcome to Day " << current_day << ", \x1b[1;3m" << username << "\x1b[22;24m!\r\nHere are the items you can buy: ";
			std::cout << "Select the item you want to buy pressing the respective number. To quit buying for the day enter -1." << std::endl << std::endl;
			print_items(items);
			std::cout << "\x1b[1mSelection:";
			std::cin >> selection;
			std::cout << "\x1b[0m";
			if(selection == -1)
				break;
			tx_success=user_inventory->purchase_item(*user,*items[selection]);
			std::cout << tx_success << std::endl;
			if(tx_success == 1){
				std::cout << "You have successfully purchased your items." << std::endl;
			}
			else if(tx_success == -1){
				std::cout << "You tried to buy more than you could afford!" << std::endl;
			}
			std::cout << "\x1b[5F\x1b[0J";				
		}
		update_prices(items);
		system("pause");
	}
	return 0;
}