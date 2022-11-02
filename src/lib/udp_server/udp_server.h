#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "../server/server.h"

typedef struct udp_server_t {
    struct server_t *server;
    void (*send)(char data[]);
    char *(*receive)(void);
} udp_server_t;

udp_server_t *new_udp_server(const char host[], const char port[]);
void free_udp_server(udp_server_t *self);

#endif