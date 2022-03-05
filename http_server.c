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

#include <string.h>
#include <stdlib.h>

#include "http_server.h"

int setStatus(int status) {
    if (status == SUCCESS) 
        return 200; 
    
    else if (status == NOT_FOUND)
        return 404;

    else if (status == SERVER_ERROR)
        return 500;
}

struct Response setResponse(char* version, int status, char* server, int contentLength, char* contentType, char* connectionStatus) {
    struct Response response;

    response.version = version;
    response.status = status;
    response.connectionStatus = connectionStatus;
    response.server = server;
    response.contentLength = contentLength;
    response.contentType = contentType;
    
    return response;
}