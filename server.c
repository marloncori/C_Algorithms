#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const* argv[]){
   int server_fd, new_socket, val_read;
   struct sockaddr_in address;
   int opt = 1;
   int addr_len = sizeof(address);
   char buffer[1024] = { 0 };
   char* hello = "Hello from Server!";

   // create socket file descriptor
   if((server_fd = socket(AF_INET, SOCK_STREAM, 0) == 0){
      perror(" socket failed!");
      exit(EXIT_FAILURE);
   }

   //forcefully attaching socket to the port
   if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
      perror("setsockopt");
      eixt(EXIT_FAILURE);
   }

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   //forcefully attaching socket to the port
   if(bind(server_fd, (strut sockaddr*)&address, sizeof(address)) < 0){
      perror(" bind failed...");
      exit(EXIT_FAILURE);
   }

   if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addr_len)) < 0){
     perror(" accept");
     exit(EXIT_FAILURE);
   }

   val_read = read(new_socket, buffer, 1024);
   printf("%\n", buffer);
   send(new_socket, hello, strlen(hello), 0);
   printf(" ---> HELLO message has been successfuly sent!\n"); 

   // close the connected socket
   close(new_socket);

   // close the listening socket
   shutdown(server_fd, SHUT_RDWR);

   return 0;
}