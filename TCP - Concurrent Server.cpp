#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

#define MAX_CLIENT 10
#define BUFFER_SIZE

using namespace std;

struct sockaddr_in servaddr,cliaddr{};

char *reverse(char *str){
	char *p1, *p2;
	
	if(!str || !*str) return str;
	
	for(p1 = str,p2 = str+strlen(str)-1; p1<p2; p1++,p2--){
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	
	return str;
}

void handel_clients(int connfd, struct sockaddr_in *cliadd){
	char buffer[1024];
	struct sockaddr_in cli = *cliadd;
	
	//receive message from client
	while(true){
		int bytes_received = recv(connfd, buffer,sizeof(buffer), 0);
		if(bytes_received == -1){
			continue;
		}
		else if(bytes_received == 0){
			cout << "Client Disconnected... " << endl;
			break;
		}
		cout << "Received Message from: " << inet_ntoa(cli.sin_addr) << " : " << ntohs(cli.sin_port) << " : " << buffer << endl;
		//reversing buffer message
		char *msg = buffer;
		msg = reverse(msg);
		
		// send to client
		send(connfd,buffer,bytes_received,0);
	}
	close(connfd);
}

int main(int argc, char *argv[]){
	//create TCP/IP socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		cout << "Socket creation failed......" << endl;
		return 1;
	}
	cout << "Socket successfully created....." << endl;
	
	//bind the socket to specific IP and PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(atoi(argv[2]));
	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		cout << "socket bind failed......." << endl;
		return 1; 
	}
	cout << "socket binded...." << endl;
		
	//listen for incoming connections
	if(listen(sockfd,MAX_CLIENT)<0){
		cout << "listen failed......" << endl;
		return 1;
	}
	cout << "Server listening on port " << atoi(argv[2]) << endl;
	
	
	//accept the incoming connection and handel them
	while(true){
		//wait for the client to connect
		socklen_t cliaddr_len = sizeof(cliaddr);
		int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &cliaddr_len);
		if(connfd<0){
			cout << "Faild to accept incoming connection......" << endl;
			continue;
		}
		
		cout << "Received connection from " << inet_ntoa(cliaddr.sin_addr) << " : " << ntohs(cliaddr.sin_port) << endl;
		
		thread newclient(handel_clients, connfd, &cliaddr);
		
		newclient.detach();
	}
	close(sockfd);

}
