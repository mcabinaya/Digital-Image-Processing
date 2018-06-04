#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 29 16:14:57 2018

@author: abinaya
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout, Activation, Flatten
from keras.optimizers import Adam
from keras.utils.np_utils import to_categorical 
from sklearn.model_selection import train_test_split
from keras.layers.normalization import BatchNormalization
from keras.utils import np_utils
from keras.layers import Conv2D, MaxPooling2D, ZeroPadding2D, GlobalAveragePooling2D
from keras.layers.advanced_activations import LeakyReLU 
from keras.preprocessing.image import ImageDataGenerator

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
    
    model.add(Conv2D(32, (3, 3), input_shape=(28,28,1)))
    model.add(Activation('relu'))
    BatchNormalization(axis=-1)
    model.add(Conv2D(32, (3, 3)))
    model.add(Activation('relu'))
    model.add(MaxPooling2D(pool_size=(2,2)))
    
    BatchNormalization(axis=-1)
    model.add(Conv2D(64,(3, 3)))
    model.add(Activation('relu'))
    BatchNormalization(axis=-1)
    model.add(Conv2D(64, (3, 3)))
    model.add(Activation('relu'))
    model.add(MaxPooling2D(pool_size=(2,2)))
    
    model.add(Flatten())
    
    BatchNormalization()
    model.add(Dense(512))
    model.add(Activation('relu'))
    BatchNormalization()
    model.add(Dropout(0.2))
    model.add(Dense(10))

    model.add(Activation('softmax'))
    
    model.compile(loss='categorical_crossentropy', optimizer=Adam(), metrics=['accuracy'])
    gen = ImageDataGenerator(rotation_range=8, width_shift_range=0.08, shear_range=0.3,
                             height_shift_range=0.08, zoom_range=0.08)
    
    test_gen = ImageDataGenerator()
    train_generator = gen.flow(x_train, y_train, batch_size=64)
    test_generator = test_gen.flow(X_test, Y_test, batch_size=64)
    
    fitted_model = model.fit_generator(train_generator, steps_per_epoch=60000//64, epochs=5, 
                        validation_data=test_generator, validation_steps=10000//64)
    
    train_score = model.evaluate(x_train, y_train, verbose=0)
    test_score = model.evaluate(X_test, Y_test, verbose=0)

    return fitted_model, train_score, test_score

x_train, x_val, y_train, y_val, X_test, Y_train, Y_test  = pre_preprocessing()
fitted_model, train_score, test_score = architecture_1(x_train, x_val, y_train, y_val, X_test, Y_train, Y_test)

fitted_model_df = pd.DataFrame(fitted_model.history)
fitted_model_df.to_csv('architecture_3.csv')
