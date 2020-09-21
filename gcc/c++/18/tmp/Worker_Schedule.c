struct worker_opts{
  pthread_t th;
  int flags;
  pthread_mutex_t mutex;
  struct worker_ctl *work;
};

int Worker_ScheduleRun(int ss)
{
  DBGPRINT("==>Worker_ScheduleRun\n");
  struct sockaddr_in client;
  socklen_t len = sizeof(client);

  Worker_Init();

  int i = 0;

  for(;SCHEDULESTATUS == STATUS_RUNNING;)
    {
      struct timeval tv;
      fd_set rfds;
      int retval = -1;
      FD_ZERO(&rfds);
      FD_SET(ss, &rfds);
      tv.tv_sec = 0;
      tv.tv_usec = 5000000;

      retval = select(ss + 1, &rfds, NULL, NULL, &tv);
      switch(retval)
	{
	case -1:
	case 0:
	  continue;
	  break;
	default:
	  if(FD_ISSET(ss, &rfds))
	    {
	      int sc = accept(ss, (struct sockaddr*)&client, &len);
	      i = WORKER_ISSTATUS(WORKER_IDEL);
	      if(i == -1)
		{
		  i = WORKER_ISSTATUS(WORKER_DETACHED);
		  if(i != -1)
		    Worker_Add(i);
		}
	      if(i != -1)
		{
		  wctl[i].conn.cs = sc;
		  pthread_mutex_unlock(&wctls[i].opts.mutex);
		}
	    }
	}
    }
  DBGPRINT("<==Worker_ScheduleRun\n");
  return 0;
}

int Worker_ScheduleStop()
{
  DBGPRINT("==>Worker_ScheduleStop\n");
  SCHEDULESTATUS = STATUS_STOP;
  int i =0;
  Worker_Destory();
  int allfired = 0;
  for(;!allfired;)
    {
      allfired = 1;
      for(i = 0; i<conf_para.MaxClient;i++)
	{
	  int flags = wctl[i]opts.flags;
	  if(flags == WORKER_DETACHED  || flags == WORKER_IDEL)
	    allfired = 0;
	}
    }
  pthread_mutex_destory(thread_init);
  for(i = 0;i<conf_para.MaxClient;i++)
    pthread_mutex_destory(&wctl[i].opts.mutex);
  free(wctls);

  DBGPRINT("<==Worker_ScheduleStop\n");
  return 0;
}

static void Worker_Init()
{
  DBGPRINT("==>Worker_Init\n");
  int i = 0;
  wctls = (struct worker_ctl*)malloc(sizeof(struct worker_ctl) *conf_opts.MaxClient);
  memset(wctls, 0, sizeof(*wctl)*conf_para.MaxClient);

}

struct worker_ctl{
  struct worker_opts opts;
  struct worker_conn conn;
};
struct worker_conn
{
#define K 1024
  char dreq[16*K];
  char dres[16*K];
  int cs;
  int to;
  struct conn_response con_res;
  struct conn_request con_req;
  struct worker_ctl *work;
};

for(i = 0;i<conf_para.MaxClient;i++)
  {
    wctls[i].opts.work = &wctls[i];
    wctls[i].conn.work = &wctls[i];

    wctls[i].opts.flags = WORKER_DETACHED;
    //wctls[i].opts.mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&wctls[i].opts.mutex, NULL);
    pthread_mutex_lock(&wctls[i].opts.mutex);

    wctls[i]conn.con_req.conn  = &wctl[i].conn;
    wctls[i]conn.con_res.conn = &wctl[i].conn;
    wctls[i]conn.con.cs = -1;

    wctls[i].conn.con_req.req.ptr = wctls[i].conn.dreq;
    wctls[i].conn.con_req.head = wctls[i].conn.dreq;
    wctls[i].conn.con_req.uri = wctls[i].conn.dreq;

    wctls[i].conn.con_res.fd = -1;
    wctls[i].conn.con_res.res.ptr = wctls[i].conn.dres;

    for(i = 0;i < conf_para.InitClient;i++)
      {
	Worker_Add(i);
      }
    DBGPRINT("<==Worker_Init");
  }

