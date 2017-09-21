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
from PIL import Image
from scipy import misc
import numpy as np
import matplotlib.pyplot as plt



#=================================================
# function definitions
#
#=================================================

## function: send_img_info(img, socket)
##
## send the image information to the server to handle, through the given client socket
##
## input: an scipy.misc object containing infomation of the image, such as image shape, channel, pixel information, etc. a client socket established and connected to the server which allows communicating with server directly
## return: None
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
    print('client: response of end flag received is %s'%message)

    # receive results black white picture from C
#this should be collect to a single function
    print('client: receiving results')
    rec_len = 0
    rec_all = ''.encode('utf8')
    all_len = img.shape[0]*img.shape[1]
    while rec_len < all_len:
        rec_bytes = socket_client.recv(img.size)
        rec_all = ''.encode('utf8').join([rec_all, rec_bytes])
        print('client: receive length is {}'.format(len(rec_bytes)))
        rec_len += len(rec_bytes)
        print('client: all received bytes length is {}'.format(rec_len))


    im_new = Image.frombytes('L',(img.shape[1], img.shape[0]),rec_all)

    im_new.save('test_bw_porn.jpg','JPEG')

    print('client: close socket ',)
    socket_client.close()


