#include "./udp_client.h"

udp_client_t *new_udp_client(const char host[], const char port[], address_family ip_version) {
    int result;
    address_t *address;
    socket_t *socket;
    udp_client_t *self;

    address = new_address(host, port, ip_version, UDP);
    socket = new_socket(address, ip_version);

    self = malloc(sizeof(udp_client_t));
    if (self == NULL) {
        perror("Could not allocate memory for udp_client");
        exit(1);
    }

    self->host = address;
    self->socket = socket;
    self->receive = &socket->receive_data_from;
    self->send = &socket->send_data_to;

    return self;
}

void free_udp_client(udp_client_t *self) {
    free_socket(self->socket);
    free_address(self->host);
    free(self);
}