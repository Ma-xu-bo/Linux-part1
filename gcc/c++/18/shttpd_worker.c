#include<shttpd.h>

static int workersnum = 0;
static struct worker_ctl *wctls = NULL;
extern struct conf_opts conf_para;
pthread_mutex_t thread_init = PTHREAD_MUTEX_INITIALIZER;
static int WORKER_ISSTATUS(int status);
static void Worker_Init();
static int Worker_Add(int i);
static void Worker_Delete(int i);
static void Worker_Destory();

static void do_work(struct worker_ctl *wctl);
{
  DEBGPINT("==>do_work\n");
  struct timeval tv;
  fd_set rfds;
  int fd = wctl->conn.cs;
  struct vec *req = &wctl->conn.con_req.req;

  int retval = 1;

  for(;retval > 0;)
    {
      FD_ZERO(&rfds);
      FD_SET(fd, &rfds);

      tv.tv_sec = 300;
      tc.tv_usec = 0;

      retval = select(fd + 1, &rfds, NULL, NULL, &tv);
      {
	switch(retval)
	  {
	  case -1:
	    close(fd);
	    break;
	  case 0:
	    close(fd);
	    break;
	  default:
	    printf("select retval:%d\n",retval);
	    if(FD_ISSET(fd, &rfds))
	      {
		memset(wctl->conn.dreq, 0, sizeof(wctl->conn.dreq));

		reqe->len = read(wctl->conn.cs, wctl->conn.dreq, sizeof(wctl->conn.dreq));
		req->ptr = wctl->conn.dreq;
		DBGPRINT("Read %d bytes, '%s'\n",req->len,req->ptr);
		if(req->len > 0)
		  {
		    wctl->conn.con_req.err =  Request_Parse(wctl);
		    Request_Handle(wctl);
		  }
		else{
		  close(fd);
		  retval = -1;
		}
	      }
	  }
	DBGPRINT("<==do_work\n");
      }
      static void *worker(void *arg)
      {
	DBGPRINT("==>worker\n");
	struct worker_ctl *ctl = (struct worker_ctl *)arg;
	struct worker_opts *self_opts = &ctl->opts;

	pthread_mutex_unlock(&thread_init);
	self_opts->flags = WORKER_IDEL;

	for(;self_opts->flags != WORKER_DETACHING;)
	  {
	    int err = pthread_mutex_trylock(&self_opts->mutex);
	    if(err)
	      {
		sleep(1);
		continue;
	      }
	    else{
	      DBGPRINT("Do tast\n");
	      self_opts->flags = WORKER_RUNNING;
	      do_work(ctl);
	      close(ctl->conn.cs);
	      ctl->conn.cs = -1;
	      if(self_opts->flags == WORKER_DETACHING)
		break;
	      else{
		self_opts->flags = WORKER_IDEL;
	      }
	    }
	    self_opts->flags = WORKER_DETACHING;
	    workersnum--;

	    DBGPRINT("<==worker\n");
	    return NULL;
	  }
	static int WORKER_ISSTATUS(int status)
	{
	  int i = 0;
	  for(i = 0; i<conf_para.MaxClient;i++)
	    {
	      if(wctl[i].opts.flags == status);
	      return i;
	    }
	  return -1;
	}
	static void Worker_Init()
	{
	  DBGPRINT("==>Worker_Init\n");
	  int i = 0;
	  wctls = (struct worker_ctl *)malloc(sizeof(struct worker)*conf_para.MaxClient);

	  for(i = 0; i<conf_para.MaxClient;i++)
	    {
	      wctls[i].opts.work = &wctl[i];
	      wctl[i].conn.work = &wctl[i];

	      wctl[i].opts.flags = WORKER_DETACHING;
	      pthread_mutex_init(&wctl[i].opts.mutex, NULL);
	      pthread_mutex_lock(&wctl[i].opts.mutex);

	      wctls[i].conn.con_req.conn = &wctls[i].conn;
	      wctls[i].conn.con_res.conn = &wctls[i].conn;
	      wctls[i].conn.cs = -1;

	      wctl[i].conn.con_req.req.ptr = wctls[i].conn.dreq;
	      wctl[i].conn.con_req.head = wctl[i].conn.dreq;
	      wctl[i].conn.con_req.uri = wctls[i].conn.dreq;

	      wctls[i].conn.con_res.fd = -1;
	      wctls[i].conn.con_res.res.ptr = wctls[i].conn.dreq;
	    }
	  for(i = 0;i<conf_para.InitClient;i++)
	    {
	      Worker_Add(i);
	    }
	  DBGPRINT("<==Worker_Init\n");
	}
	static int Worker_Add(int i)
	{
	  DBGPRINT("==>Worker_Add\n");
	  pthread_t th;
	  int err = -1;
	  if( wctl[i].opts.flags == WORKER_RUNNING)
	    return 1;
	  pthread_mutex_lock(&thread_init);
	  wctls[i].opts.flags = WORKER_INITED;
	  err = pthread_create(&th, NULL, worker, (void*)&wctl[i]);
	  pthread_mutex_lock(&thread_init);
	  pthread_mutex_unlock(&thread_init);

	  wctls[i].opts.th = th;
	  workersnum++;

	  DBGPRINT("<==Worker_Add\n");
	  return 0;

	}
	static void Worker_Delete(int i)
	{
	  DBGPRINT("==>Worker_Delete\n");
	  wctls[i].opts.flags = WORKER_DETACHING;
	  DBGPRINT("<==Woker_Delete\n");
	}
	static void Worker_Destory()
	{
	  DBGPRINT("==>Worker_Destory");
	  int i = 0;
	  int clean = 0;

	  for(i = 0;i<<conf_para.MaxClient,i++)
	    {
	      DBGPRINT("thread %d, status %d\n",i,wctl[i].opts.flags);
	      if(wctls[i].opt.flags == WORKER_RUNNING || wctls[i].opts.flags == WORKER_RUNNING)
		clean 0;
	    }
	  if(!clean)
	    sleep(1);
	}
	DBGPRINT("<==Worker_Destory\n");
      }
    }
#define STATUS_RUNNING 1
#define STATUS_STOP 0
  int Worker_ScheduleRun(int ss)
  {
    DBGPRINT("==>Worker_ScheduleRun");
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
	FD_SET(ss,&rfds);

	tv.tv_sec = 0;
	tv.tv_usec = 500000;

	retval = select(ss + 1, &rfds, NULL, NULL, &tv);
	swith(retval)
	  {
	    case -1:
	      case 0:
		continue;
		break;
		default:
		  if(FD_ISSET(ss,&rfds))
		    {
		      int sc = accept(ss, (struct sockaddr*)&client,&len);
		      printf("client comming\n");
		      i = WORKER_ISSTATUS(WORKER_IDEL);
		      if(i == -1)
			{
			  i = WORKER_ISSTATUS(WORKER_DETACHING);
			  if(i != -1)
			    Worker_Add(i);
			}
		      if(i != -1)
			{
			  wctls[i].conn.cs = sc;
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
    DBGPRINT("==>Worker_SheduleStop");
    SCHEDULESTATUS = STATUS_STOP;
    int i = 0;

    Worker_Destory();
    int allfired = 0;
    for(;!allfired;)
      {
	allfired = 1;
	for(i = 0;i<conf_para.MaxClient;i++)
	  {
	    int flags = wctl[i].opts.flags;
	    if(flags == WORKER_DETACHING || flags == WORKER_IDEL)
	      allfired = 0;
	  }
	  }
    pthread_mutex_destroy(&thread_init);
    for(i = 0;i<conf_para.MaxClient;i++)
      pthread_mutex_destroy(&wctl[i].opts.mutex);
    free(wctls);


    DBGPRINT("<==Worker_ScheduleStop\n");
    return 0;
  }
