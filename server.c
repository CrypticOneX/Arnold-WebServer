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

#include <netinet/in.h>

#include "server.h"

struct Server create_server(int domain, int service, int protocol, u_long interface, int backlog, int port, void (*start)(struct Server* server)) {
    struct Server server;

    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.backlog = backlog;
    server.port = port;

    server.address.sin_addr.s_addr = htonl(interface);
    server.address.sin_family = domain;
    server.address.sin_port = htons(port);

    if ((server.socket = socket(domain, service, protocol)) == 0) {
        perror("Unable to create socket!\n");
        exit(EXIT_FAILURE);
    }

    if ((bind(server.socket, (struct sockaddr*) &server.address, sizeof(server.address))) < 0) {
        perror("Bind socket failure!\n");
        exit(EXIT_FAILURE);
    }

    if ((listen(server.socket, server.backlog)) < 0) {
        perror("Failed to start server!\n");
        exit(EXIT_FAILURE);
    }

    server.start = start;

    return server;
}
