#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 29 19:43:07 2018

@author: abinaya
"""

from __future__ import print_function
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import keras
from keras.datasets import mnist

(x_train, y_train), (x_test, y_test) = mnist.load_data()

im_id = 9729
im = x_test[im_id,:,:]

plt.figure()
plt.imshow(im, cmap='gray')
plt.title('Test MNIST - Image Id - '+str(im_id+1))