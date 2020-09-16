#ifndef _NF_SOCKOPTE_H__
#define _NF_SOCKOPTE_H__

#define SOE_BANDIP 0x6001
#define SOE_BANDPORT 0x6002
#define SOE_BANDPING 0x6003

typedef struct nf_bandport
{
  unsigned short protocol;
  unsigned short port;
};

typedef struct band_status
{
  unsigned int band_ip;
  nf_bandport band_port;
  unsigned char band_ping;
}band_status;

#endif /*__NF_SOCKOPTE_H__*/
