#include "server.h"

server_t *new_server(const char host[], const char port[], address_family ip_version, socket_type sock_type) {
    server_t *self;
    int result, socket_fd;
    struct addrinfo hints, *address;

    // *** Setup *** 

    memset(&hints, 0, sizeof(struct addrinfo));

    if (ip_version == DUALSTACK) {
        hints.ai_family = AF_INET6;
        hints.ai_flags = AI_PASSIVE;
    } else {
        hints.ai_family = ip_version;
    }

    hints.ai_socktype = sock_type;

    result = getaddrinfo(
        host,
        port,
        &hints,
        // [WARNING]: Using this may be a mistake as I do not know the lifetime of the variable
        &(address));

    if (result != 0) {
        perror("could not retrieve socket address info");
        exit(1);
    }

    // *** Create socket ***

    socket_fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
    if (socket_fd == -1) {
        perror("could not create socket");
        exit(1);
    }

    if (ip_version == DUALSTACK) {
        int option = 0;
        result = setsockopt(socket_fd, IPPROTO_IPV6, IPV6_V6ONLY, &option, sizeof(int));
        if (result == -1) {
            perror("failed to configure dualstack server");
            exit(1);
        }
    }

    // *** Bind socket ***

    result = bind(socket_fd, address->ai_addr, address->ai_addrlen);
    if (result == -1) {
        perror("could not bind socket");
        exit(1);
    }

    // *** Initialize socket_t struct ***

    self = malloc(sizeof(server_t));
    
    if (self == NULL) {
        perror("Unable to allocate memory for new socket");
        exit(1);
    }
    
    memset(self, 0, sizeof(server_t));
    
    self->socket = socket_fd;
    self->address = address;

    free(&address);

    return self;
}

void free_server(server_t *self)
{
    close(self->socket);
    freeaddrinfo(self->address);
    free(self);
    return;
}