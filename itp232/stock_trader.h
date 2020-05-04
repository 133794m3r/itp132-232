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
		unsigned int id=0;
		static unsigned int current_id;
	public:

		Item(std::string n="None",double c=0.0){
			name=n;
			price=c;
			id=current_id++;
		}
		double get_price(){
			return price;
		}
		void set_price(double c){
			price=c;
		}
		std::string get_name(){
			return name;
		}
		void set_name(std::string n){
			name=n;
		}
		unsigned int get_id(){
			return id;
		}
		
	
};
unsigned int Item::current_id=0;
class Account;
class Inventory{
	private:
		std::vector<int> total_owned;
		std::vector<Item*> Items;
	public:
		Inventory(int total_items,std::vector<Item *>itms){
			int i=0;
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
		int purchase_item(Account &usr,Item &itm);
		int sell_item(Account &usr, Item &itm, int amount);
		void print_items(){
			for(Item *item:Items){
				std::cout << "name: " << item->get_name() << " ";
				std::cout << "cost: " << item->get_price() << " ";
				std::cout << "id: " << item->get_id() << " " << std::endl;
			}
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
		friend int Inventory::purchase_item(Account &usr,Item &itm);
		friend int Inventory::sell_item(Account &usr,Item &itm, int amount);
};
	int Inventory::purchase_item(Account &usr,Item &itm){
			int amount=0;
			double available_funds = usr.get_balance();
			double total_cost = 0;
			double price=itm.get_price();
			int can_buy = available_funds / price;
			std::cout << "\x1b[9A\x1b[0J";
			std::cout << "To exit enter zero as the amount.\r\nYou have selected " << itm.get_name() << std::endl;
			std::cout << "You can buy: " << can_buy <<".";
			std::cout << "How many would you like to buy?";
			std::cin >> amount;
			if(amount ==0)
				return 0;
			total_cost=amount*price;
	
			if(total_cost <= available_funds){
				total_owned[itm.get_id()]+=amount;
				usr.balance-=total_cost;
				return 1;
			}
			else
				return -1;
	}
		
	int Inventory::sell_item(Account &usr, Item &itm, int amount){
			unsigned int owned=total_owned[itm.get_id()];
			double price = itm.get_price();
			if(owned >= amount){
				usr.balance+=(amount*price);
				total_owned[itm.get_id()]-=amount;
				return true;
			}
			else{
				return false;
			}
	}
#endif