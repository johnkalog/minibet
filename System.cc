#include "System.h"

	//sunarthseis ths kalshs hierarchy//

void hierarchy::ploigisi(users &play,int id,double &profit,double suply) {
	bool flag=false;
	bool T=true, end=false;  //T==true an prokeitai gia klasmatikh emfanish,false gia dekadikh
	do {
		string location;
		location="/Home";
		cout<<"Location:"<<location<<endl;
		cout << "Typos apodwsewn:";
		if (T){
			cout << "klasmatiko" << endl;
		}
		else{
			cout << "dekadiko" << endl;
		}
		for(int i=0;i<categories.size();i++) {
			if ( play.am_i_director(id-1) ){
				if ( categories[i]->get_hidden()==false ){
					cout<< "	";
				}
				else{
					cout << "[Hidden]";
				}
				cout << i+1<<". "<<categories[i]->get_name()<<endl;
			}
			else{
				if ( categories[i]->get_hidden()==false ){
					cout << i+1<<". "<<categories[i]->get_name()<<endl;
				}
			}
		}
		cout<<play.get_name(id-1)<<endl;
		play.commands(id-1);
			string input;
		cin>>input;
		if(input=="H" || input=="Home") {
			flag=true;
		}
		else if(input=="T" || input=="Toggle") {
			T=!T;
			flag=true;
		}
		else if(input=="X" || input=="Exit") {
			flag=false;
		}
		else if(play.execute(id-1,input,end)) {//h execute epistrefei true otan exei epilegei mia apo tiw epilogew ekei
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
				save_hierarchy();
			}
			flag=true;  // while flag==true sunexise na diabazeis edw
		}
		else if( atoi(input.c_str()) && atoi(input.c_str())<=categories.size()) {
			int thesi=atoi(input.c_str());
			thesi-=1;
			char ch;
			ch=categories[thesi]->ploigisi(location,T,"Home",play,id,profit,suply);				
			if(ch=='X') {
				flag=false;
			}else if(ch=='H'){
				flag=true;
			}else if(ch=='S') {
				save_hierarchy();
				flag=true;
			}
		
		}
		else {
			cout<<"Wrong command"<<endl;
			flag=true;
		}
	}while(flag);
}


