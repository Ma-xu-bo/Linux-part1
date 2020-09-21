struct conf_opts{
  char CGIRoot[128];
  char DefaultFile[128];
  char DocumentFile[128];
  char ConfigFile[128];
  int ListenPort;
  int MaxClient;
  int TimeOut;
  int InitClient;
};
struct conf_opts conf_para={
			    "/usr/local/var/www/cgi-bin/";
			    "/index.html";
			    "/usr/local/var/www/";
			    "/etc/SHTTPD.conf";
			    "8080";
			    "4";
			    "3";
			    "2";
};
static char *shortopts = "c:d:f:ho:l:m:t:";
static struct option longopts[] = {
				   {"CGIRoot", required_argument, NULL, 'c'},
				   {"DefaultFile", required_argument ,NULL, 'd'},
				   {"ConfigFile", required_argument, NULL, 'f'},
				   {"DocumentFile", required_argument, NULL, 'o'},
				   {"ListenPort", required_argument, NULL, 'l'},
				   {"MaxClient", required_argument, NULL, 'm'},
				   {"TimeOut", required_argument, NULL, 't'},
				   {"Help", required_argument, NULL, 'h'},
				   {0, 0,0,0},
};
static char *l_opt_arg;
static int Para_CmdParse(int argc, char *argv[])
{
  int c;
  int len;
  int value;
  while((c = getopt_long (argc, argv, shortopts, longopts, NULL)) != -1)
    {
      switch(c)
	{
	case 'c':
	  l_opt_arg = optarg;
	  if(l_opt_arg && l_opt_arg[0]!=':'){
	    len = strlen(l_opt_arg);
	    memcpy(conf_para.CGIRoot, l_opt_arg, len + 1);
	  }
	  break;
	case 'd':
	  l_opt_arg = optarg;
	  if(l_opt_arg && l_opt_arg[0]!=':'){
	    len = strlen(l_opt_arg);
	    memcpy(conf_para.DefaultFile, l_opt_arg, len + 1);
	  }
	  break;
	case 'f':
	  l_opt_arg = optarg;
	  if(l_opt_arg && l_opt_arg[0]!=':'){
	    len = strlen(l_opt_arg);
	    memcpy(conf_para.ConfigFile, l_opt_arg, len + 1);
	  }
	  break;
	case 'o':
	  l_opt_arg = optarg;
	  if(l_opt_arg && l_opt_arg[0]!=':'){
	    len = strlen(l_opt_arg);
	    memcpy(conf_para.DocumentFile, l_opt_arg, len + 1);
	  }
	  break;
	case 'l':
	  l_opt_arg = optarg;
	  if(l_opt_arg && l_opt_arg[0]!=':'){
	    len = strlen(l_opt_arg);
	    value = strtol(l_opt_arg, NULL, 10);
	    if(value != LONG_MAX && value != LONG_MIN)
	      conf_para.ListenPort = value;
	  }
	  break;
	case 'm':
	  l_opt_arg = optarg;
	  if(l_opt_arg && l_opt_arg[0]!=':'){
	    len = strlen(l_opt_arg);
	    value = strtol(l_opt_arg, NULL, 10);
	    if(value != LONG_MAX && value != LONG_MIN)
	      conf_para.MaxClient = value;
	  }
	  break;
	case 't':
	  l_opt_arg = optarg;
	  if(l_opt_arg  && l_opt_arg[0]!=':'){
	    len = strlen(l_opt_arg);
	    value = strtol(l_opt_arg, NULL, 10);
	    if(value != LONG_MAX && value != LONG_MIN)
	      conf_para.TimeOut = value;
	  }
	  break;
	case '?':
	  printf("Invalid para\n");
	case 'h':
	  display_usage();
	  break;
	}
    }
  return 0;
}

void Para_Para_FileParse(char *file)
{
#define LINELENGTH 256
  char line[LINELENGTH];
  char *name = NULL, *value = NULL;
  int fd = -1;
  int n = 0;
  fd = open(file, O_RDONLY);
  if(fd == -1)
    {
      goto EXITPara_FileParse;
    }
  while((n = conf_readline(fd, line, LINELENGTH)) !=0)
    {
      char *pos = line;
      while (isspace(*pos)){
	pos++;
      }
      if(*pos == '#'){
	continue;
      }
      name = pos;
      while (!isspace(*pos)  && *pos != '=') {
	pos++;
      }
      *pos = '\0';
      while(isspace(*pos)){
	pos++;
      }
      value = pos;
      while(!=isspace(*pos) && *pos != '\r' && *pos != '\n'){
	pos++;
      }
      *pos = '\0';
      int ivalue;
      if(strncmp("CGIRoot", name, 7)){
	memcpy(conf_para.CGIRoot, value, strlen(value)+1);};
      else if(strncmp("DefaultFile", name , 11)){
	memcpy(conf_para.DefaultFile, value, strlen(value)+1);}
      else if(strncmp("DocumentFile", name, 12)){
	memcpy(conf_para.DocumentFile, value, strlen(value)+1);}
      else if(strncmp("ListenPort", name, 10)){
	ivalue = strtol(value, NULL, 10);
	conf_para.ListenPort = ivalue;}
      else if(strncmp("MaxClient", name, 9)){
	ivalue = strtol(value, NULL, 10);
	conf_para.MaxClient = ivalue;}
      else if(strncmp("TimeOut", name, 7)){
	ivalue = strtol(value, NULL, 10);
	conf_para.TimeOut = ivalue;}
    }
  close(fd);
 EXITPara_FileParse:
  return;
}
  
