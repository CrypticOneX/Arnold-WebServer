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

#include "request.h"

#include <string.h>
#include <stdlib.h>

int methodType(char* method) {

     if (strcmp(method, "GET"))
        return GET;

    else if (strcmp(method, "POST")) 
        return POST;

    else if (strcmp(method, "PUT")) 
        return PUT;

    else if (strcmp(method, "DELETE"))
        return DELETE;

    else if (strcmp(method, "PATCH"))
        return PATCH;

}

struct Request grabRequest(char* requestString) {

    struct Request request;
    char requestedLocal[strlen(requestString)];
    strcpy(requestedLocal, requestString);
    for (int i = 0; i < strlen(requestedLocal) - 1; i++) {
        if (requestedLocal[i] == "\n" && requestedLocal[i + 1] == "\n")   
            requestedLocal[i + 1] = "|";
    }

    char* statusLine = strtok(requestedLocal, "\n");
    char* headerFields = strtok(NULL, "|");
    char* body = strtok(NULL, "|");

    
    char* method = strtok(statusLine, " ");

    request.method = methodType(method);

    char* uri = strtok(NULL, " ");

    request.uri = uri;

    char* version = strtok(NULL, " ");
    version = strtok(version, "/");
    version = strtok(NULL, "/");

    request.version = (float) atof(version);

    return request;
}