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

#include "mime.h" 

int stringcmp(char* s1, char* s2) {
    while (*s1) {
        char* a = s1, *b = s2;

        if (*b != *a) return 0;
        s1++; s2++;
    }

    return 1;
}

char* getFileExtension(char* fileName) {
    char tempFile[strlen(fileName)];
    strcpy(tempFile, fileName);
    char* extension = strtok(tempFile, ".");
    extension = strtok(NULL, ".");

    return extension;
}

char* getMimeType(char* extension) {

    printf("%d\n", stringcmp(extension, "jpg") );

    if (stringcmp(extension, "html") || stringcmp(extension, "htm")) {
        return "text/html";
    }

    if (stringcmp(extension, "css")) {
        return "text/css";
    }

    if (stringcmp(extension, "js")) {
        return "application/javascript";
    }

    if (stringcmp(extension, "json")) {
        return "application/json";
    } 

    if (stringcmp(extension, "jpeg") || stringcmp(extension, "jpg")) {
        return "image/jpeg";
    }

    if (stringcmp(extension, "png")) {
        return "image/png";
    }

    if (stringcmp(extension, "mp4")) {
        return "video/mp4";
    }
}