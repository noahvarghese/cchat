#include "./tcp_client.h"

tcp_client_t *new_tcp_client(const char host[], const char port[], address_family ip_version) {
    int result;
    address_t *address;
    socket_t *socket;
    tcp_client_t *self;

    address = new_address(host, port, ip_version, TCP);
    socket = new_socket(address, ip_version);

    socket->connect_to(socket, address);

    self = malloc(sizeof(tcp_client_t));
    if (self == NULL) {
        perror("Could not allocate memory for tcp_client");
        exit(1);
    }

    self->socket = socket;
    self->receive = &socket->receive_data_from_any;
    self->send = &socket->send_data_to_all;

    free_address(host);

    return self;
}

void free_tcp_client(tcp_client_t *self) {
    free_socket(self->socket);
    free(self);
}