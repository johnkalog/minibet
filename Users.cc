#include "Users.h"



	//sunarthseis ths kalshs Wallet//
	
void Wallet::set_balance(double new_balance){
	my_balance = new_balance;
}

double Wallet::get_balance(){
	return my_balance;
}

string Wallet::get_freebets(){
	return my_freebets;
}

void Wallet::set_freebets(string new_freebets) {
	my_freebets=new_freebets;
}




	//sunarthseis ths kalshs Punter//
	
void Punter::print_commands() {
	Guest::print_commands();
	cout<<"A(Account),gia diaxeirish twn plhroforiwn logariasmoy xrhsth"<<endl;  //epipleon ektupwsh tou xrhsth
}


void Punter::my_selection_print(){
	cout << "P(Place),gia enapothesi stoixhmatos" << endl;  //ektupwsh sto epipedo twn agorwn
}


bool Punter::execute(string input,bool end,Bets &bets,vector_of_users &all_users) {
	/*ektelei tis sunarthseis tou xrhsth ean tis exei epileksei (input)
	 alliws (ean den exei epileksei kamia apo autes) epistrefei fasle */
	if(end){
		if ( input=="P" || input=="Place"){
			return true;
		}
	}
	if ( input=="A" || input=="Account"){
		cout << "Paikths:" << username << endl;
		cout << "Diathesimo ypoloipo:" << my_Wallet.get_balance() << endl;
		cout << "Diathesima kouponia:" << my_Wallet.get_freebets() << endl << endl;
		cout << "Epiloges:" << endl;
		cout << "R(Rename),gia allagh onomatos paikth" << endl;
		cout << "P(Password),gia allagh kwdikou" << endl;
		cout << "B(Bets),gia probolh istorikou stoixhmatwn" << endl;
		cout << "D(Deposit),gia gemisma logariasmou kai aukshsh upoloipou" << endl;
		string epilogh;
		cin >> epilogh;
		if ( epilogh=="R" || epilogh=="Rename" ){
			Rename_function(all_users);
		}
		else if( epilogh=="P" || epilogh=="Password" ){
			Password_function();
		}
		else if( epilogh=="B" || epilogh=="Bets" ){
			Bets_function(bets,all_users);
		}
		else if( epilogh=="D" || epilogh=="Deposit" ){
			Deposit_function();
		}
		else{
			cout << "Den edwses katallhlh epilogh" << endl;
		}
		return true;
	}
	return false;
}


void Punter::Rename_function(vector_of_users &all_users){
	/*allazei to onoma tou punter*/
	string new_name;
	int flag=0;
	do{
		cout << "Plhktrologhse to neo onoma" << endl;
		cin >> new_name;
		if ( new_name=="guest"){
			cout << "Mh apodekto onoma" << endl;
		}
		else{
			int i;
			for ( i=0; i<all_users.size(); i++){
				if ( new_name==all_users[i]->get_name() ){
					cout << "To onoma poy edwses yparxei hdh" << endl;
					break;
				}
			}
			if ( i==all_users.size() ){
				flag = 1;
				cout << "Epityxhs allagh,to onoma " << username << " allakse se " << new_name << endl;
				username = new_name;
			}
		}
	}while ( !flag );
}


void Punter::Password_function(){
	/* allazei to password tou punter*/
	string password1, password2;
	int flag=0;
	do{
		cout << "Dwse to neo password" << endl;
		cin >> password1;
		cout << "Ksanadwse ton neo password" << endl;
		cin >> password2;
		if ( password1!=password2 ){ //epituxhs mono ean ta password pou edwse einai idia
			cout << "Oi 2 kwdikoi den tairiazoun" << endl;
		}
		else{
			flag = 1;
			cout << "Epityxhs allagh,to password " << password << " allkse se " << password1 << endl;
			password = password1;
		}
	}while ( !flag );
}


void Punter::Bets_function(Bets &bets,vector_of_users &all_users){
	bets.player_bets(user_id);
}


void Punter::Deposit_function(){
	double last_balance=my_Wallet.get_balance(), extra_balance;
	cout << "Eisagete to poso me to opoio thelete na aykshuei to upoloipo sas" << endl;
	cin >> extra_balance;
	my_Wallet.set_balance(last_balance+extra_balance);
	cout << "Epityxhs prosthkh" << endl;
}


