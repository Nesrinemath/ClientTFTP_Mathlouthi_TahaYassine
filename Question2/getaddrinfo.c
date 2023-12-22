//
// Created by ensea on 22/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

/*int main(int argc, char **argv) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 4) {
        printf("Wrong usage: gettftp filename host port\n");
        exit(EXIT_SUCCESS);
    }

    // Extract command-line arguments
    const char *filename = argv[1];
    const char *host = argv[2];
    const char *port = argv[3];
    printf("gettftp Server: Filename: %s, Host: %s, Port: %s \n", filename, host, port);
    // Prepare data structures for address resolution
    struct addrinfo *result;
    struct addrinfo hints;

    // Initialize hints structure to specify preferences for address resolution
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        // Use IPv4 addresses
    hints.ai_socktype = SOCK_DGRAM;   // Use UDP socket type
    hints.ai_protocol = IPPROTO_UDP;  // Use UDP protocol
// Perform address resolution
    int status = getaddrinfo(argv[2], argv[3], &hints, &result);
    if (status != 0) {
        // Display an error message if host resolution fails
        printf("Error: Unable to find the host %s\n", argv[2]);
    }

    // Further code for using the result of address resolution would typically go here

   int status = getaddrinfo(argv[2], argv[3], &hints, &result);
if (status != 0) {
    printf("we can't find the host %s\n", argv[2]);
} else {
    // Loop through the results and print IP addresses
    struct addrinfo *p;
    char ipstr[INET_ADDRSTRLEN];

    return 0;
}*/