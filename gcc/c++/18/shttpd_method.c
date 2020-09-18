#include<shttpd.h>
/*
 * [HTTP/1.1 200 OK
Date: Thu, 11 Dec 2008 11:25:33 GMT
Last-Modified: Wed, 12 Nov 2008 09:00:01 GMT
Etag: "491a2a91"
Content-Type: text/plain
Content-Length: 11006
Accept-Ranges: bytes
]
*/
static int Method_DoGet(struct worker_ctl *wctl)
{
  DBGPRINT("==>Method_DoGet\n");
  struct conn_response *res = &wctl->conn.con_res;
  struct conn_response *res = &wctl->conn.con_req;
  char path[URI_MAX];
  memset(path, 0, URI_MAX);

  size_t n;/*21*/
    }