int Punter::get_balance() {
	return my_Wallet.get_balance();
}


void Punter::print_freebets() {
	string free = my_Wallet.get_freebets();
	char *tok=&free[0];
	char* ab;
	ab=strtok(tok,", \n");
	int i=0;
	while(ab!=NULL) {
		char ch='a'+i;
		cout<<ch<<". "<<ab<<endl;
		ab=strtok(NULL,", \n");
		i++;
	}
}


bool Punter::bet_with_money(string bet,double &value) {
	/*ean o punter epileksei na paiksei me xrhmata 
	afairountai apo to upoloipo tou, ean den tou ftanoun emfanizetai
	katallhlo mnm*/
	value=atof(bet.c_str());
	cout<<value<<endl;
	if(value<=0 || value>my_Wallet.get_balance()) {
		cout<<"den exeis tosa lefta :("<<endl;
		return false;
	}
	int new_balance=my_Wallet.get_balance()-value;
	my_Wallet.set_balance(new_balance);
	return true;
}


bool Punter::bet_with_freebet(string bet,double &value) {
	/*o punter epelekse na paiksei me kouponi*/
	int thesi= bet[0]-'a';
	string freebet=my_Wallet.get_freebets();
	if(freebet.empty()) {
		cout<<"den exeis kouponia"<<endl;
		return false;
	}			
	char *tok=&freebet[0];
	string new_freebet;//to kainourigio kouponi(afairei to kouponi pou xrhsimopoieise
	tok=strtok(tok,", \n");
	for(int i=0;i<thesi;i++) {
		if(tok==NULL) {
			cout<<"edwses lathos stoixeio"<<endl;
			return false;
		}else {
			if(i==0) {
				new_freebet=new_freebet+tok;
			}else {
				new_freebet=new_freebet+","+tok;
			}
		}
		tok=strtok(NULL,", \n");
	}
	value = atof(tok);
	tok=strtok(NULL,"\n");
	cout<<freebet<<endl;
	if(tok!=NULL) {
		if(new_freebet.empty()) {
			new_freebet=tok;
		}
		else {
			new_freebet=new_freebet+","+tok;
		}
	}
	my_Wallet.set_freebets(new_freebet);
	return true;
}


void Punter::return_money(double value) {
	/*epistrefei xrhmata ston xrhsth*/
	double balance=my_Wallet.get_balance() + value;
	my_Wallet.set_balance(balance);
}


void Punter::save_user(ofstream &f,int i) {
	f<<i<<'|'<<	username<<'|'<<fullname<<'|'<<password<<'|'<<1<<'|'<<status<<'|'<<my_Wallet.get_balance()<<'|'<<my_Wallet.get_freebets()<<endl;
}	



	//sunarthseis ths kalshs Trader//



void Trader::print_commands() {
	Guest::print_commands();
	cout<<"B(Bets),gia emfanish twn 20 teleutaiwn stoixhmatwn"<<endl;
	cout<<"F(Freebets),gia apodosh kouponiou se xrhsth"<<endl;
}


void Trader::my_selection_print(){
	cout << "Vo(Void),gia na akyrwthei mia epilogh" << endl;
	cout << "Se(Settle),gia dieythetisi thw agoras" << endl;
}


bool Trader::execute(string input,bool end,Bets &bets,vector_of_users &all_users) {
	if(end){
		if ( input=="Vo" || input=="Void"){
			return true;
		}
		else if(input=="Se" || input=="Settle"){
			return true;
		}
	}
	if ( input=="B" || input=="Bets"){
		bets.print_bets(20);
		return true;
	}
	else if(input=="F" || input=="Freebets"){
		give_free_bets(all_users);
		return true;
	}
	return false;
}


void Trader::give_free_bets(vector_of_users &users) {
	
	cout<<"give the name of the player: ";
	string name;
	cin>>name;
	int i;
	for(i=0;i<users.size();i++) {
		if(name==users[i]->get_name()) {
			cout<<"give the value of the free bet: ";
			string value;
			cin>>value;	
			string freebets= users[i]->get_freebets();
			freebets=freebets+","+value;
			users[i]->set_freebets(freebets);
			return;
		}
	}
	cout<<"sorry wrong name"<<endl;
}


void Trader::my_user_function(vector_of_users &all_users){}


bool Trader::ask_for_director(){
	return false;
}




	//sunarthseis ths kalshs Director//



