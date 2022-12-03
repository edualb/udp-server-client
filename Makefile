.PHONY: build run-server run-client build-client build-server

build-server:
	gcc udpserver.c -o server

build-client:
	gcc udpclient.c -o client

build: build-server build-client
	
run-server: build-server
	./server 4457

run-client: build-client
	./client 127.0.0.1 4457