/*
    Copyright 2022 Ashutosh Singh (0xAshutosh)

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "server.h"
#include "request.h"
#include "files.h"
#include "http_server.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/fcntl.h>


#define ROOT "./www"

char* itoa(int num, char* str) {
    if (str == NULL)
        return NULL;

    sprintf(str, "%d", num);

    return str;
}

char* createHeadResponse(struct Response r) {
    char* responseHead = (char*) malloc(1000 * sizeof(char));
    strcat(responseHead, "HTTP/1.1 200 OK\nServer: Arnold/1.0.0alpha\nContent-Length: ");
    char buff[5];
    int contentLength = r.contentLength;
    if (itoa(contentLength, buff) != NULL);
    strcat(responseHead, buff);
    strcat(responseHead, "\nContent-Type: ");
    strcat(responseHead, r.contentType);
    strcat(responseHead, "\nConnection: Closed\n\n");

    // char* responseHeadNew;
    // strcpy(responseHeadNew, responseHead);
    
    // free(responseHead);
    return responseHead;
}

void start(struct Server* server) {
    char buffer[1024];
    int addr_length;
    int working_socket;

    //  request;

    //  fileName;
    //  file;
    //  contentLength;
    //  mimeType;

    //  response;
    // char* responseHead;
    // char* serverResponse;

    for (;;) {
        
        printf("<---------------------ARNOLD SERVER------------------------>\n");
        printf("<----------An open source project by 0xAshutosh------------>\n");
        printf("<----------------Waiting for a new request----------------->\n");

        addr_length = sizeof(server -> address);
        working_socket = accept(server -> socket, (struct sockaddr*) &server -> address, (socklen_t*) &addr_length);
        read(working_socket, buffer, sizeof(buffer));
        struct Request request = grabRequest(buffer);
        char* fileName = malloc(300 * sizeof(char));
        strcat(fileName, ROOT);
        strcat(fileName, request.uri);
        // struct File *file = (struct File*) malloc(sizeof(struct File));
        struct File file = parseFile(fileName);
        int contentLength = file.length;
        char* mimeType = file.mimeType;
        struct Response response = setResponse("HTTP/1.1", 200, "Arnold/1.0alpha", contentLength, mimeType, "Keep-Alive");
        char* responseHead = createHeadResponse(response);

        // printf("%s\n", fileName);
        // printf("%s\n", file.fileBody);
        // printf("%s\n", mimeType);
        printf("%s\n", responseHead);
        // char* serverResponse = (char*) malloc((1000 + contentLength) * sizeof(char));
        // strcat(serverResponse, responseHead);
        // strcat(serverResponse, file.fileBody);
        printf("%s\n", request.uri);
        printf("%s\n", buffer);
        // free(serverResponse);
        write(working_socket, responseHead, strlen(responseHead));
        if (response.status == 404) {
            int fdHeader = open("./www/protected/404.html", O_RDONLY);
            int header_bytes;
            char h;

            while ((header_bytes = read(fdHeader, &h, sizeof(h))) > 0) {
                write(working_socket, &h, sizeof(h));
            }
        } else {
            int fdHeader = open(fileName, O_RDONLY);
            int header_bytes;
            char h;
            
            while ((header_bytes = read(fdHeader, &h, sizeof(h))) > 0) {
                write(working_socket, &h, sizeof(h));
            }
        }


        free(fileName);
        // free(serverResponse);
        free(responseHead);
        // free(file.fileBody);
        
        // fclose(file.fp);
        // close(file.fd);
        // close(working_socket);
    }
}

int main(void) {
    struct Server server = create_server(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 10, 80, start);
    server.start(&server);
}