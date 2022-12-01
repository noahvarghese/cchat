#include "./socket.h"

static void start_listening(socket_t *self, int connection_limit) {
    int result;
    result = listen(self->fd, connection_limit);
    if (result == -1) {
        perror("server failed to listen to socket");
        exit(1);
    }
}

static void send_data_to(socket_t *self, const char data[], struct sockaddr *destination){
    int result;
    result = sendto(self->fd, data, strlen(data), 0, destination, sizeof(struct sockaddr));
    if (result == -1) {
        perror("Failed to send data");
        exit(1);
    }
};

static char *receive_data_from(socket_t *self, struct sockaddr *source) {
    char *data;
    int size;

    data = malloc(MAX_PACKET_SIZE);
    if (data == NULL) {
        perror("Unable to allocate memory to receive message into");
        exit(1);
    }

    size = recvfrom(self->fd, data, MAX_PACKET_SIZE, 0, source, sizeof(struct sockaddr));
    if (size == -1) {
        perror("Unable to receive data");
        exit(1);
    }
    
    // Make sure data is null terminated
    if (data[size] == "\0" || data[size] == NULL || data == 0) {
        return data;
    }

    data[size] = "\0";

    return data;
};

static struct sockaddr *accept_connection(socket_t *self) {
    int result;
    struct sockaddr *address;

    result = accept(self->fd, address, sizeof(struct sockaddr));

    if (result == -1) {
       perror("Failed to accept incoming connections");
       exit(1);
    }

    return address;
};

static void connect_to(socket_t *self, address_t *host) {
    int result;
    result = connect(self->fd, host->ai_addr, host->ai_addrlen);
    if (result == -1) {
        perror("could not bind socket");
        exit(1);
    }
}

static void bind_address(socket_t *self, address_t *address) {
    int result;
    result = bind(self->fd, address->ai_addr, address->ai_addrlen);
    if (result == -1) {
        perror("could not bind socket");
        exit(1);
    }
}

static void configure_dualstack(int socket_fd) {
    int result;
    int option= 0;

    result = setsockopt(socket_fd, IPPROTO_IPV6, IPV6_V6ONLY, &option, sizeof(int));

    if (result == -1) {
        perror("failed to configure dualstack server");
        exit(1);
    }
}

/**
 * It is up to the consumer to recognize which IP version they are using
 * as the opening up a client socket would be either TCP or UDP
 * Also see https://stackoverflow.com/questions/26507532/can-bind-socket-to-remote-address#:~:text=You%20cannot%20bind()%20to,not%20in%20the%20AF_INET%20family.
 * re binding to a remote socket
*/
socket_t *new_socket(address_t *address, address_family ip_version) {
    socket_t *self;
    int socket_fd, result;

    socket_fd = socket(address->ai_family, address->ai_socktype, address->ai_protocol);

    if (socket_fd == -1) {
        perror("could not create socket");
        exit(1);
    }

    if (ip_version == DUALSTACK) {
        configure_dualstack(socket);
    }

    self = malloc(sizeof(socket_t));
    if (self == NULL) {
        perror("Could not allocate memory for socket");
        exit(1);
    }

    self->fd = socket_fd;
    self->start_listening = &start_listening;
    self->accept_connection = &accept_connection;
    self->send_data_to = &send_data_to;
    self->receive_data_from = &receive_data_from;
    self->bind_address = &bind_address;
    self->connect_to = &connect_to;

    return self;
}

void free_socket(socket_t *self) {
    close(self->fd);
    free(self);
}