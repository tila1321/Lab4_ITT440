#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h> //inet_addr

void func (int socket_desc) {

        int i;
        char buff[80];

        for(;;)
        {

                bzero(buff, sizeof(buff));
                printf("Enter messages: ");
                i=0;

                while((buff[i++] = getchar()) != '\n');
                {
                        write(socket_desc,buff, sizeof(buff));
                        bzero(buff, sizeof(buff));
                        read(socket_desc, buff, sizeof(buff));
                        printf("Server: %s", buff);

                        if((strncmp(buff, "exit", 4)) == 0 )
                        {
                                printf("Client exit...\n");
				break;
			}
                }
        }
}


int main (void){

	int socket_desc, conn;
	struct sockaddr_in server, client;

	//socket ( create )
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_desc == -1) {
		printf("Could not create socket...\n");
		exit(0);
	}
	else {
		printf("Socket successfully created....\n");
		bzero(&server, sizeof(server));
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = inet_addr("192.168.56.109");

	//connect server and client socket
	if (connect(socket_desc, (struct sockaddr *)&server, sizeof (server)) !=0)
	{
		printf("Connection with server is failed...\n");
		exit(0);
	}
	else
		printf("Connected to the server...\n");



	//func fr chat

	func(socket_desc);

	//close
	close(socket_desc);
}

/*
void func (int socket_desc) {

	int i;
	char buff[80];

	for(;;)
	{

		bzero(buff, sizeof(buff));
		printf("Enter messages: ");
		i=0;

		while(buff[i++] = getchar()) != '\n');
		{
			write(socket_desc,buff, sizeof(buff));
			bzero(buff sizeof(buff));
			read(socket_desc, buff, sizeof(buff));
			printf("Server: %s", buff);

			if((strncmp(buff, "exit", 4)) == 0 )
			{
				printf("Client exit...\n");
			}
	}
}
*/
