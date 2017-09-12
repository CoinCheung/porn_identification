#ifndef _CSERVER_H_
#define _CSERVER_H_
/* ==============================================
 *  headers to be included
 * ============================================== */
#include<stdio.h>
#include<stdlib.h>
#include"sys/types.h"
#include"sys/un.h"
#include<sys/socket.h>
#include"netinet/in.h"
#include<unistd.h> // write() read() sleep()
#include<string.h>

/* ==============================================
 * micros and data type definitions 
 * ============================================== */
#define true 1
#define false 0

/* ==============================================
 *  function definitions
 * ============================================== */
void enter_socket_listen(); //establish server socket and listen to request
unsigned int scan_leisure_port(); // look for a port not being used
int is_port_occupied(char line[], int len, int port_num); // try the line and see if there are port number

#endif
