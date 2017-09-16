#include"cserver.h"


/* ============================================
 * entrance of the thread
 * ============================================ */
pthread_t thread; 



/* ============================================
 * entrance of the thread
 * ============================================ */
int main()
{
    printf("in c process\n");

    enter_socket_listen();

    return 0;
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
    socklen_t client_addr_len = 0;
    char receive_buffer[1024];
    unsigned int free_port_num;
    char *resp = "1";
    char *endflag = "end";
    img_para img_para;

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
    printf("listening ... \n\n\n");

    // loop to serve the client connection
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
        printf("server: connection establishing ... done \n");

        /* receive image information sent by client */
        img_para = receive_img_data(socket_server, socket_client);
        fputs("server: Image pixel data received\n",stdout);

        /* handle the picture in a sub thread */
        thread_handle_img(0, &img_para);


        /* check if end signal received */
        memset(receive_buffer, 0, sizeof(receive_buffer));
        read(socket_client, receive_buffer, sizeof(receive_buffer));
        fprintf(stdout,"server: receive end flag: %s\n",receive_buffer);
        write(socket_client,resp,strlen(resp));

        if(!strcmp(receive_buffer,endflag))
            break;
    }

    // wait for the client to disconnect and kill the sokcets
    fputs("server: exit signal received, wait for client to exit ... done \n",stdout);
    sleep(2);
    fputs("\nserver: closing sockets \n",stdout);
    close(socket_client);
    close(socket_server);
    fputs("server: exited\n",stdout);

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



/* function: receive_img_data(int socket_server, int socket_client)
 *
 * receive the image parameter and collect to a struct */
img_para receive_img_data(int socket_server, int socket_client)
{
    img_para img;
    long read_num = 0;
    char receive_buffer[32];
    char *resp = "1";

    // receive image channel
    memset(receive_buffer, 0, sizeof(receive_buffer));
    read_num = read(socket_client, receive_buffer, sizeof(receive_buffer));
    while(read_num == 0)
    {
        fputs("read channel but receive no byte, try again\n",stdout);
        read_num = read(socket_client, receive_buffer, sizeof(receive_buffer));
    }
    img.channel = atoi(receive_buffer);
    fprintf(stdout,"server: receive the image channel number: %d\n",img.channel);
    write(socket_client,resp,strlen(resp));
    
    // receive image width 
    memset(receive_buffer, 0, sizeof(receive_buffer));
    read_num = read(socket_client, receive_buffer, sizeof(receive_buffer));
    while(read_num == 0)
    {
        fputs("read width but receive no byte, try again\n",stdout);
        read_num = read(socket_client, receive_buffer, sizeof(receive_buffer));
    }
    img.width = atoi(receive_buffer);
    fprintf(stdout,"server: receive the image width: %d\n",img.width);
    write(socket_client,resp,strlen(resp));

    // receive image height 
    memset(receive_buffer, 0, sizeof(receive_buffer));
    read_num = read(socket_client, receive_buffer, sizeof(receive_buffer));
    while(read_num == 0)
    {
        fputs("read height but receive no byte, try again\n",stdout);
        read_num = read(socket_client, receive_buffer, sizeof(receive_buffer));
    }
    img.height = atoi(receive_buffer);
    fprintf(stdout,"server: receive the image height: %d\n",img.height);
    write(socket_client,resp,strlen(resp));

    // receive image size 
    memset(receive_buffer, 0, sizeof(receive_buffer));
    read_num = read(socket_client, receive_buffer, sizeof(receive_buffer));
    while(read_num == 0)
    {
        fputs("read height but receive no byte, try again\n",stdout);
        read_num = read(socket_client, receive_buffer, sizeof(receive_buffer));
    }
    img.size = atoi(receive_buffer);
    fprintf(stdout,"server: receive the image size: %ld\n",img.size);
    write(socket_client,resp,strlen(resp));


    // receive image data  
    read_num = 0;
    img.data = malloc(img.size*sizeof(uint8_t));
    memset(img.data, 0, img.size*sizeof(uint8_t));
    read_num += read(socket_client, img.data+read_num, img.size * sizeof(uint8_t));
    while(read_num != img.size)
    {
        fprintf(stdout,"server: the image data received: %ld bytes \n",read_num);
        read_num += read(socket_client, img.data+read_num, img.size * sizeof(uint8_t));
    }
    write(socket_client,resp,strlen(resp));

    return img;
}



/* function: 
 *
 * 
 */
void create_thread_handle(int ind,void *img)
{
    int thread_result = 0;
    fputs("create subthread to handle this image\n",stdout);

    thread_result = pthread_create(&thread, NULL, &thread_handle_img, (img_para*)img);
    if(thread_result != 0)
    {
        perror("thread create fail");
        exit(0);
    }

}



/* function: void* thread_handle_img(int ind,void *img); 
 *
 * handle the image with different functions assigned by ind in a new thread
 */
void thread_handle_img(int ind,void *img)
{
    int thread_result = 0;
    fputs("create subthread to handle this image\n",stdout);

    thread_result = pthread_create(&thread, NULL, identify_porn, (img_para*)img);
    if(thread_result != 0)
    {
        perror("thread create fail");
        exit(0);
    }

}
