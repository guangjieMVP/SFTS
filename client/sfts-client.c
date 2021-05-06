
#include "sfts_client.h"



/* 创建两个线程：一个负责显示菜单，一个负责接收网络数据 。 在上传或下载数据都会创建一个线程来传输，支持上传和下载同时进行 */

/*
typedef enum menu_operations {
    M_OPT_LOGIN = 1,
    M_OPT_UPLOAD = 2,
    M_OPT_DOWNLOAD = 3
    M_OPT_SHOW_CUR_DIR = 4,
    M_OPT_SHOW_SERVER_DIR = 5,
}menu_opt_t;
*/

/*
typedef struct menu_opt_handler {
    menu_opt_t opt;
    void (*opt_callback)(void);
}menu_opt_hand_t;
 
*/

typedef struct stfs_client_informations
{
    char username[50];
    char password[50];

    int socketfd;
    struct sockaddr_in sock_server_addr;

    pthread_t recv_thread;
    int recv_thread_id;
}stfs_c_info_t;

static stfs_c_info_t  sfts_client;

void *thread_recv(void *arg);

static void menu_login_cb(void);
static void menu_upload_cb(void);
static void menu_download_cb(void);
static void menu_show_cur_dir_cb(void);
static void menu_show_server_file_cb(void);

static menu_opt_hand_t  main_menu_opt_handlers[] = {
    {.opt = M_OPT_LOGIN, .opt_callback = menu_login_cb},
    {.opt = M_OPT_UPLOAD, .opt_callback = menu_upload_cb},
    {.opt = M_OPT_DOWNLOAD, .opt_callback = menu_download_cb},
    {.opt = M_OPT_SHOW_CUR_DIR, .opt_callback = menu_show_cur_dir_cb},
    {.opt = M_OPT_SHOW_SERVER_DIR, .opt_callback = menu_show_server_file_cb},
};

static void menu_process(menu_opt_hand_t *menuopts, int len, int opt)
{
    int find = 0;

    for (int index = 0; index < len; index++)
    {
        if (menuopts[index].opt == ((menu_opt_t)opt))   
        {
            find = 1;
            break;
        } 
    }
    if (find && menuopts[index].opt_callback)
    {
        menuopts[index].opt_callback();
    }
}

static void system_logo(void)
{
    printf("\033[36m***********\033[0m\033[34mWelcome to Secure File Storage System\033[0m\033[36m**************\n\033[0m");
	printf("\033[36m*\033[0m \033[31m        ******     ******     *******     ******   \033[0m  \033[36m       *\n\033[0m\033[0m");
	printf("\033[36m*\033[0m \033[31m       **          *             *       **        \033[0m  \033[36m       *\n\033[0m\033[0m");
	printf("\033[36m*\033[0m \033[31m        *****      ******        *        *****    \033[0m  \033[36m       *\n\033[0m\033[0m");
	printf("\033[36m*\033[0m \033[31m            **     *             *            **   \033[0m  \033[36m       *\n\033[0m\033[0m");
	printf("\033[36m*\033[0m \033[31m       ******      *             *       ******  \033[0m \033[34mKJC\033[0m  \033[36m*\n\033[0m\033[0m");
	printf("\033[36m**************************************************************\n\033[0m");
}

static login_menu_init(void)
{
    printf("***********************************************************\r\n");
    printf("***************************用户登录**************************\r\n");
    printf("************************************************************\r\n");
    printf("用户名：");
    scanf("%s", sfts_client.username);
    printf("密码：");
    scanf("%s", sfts_client.password);
}

static void main_menu_init(void)
{
    printf("***********************************************************\r\n");
    printf("***************************1、登录**************************\r\n");
    printf("***************************2、上传文件**********************\r\n");
    printf("***************************3、下载文件**********************\r\n");
    printf("***************************4、显示当前目录文件***************\r\n");
    printf("***************************5、显示服务器文件*****************\r\n");
    printf("***********************************************************\r\n");
    printf("请输入你的操作：");

}

int get_main_menu_opt()
{
    int opt;
    scanf("%d", &opt);
    return opt;
}

void upload_menu(void)
{
    char filename[200];

    printf("请输入上传的文件名：");
    scanf("%s", filename);
}

int network_init(void)
{
	sfts_client.socketfd = socket(AF_INET, SOCK_STREAM, 0);    //创建套接字
	sfts_client.sock_server_addr.sin_family      = AF_INET;
	sfts_client.sock_server_addr.sin_port        = htons(SERVER_PORT);
 	if (0 == inet_aton(argv[1], &sfts_client.sock_server_addr.sin_addr))
 	{
		perror("invalid server_ip\n");
		return -1;
	}
	memset(sfts_client.sock_server_addr.sin_zero, 0, 8);
    
	ret = connect(sfts_client.socketfd, (const struct sockaddr *)&sfts_client.sock_server_addr, sizeof(struct sockaddr));	

	if (-1 == ret)
	{
		perror("connect error!\n");
		return -1;
	}

    ret = pthread_create(&sfts_client.recv_thread, NULL, thread_recv, (void *)&sfts_client.socketfd);  //创建负责接收线程
    if (-1 == ret)
    {
        perror("create recv errorthread error!\n");
        return -1;
    }

    return 0;
}


int main(int argc, char **argv)
{
    // signal(SIGPIPE, SIG_IGN);  
    // signal(SIGINT, SIG_IGN);            //忽略ctrl + c发送杀死终端的SIGINT信号  使用菜单提供的退出操作才能退出了客户端
    //1、显示logo
    system_logo();

    while (1)
    {
           //2、登录界面
        login_menu_init();

        //4、连接服务器
    }
 
    /* 链接服务器成功后的操作 */

    
    int opt;
    while (1)
    {
        //1、显示菜单
        main_menu_init();
         //2、选择操作
        opt = get_main_menu_opt();
        menu_process(main_menu_opt_handlers, sizeof(main_menu_opt_handlers)/sizeof(main_menu_opt_handlers[0]), opt);
    }
    
    return 0;   
}


static void menu_login_cb(void)
{

}

static void menu_upload_cb(void)
{

}

static void menu_download_cb(void)
{

}

static void menu_show_cur_dir_cb(void)
{

}

static void menu_show_server_file_cb(void)
{

}

void *thread_recv(void *arg)
{
    file_pack_fmt_t file;
    int recv_len;
    int socket = *(int *)arg;

    while (1) 
    {
        recv_len = recv(socket, &file, sizeof(file_pack_fmt_t), 0);
        if (recv_len <= 0)
        {
            printf("socket recv data error\r\n");
            continue;
        }
        
        
    }
}