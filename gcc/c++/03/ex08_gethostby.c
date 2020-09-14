#include<netdb.h>
#include<string.h>
#include<stdio.h>
#include<sys/socket.h>
#if 0
struct hostent
{
  char *h_name ;
  char **h_aliases;
  int h_addrtype;
  int h_length;
  char **h_addr_list;
}
#define h_addr h_addr_list[0]
  struct hostent *gethostbyaddr(const void *addr, int len, int type);
#endif
int main(int argc, char *argv[])
{
  struct hostent *ht = NULL;
  char host[] = "www.sina.com.cn";
#if 1
  struct hostent *ht1 = NULL, *ht2 = NULL;
  char host1[] = "www.sohu.com";
  ht1 = gethostbyaddr(host);
  ht2 = gethostbyaddr(host1);
  int j = 0;
#else
  struct in_addr in;
  in.s_addr = inet_addr("60.215.128.140");
  ht = gethostbyaddr(&in, sizsof(in), AF_INET);
#endif
  for(j = 0;j<2;j++)
    {
      if(j == 0)
	ht = ht1;
      else
	ht = ht2;
      printf("------------------\n");
      if(ht){
	int i =0;
	printf("get the host :%s addr\n",host);
	printf("name:%s\n",ht->h_name);

	printf("type:%s\n",ht->h_addrtype == AF_INET?"AF_INET":"AF_INET6");
	printf("length:%d\n",ht->h_length);

	for(i=0;;i++)
	  {
	    if(ht->h_addr_list[i] != NULL)
	      {
		printf("IP:%s\n",inet_ntoa((unsigned int*)ht->h_addr_list[i]));
	      }else {
	      break;
	    }
	  }

	for(i=0;;i++)
	  if(ht->h_aliases[i] != NULL)
	    {
	      printf("alias %d:%s\n",i,ht->h_aliases[i]);
	      
	    }
	  else{
	    break;
	  }
      }
    }
  return 0;
}
