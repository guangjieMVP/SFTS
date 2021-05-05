
#include "sfts_client.h"


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

struct stfs_client_informations
{
    char username[50];
    char password[50];

    struct sockaddr_in sock_server_addr;
};

static stfs_client_informations  sfts_client;


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


int main(int argc, char **argv)
{
    
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