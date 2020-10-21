### COSC 3342 Fall 2020 - Socket Project

This is my code for the socket project for Networking class.

======================================

Compile the code:
> gcc -g -o socket project.c randperm.c

Run the code:
> ./socket (portnumber)

~~Send demo command using netcat:~~
~~> echo -n "payload" | nc (ip addr of server) (port)~~

Use telnet to connect to ip and port for 2-way communication
> telnet <ip addr of server> <port>
