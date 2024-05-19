#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    int server_socket, client_socket;
    int num1 = 0,num2 =0;
    struct sockaddr_un server_addr, client_addr;

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");

    unlink(server_addr.sun_path); // Remove any existing socket file

    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    while (1) {
        char ch;
        socklen_t clen = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &clen);
        if (client_socket == -1) {
            perror("Accept failed");
            continue; // Continue to the next iteration instead of exiting
        }

        if (read(client_socket, &num1, sizeof(int)) == -1) {
            perror("Read failed");
            close(client_socket);
            continue; // Continue to the next iteration instead of exiting
        }
        else
        printf("got num1 %d\n",num1);


        if (read(client_socket, &num2, sizeof(int)) == -1) {
            perror("Read failed");
            close(client_socket);
            continue; // Continue to the next iteration instead of exiting
        }
        else
        printf("got num2 %d\n",num2);

       // printf("Server: I received %c from client!\n", ch);
       // ch++;
        num1 += num2;
        if (write(client_socket, &num1, sizeof(int)) == -1) {
            perror("Write failed");
            close(client_socket);
            continue; // Continue to the next iteration instead of exiting
        }
        else
        printf("addition sent\n");

        close(client_socket);
    }

    close(server_socket);
    unlink(server_addr.sun_path); // Cleanup socket file on exit
    exit(EXIT_SUCCESS);
}


