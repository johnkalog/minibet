#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Users.h"
#include <ctype.h>

using namespace std;

class Node;
typedef vector <Node *> vector_of_node;


static streampos oldpos;

string do_string(int i);

class Price {
	int a;
	int b;
	double my_price;
	bool T;
	public:
		void set_a(int x) {
			a=x;
		}
		
		void set_b(int x) {
			b=x;
		}
		int get_a(){
			return a;
		}
		int get_b(){
			return b;
		}
		double get_my_price(){
			my_price = (double)a/(double)b; //se auth thn synarthsh pairnei timh h metanblhth my_price kai epistrefetai
			return my_price;
		}
};

class Node {  //auth h klash einai uperklash autwn pou akolouthoun gia na xrhsimopoihthoun sunarthseis virtual
	public:
		Node(){			
		}
				
		virtual ~Node() {
			
		}
		
		virtual string get_name() {
			
		}
		
		virtual void set_name(string new_name){
			
		}
		
		virtual char ploigisi(string location,bool &T,string name,users &play,int id,double &profit,double suply) {
			
		}
		
		virtual int get_the_a(){
			
		}
											
        virtual int get_the_b(){
        	
		}
			
		virtual double get_Price(){
			
		}
		virtual bool get_hidden(){
			
		}
		virtual void change_hidden(){
			
		}
		
		virtual void save_hierarchy(ofstream &f,string node_id) {
			
		}
};




class Selection:public Node {
        string name;
        Price P;
        bool hidden;  //hidden=true an o kombos einai [Hidden],false alliws
        public:
            Selection(string s) {
                char *tok=&s[0];
                tok=strtok(tok," ");
                hidden = false;
                if(!strcmp(tok,"[Hidden]")) { //an uparxei h endeiksh [Hidden] prin ton kombo allazei h metablhth hidden
                	hidden=true;
                	tok=strtok(tok," ");
				}
				tok=strtok(NULL,"#");   //diabasma kai anathesh timvwn stis metablhtes
				name=tok;
				int a=atoi(tok=strtok(NULL,"/"));
				int b=atoi(tok=strtok(NULL," "));
                P.set_a(a);
                P.set_b(b);
            }
            
            Selection(string my_name,int a,int b){  //deuteros constructor
				name = my_name;
				P.set_a(a);
                P.set_b(b);
			}
                
            ~Selection() {
            	
			}
			
			Selection(Selection& s,bool flag=false){
				name = s.name + "-Copied";
				if ( flag==true ){
					hidden = true;  //flag==true otan ginetai antigrafh tou kombou kat'epilogh,dhladh exoume epileksei oti autos o komnos tha
				}                   //antigrafei se auto to epipedo.Antitheta flag==flase otan gineti antigrafh logw prohgoumenhs antigrafhs
				else{               //tou "anwterou" kombou
					hidden = s.hidden;
				}
				P.set_a(s.get_the_a());
				P.set_b(s.get_the_b());
			}
			
			string get_name() {
				return name;
			}
			
			void set_name(string new_name){
				name = new_name;
			}
		
			int get_the_a(){
				return P.get_a();
			}
											
        	int get_the_b(){
				return P.get_b();
			}
			
			double get_Price(){
				return P.get_my_price();
			}
			bool get_hidden(){
				return hidden;
			}
			void change_hidden(){
				hidden = !hidden;
			}
			void save_hierarchy(ofstream &f,string node_id) {  //sunarthsh apouhkeushs twn dedomenwn tou antistoixou kombou sto arxeio
				if(hidden) {
						f<<"[Hidden]"<<" "<<node_id<<" "<<name<<"#"<<P.get_a()<<"/"<<P.get_b()<<endl;
				}
				else {
					f<<node_id<<" "<<name<<"#"<<P.get_a()<<"/"<<P.get_b()<<endl;
				}
			}
};

