#include<config.h>
int main(int argc, char *argv[])
{
  struct sockaddr_in servaddr, cliaddr;
  int listenfd,connfd;
  pid_t childpid;

  char buf[MAX_LINE];

  socklen_t clilen;

  if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
      perror("bind error");
      exit(1);
    }
  if (listen(listenfd,LISTENQ) < 0)
    {
      perror("listen error");
      exit(1);
    }
  for(;;)
    {
      clilen = sizeof(cliaddr);
      if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) < 0)
	{
	  perror("accept error");
	  exit(1);
	}
      if ((childpid = fork()) == 0)
	{
	  close(listenfd);
	  ssize_t n;
	  char buff[MAX_LINE];
	  while ((n = read(connfd,buf,MAX_LINE)) > 0)
	    {
	      write(connfd,buff,n);
	    }
	  exit(0);
	}
      close(connfd);
    }
  return 0;
}
