#ifndef __SHTTPD_H__
#define __SHTTPD_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<netdb.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<signal.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#include<getopt.h>
#include<limits.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>
#include<stddef.h>



enum{WORKER_INITED, WORKER_RUNNING, WORKER_DETACHING, WORKER_DETACHED, WORKER_IDEL};

struct conf_opts{
  char CGIRoot[128];
  char DefaultFile[128];
  char DocumentRoot[128];
  char ConfigFile[128];
  int ListenPort;
  int MaxClient;
  int TimeOut;
  int InitClient;
};


typedef enum SHTTPD_METHOD_TYPE{
				METHOD_GET,
				METHOD_POST,
				METHOD_PUT,
				METHOD_DELETE,
				METHOD_HEAD,
				METHOD_CGI,
				METHOD_NOTSUPPORT
}SHTTPD_METHOD_TYPE;

enum {HDR_DATE, HDR_INT, HDR_STRING};


typedef struct shttpd_method{
  SHTTPD_METHOD_TYPE type;
  int name_index;
}shttpd_method;


typedef struct vec
{
  char *ptr;
  int  len;
  SHTTPD_METHOD_TYPE type;
}vec;

#define OFFSET(x)  offsetof(struct headers,x)

union variant {
  char *v_str;
  int v_int;
  big_int_t v_big_int;
  time_t v_time;
  void (*v_func)(void);
  void *v_void;
  struct vec  v_vec;
};

#define URI_MAX 16384

struct headers {
  union variant cl;
  union variant ct;
  union variant conection;
  union variant ims;
  union variant user;
  union variant auth;
  union variant useragent;
  union variant referer;
  union variant cookie;
  union variant location;
  union variant range;
  union variant status;
  union variant transenc;
};


struct cgi{
  int iscgi;
  struct vec bin;
  struct vec para;
};


struct worker_ctl;
struct worker_opts{
  pthread_t th;
  int flags;
  pthread_mutex_t mutex;

  struct worker_ctl *work;
};


struct worker_conn;

struct conn_request{
  struct vec req;
  char *head;
  char *uri;
  char rpath[URI_MAX];

  int method;
  unsigned long major;
  unsigned long minor;
  struct headers ch;
  struct worker_conn *conn;
  int err;
};

struct conn_response{
  struct vec res;
  time_t birth_time;
  time_t expire_time;

  int status;
  int cl;
  int fd;
  struct stat fstat;

  struct worker_conn *conn;
};

struct worker_conn
{
#define K 1024
  char dreq[16 * K];
  char dres[16 * K];

  int cs;
  int to;

  struct conn_response con_res;
  struct conn_request con_req;

  struct worker_ctl *work;
};

struct worker_ctl{
  struct worker_opts opts;
  struct worker_conn conn;
};

struct mine_type{
  char *extension;
  int type;
  int ext_len;
  char *mime_type;
};

void Para_Init(int argc, char *argv[]);

int Request_Parse(struct worker_ctl *wctl);
int Request_Handle(struct worker_ctl *wctl);

int Worker_ScheduleRun();
int Worker_ScheduleStop();
void Method_Do(struct worker_ctl *wctl);
void uri_parse(char *src, int len);

struct mine_type* Mine_Type(char *uri, int len, struct worker_ctl *wctl);

#define DBGPRINT printf
#endif /*__SHTTPD_H__*/
