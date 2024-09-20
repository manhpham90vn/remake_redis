#ifndef NETWORK_H
#define NETWORK_H

int start_server(int port);
void handle_client(int client_socket, Database *db);

#endif
