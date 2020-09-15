#include<stdio.h>
#include<string.h.
#include<errno.h>
#include<sys/socket.h>
#include<resolv.h>
#include<stdlib.h>
#include<netinet.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUF_LEN 1024
#define MYPROT 8888
#define BACKLOG 10

 int main(int argc, char *argv[])
 {
   int s_c;
   socklen_t len;
   int err = -1;

   struct sockaddr_in6 server_addr;
   struct sockaddr_in6 client_addr;
   char buf[BUF_LEN + 1];

   s_c = socket(PF_INET6, SOCK_STREAM, 0);
   if(s_c  == -1)
     {
       perror("socket error");
       return(1);
     }
   else{
     printf("socket() success\n");
   }

   bzero(&server_addr,sizeof(server_addr));
   server_addr.sin6_family = PF_INET6;
   server_addr.sin6_port = htons(MYPROT);
   server_addr.sin6_addr = in6addr_loopback;

   err = connect(s_c, (struct sockaddr *)&server_addr, sizeof(server_addr));
   if (err == -1)
     {
       perror("connect error");
       return (1);
     }
   else{
     printf("connect() success\n");
   }

   bzero(buf, BUF_LEN +1);
   len = recv(s_c, buf, BUF_LEN, 0);

   printf("RECVED &dbytes:%s\n",len,buf);
   bzero(buf, BUF_LEN +1);
   strcpy(buf,"From Client");
   len = send(s_c, buf, strlen(buf), 0);
   close(s_c);
   return 0;
 }