void Director::print_me(){
	cout << user_id << "-" << username << "-" << fullname << "-" << password << "-" 
	<< "3" << "-" << "-" << " " << "-" << " " << "-" << endl;
}


void Director::print_commands() {
	Trader::print_commands();
	cout << "Management" << endl;
	cout<<"Sa(Save),gia swsimo ths trexousas katastashs kai sygxronismou twn arxeiwn systhmatos"<<endl;  //Sa afou uparxei kai to Settle
	cout<<"L(Log),gia emfanish teleutaiwn 25 energeiwn sto systhma"<<endl;                               //to Settle me Se
	cout<<"U(Users),gia diaxeirhsh xreistwn"<<endl;
	cout<<"Vi(Visibility),gia enallagh oratothtas kombou"<<endl;  //Vi kai oxi V giati uparxei kai to Void
	cout<<"R(Rename),gia metonomasia komnou"<<endl;               //to Void me Vo
	cout<<"N(New),gia dhmiourgia neou kombou"<<endl;
	cout<<"C(Copy),gia thn antigrafh enos kombou ws mh oratou"<<endl;
cout<<"D(Delete),gia th diagrafh kombou"<<endl;
}


void Director::my_selection_print(){
	Trader::my_selection_print();
}


bool Director::execute(string input,bool end,Bets &bets,vector_of_users &all_users) {
	/*oi sunarthseis tou Director ulopoiountai sthn hierarchy
	edw aplws epistrefei true ean edwse swsth epilogh*/ 
	bool value=true;
	if ( input=="Sa" || input=="Save" ){
		
	}
	else if ( input=="L" || input=="Log" ){
		
	}
	else if( input=="U" || input=="Users" ){
		
	}
	else if( input=="Vi" || input=="Visibility" ){
		
	}
	else if( input=="R" || input=="Rename" ){
		
	}
	else if( input=="N" || input=="New" ){
		
	}
	else if( input=="C" || input=="Copy" ){
		
	}
	else if( input=="D" || input=="Delete" ){
		
	}
	else {
		return Trader::execute(input,end,bets,all_users);
	}
	return true;
}


void Director::my_user_function(vector_of_users &all_users){
	string diaxeirhsh;
	cout << "Dwse leitourgia diaxeithshs" << endl;
	cout << "V(View),gia emfanish pinaka xrhstwn" << endl;
	cout << "S(Search),gia anazhthsh xrhsth" << endl;
	cout << "L(Lock),gi enallagh katastashs apokleismoumenos xrhsth" << endl;
	cin >> diaxeirhsh;
	if( diaxeirhsh=="V" || diaxeirhsh=="View" ){
		View_function(all_users);
	}
	else if( diaxeirhsh=="S" || diaxeirhsh=="Search" ){
		Search_function(all_users);
	}
	else if( diaxeirhsh=="L" || diaxeirhsh=="Lock" ){
		Lock_function(all_users);
	}
	else{
		cout << "Lathos leitourgia" << endl;
	}
}


void Director::View_function(vector_of_users &all_users){
	int i;
	for ( i=0; i<all_users.size(); i++ ){
		all_users[i]->print_me();
	}
}


void Director::Search_function(vector_of_users &all_users){
	string substring, onoma;
	int flag=0, metritis;
	do{  //h epanalhpsh stamatei otan brethei kapoios xrhsths to substring na uparxei sto onoma tou
		metritis = 0;
		cout << "Dwse meros onomatos gia anazhthsh" << endl;
		cin >> substring;
		int i;
		for ( i=0; i<all_users.size(); i++ ){
			onoma=all_users[i]->get_name();
			if ( onoma.find(substring)!=string::npos ){
				all_users[i]->print_me();
				metritis++;
				flag = 1;
			}	
		}
		if ( metritis==0 ){
			cout << "Den breuhke to " << substring << " se kapoio onoma paikth" << endl;
		}
	}while (!flag);
}


