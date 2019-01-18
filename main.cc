#include <iostream>
#include <iomanip>
#include "System.h"
using namespace std;


int main(int argc,char* argv[]) {
	cout << fixed << setprecision(5) ;
	System s;   //dhmiourgia systhmatos
	int id;
	if ( argc==1 ){
		id=s.login();  //h synarthsh s.login() epistrefei to user_id tou xrhsth pou ekane eisodo
		s.ploigisi(id);
	}
	else if ( argc==2 ){
		if ( !strcmp(argv[1],"-R") ){
			cout<<"Egrafi xristh"<<endl;
			id=s.egrafi();  //automath eisodos me thn eggrafh
			s.ploigisi(id);
		}
		else{
			cout << "lathos parametros gia eggrafi.Tha ginei mono eisodos sto systhma" << endl;
		}
	}
	else{
		cout << "polles parametroi.Tha ginei mono eisodos sto systhma" << endl;
	}
	return 0;
}
