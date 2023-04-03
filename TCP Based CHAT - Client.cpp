#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

using namespace std;

int main(int argc,char *argv[]){

	// create TCP socket object
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);	
	if(sockfd == -1 ){
		cout << "Socket creation failed......" << endl;
		return 1;
	}
	cout << "Socket successfully created....." << endl;
	
	
	// assign IP and PORT
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));
	//connect to the server
	if(connect(sockfd, (struct sockaddr *)&servaddr , sizeof(servaddr)) == -1){
		cout << "server connection failed......." << endl;
		return 1;
	}
	cout << "connected to the server......" << endl;
	
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
		int recv_result = recv(sockfd, buffer, sizeof(buffer), 0);
		if(recv_result == -1){
			cout << "error in receiving message from server..." << endl;
			break;
		}
		else if(recv_result == 0){
			cout << "Server Disconnected..." << endl;
			break;
		}
		cout << "Received messsage : " << buffer << endl;
		
	}
	close(sockfd); 	
	return 0;
}
