#############################################################################
# Copyright 2022 Ashutosh Singh (0xAshutosh)

   # Licensed under the Apache License, Version 2.0 (the "License");
   # you may not use this file except in compliance with the License.
   # You may obtain a copy of the License at

       # http://www.apache.org/licenses/LICENSE-2.0

   # Unless required by applicable law or agreed to in writing, software
   # distributed under the License is distributed on an "AS IS" BASIS,
   # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   # See the License for the specific language governing permissions and
   # limitations under the License.
#############################################################################
CC = gcc
OBJFILES = arnold.o files.o http_server.o mime.o request.o server.o
TARGET = Arnold_Server

all: message $(TARGET) pmessage clean

message:
	@echo "Arnold server v1.0.0_alpha"
	@echo "An open source project by @0xAshutosh"
	@echo "https://github.com/0xAshutosh/Arnold-Server"
	@echo "Checking system requirement...."
	@echo "Installing......"

$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES)
	@mv $(TARGET) $(BIN)
pmessage:
	@echo "Installed successfully !!!"
	@echo "Host all your web files at /var/arnold_public directory"
	@echo "This software is in alpha stage so, it is full of bugs"
	@echo "so, Enjoy :) at your own Risk!"
clean:
	@bash fetch.sh