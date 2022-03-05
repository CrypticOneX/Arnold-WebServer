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

#include "files.h"
#include "mime.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>


struct File parseFile(char* requestedFile) {

    struct File file;
    // FILE* fp = fopen(requestedFile, "rb"); 
    int fd;

    char* extension = getFileExtension(requestedFile);
    file.mimeType = getMimeType(extension);
    // strcpy(file.mimeType, getMimeType(extension));

    if ((fd = open(requestedFile, O_RDONLY)) == 0) {
        file.status = 404;
        fd = open("./www/protected/404.html", O_RDONLY);
    }

    int length = 0;
    int i;
    char buffer; 
    while ((i = read(fd, &buffer, sizeof(buffer))) > 0) {
        length++;
    }

    file.length = length;
    // fclose(fp);

    // char* responsePage = (char*) malloc(length * sizeof(char));

    // read(fd, responsePage, length);
    // strcpy(file.fileBody, responsePage);
    file.status = 200;
    // file.fileBody = responsePage;
    // printf("%s\n", file.fileBody);

    // close(fd);
    // fclose(fp);
    // free(responsePage);

    // file.fd = fd;
    file.fd = fd;

    return file;
}