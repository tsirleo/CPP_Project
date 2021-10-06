#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <time.h>
#include <limits.h>
#include <unistd.h>

using namespace std;

class Human {
protected:
	string name;
	string lastname;
	int age;
public:
	Human(const char *nm="Ivan", const char *lnm="Ivanov", int a=30): name(nm), lastname(lnm), age(a) {}
	virtual ~Human() {}
	friend ostream& operator << (ostream &out, const Human *h) {
		out << h->name << " " << h->lastname;
		return out;
	}
};
Human *hum;

class Mineral {
protected:
	string name;
	long int amount;
	int price;
public: 
	Mineral(const char *nm, long int n, int p): name(nm) {
		amount = n;
		price = p;
	} 
	virtual ~Mineral() {}
	long int get_amount() const {
		return amount;
	}
	void set_amount(long int x) {
		amount = x;
	}
	int get_price() const {
		return price;
	}
	void set_price(int p) {
		price = p;
	}
	bool check_empty() {
		if (amount == 0)
			return true;
		else
			return false;
	}
	string get_name() const {
		return name;
	}
	void print_mineral_info(int n) const {
		switch (n) {
			case 0: cout << name;
					break;
			case 1: cout << amount;
					break;
			case 2: cout << price;
					break;
		}
	}
	virtual void print_mineral_info() const {
		cout << "Chosen wrong one info printer" << endl;
	} 
	friend ostream& operator << (ostream &out, const Mineral *m) {
		out<< "Mineral: " << endl << "	Name: " << m->get_name() << endl << "	Amount: " << m->get_amount() << endl << "	Price: " << m->get_price() << endl;
		return out;
	}
};

class Coal: public Mineral {
public:
	Coal(long int am, int pr): Mineral("Coal", am, pr) {}
	void print_mineral_info() const {
		cout << "Mineral: " << endl << "	Name: " << name << endl << "	Amount: " << amount << endl << "	Price: " << price << endl;
	} 
};

class Ore: public Mineral {
public:
	Ore(long int am, int pr): Mineral("Ore", am, pr) {}
	void print_mineral_info() const {
		cout << "Mineral: " << endl << "	Name: " << name << endl << "	Amount: " << amount << endl << "	Price: " << price << endl;
	} 
};

class Granite: public Mineral {
public:
	Granite(long int am, int pr): Mineral("Granite", am, pr) {}	
	void print_mineral_info() const {
		cout << "Mineral: " << endl << "	Name: " << name << endl << "	Amount: " << amount << endl << "	Price: " << price << endl;
	} 
};

class Salt: public Mineral {
public:
	Salt(long int am, int pr): Mineral("Salt", am, pr) {}
	void print_mineral_info() const {
		cout << "Mineral: " << endl << "	Name: " << name << endl << "	Amount: " << amount << endl << "	Price: " << price << endl;
	} 
};

class Limestone: public Mineral {
public:
	Limestone(long int am, int pr): Mineral("Limestone", am, pr) {}
	void print_mineral_info() const {
		cout << "Mineral: " << endl << "	Name: " << name << endl << "	Amount: " << amount << endl << "	Price: " << price << endl;
	} 
};

