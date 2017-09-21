#!/usr/local/bin/python2

from PIL import Image
import numpy
#  from scipy import *
import os
import subprocess


#  im = Image.open('pic.jpg').convert('L')
im = Image.open('pic.jpg')
#  im.save('gray.png','png')

#  im = Image.open('gray.png').convert('RGB')
#  #  im.save('backrgb.jpg','JPEG')
#
#  imnew = Image.new('RGB',im.size)
#  imnew.paste(im)
#  imnew.save('test_backRGB.png','png')
#  pic = im.load()
#  print(pic[(3,4)])


print(os.pathsep)
print(os.sep)


#  sp = subprocess.call('ls -l',shell=True)
#  sp = subprocess.call(['ls','-l'])
import time
#  import scipy
#  sp = subprocess.Popen(['./test_run'])
#
#  for i in range(5):
#      time.sleep(1)
#      print(sp.poll())
#      print(sp.returncode)
#  sp.kill()
#  for i in range(5):
#      time.sleep(1)
#      print(sp.poll())
#      print(sp.returncode)


#  while True:
#      pass



from PIL import Image
import numpy as np
a = [(1,2,3),(4,5,6),(7,8,9)]
c = []
for el in a:
    c.extend(list(el))
print(a)
b = list(a)
print(b)
print(np.ndarray.tolist(np.array(c)))

b = np.array(a)
print(b.size)
print(b)
print(b[1][2])
print(b.tostring())
print('before image')


from scipy import misc
#  im = misc.imread('pic.jpg')
im = misc.imread('test_misc_toRGB.jpg')
print(im[4][5])
print(type(im))
print('shape')
print(im.shape)
print(im.dtype)
print('size')
print(im.size)
print(im.ctypes)
print(im.strides)
print(im.__array_interface__['data'])
print(im.tobytes().__len__())

if im.shape[0]*im.shape[1]*im.shape[2] == im.size:
    print('size is right')


num = 23
print(str(hex(num)))

arr = [2,3,4,5,6]
print(type((str(arr)[2])))
arr = np.array([[1,2,3,4],[1,2,3,4]],dtype = np.uint8)
#  print(arr.tobytes())

arr_new = np.array([1,2,3,4,5,6,7])
print(arr_new)
arr = '101010'.encode('utf8')
print(arr)
print(arr.decode())
print(np.fromstring(arr, dtype = np.uint8))
print(list(arr.decode()))
print(np.array(arr))
print(type(arr))

print('numpy to bytes')
arr = np.array([1,2,3,4,5], dtype = np.uint8)
print(arr)
byarr = arr.tobytes()
print(byarr)
arrbak = np.fromstring(byarr, dtype = np.uint8)
print(arrbak)

im = np.array([1,0,0,1,0,1])
print(im)

img = Image.frombytes('1',(2,3),im.tobytes())
print('abcd')

arr = np.zeros((512,512,3),dtype = np.uint8)
img = Image.fromarray(arr,mode='RGB')
img.save('test_fromarray.jpg','JPEG')



import socket
import time

time.sleep(1)

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(('127.0.0.1',4000))

s.send('12'.encode('utf8'))
rsp = s.recv(1024)
#  print(rsp)
if rsp != b'1':
    print('Error: cserver has no response to height')

s.send('12'.encode('utf8'))
rsp = s.recv(1024)
#  print(rsp)
if rsp != b'1':
    print('Error: cserver has no response to height')

s.send('12'.encode('utf8'))
rsp = s.recv(1024)
#  print(rsp)
if rsp != b'1':
    print('Error: cserver has no response to height')

s.send('12'.encode('utf8'))
rsp = s.recv(1024)
#  print(rsp)
if rsp != b'1':
    print('Error: cserver has no response to height')

s.send('12'.encode('utf8'))
rsp = s.recv(1024)
#  print(rsp)
if rsp != b'1':
    print('Error: cserver has no response to height')

s.send('12'.encode('utf8'))
rsp = s.recv(1024)
#  print(rsp)
if rsp != b'1':
    print('Error: cserver has no response to height')


s.send('end'.encode('utf8'))

s.close()



#
#  #  exit()
#
#  print('showimage')
#  import matplotlib.pyplot as plt
#  plt.figure('show image')
#  plt.imshow(im)
#  plt.show()
#
#  #  for i in range(im.shape[0]):
#  #      for j in range(im.shape[1]):
#  #          im[i][j][1] -= 1
#
#  misc.imsave('test_misc_imsave.png',im, 'png')
#
#  im = np.fromfile('pic.jpg',np.uint8)
#  print(im[34])
#  print(im.size/3)
#  print(im.shape)
#  #  im.reshape(im.size/3, 3)
#
#  print('try to convert mode')
#  im = misc.imread('test_initImg.png',flatten = True, mode = None)
#  print(im.shape)
#  misc.imsave('test_misc_toGray.jpg',im, 'jpeg')
#
#  im = misc.imread('test_initImg.png',flatten = False, mode = 'L')
#  print(im.shape)
#  misc.imsave('test_misc_toL.jpg',im, 'jpeg')
#
#  im = misc.imread('test_initImg.png',flatten = False, mode = 'RGB')
#  im_rotated = misc.imrotate(im,45,interp='bilinear')
#  im_resized = misc.imresize(im,(400,355),interp='bilinear')
#  misc.imsave('test_misc_toRGB.jpg',im, 'jpeg')
#  misc.imsave('test_misc_rotated.jpg',im_rotated, 'jpeg')
#  misc.imsave('test_misc_resized.jpg',im_resized, 'jpeg')
#  #  misc.pilutil.imshow(im)
#  print(im.shape)
#  print(im_resized.shape)
#  print(im[3][4])
#  #  print(type(im[3][4]))
#
#
#  channels = 3000
#  #  print(str(channels).encode('utf8'))
