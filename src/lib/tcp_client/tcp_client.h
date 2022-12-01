#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "../socket/socket.h"

typedef struct tcp_client_t {
    socket_t *socket;
    void (*accept)(tcp_client_t *self);
    void (*send)(tcp_client_t *self, char data[]);
    void (*send_to)(tcp_client_t *self, char data[], struct sockaddr *server);
    char *(*receive)(tcp_client_t *self);
    char *(*receive_from)(tcp_client_t *self, struct sockaddr *server);
} tcp_client_t;

tcp_client_t *new_tcp_client(const char host[], const char port[], address_family ip_version);
void free_tcp_client(tcp_client_t *self);

#endif