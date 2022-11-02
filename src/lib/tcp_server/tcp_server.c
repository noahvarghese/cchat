#include "tcp_server.h"

static void send(char data[]) {
    // TODO: send data
}

static char *receive(void) {
    // TODO: receive data
    return "";
}


tcp_server_t *new_tcp_server(const char host[], const char port[]) {
    tcp_server_t *self;

    self = malloc(sizeof(tcp_server_t));

    if (self == NULL) {
        perror("could not allocate memory for tcp_server");
        exit(1);
    }
    
    self->server = new_server(host, port, DUALSTACK, TCP);

    // *** Listen ***

    int result;
    result = listen(self->server->socket, 10);
    if (result == -1) {
        perror("server failed to listen to socket");
        exit(1);
    }

    self->receive = &receive;
    self->send = &send;

    return self;
}

void free_tcp_server(tcp_server_t *self) {
    free_server(self->server);
    free(self);

    return;
}