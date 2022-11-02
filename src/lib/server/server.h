#ifndef SOCKET_H
#define SOCKET_H

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef enum
{
    IPV4 = AF_INET,
    IPV6 = AF_INET6,
    DUALSTACK = AF_INET6 + AF_INET,
} address_family;

typedef enum 
{
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM,
} socket_type;

typedef struct server_t {
    /**
     * File descriptor 
     */
    int socket;
    struct addrinfo *address;
} server_t;

server_t *new_server(const char host[], const char port[], address_family ip_version, socket_type type);
void free_server(server_t *self);

#endif