#include "udp_server.h"

static void send(udp_server_t *upd_server, char data[]) {
    // TODO: send data
    // sendto(upd_server->server->socket, data, strlen(data), 0, );
}

static char *receive(void) {
    // TODO: receive data
    return "";
}


udp_server_t *new_udp_server(const char host[], const char port[]) {
    udp_server_t *self;

    self = malloc(sizeof(udp_server_t));

    if (self == NULL) {
        perror("could not allocate memory for udp_server");
        exit(1);
    }
    
    self->server = new_server(host, port, DUALSTACK, UDP);
    self->receive = &receive;
    self->send = &send;

    return self;
}

void free_udp_server(udp_server_t *self) {
    free_server(self->server);
    free(self);

    return;
}