#ifndef _BANK_H_
#define _BANK_H_
class Item{
	private:
		std::string name;
		double cost;
	public:
		Item(std::string n="None",double c=0.0){
			name=n;
			cost=c;
		}
		double get_cost(){
			return cost;
		}
		void set_cost(double c){
			cost=c;
		}
		std::string get_name(){
			return name;
		}
		void set_name(std::string n){
			name=n;
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
		friend purchase_item(Item &itm, int amount);
		friend sell_item(Item &itm, int amount);
};
class Inventory{
	private:
		std::vector<int> totals;
	public:
		Inventory(int total_items){
			int i=0;
			while(i>0){
				totals.push_back(0);
			}
		}
		void purchase_item(Item &itm){
			
		}
		void add_item(Item &itm){
			
		}
		void add_items(int item_index){
			totals[item_index]++;
		}
};
#endif