class Market:public Node {
        vector_of_node select;
        string name;
        string node_id; // to id enos node to xreiazomaste sthn place gia ta stoixhmata
        bool hidden;
        public:
        	Market(ifstream& file,string s) {
                char *tok = &s[0];
                tok=strtok(tok," ");
               
                if(!strcmp(tok,"[Hidden]")) {
 	              	hidden=true;
                	node_id=strtok(tok," ");
				}
				else { //ean den einai hidden to tok einai to node_id
					hidden = false;
					node_id=tok;
				}
                tok=strtok(NULL,"\n");
                name = tok;
                string a;
//				cout << "Market  "<< name << endl;
				do{
            	  	if ( !file.eof() ) {
       	    	      	oldpos = file.tellg();
        		        if ( !getline(file,a) ){
        		            break;
						}
            	    }
					else {
            	       	break;
					}
            	    if ( s[6] == a[6] ) {
            	       	Selection *c = new Selection(a);
            	       	select.push_back(c);
            	    }else file.seekg (oldpos);
	            }while ( s[6] == a[6] ); //oso einai isa den exoun teleiwsei ta selection 
			}
			
			Market(string my_name,int a){  //deuteros constructor,h metablhth int a apla uparxei gia na ginei diaxwrismos apo ton prohgoumeno
				name = my_name;            //constructor,den xrhsimeyei kapou allou
			}
		
			~Market() {
				for(int i=0;i<select.size();i++) {
					delete select[i];
				}
			}
			
			Market(Market& s,bool flag=false){  //me thn antigrafh by copy construction enos kombou antigrafontai kai oi "upokomboi" an uparxoun
				name = s.name + "-Copied";
				if ( flag==true ){
					hidden = true;
				}
				else{
					hidden = s.hidden;
				}
				for(int i=0;i<s.select.size();i++) {
					Selection *c = new Selection(*(Selection *)s.select[i]);
					select.push_back(c);
				}
			}
			
			string get_name() {
				return name;
			}
			
			void set_name(string new_name){
				name = new_name;
			}
		
			char ploigisi(string location,bool &T,string previous_name,users &play,int id,double &profit,double supply);
			
			
			void place(users &play,int id);
				
			void Voiding(users &play,int id);
			
			
			void Settle(users &play,double &profit,double supply);
			
			bool get_hidden(){
				return hidden;
			}
			
			void change_hidden(){
				hidden = !hidden;
			}
			
			void Log_function(){
				
			}
			void Users_function(int id,users &play){
				play.the_users_function(id);
			}
			
			void Visibility_function();
			
            void Rename_function();

			void New_function();
			
			void Copy_function();
			
			void Delete_function();
			
			void save_hierarchy(ofstream &f,string node_id);
};

class Event:public Node {
    vector_of_node mark;
	string name;
	bool hidden;
    public:
        Event(ifstream& file,string s) {
        	char *tok = &s[0];
        	tok=strtok(tok," ");
            hidden = false;
            if(!strcmp(tok,"[Hidden]")) {
            	hidden=true;
            	tok=strtok(tok," ");
			}
            tok=strtok(NULL,"\n");
            name = tok;
    		string a;
//			cout << "Event  "<< name << endl;
			do{
				if ( !file.eof() ) {
		            oldpos = file.tellg();
		            if ( !getline(file,a) ){
    	    	        break;
					}
    	        }
			    else
	    	      	break;
            	if ( s[4] == a[4] ) {
					Market *c = new Market(file,a);
					mark.push_back(c);
        		}else file.seekg (oldpos);
       		}while ( s[4] == a[4] );
        }
        	
        Event(string my_name,int a){
			name = my_name;
		}
        
        ~Event() {
        	for(int i=0;i<mark.size();i++) {
        		delete mark[i];
			}
		}
		
		Event(Event& s,bool flag=false){
			name = s.name + "-Copied";
			if ( flag==true ){
				hidden = true;
			}
			else{
				hidden = s.hidden;
			}
			for(int i=0;i<s.mark.size();i++) {
				Market *c = new Market(*(Market *)s.mark[i]);
				mark.push_back(c);
			}
		}
			
		string get_name() {
			return name;
		}
		
		void set_name(string new_name){
			name = new_name;
		}
		
		char ploigisi(string location,bool &T,string previous_name,users &play,int id,double &profit,double suply);
		
		bool get_hidden(){
				return hidden;
		}
		void change_hidden(){
			hidden = !hidden;
		}
		
		void Log_function(){
			
		}
		void Users_function(int id,users &play){
			play.the_users_function(id);
		}
		
		void Visibility_function();
		
        void Rename_function();
        
		void New_function();
		
		void Copy_function();
		
		void Delete_function();
		
		void save_hierarchy(ofstream &f,string node_id);
};


