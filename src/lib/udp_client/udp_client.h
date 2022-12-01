#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "../socket/socket.h"

typedef struct udp_client_t {
    address_t *host;
    socket_t *socket;
    void (*send)(char data[]);
    char *(*receive)(void);
} udp_client_t;

udp_client_t *new_udp_client();
void free_udp_client(udp_client_t *self);

#endif