#ifndef NETWORK_H
#define NETWORK_H

int start_server(int port);
void handle_client(int client_socket, Database *db);
void* client_handler(void *arg);

#endif