class SubCategory:public Node {
        vector_of_node event;
        string name;
        bool hidden;
        public:
            SubCategory(ifstream& file,string s) {
                char *tok = &s[0];
                tok=strtok(tok," ");
                hidden = false;
                if(!strcmp(tok,"[Hidden]")) {
                	hidden=true;
                	tok=strtok(tok," ");
				}
                tok=strtok(NULL,"\n");
                name = tok;
                string a;
//				cout << "SubCategory  "<< name << endl;
				do{
	        	    if ( !file.eof() ) {
            	        oldpos = file.tellg();  //apothhkeuetai h thesi ths upokathgorias gia na thn exoume afou diabastoun kai ta events
						if ( !getline(file,a) ){
        	            	break;
						}
					}else
            	        break;
            	    if ( s[2] == a[2] ) {	
						Event *c = new Event(file,a);
						event.push_back(c);
					}else file.seekg (oldpos);  //metatopish sthn thesi oldpos

                }while ( s[2] == a[2] );  //oso autoi oi xarakthres einai idioi shmainei oti uparxei kai allos "eswterikos" komnos
				hidden = false;           //s[2] kai a[2] giati prepei na agnohsoume thn teleia
            }
            
            SubCategory(string my_name,int a){
				name = my_name;
			}
            
            ~SubCategory() {
            	for(int i=0;i<event.size();i++) {
            		delete event[i];
				}
			}
             
			SubCategory(SubCategory& s,bool flag=false){
				name = s.name + "-Copied";
				if ( flag==true ){
					hidden = true;
				}
				else{
					hidden = s.hidden;
				}
				for(int i=0;i<s.event.size();i++) {
					Event *c = new Event(*(Event *)s.event[i]);
					event.push_back(c);
				}
			}
			 
			string get_name() {
				return name;
			}  
			
			void set_name(string new_name){
				name = new_name;
			}

		char ploigisi(string location,bool &T,string previous_name,users &play,int id,double &profit,double suply);
		
		void Log_function(){
			
		}
		
		bool get_hidden(){
			return hidden;
		}
		void change_hidden(){
			hidden = !hidden;
		}
			
		void Users_function(int id,users &play){
			play.the_users_function(id);
		}
		
		void Visibility_function();
		void Rename_function();
        
		void New_function();
			
		void Copy_function();
			
		void Delete_function();
			
		void save_hierarchy(ofstream &f,string node_id);
};

class Category:public Node {
	vector_of_node sub_c;
	string name;
	bool hidden;
	public:
		Category(ifstream& file,string b) {
			string a;
			char *tok = &b[0];
            tok=strtok(tok," ");
            hidden = false;
            if(!strcmp(tok,"[Hidden]")) {
				hidden=true;
        	   	tok=strtok(NULL," ");
			}
            tok=strtok(NULL," \n");
            name = tok;
//			cout << "Category"<< name << endl;
			do{
	        	if ( !file.eof() ) {
					oldpos = file.tellg();
                    if ( !getline(file,a) ){
        	            	break;
						}
                	} else
                	    break;
    	        if ( b[0] == a[0] ) {
					SubCategory *c = new SubCategory(file,a);
					sub_c.push_back(c);
                }else {
        	        file.seekg (oldpos);
				}

            }while ( b[0] == a[0] );
		}
		
		Category(string my_name,int a){
			name = my_name;
		}
		
		~Category() {
			for(int i=0;i<sub_c.size();i++) {
				delete sub_c[i];
			}
		}
		
		Category(Category& s){
			name = s.name + "-Copied";
			hidden = true;
			for(int i=0;i<s.sub_c.size();i++) {
				SubCategory *c = new SubCategory(*(SubCategory *)s.sub_c[i]);
				sub_c.push_back(c);
			}
		}
		
		string get_name() {
			return name;
		}
		
		void set_name(string new_name){
			name = new_name;
		}
		
		char ploigisi(string location,bool &T,string previous_name,users &play,int id,double &profit,double suply);
		
		bool get_hidden(){
			return hidden;
		}
		void change_hidden(){
			hidden = !hidden;
		}
		
		void Log_function(){
			
		}
		void Users_function(int id,users &play){
			play.the_users_function(id);
		}
		
		void Visibility_function();
		
		void Rename_function();
		
		void New_function();
			
		void Copy_function();
			
		void Delete_function();
			
		void save_hierarchy(ofstream &f,string node_id);
};

