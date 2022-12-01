#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#define MAX_CONNECTIONS 100

#include <sys/socket.h>
#include "../address/address.h"
#include "../socket/socket.h"

typedef struct udp_server_t {
    socket_t *socket;
    struct sockaddr clients[MAX_CONNECTIONS];
    void (*send_to)(char data[]);
    char *(*receive_from)(void);
} udp_server_t;

udp_server_t *new_udp_server(const char host[], const char port[], address_family ip_version);
void free_udp_server(udp_server_t *self);

#endif