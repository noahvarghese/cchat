#include "tcp_server.h"

static struct sockaddr *accept_connection(tcp_server_t *self) {
    struct sockaddr *client;
    client = self->socket->accept_connection(self->socket);
    return client;
}

static void send_data_to(tcp_server_t *self, const char data[], struct sockaddr *client) {
    self->socket->send_to(self->socket, data, client);
}

static void send_data(tcp_server_t *self, const char data[]) {
    self->socket->send(self->socket, data);
}

static char *receive_data_from(tcp_server_t *self, struct sockaddr *client) {
    char *data;
    data = self->socket->receive_from(self->socket, client);
    return data;
}

static char *receive_data(tcp_server_t *self) {
    char *data;
    data = self->socket->receive(self->socket);
    return data;
}

tcp_server_t *new_tcp_server(const char host[], const char port[], address_family ip_version, int max_connections) {
    tcp_server_t *self;    
    socket_t *socket;
    address_t *address;

    address = new_address(host, port, ip_version, TCP);
    socket = new_socket(address, ip_version);

    socket->bind(socket, address);
    socket->listen(socket, max_connections);

    self = malloc(sizeof(tcp_server_t));
    if (self == NULL) {
        perror("could not allocate memory for tcp_server");
        exit(1);
    }

    self->socket = socket;
    self->accept_connection = &accept_connection;
    self->send = &send_data;
    self->send_to = &send_data_to;
    self->receive= &receive_data;
    self->receive_from = &receive_data_from;

    free_address(address);

    return self;
}

void free_tcp_server(tcp_server_t *self) {
    free_socket(self->socket);
    free(self);
}