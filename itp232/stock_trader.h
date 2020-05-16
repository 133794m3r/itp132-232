#ifndef _BANK_H_
#define _BANK_H_
#include <cmath>
#include <vector>
#include <memory>
#include <chrono>
#include "random.h"
/*
* Stock Trader CLI Application
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/
//simple precision rounder.
template <typename F,typename P> F to_fixed(F num,P precision){P modifier=pow(10,precision); return round(num*modifier)/modifier;}
//simple typedef
typedef unsigned int uint32;

//item class.
class Item{
		private:
		//all fixed sized elements should be allocated first to keep memory better aligned.
		double price;
		unsigned int id = 0;
		static unsigned int current_id;
		int flag = 0;
		//then we do items that are variable size.
		std::string name;

		
	public:
		//constructor.
		Item(std::string n="None",double c=0.0,int the_flag=0){
			name=n;
			price=c;
			//make the id auto-increment each time it's called.
			id=current_id++;
			flag=the_flag;
		}
		//getters and setters.
		double get_price(){
			return price;
		}
		
		void set_price(double c){
			price=c;
		}
		
		std::string get_name(void){
			return name;
		}
		
		void set_name(std::string n){
			name=n;
		}
		
		unsigned int get_id(){
			return id;
		}
		
		int get_flag(void){
			return flag;
		}
		
		void set_flag(int the_flag){
			flag=the_flag;
		}
	
};
//set the static item to 0 so that the item id will auto increment.
unsigned int Item::current_id=0;
//forward declare the account class so that I can call properties of it in
//the Inventory class.
class Account;

//Inventory class.
class Inventory{
	private:
		bool owns_nothing=false;
		//vector of all owned items.
		std::vector<unsigned int> total_owned;
		//vector of pointers.
		std::vector<Item*> Items;
		
	public:
		//constructor.
		Inventory(int total_items,std::vector<Item *>itms){
			int i=0;
			for(i=0;i<total_items;i++){
				Items.push_back(itms[i]);
				total_owned.push_back(0);
			}
		}
		//setter.
		void add_item(uint32 itm_idx, uint32 amount){
			total_owned[itm_idx]+=amount;
		}
		//setter.
		bool remove_item(uint32 itm_idx, uint32 amount){
			if(total_owned[itm_idx] > amount){
				total_owned[itm_idx]-=amount;
				return true;
			}
			
			else{
				return false;
			}
		}
		/*
		*stubs here so that I can declare method outside of class once Account is declared.
		*This is so that I can already have them also setup for the friend methods
		* when I declare the account class.
		*/
		//purchase an item.
		int purchase_item(Account &usr,Item &itm, unsigned int total_items);
		//sell the item.
		int sell_item(Account &usr, Item &itm, unsigned int total_items);
		//sell all of the items.
		void sell_all_items(Account &usr);
		
		//print everything in their inventory.
		bool print_items(){	
			std::cout.precision(2);
			std::cout.setf( std::ios::fixed, std::ios::floatfield );			
			int i=-1;
			//whether they own everything.
			bool owns_something=false;
			//for each loop.
			for(Item *item:Items){
				//see how many they own of every item and increment i.
				if(total_owned[i++] != 0){
					owns_something=true;
					//print the item based upon it's id and bolded.
					printf("\x1b[%dm%d\x1b[22m:",1,item->get_id());
					
					//same swtich flag as the print item normally.
					switch(item->get_flag()){
						//it's a hot item.
						case 1:
							printf("\x1b[33;1m%s\x1b[22;37m",item->get_name().c_str());
							break;
						
						//it's a bad item so make it red.
						case 2:
							printf("\x1b[31;1m%s\x1b[22;37m",item->get_name().c_str());
							break;
						//otherwise it's normal.
						default:
							printf("%s",item->get_name().c_str());
							break;
					}
					
					//print the price and how many they own.
					std::cout << " $" << item->get_price();
					std::cout << " Owned: " << total_owned[i];
					std::cout << std::endl;						
				}
			}
			//return whether they own anything if it's still false it means they don't.
			return owns_something;
		}
	
	//this was just here for debug purposes.
	void print_owned(void){
		int i=0;
		
		for(unsigned int total:total_owned){
			
			std::cout << "total_owned[" << i++ << "]=" << total << ",";
		}
		
		std::cout << std::endl;
	}

};
//Account class.
class Account{
	private:
		std::string name;
		double balance;
		
	public:
		//constructor.
		Account(std::string n="None", double bal=0.0){
			name = n;
			balance=bal;
		}
		
		//setters and getters.
		void set_balance(double bal){
			balance=bal; 
		}
		
