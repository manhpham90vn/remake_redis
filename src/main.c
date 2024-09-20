#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "db.h"
#include "network.h"

int main() {
    int port = 6379;
    int server_socket = start_server(port);

    Database *db = create_database();
    printf("Server running on port %d\n", port);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(client_socket, db);
    }

    free_database(db);
    close(server_socket);
    return 0;
}
