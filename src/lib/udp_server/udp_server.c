#include "udp_server.h"

static void send_data_to(udp_server_t *self, char data[], struct sockaddr *client) {
    self->socket->send_to(self->socket, data, client);
}

static void receive_data_from(udp_server_t *self, struct sockaddr *client) {
    char *data;
    data = self->socket->receive_from(self->socket, client);
    return data;
}

udp_server_t *new_udp_server(const char host[], const char port[], address_family ip_version) {
    udp_server_t *self;
    socket_t *socket;
    address_t *address;

    address = new_address(host, port, ip_version, UDP);
    socket = new_socket(address, ip_version);

    socket->bind(socket, address);

    self = malloc(sizeof(udp_server_t));
    if (self == NULL) {
        perror("could not allocate memory for udp_server");
        exit(1);
    }

    self->socket = socket;
    self->send_to = &send_data_to;
    self->receive_from = &receive_data_from;

    free_address(address);

    return self;
}

void free_udp_server(udp_server_t *self) {
    free_socket(self->socket);
    free(self);
}