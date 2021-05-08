#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


void func(int socket_desc){

        char buff[80];
        int j;

        for(;;)
        {
                bzero(buff,80);

                //read msg from client
                read(socket_desc, buff, sizeof(buff));

                //print buffer
                printf("Client %s To Client: ", buff);
                bzero(buff,80);

                j=0;

                //copy server msg
                while ((buff[j++] = getchar()) != '\n');

                //send buffer to client
                write(socket_desc, buff, sizeof(buff));

                //chat ended, (exit)
                if (strncmp("exit", buff, 4) == 0)
                {
                        printf("Server exit...\n");
                        break;
                }
        }
}



int main (void) {

	int socket_desc;
	struct sockaddr_in server, client;
	int conn;
	int L;

	//socket (create)
	socket_desc = socket (AF_INET, SOCK_STREAM,0);

	if(socket_desc == -1) {
		printf("Could not create socket...\n");
	}
	else
	{	printf("Socket successfully created...\n");
		bzero(&server, sizeof(server));
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = htonl(INADDR_ANY);


	//bind new socket
	if (( bind(socket_desc, (struct sockaddr *)&server, sizeof(server))) != 0)
	{
		printf("Socket binding failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded...\n");


	//listening process

	if(( listen (socket_desc,5)) != 0)
	{
		printf("Failed...\n");
		exit(0);
	}
	else
	{
		printf("Server is listening...\n");
		L = sizeof(client);
	}

	//data accepted from client

	conn = accept(socket_desc, (struct sockaddr *)&client, &L);

	if ( conn < 0 )
	{
		printf("Server accept failed...\n");
		exit(0);
	}
	else
		printf("Server accept the client...\n");


	//func
	func(conn);

	//close
	close(socket_desc);
}

/*
void func(int socket_desc){

	char buff[80];
	int j;

	for(;;)
	{
		bzero(buff,80);

		//read msg from client
		read(socket_desc, buff, sizeof(buff));

		//print buffer
		printf("Client %s :", buff);
		bzero(buff,80);

		j=0;

		//copy server msg
		while ((buff[j++] = getchar()) != '\n');

		//send buffer to client
		write(socket_desc, buff, sizeof(buff));

		//chat ended, (exit)
		if (strncmp("exit", buff, 4) == 0)
		{
			printf("Server exit...\n");
			break;
		}
	}
}
*/
