#include "Hierarchy.h"



string do_string(int i) {  //metatroph enos int se string
	string s;
	while(i!=0) {
		char digit='0'+i%10;
		i=i/10;
		s=digit+s;
	}
	return s;
}



	//sunarthseis ths kalshs Market//
	
	
	
char Market::ploigisi(string location,bool &T,string previous_name,users &play,int id,double &profit,double supply) {
	bool flag=false, end=true;  //end==true an briskomaste sto epipedo twn agorwn
	location+="/"+name;
	do {
		cout <<"Location:"<< location << endl;
		cout << "Typos apodwsewn:";
		if (T){
			cout << "klasmatiko" << endl;
		}
		else{
			cout << "dekadiko" << endl;
		}
		for(int i=0;i<select.size();i++) {
			if ( play.am_i_director(id-1) ){
				if ( select[i]->get_hidden()==false ){  //katallhlh emfanish analoga me to hidden
					cout<< "	";
				}
				else{
					cout << "[Hidden]";
				}
				cout << i+1<<". "<<select[i]->get_name();
				if (T){
					cout << " " << select[i]->get_the_a() << "/" << select[i]->get_the_b() << endl;
				}
				else{
					cout << " " << select[i]->get_Price() << endl;
				}
			}
			else{
				if ( select[i]->get_hidden()==false ){
					cout << i+1<<". "<<select[i]->get_name();
					if (T){
						cout << " " << select[i]->get_the_a() << "/" << select[i]->get_the_b() << endl;
					}
					else{
						cout << " " << select[i]->get_Price() << endl;
					}
				}
			}
		}
		cout << name << "/" << previous_name << endl;
		play.commands(id-1);  //emfanizei to sunolo twn epilogwn gia ton kathe xrhsth
		play.selection_print(id-1);  //emfanizei tis diathesimes epiloges kathe xthsth sto epipedo twn agorwn
		string input;
		cin>>input;
		if(input=="H" || input=="Home") {
			return 'H';
		}
		else if(input=="T" || input=="Toggle") {
			T=!T;
			flag=true;
		}
		else if(input=="X" || input=="Exit") {
			return 'X';
		}
		else if(play.execute(id-1,input,end)) { // ean einai true shmainei uparxei h epilogi ston sugkekrino user 
			if ( input=="P" || input=="Place"){
				place(play,id-1);
			}
			else if(input=="Vo" || input=="Void") {
				Voiding(play,id-1);
			}
			else if(input=="Se" || input=="Settle") {
				Settle(play,profit,supply);
			}
			else if ( input=="L" || input=="Log" ){
				Log_function();
			}
			else if( input=="U" || input=="Users" ){
				Users_function(id-1,play);
			}
			else if( input=="Vi" || input=="Visibility" ){
				Visibility_function();
			}
			else if( input=="R" || input=="Rename" ){
					Rename_function();
			}
			else if( input=="N" || input=="New" ){
				New_function();
			}
			else if( input=="C" || input=="Copy" ){
				Copy_function();
			}
			else if( input=="D" || input=="Delete" ){
				Delete_function();
			}
			else if( input=="Sa" || input=="Save" ) {
				play.save_bets();
				play.save_users();
				return 'S';
			}
			flag=true;
		}
		else {
			cout<<"Wrong command"<<endl;
			flag=true;
		}
	}while(flag);
}