class Trolley {
	static int allow_weight;
	static int critical_weight;
	static int price;
	static int single_stage_wear;
	Mineral *mineral;
	int wear;
	int weight;
public:	
	Trolley(): wear(0), weight(0), mineral(0) {
		cout << "	Trolley is created" << endl;
	}
	static void set_price(int p) {
		price = p;
		cout << "Trolley price is set: " << price << endl;
	}
	static int get_price() {
		return price;
	}
	static void set_allow_weight(int aw) {
		allow_weight = aw;
		cout << "Trolley allowed weight is set: " << allow_weight << endl;
	}
	static int get_allow_weight() {
		return allow_weight;
	}
	static void set_critical_weight(int cw) {
		critical_weight = cw;
		cout << "Trolley critical weight is set: " << critical_weight << endl;
	}
	static int get_critical_weight() {
		return critical_weight;
	}
	static void set_ssw(int ssw) {
		single_stage_wear = ssw;
		cout << "Trolley single stage wear is set: " << single_stage_wear << endl;
	}
	static int get_ssw() {
		return single_stage_wear;
	}
	int get_mineral_price() const {
		return mineral->get_price();
	}
	int check_wear() const {
		return wear;
	}
	bool check_broken() const {
		if (wear == 100)
			return true;
		else
			return false;
	}
	void crash() {
		wear = 100;
		throw "Trolley crashed";
	}
	void fill(int wt, Mineral *m) {
		if (wt > get_critical_weight()) 
			crash();
		if (check_broken()) 
			throw "Trolley has already broken, unable to be filled";
		weight = wt;
		mineral = m;
		cout << "Trolley is filled: " << wt << ", by mineral: ";
		m->print_mineral_info(0);
		cout << endl;
	}
	int unload() {
		if (mineral == NULL)
			throw "Trolley is empty";
		int x = weight; 
		weight = 0;
		mineral = NULL;
		cout << "Trolley is unloaded" << endl;
		return x;
	}
	void move() {
		if (weight < get_allow_weight()) {
			wear += get_ssw();
			if (wear >= 100)
				crash();		
		}
		cout << "Trolley is moved" << endl;	
	}
	bool operator > (const Trolley &t) {
		if (check_wear() < t.check_wear())
			return true;
		else 
			return false;
	}
	bool operator >= (const Trolley &t) {
		if (check_wear() <= t.check_wear())
			return true;
		else 
			return false;
	}
	bool operator == (const Trolley &t) {
		if (check_wear() == t.check_wear())
			return true;
		else 
			return false;
	}
	friend bool operator < (const Trolley &t1, const Trolley &t2) {
		if (t1.check_wear() > t2.check_wear())
			return true;
		else 
			return false;
	}
	friend bool operator <= (const Trolley &t1, const Trolley &t2) {
		if (t1.check_wear() >= t2.check_wear())
			return true;
		else 
			return false;
	}
};

class Miner: public Human {
	double power_reserve;
	int productivity;
	Mineral* mineral;
	int wage;
	int working_hours;
	int full_amount;
	int extracted_amount;
protected:
	void edit_productivity(double power) {
		if (power == 100) {
			productivity *= 1.35;
			cout << "Miner's productivity increased to the value: " << productivity << endl;
		}
		else if (power == 60.0) {
			productivity *= 0.7;
			cout << "Miner's productivity reduced to the value: " << productivity << endl;
		}
	}
	void edit_power_reserve(int negativity) { 
		if (negativity > 0) {
			power_reserve = 100.0;
			cout << "Miner's power reserve increased to the value: " << power_reserve << endl;
			edit_productivity(power_reserve);
		}
		else if (negativity < 0) {
			power_reserve = 60.0;
			cout << "Miner's power reserve reduced to the value: " << power_reserve << endl;
		}
	}
public:
	Miner(const char* nm, const char *lnm, int ag, int prd, int wg = 0, int pwr = 100, Mineral *m = NULL): Human(nm, lnm, ag) {
		power_reserve = pwr;
		productivity = prd;
		mineral = m;
		wage = wg;
		working_hours = 5;
		extracted_amount = 0;
		full_amount = 0;
	}
	void set_power_reserve(double pwr) {
		power_reserve = pwr;
		cout << "Miner's power reserve is set: " << power_reserve << endl;
	}
	
