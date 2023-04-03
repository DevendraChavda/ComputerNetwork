#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

typedef struct servent servent;

using namespace std;


int main(){
	struct hostent *res = gethostbyname("www.facebook.com");
	
	if(!res){
		cout << "The host cannot be found!!" << endl;
	}
	else{
		cout << "The host name is : " << res->h_name  << endl;
	}
	
	return 0;
}