void Market::place(users &play,int id) {
	//einai mono gia Punter kai kaleitai gia na topothetisei bet
	cout<<"to apothema sou einai: "<<play.get_balance(id)<<endl;
	cout<<"grapse \"cancel\" alliws dialekse thn epilogh sou: ";
	string epilogi;
	cin>>epilogi;
	if(epilogi=="cancel") {
		return;
	}
	if(atoi(epilogi.c_str()) && atoi(epilogi.c_str())<=select.size() && select[atoi(epilogi.c_str())-1]->get_hidden()==false ) {
		play.print_freebets(id);
		cout<<"Bale to poso stoiximatos: ";
		double value=0;
		bool flag;
		do{
			string bet;
			cin>>bet;
			if(isdigit(bet[0])) { //ean einai gramma o xrhsths dialekse na  balei kouponi
				flag=play.bet_with_money(bet,id,value); //kalei thn sunarthsh bet_with_money ths user
				if(value==0) {
					cout<<"gemise to portofoli sou"<<endl;
				}
			}
			else {
				flag=play.bet_with_freebet(bet,id,value);
			}
		}while(!flag);
		if(flag) {
			epilogi=node_id+"."+epilogi;
			play.add_bet(id+1,epilogi,value);
		}
	}		
}


	
void Market::Voiding(users &play,int id) {
	// dialagei pia epilogi tha ginei void
	cout<<"grapse \"cancel\" alliws dialekse thn epilogh sou: ";
	string epilogi;
	cin>>epilogi;
	if(epilogi=="cancel") {
		return;
	}
	if(atoi(epilogi.c_str()) && atoi(epilogi.c_str())<=select.size()) { 
		string epi=node_id+"."+epilogi;
		play.return_money(epi);//epistrefei to poso ston paixth
	}
	int thesi=atoi(epilogi.c_str());
}



void Market::Settle(users &play,double &profit,double supply) {
	//dialegei thn nikhthria epilogi
	cout<<"grapse \"cancel\" alliws dialekse thn epilogh na ginei settle: ";
	string epilogi;
	cin>>epilogi;
	if(epilogi=="cancel") {
		return;
	}
	if(atoi(epilogi.c_str()) && atoi(epilogi.c_str())<=select.size()) {
		play.settle(node_id,epilogi,select[atoi(epilogi.c_str())-1]->get_Price(),profit,supply);
	}
}



