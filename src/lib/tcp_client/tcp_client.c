#include "./tcp_client.h"

static void send_data(tcp_client_t *self, const char data[]) {
    self->socket->send(self->socket, data);
}

static void send_data_to(tcp_client_t *self, const char data[], struct sockaddr *server) {
    self->socket->send_to(self->socket, data, server);
}

static char *receive_data(tcp_client_t *self) {
    char *data;
    data = self->socket->receive(self->socket);
    return data;
}

static char *receive_data_from(tcp_client_t *self, struct sockaddr *server) {
    char *data;
    data = self->socket->receive_from(self->socket, server);
    return data;
}

tcp_client_t *new_tcp_client(const char host[], const char port[], address_family ip_version) {
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
    self->receive = &receive_data;
    self->receive_from = &receive_data_from;
    self->send = &send_data;
    self->send_to = &send_data_to;

    free_address(address);

    return self;
}

void free_tcp_client(tcp_client_t *self) {
    free_socket(self->socket);
    free(self);
}