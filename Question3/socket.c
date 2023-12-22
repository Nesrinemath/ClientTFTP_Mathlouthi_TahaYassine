#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#define MAX_SIZE_BUFFER 1024
#include <arpa/inet.h>

int main(int argc, char **argv) {
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
        exit(EXIT_FAILURE);

    }
    char rrq[MAX_SIZE_BUFFER]={0};

    const char opcode[2]={0x00,0x01};
    const char nameFile[] = "nesrine.txt";
    const char separator1[1]={0x00};
    const char netascii[]="netascii";
    const char separator2[1]={0x00};

    memcpy(rrq, opcode, 2);
    memcpy(rrq+2,nameFile,strlen(nameFile));
    memcpy(rrq+2+strlen(nameFile),separator1,1);
    memcpy(rrq+3+strlen(nameFile),netascii, strlen(netascii));
    memcpy(rrq+3+strlen(nameFile)+ strlen(netascii),separator2,1);

    int sock = socket(result -> ai_family, result -> ai_socktype, result -> ai_protocol); //sendto() is to send data on a socket
    ssize_t send=sendto(sock, rrq, strlen(nameFile)+ strlen(netascii)+4 , 0, result ->ai_addr, result->ai_addrlen);
    if (send ==-1){
        printf("Erreur de l'envoi de la demande");
        exit(EXIT_FAILURE);
    }
    return 0;
}

  /*  //Loop through the results and print IP addresses
    struct addrinfo *p;
    char ipstr[INET_ADDRSTRLEN];

    for (p = result; p != NULL; p = p->ai_next) {
        void *addr;

        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
            addr = &(ipv4->sin_addr);
        }

        // Convert the IP to a string and print it
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("IP Address: %s\n", ipstr);
    }// Free the memory allocated for address information after using it
    freeaddrinfo(result);

// Define a buffer for the RRQ (Read Request) message
    char rrq[MAX_SIZE_BUFFER] = {0};

// Format the RRQ message with the specified filename
    sprintf(rrq, " \1 %s octets", argv[1]);

    // Create a socket using the address information obtained from the result structure
    int sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

// Check if the socket creation was successful
    if (sock == -1) {
        perror("Error creating socket");
        freeaddrinfo(result); // Free the memory allocated for address information
        exit(EXIT_FAILURE);
    }// Use sendto() to send the RRQ message on the socket
    ssize_t send_result = sendto(sock, rrq, strlen(rrq), 0, result->ai_addr, result->ai_addrlen);

// Check if the send operation encountered an error
    if (send_result == -1) {
        perror("Error sending the request");
        close(sock); // Close the socket in case of an error
        freeaddrinfo(result); // Free the memory allocated for address information
        exit(EXIT_FAILURE);}

// Close the socket after sending the message
    close(sock);

// Free the memory allocated for address information after using it
    freeaddrinfo(result);
        return 0;}*/