void hierarchy::Visibility_function(){
	string input;
	for(int i=0;i<categories.size();i++) {
		if ( categories[i]->get_hidden()==false ){
			cout<< "	";
		}
		else if ( categories[i]->get_hidden()==true ){
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<<categories[i]->get_name()<<endl;
	}
	cout << "Dwse to ID gia allagh oratothtas" << endl;
	cin >> input;
	if ( atoi(input.c_str()) && atoi(input.c_str())<=categories.size() ){
		categories[atoi(input.c_str())-1]->change_hidden();
	}
	else{
		cout << "Lathos eisagwgh ID" << endl;
	}
}


void hierarchy::Rename_function(){
    string input, new_name, cancel="cancel", abort="abort";
    for(int i=0;i<categories.size();i++) {
        if ( categories[i]->get_hidden()==false ){
            cout<< "        ";
        }
        else{
            cout << "[Hidden]";
        }
        cout<<i+1<<". "<< categories[i]->get_name()<<endl;
    }
    do{
		cout << "Dwse to antisoixo ID gia allagh onomatos" << endl;
    	cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
        	break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=categories.size() ){
            cout << "Dwse to neo onoma" << endl;
            cin >> new_name;
            categories[atoi(input.c_str())-1]->set_name(new_name);
            break;
        }
		else{
        	cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}


void hierarchy::New_function(){
	string new_name, cancel="cancel", abort="abort";
	for(int i=0;i<categories.size();i++) {
		if ( categories[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< categories[i]->get_name()<<endl;
	}
	cout << "Dwse to onoma ths kainourgias kathgorias" << endl;
	cout << "Cancel/Abort,gia akurwsh" << endl;
	cin >> new_name;
    if ( !strcasecmp(cancel.c_str(),new_name.c_str()) || !strcasecmp(abort.c_str(),new_name.c_str()) || new_name=="c" || new_name=="C" || new_name=="a" || new_name=="A"){
        return;
    }
	else{
		Category *c = new Category(new_name,0);
		categories.push_back(c);
	}
}


void hierarchy::Copy_function(){
	string input, cancel="cancel", abort="abort";
	for(int i=0;i<categories.size();i++) {
		if ( categories[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
		cout<<i+1<<". "<< categories[i]->get_name()<<endl;
	}
	do{
		cout << "Dwse to antisoixo ID gia antigrafh" << endl;
		cout << "Cancel/Abort,gia akurwsh" << endl;
        cin >> input;
	    if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
    		break;
        }
		else if ( atoi(input.c_str()) && atoi(input.c_str())<=categories.size() ){
			Category *c = new Category(*(Category *)categories[atoi(input.c_str())-1]);
			categories.push_back(c);
			break;
		}
		else{
			cout << "Lathos eisagwhg ID" << endl;
		}
	}while (1);
}


void hierarchy::Delete_function(){
	string input, yesorno, cancel="cancel", abort="abort";
	for(int i=0;i<categories.size();i++) {
		if ( categories[i]->get_hidden()==false ){
			cout<< "	";
		}
		else{
			cout << "[Hidden]";
		}
			cout<<i+1<<". "<< categories[i]->get_name()<<endl;
		}
		do{
        	cout << "Dwse to antisoixo ID gia diagrafh" << endl;
    	cout << "Cancel/Abort,gia akurwsh" << endl;
            cin >> input;
        if ( !strcasecmp(cancel.c_str(),input.c_str()) || !strcasecmp(abort.c_str(),input.c_str()) || input=="c" || input=="C" || input=="a" || input=="A"){
        	break;
        }
        else if ( atoi(input.c_str()) && atoi(input.c_str())<=categories.size() ){
        	cout << "Are you sure to continue?An nai grapse Y alliws N" << endl;
			cin >> yesorno;
        	if ( yesorno=="Y"){
				delete categories[atoi(input.c_str())-1];
				categories.erase(categories.begin()+atoi(input.c_str())-1);
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

	
void hierarchy::save_hierarchy() {
	cout<<"saving"<<endl;
	ofstream f("hierarchy.dat",ios::out);
	for(int i=0;i<categories.size();i++) {
		string node=do_string(i+1)+".";
		categories[i]->save_hierarchy(f,node);
	}

}





	//sunarthseis ths kalshs System//




int System::egrafi() {  //eggrafi sto systhma
	string username, fullname, password;
	int type;
    do{
    	cout << "Dwse onoma diaforo tou guest" << endl;
    	cout<<"Username: ";
    	cin>>username;
	}while ( username=="guest" );
    if(!(players.name_available(username))) {
        cout<<"Sorry already taken"<<endl;
    }
    cout<<"Password: ";
    cin>>password;
	int id;
	id=players.make_user(username,fullname,password,type);
	return id;
}


int System::login(){  //eisodos sto systhma
    string username, password, else_username;
    int i, tmp, j=0;
	do{
		if ( j==0 ){
			cout << "Kalwsorisate sto systhma " << Name_of_System << "!" << endl
			<< "Parakalw dwste onoma xrhsth gia eisodo.An den exete logariasmo,eisagete " << endl
			<< "allagh grammhs(enter) h guest:guest ws episketpths." << endl;
		}
		cout << "Onoma xrhsth: ";  //an dwthei lathos username ginetai ksana h ervthsh gia username kai o kwdikos zhteitai
						        // an to username uparxei
		getline(cin,username);
		if ( !username.empty() ){
			tmp = players.check(username);
    		if( tmp!=-1 ) {
    	    	cout<<"Kwdikos prosbashs: ";
    	    	cin>>password;
    			if ( players.check(password,tmp-1) ){
    				break;
				}
				else{
					cout << "Lathos kwdikos,ksanaprospauhste me nea stoixeia" << endl;
				}
    		}
    		else if ( username!="guest" ){
    		cout << "Den uparxei ayto to onoma" << endl;
			}
        	else if(username=="guest") {//username=="guest"
        		cout<<"Kwdikos prosbashs: ";
    			cin>>password;
        		if ( password=="guest" ){
					tmp=players.make_guest();
					break;
				}
        		else{
    				cout << "Lathos kwdikos gia eisodo episkepth" << endl;
				}
			}
    	}
    	else{
			tmp=players.make_guest();
    		break;
		}
		j++;
		cin.ignore();  // gia na ksanadiabasei h getline()
    }while ( 1 );
    return tmp;
}
 
    
void System::ploigisi(int id) {       	
	H.ploigisi(players,id,profit,supply);
	players.save_users();
}
