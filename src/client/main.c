#include <stdio.h>
#include "../lib/tcp_client/tcp_client.h"
#include "../lib/udp_client/udp_client.h"

int main(void) {
    tcp_client_t *tcp_client = new_tcp_client(0, "80", DUALSTACK);

    tcp_client->send(tcp_client, "hello");

    char *data;
    data = tcp_client->receive(tcp_client);
    printf("%s\n", data);

    free_tcp_client(tcp_client);

    return 0;
}