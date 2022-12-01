# Cchat

Console chat application.
Supports connections via TCP and UDP sockets over both IPV4 and IPV6 (dualstack configuration).

## Expected Behaviour

- supports IPV4 and IPV6
- supports TCP and UDP
- server will accept connections on a given port
- when a new client connects a welcome message will be broadcast to all clients
- any message a client sends will be broadcast to all clients
- when a client disconnects a goodbye message will be broadcast to all clients
