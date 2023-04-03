#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

#define MAX_CLIENT 10
#define BUFFER_SIZE

using namespace std;


int main(int argc, char *argv[]){
	//create TCP/IP socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		cout << "Socket creation failed......" << endl;
		return 1;
	}
	cout << "Socket successfully created....." << endl;
	
	//connect to server
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));
	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		cout << "connection failed......." << endl;
		return 1; 
	}
	cout << "connected to server..." << endl;
	
	
	char buffer[1024];	
	while(true){
		//client input
		int n=0;
		cout << "Enter Message : ";
		cin.getline(buffer,1024);
		
		//sending message to server
		int send_result = send(sockfd,buffer,sizeof(buffer),0);
		if(send_result == -1){
			cout << "error in sending message to server......" << endl;
			break;
		}
		
		//receive data from server
		while(true){
			int bytes_received = recv(sockfd, buffer,sizeof(buffer), 0);
			if(bytes_received == -1){
				continue;
			}
			else if(bytes_received == 0){
				cout << "Client Disconnected... " << endl;
				return 1;
			}
			else{
				cout << "Received Message : " << buffer << endl;
				break;
			}
		}
		
	}
	close(sockfd);

}
