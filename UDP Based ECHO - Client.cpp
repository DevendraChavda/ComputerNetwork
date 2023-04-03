#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>

#define PORT 8001
#define BUFFER_SIZE 1024

using namespace std;

int main(){

	// create TCP socket object
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);	
	if(sockfd == -1 ){
		cout << "Socket creation failed......" << endl;
		return 1;
	}
	cout << "Socket successfully created....." << endl;
	
	
	// assign IP and PORT
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	
	const char *message = "Hello Message sent.";	
	int sent = sendto(sockfd, message, strlen(message),0,(struct sockaddr *)&servaddr, sizeof(servaddr));
	if(sent < 0){
		cout << "Faild send data......" << endl;
		return 1;
	}
	
	char buffer[BUFFER_SIZE];
	
	memset(buffer,0,BUFFER_SIZE);	
	int received = recvfrom(sockfd, buffer,BUFFER_SIZE,0, nullptr, nullptr);
	if(received < 0){
		cout << "Faild to receive data" << endl;	
		return 1;
	}
	cout << "Received data : " << buffer << endl;
	
	close(sockfd); 	
	return 0;
}
