/* A simple server side code, which echos back the
* received message. It handles multiple socket connections with
 select and fd_set on Linux*/
#include <stio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> // FD_SET, FD_ISSET, FD_ZERO macros

#define MAX_CLIENTS 30
#define        TRUE 1
#define       FALSE 0
#define        PORT 8888

int main(int argc, char *argv[]){
  int opt = TRUE;
  int master_socket, addrlen, new_socket, client_socket[MAX_CLIENTS];
  int activity, i, val_read, sd;
  int max_sd;
  struct sockaddr_in address;
  char* buffer[1025]; // 1k

  //set of socket descriptors
  fd_set read_fds;
  char* msg = " ECHO Daemon v1.0 \r\n";
  
  //initialize all client_socket[] to zero
  for(i = 0; i < MAX_CLIENTS; i++){
     client_socket[i] = 0;
  }

  //create a master socket
  if(master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0){
     perror("socket failed");
     exit(EXIT_FAILURE);
  }

  /*set master socket to allow multiple connections
  * this is just a good habit, it will work without it anyway*/
  if(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0){
     perror("setsockopt");
     exit(EXIT_FAILURE);
  }

  //type of created socket
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  //bind the socket to loclahost port
  if(bind(master_scket, (struct sockaddr*)&address, sizeof(address)) < 0){
    perror(" Bind failed...");
    exit(EXIT_FAILURE);
  }
  printf(" Listener on port %d \n", PORT);

  //try to specify maximum of 3 pending connections for the master socket
  if(listen(master_socket, 3) < 0){
    perror("listen...");
    exit(EXIT_FAILURE);
  }

  //accept the incoming connection
  addrlen = sizeof(address);
  puts("Waiting for connections...");

 while(TRUE){
    //clear the socket set
    FD_ZERO(&read_fds);

    //add master socket to set
    FD_SET(master_socket, &read_fds);
    max_sd = master_socket;

    //add child sockets to set
    for(i = 0; i < MAX_CLIENTS; i++){
       //socket descriptor
       sd = client_socket[i];

       //if valid coekt desciptor then add to read list
       if(sd > 0){
          FD_SET(sd, &read_fds);
       }
       if(sd > max_sd){
          max_sd = sd;
       }
    }
    /* wait for an activity on one of the sockets
     * timeout is NULL, so wait indefinitely */
    activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);

    if((activity < 0) && (errno != EINTR)){
      printf("select error");
    }

   //if something happened on the master sockt, then its an incoming connection
   if(FD_ISSET(master_socket, &read_fds)){
      if((new_socket = accept(master_socket,
           (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
         perror("accept error");
         exit(EXIT_FAILURE);
      }
     //inform user of socket number - used in send and receive
     printf(" New connection, socket fd is %d, \n  IP is: %s, \n  PORT is: \n",
       new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    
     //send new connection greeting message
     if(send(new_socket, msg, strlen(msg), 0) != strlen(msg)){
       perror("send error");
     }
     puts("Welcome MESSAGE sent successfully!\n");

     //add new socket to array of sockets
     for(i = 0; i < MAX_CLIENTS; i++){
        //if position is empty
        if(client_socket[i] == 0){
           client_socket[i] = new_socket;
           printf(" Adding to list of sockets as %d\n", i);
           break;
         }
      }  
    } //FD_ISSET

    for(i = 0; i < MAX_CLIENTS; i++){  
         sd = client_socket[i];  
                 
         if(FD_ISSET(sd, &read_fds)){  
           //Check if it was for closing , and also read the 
           //incoming message 
           if ((val_read = read(sd, buffer, 1024)) == 0){  
             //Somebody disconnected , get his details and print 
             getpeername(sd, (struct sockaddr*)&address, \
                     (socklen_t*)&addrlen);  
             printf("Host disconnected, ip %s , port %d \n", 
                       inet_ntoa(address.sin_addr), ntohs(address.sin_port));  
                         
             //Close the socket and mark as 0 in list for reuse 
             close(sd);  
             client_socket[i] = 0;  
           }
           //echo back the message that came in
           else {
             //set the string terminating NULL byte on the end of the data read
             buffer[val_read] = '\0';
             send(sd, buffer, strlen(buffer), 0);
           }
        }
    }
 } //while

 return 0;
}