	void set_productivity(int prd) {
		productivity = prd;
		cout << "Miner's productivity is set: " << productivity << endl;
	}
	int get_productivity() {
		return productivity;
	}
	void add_to_full_amount(int x) {
		full_amount += x;
	}
	int get_full_amount() {
		return full_amount;
	}
	void reset_full_amount() {
		full_amount = 0;
	}
	void set_wage(int wg) {
		wage = wg;
		cout << "Miner's wage is set: " << wage << endl;
		power_reserve = 100.0;
		productivity = 800;
	}	
	void reset_wage(int wg) {
		wage = wg;
		cout << "Miner's wage is reset: " << wage << endl;
		edit_power_reserve(wg - wage);
	}
	int get_wage() const {
		return wage;
	}
	void set_working_hours(int wrh) {
		working_hours = wrh;
		cout << "Miner's working hours are set: " << wage << endl;
	}
	int get_working_hours() const {
		return working_hours;
	}
	int get_daily_amount() const {
		return working_hours*productivity;
	}
	void set_extracted_amount(int exa) {
		extracted_amount = exa;
		cout << "Miner's extracted amount is set: " << extracted_amount << endl;
	}
	int get_extracted_amount() const {
		return extracted_amount;
	}
	void set_mineral(Mineral *m) {
		mineral = m;
		cout << "Miner " << name << " " << lastname << " will extract mineral: ";
		m->print_mineral_info(0);
		cout << endl;
	}
	void extract(int ext) {
		if (full_amount > get_daily_amount()) {
				full_amount = get_daily_amount();
		}
		else if ((mineral->get_amount() - ext) >= 0) {
			extracted_amount += ext;
			full_amount += ext;
			hum = this;
			cout << endl << "Miner "<< hum  << " extracted " << ext << " of " << mineral->get_name() << endl;
			mineral->set_amount(mineral->get_amount() - ext);
		}
		else
			throw "There is no mineral in Mine";
	}
	void fill_and_move_trolley(Trolley &tr, int wt) {
		try { 
			if (extracted_amount == 0) 
				throw "All extracted amount has moved";
			else if ((extracted_amount - wt) > 0) {
					tr.fill(wt, mineral);
					tr.move();
					extracted_amount -= wt;
			}
			else {
					tr.fill(extracted_amount, mineral);
					tr.move();
					extracted_amount = 0;		 		
			}
		}
		catch (const char *str) { 
			cout << endl << "ATTENTION: " << str << endl; 
			throw "Choose another trolley";
		}
	}
	friend void unload_trolley(Trolley &tr);
	bool operator > (const Miner &m) {
		if (get_daily_amount() > m.get_daily_amount())
			return true;
		else 
			return false;
	}
	bool operator >= (const Miner &m) {
		if (get_daily_amount() >= m.get_daily_amount())
			return true;
		else 
			return false;
	}
	bool operator == (const Miner &m) {
		if (get_daily_amount() == m.get_daily_amount())
			return true;
		else 
			return false;
	}
	friend bool operator < (const Miner &m1, const Miner &m2) {
		if (m1.get_daily_amount() < m2.get_daily_amount())
			return true;
		else 
			return false;
	}
	friend bool operator <= (const Miner &m1, const Miner &m2) {
		if (m1.get_daily_amount() <= m2.get_daily_amount())
			return true;
		else 
			return false;
	}
	friend ostream& operator << (ostream &out, const Miner &h) {
		out << "Miner:" << endl << "	Name: " << h.name << endl << "	Lastname: " << h.lastname << endl << "	Age: " << h.age << endl << "	Wage: " << h.wage << endl << "	Mineral: " << h.mineral->get_name() << endl;
		return out;
	}
};

