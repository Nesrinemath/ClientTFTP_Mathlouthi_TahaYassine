
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 20
#define MAXSIZE 512


int main(int argc, char *argv[]) {
    // Retrieve command-line arguments
    char* host = argv[1];
    char* port = argv[2];
    char* fileName = argv[3];

    // Check for the correct number of arguments
    if (argc != 4) {
        printf("Incorrect number of arguments: %d instead of 3 \n", argc);
        return(EXIT_FAILURE);
    }

    // Print information about the file transfer
    printf("Sending %s to host: %s@%s \n", fileName, host, port);

    // Set up address information structure
    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_UDP;
    int status;
    status = getaddrinfo(host, port, &hints, &res);
    if (status == -1) {
        printf("Could not find host %s\n", argv[1]);
    }
    // Prepare buffers for data
    char buffer[MAXSIZE] = {0};
    char buffer_receive[MAXSIZE] = {0};
    buffer[1] = 1; // Set a specific value in the buffer
    sprintf(buffer + 2, "%s", fileName);
    sprintf(buffer + 3 + strlen(fileName), "NETASCII");
    // Create a UDP socket
    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    int bufferSize = 12 + strlen(fileName);

    // Send the request to the server
    int snd = sendto(sock, buffer, bufferSize, 0, res->ai_addr, res->ai_addrlen);
    if (snd == -1) {
        printf("Error sending the request.\n");
        return EXIT_FAILURE;
    }

    // Request sent successfully

    // Receive file data from the server
    struct sockaddr adresse;
    socklen_t sizeAdress = sizeof(adresse);
    int nbByte;
    // Create or open a file for writing
    FILE *file;
    struct stat info;
    if (stat(fileName, &info) != 0) {
        file = fopen(fileName, "w");
    } else {
        printf("This file already exists.\n");
        return EXIT_SUCCESS;
    }
    int block = 1;
    char buff_ok[MAXSIZE] = {0};
    int snd2;

    do {
        // Receive data from the server
        nbByte = recvfrom(sock, buffer_receive, MAXSIZE, 0, &adresse, &sizeAdress);
        if (nbByte == -1) {
            printf("Error receiving data.\n");
            return EXIT_FAILURE;
        }
        printf("Just received %d bytes\n", nbByte);
        // Handle server response
        if (buffer_receive[0] == 0 && buffer_receive[1] == 5) {
            printf("Error received from the server during block #%d:\n%s\n", buffer_receive[3], buffer_receive + 4);
            exit(EXIT_SUCCESS);
        }
        if (buffer_receive[0] == 0 && buffer_receive[1] == 3) {
            buff_ok[1] = 4;
            buff_ok[2] = 0;
            buff_ok[3] = block;
            block++;
            // Send confirmation to the server that data is received
            snd2 = sendto(sock, buff_ok, 4, 0, &adresse, sizeAdress);
            if (snd2 == -1) {
                printf("Error sending confirmation of data acquisition.\n");
                return EXIT_FAILURE;
            }
        }
        // Write received data to the file
        fwrite(buffer_receive + 4, sizeof(char), nbByte - 4, file);
    } while (nbByte == 512);

    // Close the file
    fclose(file);

    return 0;
}