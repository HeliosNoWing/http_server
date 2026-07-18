#include "parser.h"
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<ws2tcpip.h> //fix the mem leack use const  char [] , fix character lenght,
#include<windows.h>

#define STRCT_SIZE 4096
#define CLI_SIZE 64
#define BUFF_SIZE 512

typedef struct client_accum
{
	SOCKET socket;
	char c[STRCT_SIZE];
	size_t length;
	size_t used;
}client_accum;

int main()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
		fprintf(stderr,"WSAStartup failed.\n");
		exit(1);
	}
	if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		fprintf(stderr,"version 2.2 of winsock not avaliable\n");
		WSACleanup(); 
		exit(2);
	}
	//filepinter to read from htmlfile
	FILE*ptr = fopen("index.html","r");
	//sockets 
	SOCKET lin,cin;
	//accumulator struce
	client_accum* clients[CLI_SIZE];
	//sockaddr 
	struct sockaddr_in sockad , cli_sockad;
	//fd_sets
	struct fd_set sok_set_reg,sok_set_master;
	//buffers
	char file_buffer[BUFF_SIZE]; //to store file contents
	char buffer[BUFF_SIZE];
	char buff[BUFF_SIZE];
	//lens	
	int len_sockad = sizeof(sockad);
	//httpreq
	httpreq* Httpreq = (httpreq*)malloc(sizeof(httpreq));
	

	memset(&sockad,0,sizeof(sockad));
	sockad.sin_family = AF_INET;
	sockad.sin_port = htons(8080);
	sockad.sin_addr.s_addr = htonl(INADDR_ANY);

	lin = socket(AF_INET,SOCK_STREAM,0);
	if(lin == INVALID_SOCKET)
	{
		fputs("Lin SOCKET CREATING FAILED",stderr);
		closesocket(lin);
		WSACleanup(); 
		return 1;
	}

	int bind_chk = bind(lin,(struct sockaddr*)&sockad,sizeof(sockad));
	if(bind_chk == SOCKET_ERROR)
	{
		fputs("BINDING ERROR",stderr);
		closesocket(lin);
		WSACleanup();
		return 1;
	}
	
	int listn_chk = listen(lin,10);
	if(listn_chk == SOCKET_ERROR)
	{
		fputs("LISTENING CHECNK FAILED", stderr);
		closesocket(lin); 
		WSACleanup();
		return 1;
	}

	fgets(file_buffer, sizeof(file_buffer),ptr);
	for(int i = 0; i<CLI_SIZE; i++) 
	{
			client_accum* temp = (client_accum*)malloc(sizeof(client_accum));
			//memset(&(clients[i]->c),0,4096);
			temp->socket = INVALID_SOCKET; 
			temp->length = 0;
			temp->used= 0; 
			clients[i] = temp;
			memset(&temp->c,0,4096);
	}	
	FD_ZERO(&sok_set_master);//removing garbage values
	FD_SET(lin,&sok_set_master);//inserting the listening socket
	while(1)//server loop
	{
		sok_set_reg = sok_set_master;
		int n = select(0,&sok_set_reg,NULL,NULL,NULL);

		if(FD_ISSET(lin,&sok_set_reg))
		{
			cin = accept(lin,(struct sockaddr*)&sockad,&len_sockad);
			if(cin == INVALID_SOCKET)
			{
				fputs("accpet failed",stderr);
				closesocket(cin);
				break;
			}
			for(int i = 0; i<CLI_SIZE; i++)
			{
				if(clients[i]->socket == INVALID_SOCKET)
				{
					clients[i]->socket = cin;
					FD_SET(clients[i]->socket,&sok_set_master); 
					break;
				}
			}
		}
		for(int i = 0; i<CLI_SIZE; i++) //write an accumulator : you have to parse one byte at a time to detect \r\n\r\n
		{
			if(clients[i]->socket == INVALID_SOCKET) continue;
			if(FD_ISSET(clients[i]->socket,&sok_set_reg))
			{
			int r_in = 1;
			while(r_in > 0) 
				{
					memset(&buff,0,CLI_SIZE); //buff will hold the the recieving data from the http request. it will be parsed int the struct.buffer[]
					r_in = recv(clients[i]->socket,buff,BUFF_SIZE,0);
					if(r_in == 0){
						clients[i]->used = 1; 
						break;
					}
					fputs(buff,stdout);
					memcpy(&clients[i]->c[clients[i]->length],buff,BUFF_SIZE);
					clients[i]->length += strlen(buff);
				}

				//fputs(clients[i]->c,stdout); 
				if(clients[i]->used == 0)
				{
					FD_CLR(clients[i]->socket,&sok_set_master);
					closesocket(clients[i]->socket);
					clients[i]->socket = INVALID_SOCKET;
					continue;
				}

				//buff[(int)strlen(buff)] = '\0';
				//parser(Httpreq,clients[i]->c);
				//printf("\n-------%d-------\n",(int)strlen(clients[i]->c));	
				//fputs(Httpreq->method,stdout);
				//fputs(Httpreq->path,stdout);
				//fputs(Httpreq->version,stdout);
				//send(clients[i]->socket,buffer,strlen(buffer)+1,0);
			}
		}
	}
	closesocket(cin);
	closesocket(lin);
	WSACleanup();
} 
