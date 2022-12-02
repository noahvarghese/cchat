#include <stdio.h>
#include "../lib/tcp_server/tcp_server.h"

int main(void) {
    tcp_server_t *tcp_server = new_tcp_server(0, "80", DUALSTACK, 100);

    struct sockaddr *client = tcp_server->accept_connection(tcp_server);

    char *data;
    data = tcp_server->receive_from(tcp_server, client);
    printf("%s\n", data);

    free_tcp_server(tcp_server);

    return 0;
}