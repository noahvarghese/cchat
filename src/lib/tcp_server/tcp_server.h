#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#define MAX_CONNECTIONS 100

#include <sys/socket.h>
#include "../address/address.h"
#include "../socket/socket.h"

typedef struct tcp_server_t {
    socket_t *socket;
    struct sockaddr clients[MAX_CONNECTIONS];
    void (*accept_connection)(void);
    void (*send_to_all)(char data[]);
    void (*send_to)(char data[]);
    char *(*receive_from_any)(void);
    char *(*receive_from)(void);
} tcp_server_t;

tcp_server_t *new_tcp_server(const char host[], const char port[], address_family ip_version);
void free_tcp_server(tcp_server_t *self);

#endif