void Director::Lock_function(vector_of_users &all_users){
	string name, tmp_status, reason, final_status;
	int i, metritis=0;
	cout << "Dwste onoma paikth" << endl;
	cin >> name;
	for ( i=0; i<all_users.size(); i++ ){
		if ( !all_users[i]->ask_for_director() ){
			if ( name==all_users[i]->get_name() ){
				tmp_status = all_users[i]->get_status();
				break;
			}
		}
		metritis++;
	}
	if ( metritis!=all_users.size() ){//gia elegxo an brethhke to onoma
		if ( tmp_status[0]=='A' ){
			cout << "O xrhsths einai energos,dwste logo apokleismou (an den uparxei pathste X)" << endl;
			cin >> reason;
			if ( reason=="X"){
				reason = "N/A";
			}
			else{
				final_status = "L," + reason;
			}
			all_users[i]->set_status(final_status);
		}
		else{
			cout << "O xrhsths einai apokleismenos,dwste kapoio sxolio (an den uparxei pathste keno)" << endl;
			cin >> reason;
			if ( reason==" "){
				final_status = "A";
			}
			else{
				final_status = "A," + reason;
			}
			all_users[i]->set_status(final_status);
		}
	}
	else{
		cout << "To " << name << " den brethhke" << endl;
	}
}


bool Director::ask_for_director(){
	return true;
}

void Director::save_user(ofstream &f,int i) {  //apothhkeush xrhsth
	f<<i<<'|'<<	username<<'|'<<fullname<<'|'<<password<<'|'<<3<<'|'<<'|'<<'|'<<endl;
}




	//sunarthseis ths kalshs users//


int users::check(string username) {  //epistrofh thesis an to username uparxei alliws -1
	int i;
	for(i=0;i<all_users.size();i++) {
	    if( username==all_users[i]->get_name() ) {
	        return ++i;
		}
    }
    return -1;
}


int users::check(string password,int tmp){  //epistrofh 1 an to password einai tou xrhsth sth thesi tmp,alliws 0
	if ( all_users[tmp]->get_password()==password ){
		return 1;
	}
	else{
		return 0;
	}
}


int users::make_user(string username,string fullname,string password,int type) { //dhmiourgia xrhsth kai prosthkh sth mnhmh
    ofstream file_users("users.csv",ios::app);
	Guest *item;
    int k = all_users.size(), j = all_users[k-1]->get_user_id();
    int user_id = ++j;
    item = new Punter(user_id,username,"Unknown",password," ",0," ");
	all_users.push_back(item);
    file_users << user_id << "|" << username << "|" << fullname << "|" << password << "|"
    << type << "|" << " " << "|" << " " << "|" << " " << "|" << endl;
    ofstream f("users.csv",ios::app);
    f<< user_id << "|" << username << "|" << fullname << "|" << password<<endl;
    file_users.flush();
    return user_id;
}


int users::make_guest() {  //dhmiourgia episkepth
	int k=all_users.size();
	int j = all_users[k-1]->get_user_id();
	int user_id = ++j;
	Guest *item;
	item = new Guest();
	all_users.push_back(item);
	return user_id; 
}


void users::return_money(string epilogi) {
	/*kaleitai gia thn entolh void
	kai briskei mia-mia ton node_id pou exei ginei stoixhma
	kai epistefei to poso ston xrhsth*/ 
	int user_id;
	double value;
	bool flag;
	flag=bets.delete_epilogi(epilogi,user_id,value);//flag==true ara brethike stoixima sthn epilogh auth
	while(flag) {
		all_users[user_id-1]->return_money(value);
		flag=bets.delete_epilogi(epilogi,user_id,value);
	}
	bets.save_bets();
	save_users();
}


void users::the_users_function(int id){
	all_users[id]->my_user_function(all_users);	
}


bool users::am_i_director(int id){
	return all_users[id]->ask_for_director();
}


void users::settle(string node,string epilogi,double P,double &profit,double supply) {
	/* douleui paromia me thn return_money
	aplws ean mia epilogh einai Win tote kanei tis 
	katallhles energeies*/ 
	int user_id;
	double value;
	bool Win;
	while(bets.settle_epilogi(node,epilogi,user_id,value,Win)) {
		if(Win) {
			value=value+value*P;
			int system_supply=value*supply;
			profit+=system_supply;
			value-=system_supply;
			all_users[user_id-1]->return_money(value);
		}
	}
	save_bets();//swzei sta arxeia tis allages
	save_users();
}

void users::save_bets() {
	bets.save_bets();
}


void users::save_users() {
	ofstream f("users.csv",ios::out);
	for(int i=0;i<all_users.size();i++) {
		all_users[i]->save_user(f,i+1);
	}
}