class Mine {
	vector <Mineral *> Minerals;
	vector <Miner> Miners;
	vector <Trolley> Trolleys;
	int trolleys_num;
	long int money;
	int min_working_time;
	int req_working_time;
	int min_daily_amount;
protected:
	bool check1() {
		vector <Miner> :: iterator p = Miners.begin();
		while (p != Miners.end()) {
			if (p->get_full_amount() < p->get_daily_amount())
				return true;
			p++;
		}
		return false;			
	}
	bool check2() {
		vector <Miner> :: iterator p = Miners.begin();
		while (p != Miners.end()) {
			if (p->get_extracted_amount() > 0)
				return true;
			p++;
		}
		return false;		
	}
	bool check3() {
		vector <Trolley> :: iterator p = Trolleys.begin();
		while (p != Trolleys.end()) {
			if (!p->check_broken())
				return false;
			p++;
		}
		return true;		
	}
public:
	Mine(long int mn, int mnwt, int rqwt, int dlam) {
		money = mn;
		min_working_time = mnwt;
		req_working_time = rqwt;
		min_daily_amount = dlam;
		cout << "Mine is created" << endl;
	}
	void add_mineral(Mineral *m) {
		Minerals.push_back(m);
		cout << "New type of mineral is added to mine: " << m << endl;
	}
	void add_miner(Miner &m) {
		Miners.push_back(m);
		cout << "New miner is added to mine: " << m << endl;
	}
	int set_trolleys_num(int n) {
		trolleys_num = n;
		for(int i=0; i<n; i++) 
			Trolleys.push_back(Trolley());
		if (n == 1)
			cout << "1 trolley is added to mine" << endl;
		else if (n > 1)
			cout << n << " trolleys are added to mine" << endl;
	}
	int get_miners_num() const {
		return Miners.size();
	}
	int get_trolleys_num() const {
		return Trolleys.size();
	}
	void set_money(long int x) {
		money = x;
		cout << "Money amount is set: " << money << endl;
	}
	long int get_money() const {
		return money;
	}
	void set_mnwt(int x) {
		min_working_time = x;
		cout << "Minimal working time is set: " << min_working_time << endl;
	}
	int get_mnwt() const {
		return min_working_time;
	}
	void set_rqwt(int x) {
		req_working_time = x;
		cout << "Required working time is set: " << req_working_time << endl;
	}
	int get_rqwt() const {
		return req_working_time;
	}
	void set_dlam(int x) {
		min_daily_amount = x;
		cout << "Minimal daily amount is set: " << min_daily_amount << endl;
	}
	int get_dlam() const {
		return min_daily_amount;
	}
	void delete_broken_trolleys() {
		vector <Trolley> :: iterator p = Trolleys.begin();
		while (p != Trolleys.end()) {
			if (p->check_broken()) {
				Trolleys.erase(p);
				cout << "Broken trolley is thrown out" << endl;
			}
			else
				p++;
		}
		cout << endl;
	}
	void delete_bad_workers() {
		vector <Miner> :: iterator p = Miners.begin();
		while (p != Miners.end()) {
			if ((p->get_working_hours() < min_working_time) || (p->get_daily_amount() < min_daily_amount)) {
				cout << "Bad miner is fired from the mine: " << *p;
				Miners.erase(p);
			}
			else
				p++;
		}
		cout << endl;		
	}
	void delete_full_extracted_minerals() {
		vector <Mineral *> :: iterator p = Minerals.begin();
		while (p != Minerals.end()) {
			if ((*p)->check_empty()) {
				cout << (*p)->get_name() << " reserve is fully extracted" << endl;
				Minerals.erase(p);
			}
			else
				p++;
		}	
		cout << endl;	
	}
	void unload_trolley(Trolley &tr) {
		try {
			int pr = tr.get_mineral_price();
			int x = (pr*tr.unload());
			money += x;
			cout << "	" << x << " - money get" << endl;
			cout << "	" << money << " - all money" << endl;
		}
		catch (const char *str) { cout << endl << "ATTENTION: " << str << endl; }
	}
	void buy_new_trolley() {
		vector <Miner> :: iterator p = Miners.begin();
		long int used_money = 0;
		long int free_money;
		while (p != Miners.end()) {
			used_money += p->get_wage();
			p++;
		}	
		free_money = money - used_money;
		cout << "Start buying new trolleys: " << endl;
		for (int i=Trolleys.size(); i<trolleys_num; i++) {			
			if (free_money - Trolley::get_price() > 0) {
				money -= Trolley::get_price();
				cout << "	" << Trolley::get_price() << " money spent" << endl;
				Trolleys.push_back(Trolley());
			}
			else 
				throw "There is no enough money to buy a trolley";
		}
		cout << "All new trolleys are bought: " << money << " - money left" << endl << endl;
	}
	void pay_wages() {
		vector <Miner> :: iterator p = Miners.begin();
		cout << "Start paying wages: " << endl;
		while (p != Miners.end()) {
			if (money - p->get_wage() > 0) {
				money -= p->get_wage();
				cout << "	" << p->get_wage() << " paid out" << endl;
				p++;
			}
			else
				throw "There is no enough money to pay wages";
		}	
		cout << "All miners got their wages: " << money << " - money left" << endl << endl;
	}
	void issue_salary_bonuses() {
		vector <Miner> :: iterator p = Miners.begin();
		cout << "Start issue salary bonuses: " << endl;
		while (p != Miners.end()) {
			if (p->get_working_hours() >= req_working_time) {
				if (money - p->get_wage()*0.25 > 0) {
					money -= p->get_wage()*0.25;
					cout << "	" << p->get_wage()*0.25 << " paid out" << endl;
				}
				else 
					throw "There is no enough money to issue salary bonus";
			}
			p++;
		}
		cout << "All salary bonuses are issued: " << money << " - money left" << endl << endl;	
	}
	void work() {
		while (check1()) {
			if (check3()) {
				cout << endl << "All trollyes are broken, buying new ones, wait" << endl;
				sleep(5);
				try { 
					buy_new_trolley();
				}
				catch (const char *str) { cout << endl << "ATTENTION: " << str << endl; }
			}
			sleep(1);
			srand(time(NULL));
			int x = rand();
			int m = x%Miners.size();
			int t = x%Trolleys.size();
			try {
				Miners[m].extract(x%Miners[m].get_productivity());
			}
			catch (const char *str) { cout << endl << "ATTENTION: " << str << endl; }
			try {
				Miners[m].fill_and_move_trolley(Trolleys[t], x%Miners[m].get_extracted_amount());
				unload_trolley(Trolleys[t]);
			}
			catch (const char *str) { cout << "ATTENTION: " << str << endl; }
		}
		while(check2()) {
			if (check3()) {
				cout << endl << "All trollyes are broken, buying new ones, wait" << endl;
				sleep(5);
				delete_broken_trolleys();
				try { 
					buy_new_trolley();
				}
				catch (const char *str) { cout << endl << "ATTENTION: " << str << endl; }				
			}
			sleep(1);
			srand(time(NULL));
			int x = rand();
			int m = x%Miners.size();
			int t = x%Trolleys.size();
			try {
				cout << endl;
				if (Miners[m].get_extracted_amount() < Trolley::get_critical_weight())
					Miners[m].fill_and_move_trolley(Trolleys[t], Miners[m].get_extracted_amount());
				else if ((Miners[m].get_extracted_amount()/2) < Trolley::get_critical_weight())
					Miners[m].fill_and_move_trolley(Trolleys[t], Miners[m].get_extracted_amount()/2);		
				unload_trolley(Trolleys[t]);
			}
			catch (const char *str) { cout << "ATTENTION: " << str << endl; }			
		}
	}
	void new_day() {
		cout << endl << "-----------------------------------------------------------------New day started---------------------------------------------------------------------------" << endl;
		delete_bad_workers();
		delete_broken_trolleys();
		delete_full_extracted_minerals();
		try {
			pay_wages();
		}
		catch (const char *str) { cout << endl << "ATTENTION: " << str << endl; }
		try { 
			buy_new_trolley();
		}
		catch (const char *str) { cout << endl << "ATTENTION: " << str << endl; }
		print_trolley_info();
		cout << endl;
		try { 
			issue_salary_bonuses();
		}
		catch (const char *str) { cout << endl << "ATTENTION: " << str << endl; }
		vector <Miner> :: iterator p = Miners.begin();
		while (p != Miners.end()) {
			p->reset_full_amount();
			p++;
		}
		work();
	}
	void print_miners_info() {
		vector <Miner> :: iterator p = Miners.begin();
		cout << endl << "---------------------------------------------------------------On mine are working---------------------------------------------------------------------" << endl;
		while (p != Miners.end()) {
			cout << (*p);
			p++;
		}
	}
	void print_minerals_info() {
		vector <Mineral *> :: iterator p = Minerals.begin();
		cout << endl << "-----------------------------------------------------------------Minerals of mine------------------------------------------------------------------------" << endl;
		while (p != Minerals.end()) {
			cout << (*p);
			p++;
		}
	}
	void print_trolley_info() {
		vector <Trolley> :: iterator p = Trolleys.begin();
		int i = 1;
		cout << endl << "---------------------------------------------------------------Condition of trolleys---------------------------------------------------------------------" << endl;
		while (p != Trolleys.end()) {
			if(p->check_broken())
				cout << "Trolley " << i << ":" << endl << "	Wear: " << p->check_wear() << endl << "	Broken: yes" << endl;
			else
				cout << "Trolley " << i << ":" << endl << "	Wear: " << p->check_wear() << endl << "	Broken: no" << endl;
			i++;
			p++;
		}
	}
	void print_full_info() {
		print_minerals_info();
		print_miners_info();
		print_trolley_info();
	}
};

