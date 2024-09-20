#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "db.h"
#include "network.h"

void handle_client(int client_socket, Database *db) {
    char buffer[1024];
    int len;

    while (1) {
        len = read(client_socket, buffer, sizeof(buffer) - 1);

        if (len <= 0) {
            close(client_socket);
            break;
        }

        buffer[len] = '\0';

        char command[10], key[256], value[256];
        if (sscanf(buffer, "%s %s %s", command, key, value) >= 2) {
            if (strcmp(command, "SET") == 0) {
                set(db, key, value);
                write(client_socket, "OK\n", 3);
            } else if (strcmp(command, "GET") == 0) {
                const char *result = get(db, key);
                if (result) {
                    write(client_socket, result, strlen(result));
                    write(client_socket, "\n", 1);
                } else {
                    write(client_socket, "NULL\n", 5);
                }
            }
        }
    }
}

void* client_handler(void *arg) {
    int client_socket = *(int*)arg;
    Database *db = (Database*)((char*)arg + sizeof(int));
    handle_client(client_socket, db);
    free(arg);
    return NULL;
}

int start_server(int port) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    return server_socket;
}