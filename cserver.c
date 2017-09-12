#include"cserver.h"


/* ============================================
 * entrance of the thread
 * ============================================ */
int main()
{
    printf("in c process\n");

    enter_socket_listen();
}


/* ============================================
 * function implementations
 * ============================================ */

/* function: void enter_socket_listen()
 *
 * establish server socket
 * run the socket server and listen to a leisure port */
void enter_socket_listen()
{
    /* varaiables */
    struct sockaddr_in server_addr; // server address
    struct sockaddr_in client_addr; // request client address
    int socket_server = -1; // 建立失败不返回值，保持-1
    int socket_client = -1; // 没得到client的socket信息，返回值不变
    int bind_result = -1; // bind 失败不返回值
    int listen_result = -1; // 监听失败无返回值，仍为-1 
    int client_addr_len = 0;
    char receive_buffer[1024];
    unsigned int free_port_num;
    char *endflag = "end";

    /* find an unoccupied port */
    free_port_num = scan_leisure_port();
    printf("find free port ... done\n port number is: %d\n",free_port_num);
    free_port_num = 4000;
    fprintf(stdout,"set the server port number as:%d\n",free_port_num);

    /* initalize server address struct */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //监听任何一个地址
    server_addr.sin_port = htons(4000); //使用free_port_num端口


    /* create server socket */
    socket_server = socket(AF_INET, SOCK_STREAM, 0); //使用网络通信模式，tcp通信
    if(socket_server == -1)
    {
        perror("create server socket failed!\n");
        close(socket_server);
        exit(0);
    }
    printf("establish server socket ... done \n");

    /* bind socket with the listening port  */
    bind_result = bind(socket_server, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(bind_result == -1)
    {
        perror("cannot bind the server socket to port free_port_num\n");
        close(socket_server);
        exit(0);
    }
    printf("server bind to port ... done \n");

    /* let socket listen to the port it binde */
    listen_result = listen(socket_server, 5);
    if(listen_result == -1)
    {
        perror("server listen to port failed\n");
        close(socket_server);
        exit(1);
    }
    printf("listening ... \n");

    // loop to serve the client connection
    char *ss = "server: received";
    while(true)
    {
        /* establish the connection when a requset is accepted */
        client_addr_len = sizeof(client_addr);
        socket_client = accept(socket_server, (struct sockaddr *)&client_addr, &client_addr_len);
        if(socket_client == -1)
        {
            perror("cannot get client socket information\n");
            close(socket_server);
            close(socket_client);
            exit(0);
        }
        printf("client connection establish ... done \n");

        /* receive message sent by client */
        memset(receive_buffer, 0, sizeof(receive_buffer));
        read(socket_client, receive_buffer, sizeof(receive_buffer));
        fprintf(stdout,"the message is: %s\n",receive_buffer);
        write(socket_client,ss,strlen(ss));

        if(!strcmp(receive_buffer,endflag))
            break;
    }

    // wait for the client to disconnect and kill the sokcets
    fputs("cserver exit signal received, wait for client to exit ... done \n",stdout);
    sleep(3);
    close(socket_client);
    close(socket_server);
    fputs("cserver exited\n",stdout);
}


/* function: unsigned int scan_leisure_port()
 *
 * scan the ports of the computer and return an unoccupied one
 * netstat is required here */
unsigned int scan_leisure_port()
{
    unsigned int port_num = 1025;
    char line[1024];
    FILE *fhd = NULL;
    char portExists = 0;

    system("netstat -ano > netstat.log");
    
    fhd = fopen("netstat.log", "r");
    if(fhd == NULL)
    {
        perror("fail to open 'netstat.log'\n");
        exit(0);
    }
    rewind(fhd);

    while(1)
    {
        memset(line, 0, sizeof(line));  //reset the readline buffer

        portExists = 0;
        while(!feof(fhd))
        {
            fgets(line,sizeof(line),fhd);  // read one line from the file
            portExists = is_port_occupied(line, strlen(line), port_num);
            if(portExists == true) // if the port is occupied, try next one
                break;
        }

        if(portExists == false) // if the port is not occupied, break the loop
            break;

        port_num++;
    }

    if(fclose(fhd))
    {
        perror("fail to close the file!!\n");
        fclose(fhd);
        exit(1);
    }

    return port_num;
}


/* function: is_port_occupied(char[], int len, int port_num)
 *
 * try the line char[] to see if port is in it */
int is_port_occupied(char line[],int len, int port_num)
{
    char port_str1[10];
    char port_str2[10];
    char substr[10];
    short i;
    short port_len;

    sprintf(port_str1," %d ",port_num); // " port_num " partern
    sprintf(port_str2,":%d ",port_num); // ":port_num " partern

    port_len = strlen(port_str1);
    for(i = 0; i < len-port_len+1; i++)
    {
        strncpy(substr,line+i,port_len);
        substr[i+port_len] = 0;
        if(strcmp(substr,port_str1) || strcmp(substr,port_str2))
            return true;
    }
    return false;
}

