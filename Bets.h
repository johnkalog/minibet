#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <cstdlib>


using namespace std;




class bet {
	/* h klash bet periexei thn plhroforia
	   enos mono stoiximatos*/
	int bet_id;
	int user_id;
	string node_id;//h epilogi tou paxth
	double stake;
	char result;// to apotelesma ( '-' ean den exei oristei)

	public:
		bet(int bet,int user,string node,double sta,char res): bet_id(bet), user_id(user), stake(sta), node_id(node),result(res)   {
			
		}
		void print_bet();

		int get_user_id();

		int get_bet_id();

		string get_node_id();

		double get_user_stake();

		char get_result();

		void set_result(char ch);
};


typedef vector <bet *> vector_of_bet;


class Bets { // klash Bet periexei enan vector apo bet
	vector_of_bet B;

	public:
		Bets() {
			/* diabazei apo to arxeio bets.cvs kai arxikopoiei to bets */
			ifstream fbets("bets.csv");//anoigei arxeio mono gia diabasma
  			bet* be;
			while (true) {
				string line;
				getline(fbets, line);// diabazei mia grammh apo ton fakelo
				if ( fbets.eof() ) break;

				int bet_id,user_id;
				string node_id;
				double stake;
				char result;
				char *tok=&line[0];
				bet_id=atoi(tok=strtok(tok,"|"));
				user_id=atoi(tok=strtok(NULL,"|"));
				node_id=(tok=strtok(NULL,"|"));
				stake=atof(tok=strtok(NULL,"|"));
				tok=strtok(NULL,"|\n");
				result=tok[0];

				be= new bet(bet_id,user_id,node_id,stake,result);
				B.push_back(be);

			}
		}

		void print_bets(int num);

		void player_bets(int user_id);

		int get_last_id();

		void add_bet(int id,string node_id,double value);

		bool delete_epilogi(string epilogi,int &user_id,double &value);

		bool settle_epilogi(string node,string epilogi,int &user_id,double &value,bool &Win);

		void save_bets();

};
