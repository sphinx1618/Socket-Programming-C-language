#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#define PORT 1618
int main()
{
	 while(1)
	 {
	 	 int sock = 0;
	      	 struct sockaddr_in server;
	 	 char filename[1024];
	 	 
	 	 server.sin_family = AF_INET; 
		 server.sin_port = htons(PORT);
		 server.sin_addr.s_addr = INADDR_ANY;
		 sock = socket(AF_INET, SOCK_STREAM, 0);
	 	 connect(sock, (struct sockaddr * )&server, sizeof(server));
	 	 printf("Enter the name of file you want to download :\n");	
		 scanf("%s", &filename);   
		 send(sock, filename, strlen(filename), 0);
		 printf("Request sent !\nWaiting for the file \n");
		 
		 long size;
		 read(sock, &size, sizeof(size));
		 size=ntohl(size);
		 
		 		
		 if(size==-1)
		 {
			printf("File Not Found! \npress 1 to enter the name again ,else press 0:\n");
			long check=2;
			scanf("%d", &check);
			if(check==0)
			{
				close(sock);
				break;
						
			}
				
		}
		if(size!=-1)
		{
			char filedata[size];
			read(sock, filedata, size);
			 printf("Input size is  %d\n",size);
			 FILE *fileptr;
	 	 	 fileptr=fopen("recieved.txt","w+");
			 if(fileptr==NULL)
			 {
			 	printf("Error Opening the download file\n");
			 	break;
			 	exit(0);
			 }
			 
			 
			 fwrite(filedata, 1, size,fileptr);
			 fclose(fileptr);
			 printf("File recieved.\n");
			 printf("Closing the connection \n");
			 close(sock);
			 break;
		}	
	}
}
