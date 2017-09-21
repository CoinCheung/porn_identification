#ifndef _CSERVER_H_
#define _CSERVER_H_

/* ==============================================
 *  headers to be included
 * ============================================== */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"sys/types.h"
#include"sys/un.h"
#include<sys/socket.h>
#include"netinet/in.h"
#include<unistd.h> // write() read() sleep()
#include<string.h>
#include"imgpro.h"
#include<pthread.h>

/* ==============================================
 * micros and data type definitions 
 * ============================================== */

/* types definition */
// struct of the parameters passed to the new thread
typedef struct
{
    void *img; // points to the structure containing image information 
    int ind; // index of the method
    int socket_client;
    int socket_server;
    int result;
}thread_para;




/* ==============================================
 *  function definitions
 * ============================================== */
void enter_socket_listen(); //establish server socket and listen to request
unsigned int scan_leisure_port(); // look for a port not being used
bool is_port_occupied(char line[], int len, int port_num); // try the line and see if there are port number
img_para receive_img_data(int server, int client); // receive information struct of image
void *thread_handle_img(thread_para *tp); // 
void create_thread_handle(int ind,void *img, int socket_server, int socket_client);//create a new thread and handle the picture 


#endif
