#include "Bets.h"

using namespace std;

class users;

class Guest;

typedef vector <Guest *> vector_of_users;


class Wallet{
	private:
		double my_balance;
		string my_freebets;
	public:
		Wallet(double balance,string freebets){
			my_balance = balance;
			my_freebets = freebets;
		}
		
		~Wallet(){
			
		}
		
		void set_balance(double new_balance);
		
		double get_balance();
		
		string get_freebets();
		
		void set_freebets(string new_freebets);
		
		virtual void my_user_function(){
		}
};


class Guest{
	private:	
	public:
		Guest(){
			
		}
		virtual ~Guest(){
			
		}

        virtual string get_name() {
		return "guest";
	}
		
		virtual string get_password() {
			
		}
		
        virtual int get_user_id() {
        	
		}
		
		virtual void print_me(){
			
		}
		
		virtual void set_status(string final_status){
			
		}
		
		virtual string get_status(){
			
		}
		
		virtual void print_commands() {
			cout<<"epilekste:"<<endl;
			cout<<"to ID tou kombou pou thelete na episkefteite"<<endl;
			cout<<"H(Home), gia epistrofi sthn arxikh othoni"<<endl;
			cout<<"T(Toggle), gia enallagi probolis timwn"<<endl;
			cout<<"X(Exit),gia eksodo apo to sustima"<<endl;
		}
		virtual void my_selection_print(){
			
		}
		
		virtual bool execute(string input,bool end,Bets &bets,vector_of_users &all_users) {
			return false;
		}
		
		virtual int get_balance() {
			
		}
		
		virtual void print_freebets() {
			
		}
		
		virtual bool bet_with_money(string bet,double &value) {
			
		}
		
		virtual bool bet_with_freebet(string bet,double &value) {
			
		}
		
		virtual void return_money(double value) {
			
		}
		
		virtual void my_user_function(vector_of_users &all_users){
			
		}
		
		virtual bool ask_for_director(){  //epistrefei true h false an einai diaxeirhsths h oxi
			return false;
		}	
		
		
		virtual void save_user(ofstream &f,int i) {
			
		}
		
		virtual string get_freebets() {
			
		}
		
		virtual void set_freebets(string new_freebets) {
			
		}
		
};

class Punter:public Guest{
	private:
		int user_id;
		Wallet my_Wallet;
		string username, fullname, password, status;
	public:
		Punter(int user_id,string username,string fullname,string password,string status,double balance,string freebets):my_Wallet(balance,freebets)
		{
			this->user_id = user_id;
			this->username = username;
			this->fullname  = fullname;
			this->password = password;
			this->status = status;
		}
		
		~Punter(){
			
		}
		
		string get_name() {
            return username;
        }
        
        string get_fullname() {
			return fullname;
		}
        
        string get_password() {
            return password;
        }
        
		int get_user_id(){
            return user_id;
        }
		
		void print_me(){
			cout << user_id << "-" << username << "-" << fullname << "-" << password << "-" 
			<< "1" << "-" << status << "-" << my_Wallet.get_balance() << "-" << my_Wallet.get_freebets() << "-" << endl;
		}
		
		void set_status(string final_status){
			status = final_status;
		}
		
		string get_status(){
			return status;
		}
		
		string get_freebets() {
			return my_Wallet.get_freebets();	
		}
		
		void set_freebets(string new_freebets) {
			my_Wallet.set_freebets(new_freebets);	
		}
		
		void print_commands();
		
		void my_selection_print();
		
		bool execute(string input,bool end,Bets &bets,vector_of_users &all_users);
		
		void Rename_function(vector_of_users &all_users);
		
		void Password_function();
		
		void Bets_function(Bets &bets,vector_of_users &all_users);
		
		void Deposit_function();
		
		int get_balance();
		
		void print_freebets();
		
		
		bool bet_with_money(string bet,double &value);
		
		
		bool bet_with_freebet(string bet,double &value);
		
		
		void return_money(double value);
		
		void my_user_function(vector_of_users &all_users){
		}
		
		bool ask_for_director(){
			return false;
		}
		
		void save_user(ofstream &f,int i);
		
};

class Trader:public Guest{
	protected:
		int user_id;
		string username, fullname, password;
	public:
		Trader(int user_id,string username,string fullname,string password)
		{
			this->user_id = user_id;
			this->username = username;
			this->fullname  = fullname;
			this->password = password;
	//		cout << "Created Trader" << endl;
		}
		~Trader(){
			
		}
		
		string get_name() {
            return username;
        }
        
