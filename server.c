#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#define PORT 1618
int main()
{
 int socketId, client;
 struct sockaddr_in server;
 int addLen = sizeof(server);
 char  filename[1024] = {0};
 
 server.sin_family = AF_INET;
 server.sin_port = htons(PORT);
 server.sin_addr.s_addr = INADDR_ANY;
 socketId = socket(AF_INET, SOCK_STREAM, 0);
 bind(socketId, (struct sockaddr *)&server, sizeof(server));
 
 while(1)
 {
	listen(socketId, 0);
	printf("Server ready\n");
	client = accept(socketId, (struct sockaddr *)&server, (socklen_t *)&addLen);
	printf(" Connection Established  \n");
	read(client, filename, 1024);
	printf("Client reqeusted for this file : %s\n", filename);
	printf("Processing request..........\n");

	FILE *fileptr;
	fileptr=fopen(filename,"r");
	if(fileptr==NULL)
	{
		printf("File Not Found!\n");
		int converted_number = htonl(-1);
		send(client, &converted_number, sizeof(converted_number),0);
		
	}
	else
	{
		fseek(fileptr, 0, SEEK_END);  
    		long res = ftell(fileptr);
    		fseek(fileptr, 0, SEEK_SET);
    		
    		char textToSend[res];
    		fread(textToSend,1, res, fileptr);
    		fclose(fileptr); 
		
		long converted_number = htonl(res);
		send(client, &converted_number, sizeof(converted_number),0);
		send(client, textToSend, res, 0);
		
	}
	printf(" Do you want to close the server? (press 1 to continue else press 0) ");
	int check=0;
	scanf("%d", &check);
	if(check==0)
	{
		close(socketId);
		close(client);
		break;
		exit(1);
	}
  }
}
