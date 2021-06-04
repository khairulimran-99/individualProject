#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <string.h>     //strlen
#include <unistd.h>      //write
#include <stdlib.h>

int main(int argc , char *argv[])
{
        int socket_desc;
        struct sockaddr_in server;
        char *message = malloc (1000);
        char server_reply[200];

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Socket Error");
        }

        server.sin_addr.s_addr = inet_addr("192.168.56.103"); //Please enter the ip address >
        server.sin_family = AF_INET;
        server.sin_port = htons(8888);

        //Connect to remote server
        if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("connect error");
                return 1;
        }

        puts("Connected to Server \n");

        //Send some data
        while(1)
        {
                printf("Client: ");
                fgets(message, 100, stdin);
                send(socket_desc, message, 1000, 0);
                break;
        }
        if(send(socket_desc, message,strlen(message), 0) <0)
        {
                puts("Send Failed");
                return 1;
        }
        puts("Send to server\n");



         //Receive a reply from the server
        if( recv(socket_desc, server_reply , 2000 , 0) < 0)
        {
                puts("recv failed");
        }

        printf("Server: %s", server_reply);
        puts("Server reply\n");


        return 0;
}
