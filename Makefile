all: server.o client.o
	gcc -o server ./serverDir/server.o
	gcc -o client ./clientDir/client.o

server.o:
	gcc -c -o ./serverDir/server.o ./serverDir/server.c

client.o:
	gcc -c -o ./clientDir/client.o ./clientDir/client.c

clean:
	rm server client ./serverDir/server.o ./clientDir/client.o a.out *~
