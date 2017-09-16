#!/usr/bin/python3
#filename: main.py
#-*- coding:utf-8 -*-

#=================================================
# modules and packages
#
#=================================================
import os
import subprocess
import socket
import time
import ctypes
from scipy import misc
import numpy as np



#=================================================
# function definitions
#
#=================================================

## function: send_img_info(img, socket)
##
##
def send_img_info(img, socket_client):
    channels = img.shape[2]
    width = img.shape[1]
    height = img.shape[0]
    size = img.size
    pxl_matrix_bytes = img.tobytes()

    # send image pixel channel numbers
    socket_client.send(str(channels).encode('utf8'))
    rsp = socket_client.recv(32)
    if rsp != b'1':
        print('client: cserver has no response to channels')
        os._exit(0)
    print('client: response to channel number received')

    # send image width
    socket_client.send(str(width).encode('utf8'))
    rsp = socket_client.recv(32)
    if rsp != b'1':
        print('client: cserver has no response to width')
        os._exit(0)
    print('client: response to img width received')

    # send image height
    socket_client.send(str(height).encode('utf8'))
    rsp = socket_client.recv(32)
    if rsp != b'1':
        print('client: cserver has no response to height')
        os._exit(0)
    print('client: response to img height received')

    # send image size
    socket_client.send(str(size).encode('utf8'))
    rsp = socket_client.recv(32)
    if rsp != b'1':
        print('client: cserver has no response to size')
        os._exit(0)
    print('client: response to img size received')

    # send image pixel matrix pointer
    sent_num = socket_client.send(pxl_matrix_bytes)
    rsp = socket_client.recv(32)
    print('client: all bytes sent, and response to data received: %s'%(rsp))
    if rsp != b'1':
        print('client: cserver has no response to data: %s'%rsp)
        os._exit(0)




#=================================================
# entrance of the program
#
#=================================================
if __name__ == '__main__':
    # set up the C program server
    cserverprocess = subprocess.Popen(['./cserver'])

    # wait till server established
    time.sleep(1)

    # establish client socket and connect to server
    host = '127.0.0.1'
    port = 4000
    print('client: establishing client socket')
    socket_client = socket.socket(socket.AF_INET,socket.SOCK_STREAM) # create a client socket
    print('client: start to connect to server')
    socket_client.connect((host,port))


    # open the image and fetch its pixel information
    imfile = ''.join([os.getcwd(),os.path.sep,'pic.jpg'])
    img = misc.imread(imfile, mode = 'RGB')

    # send image data and information to server
    print('client: start to send image data ... ',)
    send_img_info(img, socket_client)
    print(' \n ')

    # send end flag to server
    socket_client.send('end'.encode('utf8'))
    message = socket_client.recv(32)
    #  if message != '1':
    #      message = socket_client.recv(32)
    print('client: response of end flag received is %s'%message)

    print('client: close socket ',)
    socket_client.close()

    time.sleep(3)

