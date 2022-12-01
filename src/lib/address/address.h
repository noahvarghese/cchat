#ifndef ADDRESS_H
#define ADDRESS_H

#include <netdb.h>

typedef struct addrinfo address_t;

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

address_t *new_address(const char host[], const char port[], address_family ip_version, socket_type sock_type);
void free_address(address_t *address);

#endif