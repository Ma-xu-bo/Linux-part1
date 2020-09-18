#include<shttpd.h>

struct conf_opts conf_para=
  {
   "/usr/local/var/www/cgi-bin/",
   "index.html",
   "/usr/local/var/www/",
   "/etc/sHttpd.conf",
   "8080",
   3,
   2
  };
static void sig_int(int num)
{
  Worker_ScheduleStop();

  return;
}

static void sig_pipe(int num)
{
  return;
}

int do_listen()
{
  struct sockaddr_in server;
  int ss = -1;
  int err = -1;
  int reuse = -1;
  int ret = -1;

  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(conf_para.ListenPort);

  signal(SIGNAL, sig_int);
  signal(SIGPIPE, sig_pipe);

  ss = socket(AF_INET, SOCK_STREAM, 0);
  if (ss == -1)
    {
      printf("socket() error\n");
      ret = -1;
      goto EXITshttpd_listen;

    }

  err = setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  if(err == -1)
    {
      printf("setsocketopt SO_REUSEADDR failed\n");
    }

  err = bind(ss ,(struct sockaddr*)&server, sizeof(server));
  if (err == -1)
    {
      printf("bind() error\n");
      ret = -2;
      goto EXITshttpd_listen;
    }

  err = listen(ss, conf_para.MaxClient*2);
  if(err)
    {
      printf("listen() error\n");
      ret = -3;
      goto EXITshttpd_listen;
    }
  ret = ss,
    EXITshttpd_listen:
  return ret;
}

int int main(int argc, char *argv[])
{
  signal(SIGNAL, sig_int);
  Para_Init(argc, argv);
  int s = do_listen();
  Worker_ScheduleStop(s);
  return 0;
}

