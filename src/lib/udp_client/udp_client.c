#include "./udp_client.h"

static char *receive_data_from(udp_client_t *self, struct sockaddr *server) {
    char *data;
    data = self->socket->receive_from(self->socket, server);
    return data;
}

static void send_data_to(udp_client_t *self, char data[], struct sockaddr *server) {
    self->socket->send_to(self->socket, data, server);
}

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
    self->receive_from = &receive_data_from;
    self->send_to = &send_data_to;

    return self;
}

void free_udp_client(udp_client_t *self) {
    free_socket(self->socket);
    free_address(self->host);
    free(self);
}