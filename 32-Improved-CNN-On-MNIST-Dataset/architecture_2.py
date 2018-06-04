#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 29 16:14:57 2018

@author: abinaya
"""


import numpy as np # linear algebra
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from keras.datasets import mnist
from keras.utils.np_utils import to_categorical # convert to one-hot-encoding
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten, Conv2D, MaxPool2D, BatchNormalization
from keras.optimizers import Adam
from keras.preprocessing.image import ImageDataGenerator
from keras.callbacks import LearningRateScheduler
import pandas as pd

np.random.seed(25)

def pre_preprocessing(): 
    (X_train, y_train), (X_test, y_test) = mnist.load_data()
    
    X_train = X_train.reshape(X_train.shape[0], 28, 28, 1)
    X_test = X_test.reshape(X_test.shape[0], 28, 28, 1)
    
    X_train = X_train.astype('float32')
    X_test = X_test.astype('float32')
    
    X_train/=255
    X_test/=255
    
    
    number_of_classes = 10
    
    Y_train = to_categorical(y_train, number_of_classes)
    Y_test = to_categorical(y_test, number_of_classes)
    
    random_seed = 2
    
    x_train, x_val, y_train, y_val = train_test_split(X_train, Y_train, test_size = 0.1, random_state=random_seed)
    
    return x_train, x_val, y_train, y_val, X_test, Y_train, Y_test

def architecture_1(x_train, x_val, y_train, y_val, X_test, Y_train, Y_test):
    model = Sequential()
    
    model.add(Conv2D(filters = 16, kernel_size = (3, 3), activation='relu',
                     input_shape = (28, 28, 1)))
    model.add(BatchNormalization())
    model.add(Conv2D(filters = 16, kernel_size = (3, 3), activation='relu'))
    model.add(BatchNormalization())
    model.add(MaxPool2D(strides=(2,2)))
    model.add(Dropout(0.25))
    
    model.add(Conv2D(filters = 32, kernel_size = (3, 3), activation='relu'))
    model.add(BatchNormalization())
    model.add(Conv2D(filters = 32, kernel_size = (3, 3), activation='relu'))
    model.add(BatchNormalization())
    model.add(MaxPool2D(strides=(2,2)))
    model.add(Dropout(0.25))
    
    model.add(Flatten())
    model.add(Dense(512, activation='relu'))
    model.add(Dropout(0.25))
    model.add(Dense(1024, activation='relu'))
    model.add(Dropout(0.5))
    model.add(Dense(10, activation='softmax'))
    
    datagen = ImageDataGenerator(zoom_range = 0.1,
                                height_shift_range = 0.1,
                                width_shift_range = 0.1,
                                rotation_range = 10)
    
    model.compile(loss='categorical_crossentropy', optimizer = Adam(lr=1e-4), metrics=["accuracy"])
    
    annealer = LearningRateScheduler(lambda x: 1e-3 * 0.9 ** x)
    
    fitted_model = model.fit_generator(datagen.flow(x_train, y_train, batch_size=16),
                               steps_per_epoch=500,
                               epochs=20, #Increase this when not on Kaggle kernel
                               verbose=2,  #1 for ETA, 0 for silent
                               validation_data=(x_val[:400,:], y_val[:400,:]), #For speed
                               callbacks=[annealer])
    
    train_score = model.evaluate(x_train, y_train, verbose=0)
    test_score = model.evaluate(X_test, Y_test, verbose=0)
    
    return fitted_model, train_score, test_score

x_train, x_val, y_train, y_val, X_test, Y_train, Y_test  = pre_preprocessing()
fitted_model, train_score, test_score = architecture_1(x_train, x_val, y_train, y_val, X_test, Y_train, Y_test)

fitted_model_df = pd.DataFrame(fitted_model.history)
fitted_model_df.to_csv('architecture_2.csv')
