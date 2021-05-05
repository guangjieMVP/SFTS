#ifndef _SFTS_CLIENT_H_
#define _SFTS_CLIENT_H_

#include <sys/types.h>          
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h> 
#include <signal.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

typedef enum menu_operations {
    M_OPT_LOGIN = 1,
    M_OPT_UPLOAD = 2,
    M_OPT_DOWNLOAD = 3
    M_OPT_SHOW_CUR_DIR = 4,
    M_OPT_SHOW_SERVER_DIR = 5,
}menu_opt_t;

typedef struct menu_opt_handler {
    menu_opt_t opt;
    void (*opt_callback)(void);
}menu_opt_hand_t;

typedef struct file_packet_format
{
	int cmd;
	int  filesize;
	int  ack;
	char username[50];
	char filename[125];
	char buf[1024];  
}file_pack_fmt_t;



#endif // _SFTS_CLIENT_