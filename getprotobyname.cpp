#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

typedef struct servent servent;

using namespace std;


int main(){
	struct protoent *res = getprotobyname("udp");
	
	if(!res){
		cout << "Prorocol cannot be found!!" << endl;
	}
	else{
		cout << "The protocol used : " << res->p_name << " and its number is " << res->p_proto << endl;
	}
	
	return 0;
}
