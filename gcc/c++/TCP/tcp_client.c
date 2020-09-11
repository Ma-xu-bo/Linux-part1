#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<Linux/in.h>
#define PORT 8888
int main(int argc,char *argv[])
{
  int s;
  struct sockaddr_in server_addr;
  int err;

  s = socket(AF_INET,SOCK_STREAM,0);
  if (s<0)
    {
      printf("socket error]n");
      return -1;
      }
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  inet pton(AF_INET, argv[1], &server_addr.sin_addr);
  connect(s,(struct sockaddr*)&server_addr,sizeof(struct sockaddr));
  process_conn_server(s);
  close(s);
    
}
  
