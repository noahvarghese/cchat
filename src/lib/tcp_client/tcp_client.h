#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "../socket/socket.h"

typedef struct tcp_client_t {
    socket_t *socket;
    void (*accept)(struct tcp_client_t *self);
    void (*send)(struct tcp_client_t *self, const char data[]);
    void (*send_to)(struct tcp_client_t *self, const char data[], struct sockaddr *server);
    char *(*receive)(struct tcp_client_t *self);
    char *(*receive_from)(struct tcp_client_t *self, struct sockaddr *server);
} tcp_client_t;

tcp_client_t *new_tcp_client(const char host[], const char port[], address_family ip_version);
void free_tcp_client(tcp_client_t *self);

#endif