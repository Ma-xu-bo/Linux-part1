all:client server
 client:tcp_client.o tcp_process.o
	gcc -o  client tcp_process.o tcp_client.o
 server:tcp_process.o tcp_server.o
	gcc -o server tcp_process.o tcp_server.o
tcp_client.o:tcp_client.c tcp_process.c
	gcc -o tcp_client.o tcp_client.c tcp_process.c
tcp_server.o:tcp_server.c tcp_process.c
	gcc -o tcp_server.o tcp_server.c tcp_process.c
tcp_process.o:tcp_process.c
	gcc -o tcp_process.o tcp_process.c
clean:
	rm -f client server *.c

