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
from keras.layers import Dense, Dropout, Flatten, Conv2D, MaxPooling2D, BatchNormalization
from keras.optimizers import RMSprop
from keras.preprocessing.image import ImageDataGenerator
from keras.callbacks import LearningRateScheduler, ReduceLROnPlateau
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
    
    return  x_train, x_val, y_train, y_val, X_test, Y_train, Y_test

def architecture_1(x_train, x_val, y_train, y_val, X_test, Y_train, Y_test):
    model = Sequential()
    model.add(Conv2D(filters = 32, kernel_size = (5,5),padding = 'Same', 
                 activation ='relu', input_shape = (28,28,1)))
    model.add(Conv2D(filters = 32, kernel_size = (5,5),padding = 'Same', 
                 activation ='relu'))
    model.add(MaxPooling2D(pool_size=(2,2)))
    model.add(Dropout(0.25))
    
    
    model.add(Conv2D(filters = 64, kernel_size = (3,3),padding = 'Same', 
                 activation ='relu'))
    model.add(Conv2D(filters = 64, kernel_size = (3,3),padding = 'Same', 
                 activation ='relu'))
    model.add(MaxPooling2D(pool_size=(2,2), strides=(2,2)))
    model.add(Dropout(0.25))

    model.add(Flatten())
    model.add(Dense(256, activation = "relu"))
    model.add(Dropout(0.5))
    model.add(Dense(10, activation = "softmax"))
    
    optimizer = RMSprop(lr=0.001, rho=0.9, epsilon=1e-08, decay=0.0)
    model.compile(optimizer = optimizer , loss = "categorical_crossentropy", metrics=["accuracy"])
    learning_rate_reduction = ReduceLROnPlateau(monitor='val_acc', 
                                            patience=3, 
                                            verbose=1, 
                                            factor=0.5, 
                                            min_lr=0.00001)
    epochs = 30 
    batch_size = 86


    datagen = ImageDataGenerator(
            rotation_range=10, 
            zoom_range = 0.1, 
            width_shift_range=0.1, 
            height_shift_range=0.1,  
            horizontal_flip=False,  
            vertical_flip=False)  
    
    
    datagen.fit(x_train)

    fitted_model = model.fit_generator(datagen.flow(x_train,x_train, batch_size=batch_size),
                              epochs = epochs, validation_data = (x_val,x_val),
                              verbose = 2, steps_per_epoch=x_train.shape[0] // batch_size
                              , callbacks=[learning_rate_reduction])
        
    train_score = model.evaluate(x_train, y_train, verbose=0)
    test_score = model.evaluate(X_test, Y_test, verbose=0)

    return fitted_model, train_score, test_score

x_train, x_val, y_train, y_val, X_test, Y_train, Y_test  = pre_preprocessing()
fitted_model, train_score, test_score = architecture_1(x_train, x_val, y_train, y_val, X_test, Y_train, Y_test)

fitted_model_df = pd.DataFrame(fitted_model.history)
fitted_model_df.to_csv('architecture_4.csv')




