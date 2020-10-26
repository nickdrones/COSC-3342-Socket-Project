### COSC 3342 Fall 2020 - Socket Project

This is my code for the socket project for Networking class.

======================================

Compile the code:
> gcc -g -o socket project.c randperm.c

Run the code:
> ./socket (portnumber)

Use telnet to connect to ip and port for 2-way communication
> telnet (ip addr of server) (port)

======================================

Once server is connected, you can play a card game!
Available Commands:
- deal (shuffles the deck and deals you all 52 cards in the following format: "Card (num 0-51 ordered):(card number 0-51 randomized)")