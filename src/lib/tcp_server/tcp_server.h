#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "../server/server.h"

typedef struct tcp_server_t {
    struct server_t *server;
    void (*send)(char data[]);
    char *(*receive)(void);
    // TODO: accept connections
} tcp_server_t;

tcp_server_t *new_tcp_server(const char host[], const char port[]);
void free_tcp_server(tcp_server_t *self);

#endif