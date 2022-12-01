#include "tcp_server.h"

tcp_server_t *new_tcp_server(const char host[], const char port[], address_family ip_version) {
    tcp_server_t *self;    
    socket_t *socket;
    address_t *address;

    address = new_address(host, port, ip_version, TCP);
    socket = new_socket(address, ip_version);

    socket->bind_address(socket, address);
    socket->start_listening(socket, MAX_CONNECTIONS);

    self = malloc(sizeof(tcp_server_t));
    if (self == NULL) {
        perror("could not allocate memory for tcp_server");
        exit(1);
    }

    self->socket = socket;
    self->accept_connection = &socket->accept_connection;
    self->send_to = &socket->send_data_to;
    self->send_to_all = &socket->send_data_to_all;
    self->receive_from = &socket->receive_data_from;
    self->receive_from_any = &socket->receive_data_from_any;

    free_address(address);

    return self;
}

void free_tcp_server(tcp_server_t *self) {
    free_socket(self->socket);
    free(self);
}