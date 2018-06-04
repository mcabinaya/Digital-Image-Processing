#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sat Mar 24 16:41:59 2018

@author: abinaya
"""

import numpy as np
import matplotlib.pyplot as plt
plt.close('all')

X = np.loadtxt('energyfeature.txt')
X = X[:,1]
X = X.reshape([12,9])
X = X.astype(int)

label_colors = ['r','g','b','r','b','r','c','c','g','c','b','g']


for i in range(0,9):
    plt.figure()
    plt.bar(X[:,i], [1]*12, color=label_colors)
    plt.title('Feature '+str(i+1))
    plt.xlabel('Feature Values')
    plt.ylabel('Count')
    plt.savefig('feature_'+str(i+1)+'.png')