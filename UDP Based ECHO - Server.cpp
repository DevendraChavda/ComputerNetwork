#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

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
	
	
	//Bind the socket to a specific IP and PORT
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	if(bind(sockfd, (struct sockaddr *)&servaddr , sizeof(servaddr)) < 0){
		cout << "socket bind failed......." << endl;
		return 1;
	}
	cout << "socket binded...." << endl;
	
	//receive data from the client and echo it back
	struct sockaddr_in cliaddr;
	socklen_t cli_addr_size = sizeof(cliaddr);
	char buffer[BUFFER_SIZE];
	
	while(true){
		memset(buffer,0,BUFFER_SIZE);
		int received = recvfrom(sockfd, buffer,BUFFER_SIZE,0, (struct sockaddr *)&cliaddr, &cli_addr_size);
		if(received < 0){
			cout << "Faild to receive data" << endl;	
			break;
		}
		cout << "Received data : " << buffer << endl;
			
		int send_result = sendto(sockfd, buffer,received,0, (struct sockaddr *)&cliaddr, cli_addr_size);
		if(send_result < 0){
			cout << "faied to send data........." << endl;
			break;
		}
	}
	close(sockfd);
	return 0;
}
