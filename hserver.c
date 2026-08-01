#include "parser.h"
#include "doc_prep.h"
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
#include<ws2tcpip.h> 
#include<windows.h>
#include<stddef.h>

#define STRCT_SIZE 4096
#define CLI_SIZE 64
#define BUFF_SIZE 512

typedef struct client_accum
{
	SOCKET socket;
	char c[STRCT_SIZE];
	size_t length;
}client_accum;

void client_clean(client_accum* client)
{
	memset(client->c,0,STRCT_SIZE); 
	client->length = 0; 
}

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
	char HTML_FILE_BUFFER[STRCT_SIZE];
	//lens	i
	int len_sockad = sizeof(sockad);
	//httpreq
	httpreq* Httpreq = (httpreq*)malloc(sizeof(httpreq));
	

	memset(&sockad,0,sizeof(sockad));
	sockad.sin_family = AF_INET;
	sockad.sin_port = htons(8081);
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
			client_clean(temp); 
			clients[i] = temp;
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

			if(clients[i]->socket == INVALID_SOCKET) continue ;
			if(FD_ISSET(clients[i]->socket,&sok_set_reg))
			{
				int r_in = 1;
				while(r_in > 0) 
					{
						memset(&buff,0,BUFF_SIZE); //buff will hold the the recieving data from the http request. it will be parsed int the struct.buffer[]
						r_in = recv(clients[i]->socket,buff,BUFF_SIZE,0);
						if(r_in == 0)
						{
							FD_CLR(clients[i]->socket,&sok_set_master);
							closesocket(clients[i]->socket);
							clients[i]->socket = INVALID_SOCKET;
							break;
						}
						if((r_in + clients[i]->length) > STRCT_SIZE) //to catch buffers overflow
						{
							fputs("buffer overflow",stdout);
							break;
						}
						memcpy(&clients[i]->c[clients[i]->length],buff,r_in);
						clients[i]->length += r_in;
						if(strstr(clients[i]->c,"\r\n\r\n"))// change this later for f**K sake (censored for github)
						{
							buffer[strlen(buffer)+1] = '\0';
							parser(Httpreq,clients[i]->c);
							size_t content_length = doc_prep(Httpreq->path,HTML_FILE_BUFFER);
							if(content_length == FILE_NOT_FOUND) 
							{
								fputs("NO_FILE",stdout);
								continue;
							}
							//printf("\ncontent_length: %zu\n",content_length);
							//fputs(clients[i]->c,stdout);
							//fputs(HTML_FILE_BUFFER,stdout);
							//int s_chk =send(clients[i]->socket,char_buff,strlen(char_buff),0);
						}		
					}
					//fputs("loop ended");
					//fputs(clients[i]->c,stdout);
					//send(clients[i]->socket,buffer,strlen(buffer)+1,0);
					client_clean(clients[i]);  //cleaning the buffer so its reusabui when selected again
			}
		}
	}
	closesocket(cin);
	closesocket(lin);
	WSACleanup();
} 
