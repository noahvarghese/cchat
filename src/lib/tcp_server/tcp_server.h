#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <sys/socket.h>
#include "../address/address.h"
#include "../socket/socket.h"

typedef struct tcp_server_t {
    socket_t *socket;
    struct sockaddr *(*accept_connection)(tcp_server_t *self);
    void (*send)(tcp_server_t *self, char data[]);
    void (*send_to)(tcp_server_t *self, char data[], struct sockaddr *client);
    char *(*receive)(tcp_server_t *self);
    char *(*receive_from)(tcp_server_t *self, struct sockaddr *client);
} tcp_server_t;

tcp_server_t *new_tcp_server(const char host[], const char port[], address_family ip_version, int max_connections);
void free_tcp_server(tcp_server_t *self);

#endif