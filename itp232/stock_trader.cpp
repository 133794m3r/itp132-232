#include <iostream>
#include "terminal.h"
#include "stock_trader.h"
#include <stdio.h>
//this'll be a simple trading game. Buy an item for a price, then see if you want to seell it. 
//costs'll be randomized each day. Goal is to have the maximum amount of money in the end.


typedef std::vector<Item*> vector_ptr_item;
typedef std::vector<int*> vector_ptr_int;

void print_items(vector_ptr_item &Items){

	std::cout.precision(2);
	std::cout.setf( std::ios::fixed, std:: ios::floatfield );
	for(Item *current:Items){
		printf("\x1b[%dm%d\x1b[22m:",1,current->get_id());
		switch(current->get_flag()){
			case 1:
				printf("\x1b[33;1m%s\x1b[37;22m",current->get_name().c_str());
				break;
			case 2:
				printf("\x1b[31;1m%s\x1b[37;22m",current->get_name().c_str());
				break;
			default:
				printf("%s",current->get_name().c_str());
				break;
		}		
		std::cout << " $" << current->get_price();
		std::cout << std::endl;
	}
	//std::cout << std::endl;
}

void update_prices(vector_ptr_item &Items){
	double current_price=0.0f;
	double modifier=0.0f;
	double new_price=0.0f;
	char flag=0;
	for(Item *current_item:Items){
		current_price=current_item->get_price();
		modifier=xorshift128(0.85,1.15);
		flag=xorshift128(0,25);
		if(flag >= 10 && flag <= 16){
			flag=1;
			modifier+=xorshift128(0.5,1.25);
		}
		else if(flag >=17 && flag <= 22){
			modifier-=xorshift128(0.25,0.55);
			flag=2;
		}
		else
			flag=0;
		new_price=current_price*modifier;
		current_item->set_flag(flag);
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
	unsigned int max_days=9;
	double starting_balance=1000.0f;
	double final_balance=0.0f;
	int selection=0;
	int tx_success=0;	
	bool owns_something=false;
	vector_ptr_item items = { new Item("Tuna Fish", 10.5), new Item("Bunch of Bananas", 3.7),
	new Item("Barrel of Oil", 100.35), new Item("Wuhan Bat Soup",66.6), new Item("Shiny Water Charizard",37.51),
	new Item("Chocolate Chip Cookies Futures",5.31), new Item("Giant Fishstick",13.31), new Item("Signed Photo of Nessie", 3.50)
	};
	int total_items=items.size();

	std::cout << "Please enter your name: ";
	getline(std::cin, username);
	Account *user = new Account(username,starting_balance);
	Inventory *user_inventory=new Inventory(total_items,items);
	//make sure that the colors are always what I want. White on black.
	std::cout << "\x1b[37;40m";
	std::cout << "\x1b[0;0H";
	std::cout << "\x1b[0J" << "\x1b[0;0H";
	std::cout << "Welcome to the Trading simulator. You will play for "<< max_days << " days. The goals is to end up with the maximum money at the end of it.\r\nYou start off with $1000.0\r\nEach day there will be a list of items to buy at the start, then a list of items that people want to buy. Both will have a price listed beside them along with how many of them there are. At the end of the game any unsold items will be automatically sold for the final sale price and added to your final total" << std::endl;
	std::cout << "The item of the day is \x1b[1mBolded\x1b[22m and also colored \x1b[93mBright Yellow\x1b[37m. This item is in high demand so the price is SKY HIGH! Also the item no one wants is also \x1b[1mBolded\x1b[22m and it's color is \x1b[31mRed\x1b[37m. That means the item is at a ROCK BOTTOM PRICE! So keep your eyes peeeled for this deals. Remember to sell \x1b[1;93mHIGH\x1b[22;37m and buy \x1b[1;93mLOW\x1b[22;37m if you can!"<< std::endl;
	
	
	for(current_day=0;current_day < max_days;current_day++){
		selection=0;
		while(selection != -1){
			std::cout << "Welcome to Day " << current_day << ", \x1b[1;3m" << username << "\x1b[22;24m!";
			std::cout << " You currently have: $" << user->get_balance() << std::endl;
			std::cout << "\r\nHere are the items you can buy: ";
			std::cout << "Select the item you want to buy pressing the respective number. To quit buying for the day enter -1." << std::endl << std::endl;
			print_items(items);
			std::cout << "\x1b[1mSelection:";
			std::cin >> selection;
			std::cout << "\x1b[0m";
			if(selection == -1){
				selection=0;		
				break;
			}
			else if(selection < total_items){
				tx_success=user_inventory->purchase_item(*user,*items[selection],total_items);
				if(tx_success == 1){
				std::cout << "You have successfully purchased your items." << std::endl;
				}
				else if(tx_success == -1){
					std::cout << "You tried to buy more than you could afford!" << std::endl;
				}
			}
			else
				std::cout << "Your selection: " << selection << " wasn't valid. Please try again." << std::endl;
			system("pause");
			move_and_clear_terminal(5,total_items);
	
		}
		move_and_clear_terminal(7,total_items);	
		while(selection != -1){
			std::cout << "Welcome to the end of day " << current_day << ", \x1b[1;3m" << username << "\x1b[22;24m!";
			std::cout << " You currently have: $" << user->get_balance() << std::endl;
			std::cout << "\r\nHere are the items you can sell: ";
			std::cout << "Select the item you want to sell pressing the respective number. To quit selling for the day enter -1." << std::endl << std::endl;
			owns_something=user_inventory->print_items();
			std::cout << "\x1b[1mSelection:";
			std::cin >> selection;
			std::cout << "\x1b[0m";
			if(selection == -1){
				selection=0;
				if(!owns_something)
					move_and_clear_terminal(6,0);
				else
					move_and_clear_terminal(5,total_items);
				break;
			}
			else if(selection < total_items){
				tx_success=user_inventory->sell_item(*user,*items[selection],total_items);
				if(tx_success == 1){
					std::cout << "You have successfully sold your items." << std::endl;
				}
				else if(tx_success == -1){
					std::cout << "You tried to sell more than you own!" << std::endl;
				}
				system("pause");
				if(!owns_something)
					move_and_clear_terminal(6,0);
				else
					move_and_clear_terminal(5,total_items);
				}
			else
				std::cout << "Your selection: '" << selection << "' wasn't valid. Please try again." << std::endl;			
		}
		update_prices(items);

	}
	user_inventory->sell_all_items(*user);
	final_balance=user->get_balance();
	std::cout << "At the end of day " << current_day+1;
	std::cout << ". All of your items were sold.\r\nYour final balance is $" << final_balance;
	final_balance-=starting_balance;
	std::cout << "Your net profit was: $";
	if(final_balance < 0)
		std::cout << "\x1b[31;1m";
	else
		std::cout << "\x1b[93;1m";
	std::cout << final_balance << "\x1b[37;22m" << std::endl;
	std::cout << "Try again to see how much you can wrack up!" << std::endl;
	return 0;
}