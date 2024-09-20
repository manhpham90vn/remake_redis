#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "db.h"
#include "network.h"

int main() {
    int port = 6379; // Redis thường sử dụng port này
    int server_socket = start_server(port);

    Database *db = create_database();
    printf("Server running on port %d\n", port);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int *client_socket = malloc(sizeof(int));
        *client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

        if (*client_socket < 0) {
            perror("Accept failed");
            free(client_socket);
            continue;
        }

        // Tạo thread cho mỗi client
        pthread_t tid;
        if (pthread_create(&tid, NULL, client_handler, client_socket) != 0) {
            perror("Failed to create thread");
            free(client_socket);
        }

        // Không cần đợi thread hoàn thành
        pthread_detach(tid);
    }

    free_database(db);
    close(server_socket);
    return 0;
}
