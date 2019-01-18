#include "Hierarchy.h"





class hierarchy {
	vector_of_node categories;
	public:	
		hierarchy() {
			ifstream file("hierarchy.dat", ios::in);
			string b;
			do{
				if ( !file.eof() ){
              		if ( !getline(file,b) ){
        	            	break;
						}
              	}
				Category *c = new Category(file,b);
				categories.push_back(c);
			}while ( !file.eof() );
		}
		
		~hierarchy() {
			for(int i=0;i<categories.size();i++) {
				delete categories[i];
			}
		}
		
		void ploigisi(users &play,int id,double &profit,double suply);

		void Log_function(){}
		
		void Users_function(int id,users &play){
			play.the_users_function(id);
		}
			
		void Visibility_function();

		void Rename_function();
		
		void New_function();
			
		void Copy_function();
			
		void Delete_function();
	
		void save_hierarchy();
};


class System {
	string Name_of_System;
	double profit;  //kerdos systhmatos
	double supply;  //pososto promithias systhmatos
	users players;
	hierarchy H;
	public:
		System(int profit=1000,double supply=0.05) {
			Name_of_System = "Bet-On";
		}
		
		~System() {
			
		}

	    int egrafi();

	    int login();
			 
	    void ploigisi(int id);
		
		
};