int Trolley::allow_weight;
int Trolley::critical_weight;
int Trolley::price;
int Trolley::single_stage_wear;
	
int main() {
	Coal cl(4500000000, 35);
	Salt slt(27000000000, 15);
	Granite grnt(6000000000, 250);
	Limestone lmstn(31000000000, 80);
	Ore ore(4700000000, 100);
	Miner mnr1("Ivanov", "Ivan", 23, 1000, 70000), mnr2("Petrov", "Petr", 27, 900, 85000), mnr3("Smirnov", "Alexey", 26, 1100, 77000), mnr4("Popov", "George", 24, 1050, 100000), mnr5("Prohorov", "Danil", 29, 900, 105000), mnr6("Vanin", "Pavel", 31, 950, 73000), mnr7("Barinov", "Oleg", 30, 880, 83000);
	Mine mine(45000000, 5, 9, 4500);
	//------------Set trolley parameters-------------//
		Trolley::set_allow_weight(500);
		Trolley::set_critical_weight(1500);
		Trolley::set_price(10000);
		Trolley::set_ssw(2);
		cout << endl;
		mine.set_trolleys_num(32);
		cout << endl;
	//------------Add minerals to mine-------------//
		mine.add_mineral(&cl);
		mine.add_mineral(&slt);
		mine.add_mineral(&grnt);
		mine.add_mineral(&lmstn);
		mine.add_mineral(&ore);	
		cout << endl;
	//------------Set minerals which miners will extract------------//
		mnr1.set_mineral(&lmstn);
		mnr2.set_mineral(&ore);
		mnr3.set_mineral(&grnt);
		mnr4.set_mineral(&slt);
		mnr5.set_mineral(&cl);
		mnr6.set_mineral(&ore);
		mnr7.set_mineral(&cl);
		cout << endl;
	//---------------Set working hours for each miner---------------//
		mnr1.set_working_hours(5);
		mnr2.set_working_hours(6);
		mnr3.set_working_hours(7);
		mnr4.set_working_hours(8);
		mnr5.set_working_hours(9);
		mnr6.set_working_hours(10);
		mnr7.set_working_hours(9);
		cout << endl;
	//---------------Add miners to mine-------------//
		mine.add_miner(mnr1);
		mine.add_miner(mnr2);
		mine.add_miner(mnr3);
		mine.add_miner(mnr4);
		mine.add_miner(mnr5);
		mine.add_miner(mnr6);
		mine.add_miner(mnr7);
	//---------------Print info---------------------//
		mine.print_full_info();
	//---------------Start working------------------//
		int i = 0;
		while(i <= 30) {
			mine.new_day();
			i++;
		}
	cout << endl << "----------------------------------------------Mine has been working for a month-----------------------------------------------" << endl;
	return 0;
}
