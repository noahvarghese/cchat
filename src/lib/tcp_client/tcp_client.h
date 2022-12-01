#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "../socket/socket.h"

typedef struct tcp_client_t {
    socket_t *socket;
    void (*send)(char data[]);
    char *(*receive)(void);
} tcp_client_t;

tcp_client_t *new_tcp_client();
void free_tcp_client(tcp_client_t *self);

#endif