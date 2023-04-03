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
	
	
	//Bind the socket to a specific IP and PORT
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));
	if(bind(sockfd, (struct sockaddr *)&servaddr , sizeof(servaddr)) != 0){
		cout << "socket bind failed......." << endl;
		return 1;
	}
	cout << "socket binded...." << endl;
		
	//listen for incoming connections
	if((listen(sockfd,10) != 0)){
		cout << "listen failed......" << endl;
		return 1;
	}
	cout << "Server listening on port " << atoi(argv[2]) << endl;
	
	while(true){
		//accept the data packet from clien and verification
		struct sockaddr_in cliaddr;
		socklen_t cli_addr_size = sizeof(cliaddr);
		int connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &cli_addr_size);
		
		if(connfd == -1){
			cout << "Faild to accept incoming connection......" << endl;
			continue;
		}
		
		cout << "connection from " << inet_ntoa(cliaddr.sin_addr) << " established...." << endl;
		
		while(true){
			//Receive data from the client
			char buffer[1024];
			int recv_result = recv(connfd, buffer, sizeof(buffer), 0);
			
			// if no data received, break out of the loop
			if(recv_result == 0){
				break;
			}
			else
				cout << "From client : " << buffer << endl;
			
			//send the same data to client
			int send_result = send(connfd,buffer,recv_result,0);
			
			if(send_result == -1){
				cout << "faied to send data to client........." << endl;
				break;
			}
		}
		
		close(connfd);
	}
	close(sockfd);
	return 0;
}
