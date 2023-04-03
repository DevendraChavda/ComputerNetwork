#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

typedef struct servent servent;

using namespace std;


int main(){
	char name[5] = "http";
	char proto[4] = "tcp";
	int port;
	
	servent *app_name = getservbyname(name, proto);
	
	if(!app_name){
		cout << " unknown application !" << endl;
	}
	else{
	cout << "Service Name : " << app_name->s_name << endl;
	cout << "Service protocol : " << app_name->s_proto << endl;
	cout << "Service prot : " << app_name->s_port << endl;
	}
	
	return 0;
}
