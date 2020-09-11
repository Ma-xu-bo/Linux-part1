#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 1234
#define BACKLOG 1

int main()
{
  int listenfd, connectfd;
  struct sockaddr_in server;
  struct sockaddr_in client;
  socklen_t addrlen;

  if((listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
      perror("socket() error.\n");
      exit(1);
    }
  int opt = SO_REUSEADDR;
  setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

  bzero(&server,sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(listenfd,(struct sockaddr*)&server,sizeof(server)) == -1)
    {
      perror("Bind() error.\n");
      exit(1);
    }
  if((connectfd = accept(listenfd,(struct sockaddr *)&client,&addrlen)) == -1)
    {
      perror("accept() error\n");
      exit(1);
    }
  printf("Tou got a connection from clent's is %s,port is %d.\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
  send(connectfd, "Welcome,\n",8,0);
  close(connectfd);
  close(listenfd);
  return 0;

}
