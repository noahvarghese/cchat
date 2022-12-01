#include "./address.h"

address_t *new_address(const char host[], const char port[], address_family ip_version, socket_type sock_type) {
    int result;
    address_t hints, *address;

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
        &address);

    if (result != 0) {
        perror("could not retrieve socket address info");
        exit(1);
    }

    return address;
}

void free_address(address_t *address) {
    freeaddrinfo(address);
}