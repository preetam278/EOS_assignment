#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    int client_socket;
    int num1 = 0 ,num2 = 0;
    struct sockaddr_un server_addr;

    char ch = 'C';

    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    printf("please Enter the two numbers\n");
    scanf("%d %d",&num1,&num2);
    if (write(client_socket, &num1, sizeof(int)) == -1) {
        perror("Write failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    else
    printf("Num1 sent\n");


    if (write(client_socket, &num2, sizeof(int)) == -1) {
        perror("Write failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    else
    printf("Num2 sent\n");

    if (read(client_socket, &num1, sizeof(int)) == -1) {
        perror("Read failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    else
    printf("Addition of the two numbers is %d\n",num1);

  //  printf("Client: I received %c from server!\n", ch);
    close(client_socket);
    exit(EXIT_SUCCESS);
}