		double get_balance(){
			return balance;
		}
		
		//showing off the this pointer.
		void set_name(std::string n){
			this->name=n;
		}
		//same here.
		std::string get_name(){
			return this->name;
		}
		
		bool deposit(double amount){
			balance+=amount;
			return true;
		}
		
		bool withdraw(double amount){
			if (balance-amount>=0){
				balance-=amount;
				return true;
			}
			else{
				return false; 
			}
		}
		
		//friend functions fully defined as a method of another class not available
		//to anything else.
		friend int Inventory::purchase_item(Account &usr,Item &item,unsigned int total_items);
		friend int Inventory::sell_item(Account &usr,Item &item,unsigned int total_items);
		friend void Inventory::sell_all_items(Account &usr);
};


//The other class methods are declared below.
/*
* Inventory Purchase Item method.
* Account &usr is an Account pointer to the user's account.
* Item &item is an Item pointer to the current item.
* returns a status code.
*/
int Inventory::purchase_item(Account &usr,Item &item,unsigned int total_items){
	int amount=0;
	//get their current balance.
	double available_funds = usr.get_balance();
	//initialize a bunch of vars.
	double total_cost = 0;
	double price=item.get_price();
	//figure out how many they can buy.
	double can_buy = floor(available_funds / price);
	//get ready to print our stuff.
	move_and_clear_terminal(4,total_items);
	//show the menu to them.
	std::cout << "To exit enter zero as the amount.\r\nYou have selected " << item.get_name() << std::endl;
	std::cout << "You currently have $" << available_funds << std::endl;
	std::cout << "You can buy: " << can_buy <<" at $" << item.get_price() << "each.";
	std::cout << "How many would you like to buy?";
	//get how many they want.
	std::cin >> amount;
	
	//if they entered zero it's time to end it.
	if(amount ==0)
		return 0;
	//get the total cost of how many they wanted.
	total_cost=amount*price;
	//if they can afford it we buy it.
	if(total_cost <= available_funds){
		//tell them they bought however many of the item.
		std::cout << "bought " << amount << " " << item.get_id() << std::endl;
		//increment the total that they own.
		total_owned[item.get_id()]+=amount;
		//decrease their balance by the total cost.
		usr.balance-=total_cost;
		//purchase acccess is good.
		return 1;
	}
	//they tried to buy more than they could afford.
	else
		return -1;
}
/*
* Sell item Method.
* Params: 
*	Account &usr is an Account pointer to the user's account.
* 	Item &item is an Item pointer to the current item.
* 	Int total_items is how many items that there are in total.
* 
* Returns:
	Int < Status code> 0 == Nothing happened. 1 == success. -1 == failure.
*/
int Inventory::sell_item(Account &usr, Item &item,unsigned int total_items){
	unsigned int amount =0;
	//figure out how many they own.
	unsigned int owned=total_owned[item.get_id()];
	//get the item's price.
	double price = item.get_price();
	//clear the screen.
	move_and_clear_terminal(4,total_items);
	//give them the menu.
	std::cout << "To exit enter zero as the amount.\r\nYou have selected " << item.get_name().c_str() << std::endl;
	std::cout << "You have " << owned <<".";
	std::cout << "How many would you like to sell?";
	//get the amount that they want to sell.
	std::cin >> amount;
	//if they select 0 it's time to return as they didn't care.
	if(amount == 0){
		return 0;
	}
	//they own at least as many as they want to sell they can sell it.
	if(owned >= amount){
		//increase their balance by the total value of sold items.
		usr.balance+=(amount*price);
		//decrease their owned by the amount.
		total_owned[item.get_id()]-=amount;
		//tell them what they did.
		std::cout << "You have sold " << amount << std::endl;
		std::cout << item.get_id() << std::endl;
		//return success.
		return 1;
	}
	//otherwise they tried to sell more than they owned.
	else
		return -1;
}
/*
* Inventory Sell All Items method.
* Params:
*	Account usr is an Account pointer to the user's account.
* Returns:
* Nothing.
*/
void Inventory::sell_all_items(Account &usr){
	unsigned int owned=0;
	double total_sales=0.0f;
	unsigned int i=0;
	//for each loop with each item being taken from the pointers.
	//since it's a method of Inventory we can acccess the items from here.
	//plus since all items are pointers we can access them from within the method or without.
	for(Item *current_item:Items){
		//get their currently owned amount.
		owned=total_owned[i++];
		//if it's not zero.
		if(owned != 0){
			//sell all that they own for the current price.
			total_sales+=(owned*current_item->get_price());
		}
	}
	//set their balance to equal to the total sales amount.
	usr.balance+=total_sales;
}	
#endif