        string get_password() {
            return password;
        }
        
        
		int get_user_id(){
            return user_id;
        }
        
        void my_selection_print();
        
        void print_me(){  //ektupwsh pkhroforiwn
			cout << user_id << "-" << username << "-" << fullname << "-" << password << "-" 
			<< "2" << "-" << "-" << " " << "-" << " " << "-" << endl;
		}
		
		void set_status(string final_status){
			
		}
		
		string get_status(){
			
		}
		
		void print_commands();
		
		bool execute(string input,bool end,Bets &bets,vector_of_users &all_users);
		
		void give_free_bets(vector_of_users &users);
		
		void my_user_function(vector_of_users &all_users);
		
		bool ask_for_director();
		
		virtual void save_user(ofstream &f,int i) {
			f<<i<<'|'<<	username<<'|'<<fullname<<'|'<<password<<'|'<<2<<'|'<<'|'<<'|'<<endl;
		}
};

class Director:public Trader{
	private:
		
	public:
		Director(int user_id,string username,string fullname,string password):Trader(user_id,username,fullname,password)
		{
//			cout << "Created Director" << endl;
		}
		~Director(){
			
		}
		
		void print_me();
		
		void print_commands();
		
		void my_selection_print();
		
		bool execute(string input,bool end,Bets &bets,vector_of_users &all_users);
		
		void my_user_function(vector_of_users &all_users);
		
		void View_function(vector_of_users &all_users);
		
		void Search_function(vector_of_users &all_users);
		
		void Lock_function(vector_of_users &all_users);
		
		bool ask_for_director();
		
		void save_user(ofstream &f,int i);
};







class users {
	private:
		vector_of_users all_users;
		Bets bets;
	public:
		users() {
			ifstream file_users("users.csv", ios::in);
			string a;
			int user_id, type;
			double balance;
			string username, fullname, password, status, freebets;
			Guest *item;
			while ( !file_users.eof() ){
				if ( !getline(file_users,a) ) {
					break;
				}

				char *tok=&a[0];  //diabasma apo to arxeio xrhstwn gia apothhkeush sth mnhmh
				user_id= atoi(tok=strtok(tok,"|"));
				username = (tok=strtok(NULL,"|"));
				fullname = (tok=strtok(NULL,"|"));
				password = (tok=strtok(NULL,"|"));
				type = atoi(tok=strtok(NULL,"|"));
				tok=strtok(NULL,"|");
				if(tok!=NULL) status = tok;
				tok=strtok(NULL,"|");
				if(tok!=NULL) balance = atof(tok);
				tok=strtok(NULL,"| \n");
				if(tok!=NULL) freebets = (tok);
				if ( type==1 ){
					item = new Punter(user_id,username,fullname,password,status,balance,freebets);
				}
				else if ( type==2 ){
					item = new Trader(user_id,username,fullname,password);
				}
				else{
					item = new Director(user_id,username,fullname,password);
				}
				all_users.push_back(item);
			}
		}
		
		~users(){
			for(int i=0;i<all_users.size();i++) {
				delete all_users[i];
			}
		}

        bool name_available(string new_name) { //an to to new_name uoarxei hdh epistrefetai false
            int i;
            for(i=0;i<all_users.size();i++) {
                if(new_name==all_users[i]->get_name()) {
                    return false;
                }
            }
            return true;
        }
        
        
        int check(string username);
		
		int check(string password,int tmp);
		
		int make_user(string username,string fullname,string password,int type);
		
		
		int make_guest();

		void commands(int id) {
			all_users[id]->print_commands();
		}
		
		string get_name(int id) {
			return all_users[id]->get_name();
		}
		
		void selection_print(int id){
			all_users[id]->my_selection_print();
		}
		
		
		bool execute(int id,string input,bool end) {
			return all_users[id]->execute(input,end,bets,all_users);
		}
		
		int get_balance(int id) {
			return all_users[id]->get_balance();
		}
		
		void print_freebets(int id) {
			all_users[id]->print_freebets();
		}
		
		bool bet_with_money(string bet,int id,double &value) {
			return all_users[id]->bet_with_money(bet,value);
		}
		
		bool bet_with_freebet(string bet,int id,double &value) {
			return all_users[id]->bet_with_freebet(bet,value);
		}
		
		void add_bet(int id,string node_id,double value) {
			bets.add_bet(id,node_id,value);
		}
		
		
		void return_money(string epilogi);
		
		void the_users_function(int id);
		
		bool am_i_director(int id);
		
		
		void settle(string node,string epilogi,double P,double &profit,double supply);
		
		void save_bets();
		
		void save_users();
		
};


