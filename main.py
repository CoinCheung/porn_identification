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
from scipy import misc
import numpy as np



#=================================================
# function definitions
#
#=================================================
## function: initImage(img)
##
## convert various pictures to one unified mode and size
def initImage(img):
    img = Image.open(imfile)
    img = firmsize(img)

    bands = img.getbands()  # channels of this image
    if len(bands) == 1:
        imgnew = Image.new('RGB',img.size)
        imgnew.paste(img)
        im.close()
        return imgnew

    return img


## function: firmsize(img)
##
## to adjust the size of the picture with max length or width of 1000
def firmsize(img):
    maxwidth = 1000
    maxheight = 1000
    originwidth, originheight = img.size

    if originwidth > originheight and originwidth > maxwidth:
        width = maxwidth
        height = int((maxwidth/originwidth)*originheight)

    if originwidth < originheight and originheight > maxheight:
        width = int((maxheight/originheight)*originwidth)
        height = maxheight

    return img.resize((width,height),Image.LANCZOS)


def send_img_info(img, socket_client):
    channels = img.shape[2]
    width = img.shape[1]
    height = img.shape[0]
    pxl_matrix_pointer = img.ctypes.data

    socket_client.send(str(channels).encode('utf8'))
    rsp = socket_client.recv(1024)
    send_img_info(img, socket_client)
    if rsp != '1':
        print('Error: cserver has no response to channels')
        os



#=================================================
# entrance of the program
#
#=================================================
if __name__ == '__main__':
    # set up the C program server
    cserverprocess = subprocess.Popen(['./cserver'])

    # open the image and fetch its pixel information
    imfile = ''.join([os.getcwd(),os.path.sep,'pic.jpg'])
    img = misc.imread(imfile, mode = 'RGB')

    # establish client socket and connect to server
    host = '127.0.0.1'
    port = 4000
    socket_client = socket.socket(socket.AF_INET,socket.SOCK_STREAM) # create a client socket
    socket_client.connect((host,port))
    print('client: receive response')
    print(message)



    socket_client.send('end'.encode('utf8'))
    message = socket_client.recv(1024)
    socket_client.close()

