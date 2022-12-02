#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "../socket/socket.h"

typedef struct udp_client_t {
    address_t *host;
    socket_t *socket;
    void (*send_to)(struct udp_client_t *self, char data[], struct sockaddr *server);
    char *(*receive_from)(struct udp_client_t *self, struct sockaddr *server);
} udp_client_t;

udp_client_t *new_udp_client(const char host[], const char port[], address_family ip_version);
void free_udp_client(udp_client_t *self);

#endif