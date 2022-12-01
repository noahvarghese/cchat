#ifndef SOCKET_H
#define SOCKET_H

#define MAX_PACKET_SIZE 65535


#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../address/address.h"

/**
 * Client in the AF_INET family would connect/send/receive (if UDP then no connect is necessary)
 * Servers in the AF_INET family would accept/send/receive/bind/listen (if UDP then no accept necessary)
*/
typedef struct socket_t {
    int fd;
    void (*bind)(socket_t *self, address_t *address);
    void (*connect_to)(socket_t *self, address_t *host);
    void (*listen)(socket_t *self, int connection_limit);
    void (*send_to)(socket_t *self, const char data[], struct sockaddr *destination);
    void (*send)(socket_t *self, const char data[]);
    char *(*receive_from)(socket_t *self, struct sockaddr *source);
    char *(*receive)(socket_t *self);
    struct sockaddr *(*accept_connection)(socket_t *self);
} socket_t;

socket_t *new_socket(address_t *address, address_family ip_version);
void free_socket(socket_t *socket_fd);

#endif