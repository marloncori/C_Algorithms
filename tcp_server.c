#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX_SIZE 80
#define PORT 8080
#define SA struct sockaddr

void client_server_chat(int conn_fd){
    char buff[MAX_SIZE];
    int n;

    for(;;){
      bzero(buff, MAX_SIZE);

      //read msg from client and copy it to buffer
      read(conn_fd, buff, sizeof(buff));
      // print buffer
      printf("Received a message from Client: \n%s\t To client: ", buff);
      bzero(buff, MAX_SIZE);
      n = 0;
      //copy server msg into buffer
      while((buff[n++] = getchar()) != '\n');

      //and send that buffer to client
      write(conn_fd, buff, sizeof(buff));

      //if msg contains "Exit" thens erver exit and chat ends
      if((strncmp("exit", buff 4) == 0) ||
         (strncmp("Exit", buff 4) == 0) ||
         (strncmp("EXIT", buff 4) == 0)){
        prinft(" Closing chat connection between Server and Client...\n"); 
        break;
      }  
    }
}

int main(){
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
 
    //socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
       perror(" socket creation failed...\n");
       exit(0);
    }
    else {
       printf(" Socket successfully created.\n");
       bzero(&servaddr, sizeof(servaddr));
    }
    
    // assing IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // bind newly created socket to given IP and verify it
    if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){
      perror("socket bind failed...\n");
      exit(0);
    }
    else {
      printf(" Socket successfully binded.\n");
    }    

    if((listen(sockfd, 5) != 0){
      perror("Listen failed...\n");
      exit(0);
    }
    else {
      printf(" Server listening...\n");
      len = sizeof(cli);
    }

    //accept the data packet from client and verify it
    connfd = accept(sockfd, (SA*)&cli, &len);
    if(connfd < 0){
      perror("server accept failed...\n");
      exit(0);
    }
    else {
      printf(" Server accepted the client.\n");
    }

    client_server_chat(connfd);

    //after chatting close the socket
    close(sockfd);    

  return 0;
}