void Market::Visibility_function(){
	//allazei to hidden
	string input;
	for(int i=0;i<select.size();i++) {
		if ( select[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<<select[i]->get_name()<<endl;
	}
	cout << "Dwse to ID gia allagh oratothtas" << endl;
	cin >> input;
	if ( atoi(input.c_str()) && atoi(input.c_str())<=select.size() ){
		select[atoi(input.c_str())-1]->change_hidden();
	}
	else{
		cout << "Lathos eisagwhg ID" << endl;
	}
}


void Market::Rename_function(){
   	//allazei to onoma ston kombo
    string input, new_name, cancel="cancel", abort="abort";
    for(int i=0;i<select.size();i++) {
        if ( select[i]->get_hidden()==false ){
			cout<< "        ";
       	}
       	else{	
            cout << "[Hidden]";
        }
        cout<<i+1<<". "<< select[i]->get_name()<<endl;
    }
    do{     //elegxos mexri na dwthei kapoio onoma h na akurwthei h leitourgia
        cout << "Dwse to antisoixo ID gia allagh onomatos" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;  //h sunarthsh strcasecmp epistrefei 0 an ta 2 (const char *) einai idia case insensitive
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=select.size() ){
            cout << "Dwse to neo onoma" << endl;
            cin >> new_name;
            select[atoi(input.c_str())-1]->set_name(new_name);
            break;
       	}	
        else{
	        cout << "Lathos eisagwhg ID" << endl;
        }
    }while (1);
}


void Market::New_function(){
	string new_name, cancel="cancel", abort="abort";
	int a, b;
	for(int i=0;i<select.size();i++) {
		if ( select[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
			cout<<i+1<<". "<< select[i]->get_name()<<endl;
		}
		cout << "Dwse to onoma ths kainourgias kathgorias" << endl;
		cout << "Cancel/Abort,gia akurwsh" << endl;
		cin >> new_name;
        if ( !strcasecmp(cancel.c_str(),new_name.c_str()) || !strcasecmp(abort.c_str(),new_name.c_str()) || new_name=="c" || new_name=="C" || new_name=="a" || new_name=="A"){
            return;
        }
		else{
		cout << "Dwse arithmith klasmatos apodoshs" << endl;
	    cin >> a;
        cout << "Dwse paronomasth" << endl;
        cin >> b;
        Selection *c = new Selection(new_name,a,b);
       	select.push_back(c);
	}
}


void Market::Copy_function(){
	string input, cancel="cancel", abort="abort";
	for(int i=0;i<select.size();i++) {
		if ( select[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< select[i]->get_name()<<endl;
	}
	do{
      	cout << "Dwse to antisoixo ID gia antigrafh" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=select.size() ){
			Selection *c = new Selection(*(Selection *)select[atoi(input.c_str())-1],true);
			select.push_back(c);
			break;
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}

			
void Market::Delete_function(){
	string input, yesorno, cancel="cancel", abort="abort";
	for(int i=0;i<select.size();i++) {
		if ( select[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< select[i]->get_name()<<endl;
	}
	do{
        cout << "Dwse to antisoixo ID gia diagrafh" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
		cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=select.size() ){
	        cout << "Are you sure to continue?An nai grapse Y alliws N" << endl;
			cin >> yesorno;
           	if ( yesorno=="Y"){
				delete select[atoi(input.c_str())-1];
				select.erase(select.begin()+atoi(input.c_str())-1);
				break;
			}
			else if ( yesorno=="N" ){  //epalhtheush me Y or N
				cout << "Akyrwthhke h diagrafh" << endl;
				break;
			}
			else{
				cout << "Lathos eisagwgh" << endl;
			}
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}


void Market::save_hierarchy(ofstream &f,string node_id) {
	if(hidden) {
		f<<"[Hidden]"<<" "<<node_id<<" "<<name<<endl;
	}
	else {
		f<<node_id<<" "<<name<<endl;
	}
	for(int i=0;i<select.size();i++) {
		string node=do_string(i+1);
		node=node_id+"."+node;
		select[i]->save_hierarchy(f,node);
	}
}



	//sunarthseis ths kalshs Event//
	
	

char Event::ploigisi(string location,bool &T,string previous_name,users &play,int id,double &profit,double suply) {
	location+="/"+name;
	bool flag=false, end=false;
	do {
		cout<<"Location:"<<location<<endl;
		cout << "Typos apodwsewn:";
		if (T){
			cout << "klasmatiko" << endl;
		}
		else{
			cout << "dekadiko" << endl;
		}
		for(int i=0;i<mark.size();i++) {
			if ( play.am_i_director(id-1) ){
				if ( mark[i]->get_hidden()==false ){
					cout<< "	";
				}
				else{
					cout << "[Hidden]";
				}
				cout << i+1<<". "<<mark[i]->get_name()<<endl;
			}
			else{
				if ( mark[i]->get_hidden()==false ){
					cout << i+1<<". "<<mark[i]->get_name()<<endl;
				}
			}
		}
		cout << name << "/" << previous_name << endl;
		play.commands(id-1);
		string input;
		cin>>input;
		if(input=="H" || input=="Home") {
			return 'H';
		}
			else if(input=="T" || input=="Toggle") {
			T=!T;
			flag=true;
		}
		else if(input=="X" || input=="Exit") {
			return 'X';
		}
		else if(play.execute(id-1,input,end)) {
			if ( input=="L" || input=="Log" ){
					Log_function();
			}
			else if( input=="U" || input=="Users" ){
				Users_function(id-1,play);
			}
			else if( input=="Vi" || input=="Visibility" ){
				Visibility_function();
				}
			else if( input=="R" || input=="Rename" ){
				Rename_function();
			}
			else if( input=="N" || input=="New" ){
				New_function();
				}
			else if( input=="C" || input=="Copy" ){
				Copy_function();
				}
			else if( input=="D" || input=="Delete" ){
				Delete_function();
			}
				else if( input=="Sa" || input=="Save" ) {
				play.save_bets();
				play.save_users();
				return 'S';
			}
			flag=true;
		}
		else if( atoi(input.c_str()) && atoi(input.c_str())<=mark.size()) {  //elegxos an h eisodos einai arithmos kai enas apo
	          int thesi=atoi(input.c_str());                                   //tous epomenous kombous
			thesi-=1;  ///thesi einai h thesi tou epilegmenou kombou ston vector ths klashs pou briskomaste
			char ch;
			ch=mark[thesi]->ploigisi(location,T,"Home",play,id,profit,suply);				
			return ch;
		}
		else {
			cout<<"Wrong command"<<endl;
			flag=true;
		}
	}while(flag);
}



void Event::Visibility_function(){
	string input;
	for(int i=0;i<mark.size();i++) {
		if ( mark[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<<mark[i]->get_name()<<endl;
	}
	cout << "Dwse to ID gia allagh oratothtas" << endl;
	cin >> input;
	if ( atoi(input.c_str()) && atoi(input.c_str())<=mark.size() ){
		mark[atoi(input.c_str())-1]->change_hidden();
	}
	else{
		cout << "Lathos eisagwhg ID" << endl;
	}
}


void Event::Rename_function(){
    string input, new_name, cancel="cancel", abort="abort";
    for(int i=0;i<mark.size();i++) {
        if ( mark[i]->get_hidden()==false ){
            cout<< "        ";
        }
        else{
            cout << "[Hidden]";
        }
	    cout<<i+1<<". "<< mark[i]->get_name()<<endl;
    }
    do{
       	cout << "Dwse to antisoixo ID gia allagh onomatos" << endl;
      	cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=mark.size() ){
            cout << "Dwse to neo onoma" << endl;
            cin >> new_name;
	        mark[atoi(input.c_str())-1]->set_name(new_name);
            break;
        }
        else{
            cout << "Lathos eisagwhg ID" << endl;
        }
    }while (1);
}

      
void Event::New_function(){
	string new_name, cancel="cancel", abort="abort";
	for(int i=0;i<mark.size();i++) {
		if ( mark[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< mark[i]->get_name()<<endl;
	}
	cout << "Dwse to onoma ths kainourgias agoras" << endl;
	cout << "Cancel/Abort,gia akurwsh" << endl;
	cin >> new_name;
    if ( !strcasecmp(cancel.c_str(),new_name.c_str()) || !strcasecmp(abort.c_str(),new_name.c_str()) || new_name=="c" || new_name=="C" || new_name=="a" || new_name=="A"){
        return;
    }
	else{
		Market *c = new Market(new_name,0);
		mark.push_back(c);
	}
}


void Event::Copy_function(){
	string input, cancel="cancel", abort="abort";
	for(int i=0;i<mark.size();i++) {
		if ( mark[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< mark[i]->get_name()<<endl;
	}
	do{
        cout << "Dwse to antisoixo ID gia antigrafh" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=mark.size() ){
			Market *c = new Market(*(Market *)mark[atoi(input.c_str())-1],true);
			mark.push_back(c);
			break;
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}


void Event::Delete_function(){
	string input, yesorno, cancel="cancel", abort="abort";
	for(int i=0;i<mark.size();i++) {
		if ( mark[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
			cout<<i+1<<". "<< mark[i]->get_name()<<endl;
		}
		do{
          	cout << "Dwse to antisoixo ID gia diagrafh" << endl;
            cout << "Cancel/Abort,gia akurwsh" << endl;
            cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=mark.size() ){
            cout << "Are you sure to continue?An nai grapse Y alliws N" << endl;
            cin >> yesorno;
            if ( yesorno=="Y"){
				delete mark[atoi(input.c_str())-1];
				mark.erase(mark.begin()+atoi(input.c_str())-1);
				break;
			}
			else if ( yesorno=="N" ){
				cout << "Akyrwthhke h diagrafh" << endl;
				break;
			}
			else{
				cout << "Lathos eisagwgh" << endl;
			}
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}


void Event::save_hierarchy(ofstream &f,string node_id) {
	//kanei save thn plhroforia sto arxeio hierarchy.dat
	if(hidden) {
		f<<"[Hidden]"<<" "<<node_id<<" "<<name<<endl;
	}
	else {
		f<<node_id<<" "<<name<<endl;
	}
	for(int i=0;i<mark.size();i++) {
		string node=do_string(i+1);
		node=node_id+"."+node;
		mark[i]->save_hierarchy(f,node);
	}
}





	//sunarthseis ths kalshs SubCategory//
	
	
	
char SubCategory::ploigisi(string location,bool &T,string previous_name,users &play,int id,double &profit,double suply) {
	location+="/"+name;
	bool flag=false, end=false;
	do {
		cout<<"Location:"<<location<<endl;
		cout << "Typos apodwsewn:";
		if (T){
			cout << "klasmatiko" << endl;
		}
		else{
			cout << "dekadiko" << endl;
		}
		for(int i=0;i<event.size();i++) {
			if ( play.am_i_director(id-1) ){
				if ( event[i]->get_hidden()==false ){
					cout<< "	";
				}
				else{
					cout << "[Hidden]";
				}
				cout << i+1<<". "<<event[i]->get_name()<<endl;
			}	
			else{
				if ( event[i]->get_hidden()==false ){
					cout << i+1<<". "<<event[i]->get_name()<<endl;
				}
			}
		}
		cout << name << "/" << previous_name << endl;
		play.commands(id-1);
		string input;
		cin>>input;
		if(input=="H" || input=="Home") {
			return 'H';
		}
		else if(input=="T" || input=="Toggle") {
			T=!T;
			flag=true;
		}
		else if(input=="X" || input=="Exit") {
			return 'X';
		}
		else if(play.execute(id-1,input,end)) {
			if ( input=="L" || input=="Log" ){
				Log_function();
			}
			else if( input=="U" || input=="Users" ){
				Users_function(id-1,play);
			}
			else if( input=="Vi" || input=="Visibility" ){
				Visibility_function();
			}
			else if( input=="R" || input=="Rename" ){
				Rename_function();
			}
			else if( input=="N" || input=="New" ){
				New_function();
			}
			else if( input=="C" || input=="Copy" ){
				Copy_function();
			}
			else if( input=="D" || input=="Delete" ){
				Delete_function();
			}
			else if( input=="Sa" || input=="Save" ) {
				play.save_bets();
				play.save_users();
				return 'S';
			}
			flag=true;
		}
		else if( atoi(input.c_str()) && atoi(input.c_str())<=event.size()) {
			int thesi=atoi(input.c_str());
			thesi-=1;
			char ch;
			ch=event[thesi]->ploigisi(location,T,"Home",play,id,profit,suply);				
			return ch;
		}
		else {
			cout<<"Wrong command"<<endl;
			flag=true;
		}
	}while(flag);
}



void SubCategory::Visibility_function(){
	string input;
	for(int i=0;i<event.size();i++) {
		if ( event[i]->get_hidden()==false ){
				cout<< "	";
			}
			else{
				cout << "[Hidden]";
			}
		cout<<i+1<<". "<<event[i]->get_name()<<endl;
	}
	cout << "Dwse to ID gia allagh oratothtas" << endl;
	cin >> input;
	if ( atoi(input.c_str()) && atoi(input.c_str())<=event.size() ){
		event[atoi(input.c_str())-1]->change_hidden();
	}
	else{
		cout << "Lathos eisagwhg ID" << endl;
	}
}


void SubCategory::Rename_function(){
    string input, new_name, cancel="cancel", abort="abort";
    for(int i=0;i<event.size();i++) {
        if ( event[i]->get_hidden()==false ){
            cout<< "        ";
        }
        else{
            cout << "[Hidden]";
        }
        cout<<i+1<<". "<< event[i]->get_name()<<endl;
    }
    do{
		cout << "Dwse to antisoixo ID gia allagh onomatos" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=event.size() ){
            cout << "Dwse to neo onoma" << endl;
        	cin >> new_name;
            event[atoi(input.c_str())-1]->set_name(new_name);
            break;
        }
        else{
            cout << "Lathos eisagwhg ID" << endl;
		}
    }while (1);
}

     
void SubCategory::New_function(){
	string new_name, cancel="cancel", abort="abort";
	for(int i=0;i<event.size();i++) {
		if ( event[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< event[i]->get_name()<<endl;
	}
	cout << "Dwse to onoma tou kainourgiou gegonotos" << endl;
	cout << "Cancel/Abort,gia akurwsh" << endl;
	cin >> new_name;
    if ( !strcasecmp(cancel.c_str(),new_name.c_str()) || !strcasecmp(abort.c_str(),new_name.c_str()) || new_name=="c" || new_name=="C" || new_name=="a" || new_name=="A"){
        return;
    }
	else{
		Event *c = new Event(new_name,0);
		event.push_back(c);
	}
}


void SubCategory::Copy_function(){
	string input, cancel="cancel", abort="abort";
	for(int i=0;i<event.size();i++) {
		if ( event[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< event[i]->get_name()<<endl;
	}
	do{
        cout << "Dwse to antisoixo ID gia antigrafh" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
    	cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
      	else if ( atoi(input.c_str()) && atoi(input.c_str())<=event.size() ){
			Event *c = new Event(*(Event *)event[atoi(input.c_str())-1],true);
			event.push_back(c);
			break;
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}


void SubCategory::Delete_function(){
	string input, yesorno, cancel="cancel", abort="abort";
	for(int i=0;i<event.size();i++) {
		if ( event[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< event[i]->get_name()<<endl;
	}
	do{
        cout << "Dwse to antisoixo ID gia diagrafh" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=event.size() ){
            cout << "Are you sure to continue?An nai grapse Y alliws N" << endl;
          	cin >> yesorno;
            if ( yesorno=="Y"){
				delete event[atoi(input.c_str())-1];
				event.erase(event.begin()+atoi(input.c_str())-1);
				break;
			}
			else if ( yesorno=="N" ){
				cout << "Akyrwthhke h diagrafh" << endl;
				break;
			}
			else{
				cout << "Lathos eisagwgh" << endl;
			}
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}

	
void SubCategory::save_hierarchy(ofstream &f,string node_id) {
	if(hidden) {
		f<<"[Hidden]"<<" "<<node_id<<" "<<name<<endl;
	}
	else {
		f<<node_id<<" "<<name<<endl;
	}
	for(int i=0;i<event.size();i++) {
		string node=do_string(i+1);
		node=node_id+"."+node;
		event[i]->save_hierarchy(f,node);
	}
}





	//sunarthseis ths kalshs Category//
	
	

char Category::ploigisi(string location,bool &T,string previous_name,users &play,int id,double &profit,double suply) {
	location+="/"+name;
	bool flag=false, end=false;
	do {
		cout<<"Location:"<<location<<endl;
		cout << "Typos apodwsewn:";
		if (T){
			cout << "klasmatiko" << endl;
		}
		else{
			cout << "dekadiko" << endl;
		}
		for(int i=0;i<sub_c.size();i++) {
			if ( play.am_i_director(id-1) ){
				if ( sub_c[i]->get_hidden()==false ){
					cout<< "	";
				}
				else{
					cout << "[Hidden]";
				}
				cout << i+1<<". "<<sub_c[i]->get_name()<<endl;
			}
			else{
				if ( sub_c[i]->get_hidden()==false ){
					cout << i+1<<". "<<sub_c[i]->get_name()<<endl;
				}
			}
		}
		cout << name << "/" << previous_name << endl;
		play.commands(id-1);
		string input;
		cin>>input;
		if(input=="H" || input=="Home") {
			return 'H';
		}
		else if(input=="T" || input=="Toggle") {
			T=!T;
			flag=true;
		}
		else if(input=="X" || input=="Exit") {
			return 'X';
		}
		else if(play.execute(id-1,input,end)) {
			if ( input=="L" || input=="Log" ){
				Log_function();
			}
			else if( input=="U" || input=="Users" ){
				Users_function(id-1,play);
			}
			else if( input=="Vi" || input=="Visibility" ){
				Visibility_function();
			}
			else if( input=="R" || input=="Rename" ){
				Rename_function();
			}
			else if( input=="N" || input=="New" ){
				New_function();
			}
			else if( input=="C" || input=="Copy" ){
				Copy_function();
			}
			else if( input=="D" || input=="Delete" ){
				Delete_function();
			}
			else if( input=="Sa" || input=="Save" ) {
				play.save_bets();
				play.save_users();
				return 'S';
			}
			flag=true;
		}
		else if( atoi(input.c_str()) && atoi(input.c_str())<=sub_c.size()) {
			int thesi=atoi(input.c_str());
			thesi-=1;
			char ch;
			ch=sub_c[thesi]->ploigisi(location,T,"Home",play,id,profit,suply);				
			return ch;
		}
		else {
			cout<<"Wrong command"<<endl;
			flag=true;
		}
	}while(flag);				
}


void Category::Visibility_function(){
	string input;
	for(int i=0;i<sub_c.size();i++) {
		if ( sub_c[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<<sub_c[i]->get_name()<<endl;
	}
	cout << "Dwse to ID gia allagh oratothtas" << endl;
	cin >> input;
	if ( atoi(input.c_str()) && atoi(input.c_str())<=sub_c.size() ){
		sub_c[atoi(input.c_str())-1]->change_hidden();
	}
	else{
		cout << "Lathos eisagwhg ID" << endl;
	}
}


void Category::Rename_function(){
	string input, new_name, cancel="cancel", abort="abort";
	for(int i=0;i<sub_c.size();i++) {
		if ( sub_c[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< sub_c[i]->get_name()<<endl;
	}
	do{
        cout << "Dwse to antisoixo ID gia allagh onomatos" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
	    else if ( atoi(input.c_str()) && atoi(input.c_str())<=sub_c.size() ){
			cout << "Dwse to neo onoma" << endl;
			cin >> new_name;
			sub_c[atoi(input.c_str())-1]->set_name(new_name);
			break;
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}


void Category::New_function(){
	string new_name, cancel="cancel", abort="abort";
	for(int i=0;i<sub_c.size();i++) {
		if ( sub_c[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< sub_c[i]->get_name()<<endl;
	}
	cout << "Dwse to onoma ths kainourgias ypokathgorias" << endl;
	cout << "Cancel/Abort,gia akurwsh" << endl;
	cin >> new_name;
    if ( !strcasecmp(cancel.c_str(),new_name.c_str()) || !strcasecmp(abort.c_str(),new_name.c_str()) || new_name=="c" || new_name=="C" || new_name=="a" || new_name=="A"){
        return;
    }
	else{
		SubCategory *c = new SubCategory(new_name,0);
		sub_c.push_back(c);
	}
}


void Category::Copy_function(){
	string input, cancel="cancel", abort="abort";
	for(int i=0;i<sub_c.size();i++) {
		if ( sub_c[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< sub_c[i]->get_name()<<endl;
	}
	do{
        cout << "Dwse to antisoixo ID gia antigrafh" << endl;
        cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
            break;
        }
		else if ( atoi(input.c_str()) && atoi(input.c_str())<=sub_c.size() ){
			SubCategory *c = new SubCategory(*(SubCategory *)sub_c[atoi(input.c_str())-1],true);
			sub_c.push_back(c);
			break;
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}


void Category::Delete_function(){
		string input, yesorno, cancel="cancel", abort="abort";
		for(int i=0;i<sub_c.size();i++) {
			if ( sub_c[i]->get_hidden()==false ){
				cout<< "	";
			}
			else{
				cout << "[Hidden]";
			}
			cout<<i+1<<". "<< sub_c[i]->get_name()<<endl;
		}
		do{
            cout << "Dwse to antisoixo ID gia diagrafh" << endl;
            cout << "Cancel/Abort,gia akurwsh" << endl;
            cin >> input;
            if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
                break;
            }
            else if ( atoi(input.c_str()) && atoi(input.c_str())<=sub_c.size() ){
            cout << "Are you sure to continue?An nai grapse Y alliws N" << endl;
            cin >> yesorno;
            if ( yesorno=="Y"){
				delete sub_c[atoi(input.c_str())-1];
				sub_c.erase(sub_c.begin()+atoi(input.c_str())-1);
				break;
			}
			else if ( yesorno=="N" ){
				cout << "Akyrwthhke h diagrafh" << endl;
				break;
			}
			else{
				cout << "Lathos eisagwgh" << endl;
			}
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}

	
void Category::save_hierarchy(ofstream &f,string node_id) {
	if(hidden) {
			f<<"[Hidden]"<<" "<<node_id<<" "<<name<<endl;
	}
	else {
		f<<node_id<<" "<<name<<endl;
	}
	for(int i=0;i<sub_c.size();i++) {
		string node=do_string(i+1);
		node=node_id+node;
		sub_c[i]->save_hierarchy(f,node);
	}
}
