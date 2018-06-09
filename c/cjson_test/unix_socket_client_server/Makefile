cc=gcc

all: server client
server: server.o cJSON.o
	$(cc) $^ -o $@
client: client.o cJSON.o
	$(cc) $^ -o $@
%.o:%.c
	$(cc) -c $< -o $@
clean:
	rm *.o
	rm client
	rm server
