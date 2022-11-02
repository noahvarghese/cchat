BINARY=cchat
LIB_SRC=$(wildcard ./lib/**/*.c)

CLIENT_BIN=$(BINARY)_client
CLIENT_SRC=./client/main.c $(LIB_SRC)
CLIENT_OBJS=$(CLIENT_SRC:.c=.o)

SERVER_BIN=$(BINARY)_server
SERVER_SRC=./server/main.c $(LIB_SRC)
SERVER_OBJS=$(SERVER_SRC:.c=.o)

GLIBS=
CCFLAGS=-Werror -Wall

clean:
	rm ./*.o

dirs:
	mkdir -p ./bin

%.o: %.c
		$(CC) -o $@ -c $< $(CCFLAGS)

client: $(CLIENT_OBJS)
	$(LD) -o ./bin/$(CLIENT_BIN) $^

server: $(SERVER_OBJS)
	$(LD) -o ./bin/$(SERVER_BIN) $^