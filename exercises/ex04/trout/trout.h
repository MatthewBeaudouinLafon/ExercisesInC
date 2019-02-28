// #include <sys/types.h>
// #include <sys/socket.h>
// #include <sys/time.h>
// #include <time.h>
// #include <netinet/in.h>
// #include <netinet/in_systm.h>
// #include <netinet/ip.h>
// #include <netinet/ip_icmp.h>
// #include <netinet/udp.h>
// #include <arpa/inet.h>
// #include <netdb.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <signal.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <getopt.h>
// #include <sys/un.h>
// #include <stdarg.h>
// #include <syslog.h>
#include "util.h"

#define BUFSIZE 1500

int max_ttl;

typedef struct rec {                /* outgoing UDP data */
  u_short seq;          /* sequence number */
} Rec;

typedef struct timeval Timeval;
typedef struct sockaddr Sockaddr;

Sockaddr *sasend;    /* socket addresses for various purposes */
Sockaddr *sarecv;
Sockaddr *salast;
Sockaddr *sabind;

socklen_t salen;                    /* length of a socket address */
// int datalen;         /* length of the data in a datagram */
/* the following are a few definitions from Stevens' unp.h */

#define max(a,b) ((a) > (b) ? (a) : (b))

void loop_ttl ();




