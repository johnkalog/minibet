#include "Bets.h"


	//sunarthseis ths kalshs bet//

void bet::print_bet() { //ektupwnei ena stoixima
	cout<<bet_id<<"\t"<<user_id<<"\t"<<node_id<<"\t"<<stake<<"\t"<<result<<endl;
}


int bet::get_user_id() {
	return user_id;
}


int bet::get_bet_id() {
	return bet_id;
}


string bet::get_node_id() {
	return node_id;
}


double bet::get_user_stake() {
	return stake;
}


char bet::get_result() {
	return result;
}

void bet::set_result(char ch) {
	result=ch;
}




	//sunarthseis ths kalshs Bets//

void Bets::print_bets(int num) {
	/* ektupwnei ta teleutaia -num- bets*/
	int last=B.size()-1;
	for(int i=last;i>last-num && i>=0;i--) {
	//prepei na arxisei apo to telos pros thn arxh
		B[i]->print_bet();// kaleite sunartish ths klashs bet
	}
}



void Bets::player_bets(int user_id) {
	/*ektupwnei ta bet enos sugkekrimenou player
	prepei na dwthei to user id tou */
	int i;
	for(i=0;i<B.size();i++) {
		if(B[i]->get_user_id()==user_id) {
			B[i]->print_bet();
		}
	}
}


int Bets::get_last_id() {
	int thesi=B.size()-1;
	return B[thesi]->get_bet_id();
}


void Bets::add_bet(int id,string node_id,double value) {
	/*dhmiourgei kainourgio bet kai to prostetei sto
	telos tou vector kai sto telos tou arxiou*/
	bet *be;
	int bet_id=get_last_id()+1;
	be= new bet(bet_id,id,node_id,value,'-'); //ftiaxnei to kainourgio bet profanws den exei timh('-')
	B.push_back(be);//to topothetei teleutaio ston vector
	ofstream f("bets.csv",ios::app); //fakelos gia grapsimo
	f<<bet_id<<"|"<<id<<"|"<<node_id<<"|"<<value<<"|"<<"-"<<endl; //grafei ston fakelo to kainourgio stoixima
}


bool Bets::delete_epilogi(string epilogi,int &user_id,double &value) {
	/* kanei ena bet thn fora Void 'V' kai enhmerwnei ta user_id kai to value
  epistrefei true ean brethike stoixima pou den exei dieuthetithei alliws false*/
	for(int i=0;i<B.size();i++) {
		if(B[i]->get_node_id()==epilogi && B[i]->get_result()=='-') {//ean den exei dwthei akoma timh
			user_id=B[i]->get_user_id();
			value=B[i]->get_user_stake();
			B[i]->set_result('V');
			return true;
		}
	}
	return false;
}



bool Bets::settle_epilogi(string node,string epilogi,int &user_id,double &value,bool &Win) {
    /* kanei ena bet thn fora settle (W,L,-) kai enhmerwnei ta user_id kai to value
    epistrefei true ean brethike stoixima pou den exei dieuthetithei alliws false*/
	for(int i=0;i<B.size();i++) {
		string bet_node=B[i]->get_node_id();
		if(!(bet_node.compare(0,bet_node.length()-2,node))  && B[i]->get_result()=='-') {
			if(bet_node[bet_node.length()-1]==epilogi[0]) {
				B[i]->set_result('W');
				Win=true;
				user_id=B[i]->get_user_id();
				value=B[i]->get_user_stake();
			}
			else {
				B[i]->set_result('L');
				Win=false;
			}
			return true;
		}
	}
	return false;
}



void Bets::save_bets() {
	//grafei ston fakelo ola ta bets
	ofstream f("bets.csv",ios::out);
	for(int i=0;i<B.size();i++) {
		f<< i <<'|'<< B[i]->get_user_id() << '|' << B[i]->get_node_id() << '|' << B[i]->get_user_stake() << '|' << B[i]->get_result()<<endl;
	}
}
