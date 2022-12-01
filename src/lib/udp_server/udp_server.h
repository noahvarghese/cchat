#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <sys/socket.h>
#include "../address/address.h"
#include "../socket/socket.h"

typedef struct udp_server_t {
    socket_t *socket;
    void (*send_to)(udp_server_t *self, char data[], struct sockaddr *client);
    char *(*receive_from)(udp_server_t *self, struct sockaddr *client);
} udp_server_t;

udp_server_t *new_udp_server(const char host[], const char port[], address_family ip_version);
void free_udp_server(udp_server_t *self);

#endif