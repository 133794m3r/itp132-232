#ifndef _BANK_H_
#define _BANK_H_
#include <cmath>
#include <vector>
#include <memory>
#include <chrono>
#include "random.h"
//template <typename T> T rand_range_real(T L, T H){ return L+((H-L)*(xorshift128()/UINT64_MAX));}
//template <typename T> T rand_range(T L, T H){return rand_range_real(L,H);}

double rand_double(double L,double H){return L+(rand()/(RAND_MAX /(H-L)));}

template <typename F,typename P> F to_fixed(F num,P precision){P modifier=pow(10,precision); return round(num*modifier)/modifier;}

typedef unsigned int uint32;

class Item{
	private:
		std::string name;
		double price;
		unsigned int id = 0;
		static unsigned int current_id;
		int flag = 0;
	public:

		Item(std::string n="None",double c=0.0,int the_flag=0){
			name=n;
			price=c;
			id=current_id++;
			flag=the_flag;
		}
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

unsigned int Item::current_id=0;

class Account;
class Inventory{
	private:
		bool owns_nothing=false;
		std::vector<int> total_owned;
		std::vector<Item*> Items;
	public:
		Inventory(unsigned int total_items,std::vector<Item *>itms){
			unsigned int i=0;
			for(i=0;i<total_items;i++){
				Items.push_back(itms[i]);
				total_owned.push_back(0);
			}
		}
		
		void add_item(uint32 itm_idx, uint32 amount){
			total_owned[itm_idx]+=amount;
		}
		
		bool remove_item(uint32 itm_idx, uint32 amount){
			if(total_owned[itm_idx] > amount){
				total_owned[itm_idx]-=amount;
				return true;
			}
			else{
				return false;
			}
		}
		
		int purchase_item(Account &usr,Item &itm,unsigned int);
		int sell_item(Account &usr, Item &itm,unsigned int);
		void sell_all_items(Account &usr);
		
		bool print_items(){
			std::cout.precision(2);
			std::cout.setf( std::ios::fixed, std::ios::floatfield );			
			int i=-1;
			bool owns_something=false;
			for(Item *item:Items){
				if(total_owned[i++] != 0){
					owns_something=true;
					printf("\x1b[%dm%d\x1b[22m:",1,item->get_id());
					switch(item->get_flag()){
						case 1:
							printf("\x1b[33;1m%s\x1b[22;37m",item->get_name().c_str());
							break;
						case 2:
							printf("\x1b[31;1m%s\x1b[22;37m",item->get_name().c_str());
							break;
						default:
							printf("%s",item->get_name().c_str());
							break;
					}
					std::cout << " $" << item->get_price();
					std::cout << " Owned: " << total_owned[i];
					std::cout << std::endl;						
				}
			}
			return owns_something;
		}
		
	void print_owned(void){
		int i=0;
		for(unsigned int total:total_owned){
			std::cout << "total_owned[" << i++ << "]=" << total << ",";
		}
		std::cout << std::endl;
	}		
};
class Account{
	private:
		std::string name;
		double balance;
	public:
		Account(std::string n="None", double bal=0.0){
			name = n;
			balance=bal;
		}
		void set_balance(double bal){
			balance=bal; 
		}
		double get_balance(){
			return balance;
		}
		void set_name(std::string n){
			this->name=n;
		}
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
		friend int Inventory::purchase_item(Account &usr,Item &item,unsigned int);
		friend int Inventory::sell_item(Account &usr,Item &item,unsigned int);
		friend void Inventory::sell_all_items(Account &usr);
};
	int Inventory::purchase_item(Account &usr,Item &item,unsigned int total_items){
			int amount=0;
			double available_funds = usr.get_balance();
			double total_cost = 0;
			double price=item.get_price();
			int can_buy = available_funds / price;
			move_and_clear_terminal(4,total_items);
			std::cout << "To exit enter zero as the amount.\r\nYou have selected " << item.get_name().c_str() << std::endl;
			std::cout << "You currently have $" << available_funds << std::endl;
			std::cout << "You can buy: " << can_buy <<" at $" << item.get_price() << "each.";
			std::cout << "How many would you like to buy?";
			std::cin >> amount;
			if(amount ==0)
				return 0;
			total_cost=amount*price;
	
			if(total_cost <= available_funds){
				std::cout << "bought " << amount << " " << item.get_id() << std::endl;
				total_owned[item.get_id()]+=amount;
				usr.balance-=total_cost;
				return 1;
			}
			else
				return -1;
	}
	int Inventory::sell_item(Account &usr, Item &item,unsigned int total_items){
			unsigned int amount =0;
			unsigned int owned=total_owned[item.get_id()];
			double price = item.get_price();
			move_and_clear_terminal(4,total_items);
			std::cout << "To exit enter zero as the amount.\r\nYou have selected " << item.get_name().c_str() << std::endl;
			std::cout << "You have " << owned <<".";
			std::cout << "How many would you like to sell?";
			std::cin >> amount;
			if(amount == 0){
				return 0;
			}
			if(owned >= amount){
				usr.balance+=(amount*price);
				total_owned[item.get_id()]-=amount;
				std::cout << "You have sold " << amount << std::endl;
				std::cout << item.get_id() << std::endl;
				return 1;
			}
			else{
				return -1;
			}
	}
	
	void Inventory::sell_all_items(Account &usr){
		unsigned int owned=0;
		double total_sales=0.0f;
		unsigned int i=0;
		for(Item *current_item:Items){
			owned=total_owned[i++];
			if(owned != 0){
				total_sales+=(owned*current_item->get_price());
			}
		}
		usr.balance+=total_sales;
	}	
#endif