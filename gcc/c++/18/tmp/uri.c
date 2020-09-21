static int uri_decode(char *src, int src_len, char *dst, int dst_len)
{
  int i, j, a, b;
#define HEXTOI(x) (isdigit(x) ? x - '0' : x - 'W')
  for(i = j =0; i < src_len && j <dst_len - 1;i++,j++)
    {
      switch (src[i])
	{
	case '%':
	  if(isxdigit(((unsigned char *)src)[i + 1]) &&
	     isxdigit(((unsigned char *)src)[i + 2]))
	    {
	      a = tolower(((unsigned char *)src)[i + 1]);
	      b = tolower(((unsigned char *)src)[i + 2]);
	      dst[j] = (HEXTOI(a)  << 4)  |  HEXTOI(b);
	      i += 2;
	    }
	  else
	    {
	      dst[j] = '%';
	    }
	  break;
	default:
	  dst[j] = src[i];
	  break;
	}
    }
  dst[j] = '\0';
  return (j);
}

static void remove_double_dots(char *s)
{
  char *p = s;
  while(*s != '\0')
    {
      *p++ = *s++;
      if (s[-1] == '/'  || s[-1]  == '\\')
	{
	  while(*s == '.' || *s == '/' || *s == '\\')
	    {
	      s++;
	    }
	}
    }
  *p = '\0';
}

typedef struct vec
{
  char *ptr;
  int len;
  SHTTPD_METHOD_TYPE type;
}vec;
struct vec _shttpd_methods[] = {
				{"GET", 3, METHOD_GET},
				{"POST", 4, METHOD_POST},
				{"PUT", 3, METHOD_PUT},
				{"DELETE" 6,METHOD_DELETE},
				{"HEAD", 4, METHOD_HEAD},
				{NULL, 0, }
};

struct vec *m = NULL;
for(m = &_shttpd_methods[0];m->ptr!=NULL,m++)
  {
    if(!strncmp(m->ptr, pos, m->len))
      {
	req->method = m->type;
	found = -1;
	break;
      }
  }
void Method_Do(struct  worker_ctl *wctl)
{
  DBGPRINT("==>Method_Do\n");
  if(0)
    Method_DoCGI(wctl);
  switch(wctl->conn.con_req.method)
    {
    case METHOD_PUT:
      Method_DoPut(wctl);
      break;
    case METHOD_DELETE:
      Method_DoDelete(wctl);
      break;
    case METHOD_GET:
      Method_DoGet(wctl);
      break;
    case METHOD_POST:
      Method_DoPost(wctl);
    case METHOD_HEAD:
      Method_DoHEAD(wctl);
    default:
      Method_DoList(wctl);
    }
  DBGPRINT("<==Method_Do\n");
}

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

struct headers {
  union variant cl;
  union variant ct;
  union variant connection;
  union variant ims;
  union variant user;
  union variant auth;
  union variant useragent;
  union variant referer;
  union variant cookie;
  union variant location;
  union variant range;
  union variant status;
  union variant stansenc;
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

static int Method_DoGet(struct worker_ctl *wctl)
{
  DBGPRINT("==>Method_DoGet\n");
  struct conn_response *res = &wctl->conn.con_res;
  struct conn_request *req = &wctl->conn.con_req;
  char path[URI_MAX];
  memset(path, 0, URI_MAX);
  size_t n;
  unsigned long r1, r2;
  char  *fmt = "%a, %d %Y %H:%M:%S GMT";
  size_t status = 200;
  char *msg = "OK";
  char date[64] = "";
  char lm[64] = "";
  char etag[64] = "";
  big_int_t cl;
  char range[64] = "";
  struct mine_type *mine = NULL;

  time_t t = time(NULL);
  (void) strftime(date,
		  sizeof(date),
		  fmt,
		  localtime(&t));
  (void) strftime(lm,
		  sizeof(lm),
		  fmt,
		  localtime(&res->fstat.st_mtime));
  (void) snprintf(etag,
		  sizeof(etag),
		  "%lx.%lx",
		  (unsigned long) res->fstat.st_mtime,
		  (unsigned long) res->fstat.st_size);
  mine = Mine_Type(req->uri, strlen(req->uri), wctl);
  cl = (big_int_t) res->fstat.st_size;
  memset(range,0,sizeof(range));
  n = -1;
  if(req->ch.range.v_vec.len > 0)
    {
      printf("request range:%d\n",req->ch.range.v_vec.len);
      n = sscanf(req->ch.range.v_vec.ptr,"bytes=%lu-%lu",&r1,&r2);
    }
  printf("n:%d'n",n);
  if(n > 0)
    {
      status = 206;
      (void) fseek(res->fd, r1, SEEK_SET);
      cl = n == 2 ? r2 -r1 + 1 : cl - r1;
      (void) snprintf(range,
		      sizeof(range),
		      "Content-Range: bytes %lu-%lu/%lu\r\n",
		      r1,
		      r1 + cl - 1,
		      (unsigned long) res->fstat.st_size);
      msg = "Partial Content";
    }
  memset(res->res.ptr, 0, sizeof(wctl->conn.dres));
  snprintf(
	   res->res.ptr,
	   sizeof(wctl->conn.dres),
	   "HTTP/1.1 %d %s\r\n"
	   "Date: %s\r\n"
	   /*
	    * 
	   
 
	    */)
    res->cl = cl;
  res->status = status;
  DBGPRINT("<==Method_DoGet\n");
  return 0;
}
