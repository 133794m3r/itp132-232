#include <iostream>
#include "terminal.h"
#include "stock_trader.h"
#include <cstdio>
#include <string>

/*
* Stock Trader CLI Application
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/
//this'll be a simple trading game. Buy an item for a price, then see if you want to seell it. 
//costs'll be randomized each day. Goal is to have the maximum amount of money in the end.

typedef std::vector<Item*> vector_ptr_item;
typedef std::vector<int*> vector_ptr_int;

//prints all items by reference.
void print_items(vector_ptr_item &Items){
	//have to set it up for every freaking function it should be able to be global but oh well.
	std::cout.precision(2);
	//then make sure it always prints 2 digits.
	std::cout.setf( std::ios::fixed, std::ios::floatfield);
	
	//for each loop for each item pointer in the item.
	for(Item *current:Items){
		//bold the first character of the id and reset the bold.
		printf("\x1b[%dm%d\x1b[22m:",1,current->get_id());
		
		//switch statement based upon flag.
		switch(current->get_flag()){
			//case 1 is the yellow version aka "hot item"
			case 1:
				printf("\x1b[33;1m%s\x1b[37;22m",current->get_name().c_str());
				break;
			
			//case 2 is the red version aka "no one wants"
			case 2:
				printf("\x1b[31;1m%s\x1b[37;22m",current->get_name().c_str());
				break;
			
			//otherwise it's a normal type.
			default:
				printf("%s",current->get_name().c_str());
				break;
		}
		//put the dollar sign before the price.
		std::cout << " $" << current->get_price();
		std::cout << std::endl;
	}
}
//update all of the prices.
void update_prices(vector_ptr_item &Items){
	//init files.
	double current_price=0.0f;
	double modifier=0.0f;
	double new_price=0.0f;
	char flag=0;
	//for each.
	for(Item *current_item:Items){
		//get price.
		current_price=current_item->get_price();
		//calculate the modifier between 0.85 and 1.15 inclusive.
		modifier=xorshift128(0.85,1.15);
		//what flag the item should have.
		flag=xorshift128(0,25);
		//6/25 ~5% chance of being a hot item.
		if(flag >= 10 && flag <= 16){
			flag=1;
			//figure out how much more it should be worth.
			modifier+=xorshift128(0.5,1.25);
		}
		
		//next block of 6 is for lower cost items.
		else if(flag >=17 && flag <= 23){
			modifier-=xorshift128(0.25,0.55);
			flag=2;
		}
		//otherwise it's a normal.
		else
			flag=0;
		//update everything.
		new_price=current_price*modifier;
		current_item->set_flag(flag);
		current_item->set_price(new_price);
	}
}

//templated function to clear all vecotr points.
template <typename T> void clear_all_vectors(T &vectors){
	for(auto &x:vectors){
		delete x;
	}
}

//main.
int main(){
	//xor128 isn't the best PRNG but it's good enough for this simple exercise.
	s_xor_128();
	//their username.
	std::string username;
	//all of the variables getting setup.
	unsigned int current_day=0;
	unsigned int max_days=2;
	double starting_balance=1000.00f;
	double final_balance=0.0f;
	int selection=0;
	int tx_success=0;	
	bool owns_something=false;

	//create a pointer to other pointers.
	vector_ptr_item items = { new Item("Tuna Fish", 10.5), new Item("Bunch of Bananas", 3.7),
	new Item("Barrel of Oil", 100.35), new Item("Wuhan Bat Soup",66.6), new Item("Shiny Water Charizard",37.51),
	new Item("Chocolate Chip Cookies Futures",5.31), new Item("Giant Fishstick",13.31), new Item("Signed Photo of Nessie", 3.50)};
	
	//get the total items.
	int total_items=items.size();
	
	//prompt for name.
	std::cout << "Please enter your name: ";
	getline(std::cin, username);
	
	//the user will be a pointer of Account type.
	Account *user = new Account(username,starting_balance);
	
	//Inventory is the same also set it up.
	Inventory *user_inventory=new Inventory(total_items,items);
	
	//make sure that the colors are always what I want. White on black.
	std::cout << "\x1b[37;40m";
	//jump to the top.
	std::cout << "\x1b[0;0H";
	//clear all of the terminal and reset cursor to the top.
	std::cout << "\x1b[0J" << "\x1b[0;0H";
	
	//tell them the startup information.
	std::cout << "Welcome to the Trading simulator. You will play for "<< max_days << " days. The goals is to end up with the maximum money at the end of it.\r\nYou start off with $1000.00\r\nEach day there will be a list of items to buy at the start, then a list of items that people want to buy. Both will have a price listed beside them along with how many of them there are. At the end of the game any unsold items will be automatically sold for the final sale price and added to your final total" << std::endl;
	std::cout << "The item of the day is \x1b[1mBolded\x1b[22m and also colored \x1b[93mBright Yellow\x1b[37m. This item is in high demand so the price is SKY HIGH! Also the item no one wants is also \x1b[1mBolded\x1b[22m and it's color is \x1b[31mRed\x1b[37m. That means the item is at a ROCK BOTTOM PRICE! So keep your eyes peeeled for this deals. Remember to sell \x1b[1;93mHIGH\x1b[22;37m and buy \x1b[1;93mLOW\x1b[22;37m if you can!"<< std::endl;
	
	//go through each of the days.
	for(current_day=0;current_day < max_days;current_day++){
		//reset the selection to 0 at the beginning of each day.
		selection=0;
		//-1 means they're done with it.
		while(selection != -1){
			//welcome them.
			std::cout << "Welcome to Day " << current_day << ", \x1b[1;3m" << username << "\x1b[22;24m!";
			std::cout << " You currently have: $" << user->get_balance() << std::endl;
			std::cout << "\r\nHere are the items you can buy: ";
			std::cout << "Select the item you want to buy pressing the respective number. To quit buying for the day enter -1." << std::endl << std::endl;
			
			//print all of the items.
			print_items(items);
			
			//prompt for selection.
			std::cout << "\x1b[1mSelection\x1b[22m:";
			//std::cin >> selection;
			proper_input(selection);
			//if it's -1 we're done.
			if(selection == -1){
				selection=0;
				break;
			}
			//if it's less than the total items it's a valid number.
			else if(selection < total_items && selection >= 0){
				//try to purchase the item.
				tx_success=user_inventory->purchase_item(*user,*items[selection],total_items);
				//it succeeded tell them they bought it.
				if(tx_success == 1){
				std::cout << "You have successfully purchased your item(s)." << std::endl;
				}
				//it failed for some reason.
				else if(tx_success == -1){
					std::cout << "You tried to buy more than you could afford!" << std::endl;
				}
				pause();
//system("pause");
				move_and_clear_terminal(0,total_items);
			}
			else {
				//they tried to do something other than what's valid.
				std::cout << "Your selection: " << selection << " wasn't valid. Please try again." << std::endl;
				//move the terminal back up and clear the old stuff.
				pause();
//system("pause");
				move_and_clear_terminal(8,total_items);				
			}
			//evil pause thing since I don't want to prompt for something else during the loop.
	
	
		}
		//we're done with the day so move it up and clear it.
		move_and_clear_terminal(7,total_items);
		
		//next selection.
		while(selection != -1){
			//end of day is when they sell things.
			std::cout << "Welcome to the end of day " << current_day << ", \x1b[1;3m" << username << "\x1b[22;24m!";
			std::cout << " You currently have: $" << user->get_balance() << std::endl;
			std::cout << "\r\nHere are the items you can sell: ";
			std::cout << "Select the item you want to sell pressing the respective number. To quit selling for the day enter -1." << std::endl << std::endl;
			
			//see if you own _anything_.
			owns_something=user_inventory->print_items();
			//prompt them for their selection.
			std::cout << "\x1b[1mSelection:\x1b[22m";
			proper_input(selection);
			
			//if it's -1 then it's time to end the day.
			if(selection == -1){
				selection=0;
				//if they don't own anything then we have less to do.
				if(!owns_something)
					move_and_clear_terminal(6,0);
				
				else
					move_and_clear_terminal(5,total_items);
				break;
			}
			//once again it's a valid selection
			else if(selection < total_items && selection >= 0){
				//see if they can sell an item from inventory.
				tx_success=user_inventory->sell_item(*user,*items[selection],total_items);
				//yes they could.
				if(tx_success == 1){
					std::cout << "You have successfully sold your items." << std::endl;
				}
				//nope they couldn't.
				else if(tx_success == -1){
					std::cout << "You tried to sell more than you own!" << std::endl;
				}
			}
			//they tried to do something invalid.
			else
				std::cout << "Your selection: '" << selection << "' wasn't valid. Please try again." << std::endl;			
			
			//evil pause.
			pause();
//system("pause");
			//see if you own anything if not we have to do less work.
			if(!owns_something)
				move_and_clear_terminal(6,0);
			
			else
				move_and_clear_terminal(5,total_items);			
		}
		//update all prices as a day has passed.
		update_prices(items);

	}
	//sell all of their items at the end of the game.
	user_inventory->sell_all_items(*user);
	//get their final balance.
	final_balance=user->get_balance();
	//tell them how well they did.
	std::cout << "At the end of day " << current_day+1;
	std::cout << ". All of your items were sold.\r\nYour final balance is $" << final_balance;
	//whether they were in the red(lost money) or in the yellow(gained money)
	final_balance-=starting_balance;
	std::cout << "Your net profit was: $";
	//if it's - they lost money.
	if(final_balance < 0)
		std::cout << "\x1b[31;1m";
	//they made a profit.
	else
		std::cout << "\x1b[93;1m";
	std::cout << final_balance << "\x1b[37;22m" << std::endl;
	//prompt them to play again.
	std::cout << "Try again to see how much you can wrack up!" << std::endl;
	
	//cleanup my mess.
	delete user;
	delete user_inventory;
	//this'll loop over a vector and delete all elements that are pointers.
	clear_all_vectors(items);
	items.clear();
	return 0;
}