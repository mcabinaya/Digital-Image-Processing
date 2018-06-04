#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 29 16:14:57 2018

@author: abinaya
"""



import numpy as np
import pandas as pd
import keras
import matplotlib.pyplot as plt
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout, Activation, Flatten
from keras.optimizers import Adam
from keras.layers.normalization import BatchNormalization
from keras.utils.np_utils import to_categorical 
from keras.utils import np_utils
from keras.layers import Conv2D, MaxPool2D, ZeroPadding2D, GlobalAveragePooling2D
from keras.layers.advanced_activations import LeakyReLU 
from keras.preprocessing.image import ImageDataGenerator
from keras.optimizers import RMSprop
from keras.callbacks import ReduceLROnPlateau
from sklearn.model_selection import train_test_split

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

    batch_size = 64
    num_classes = 10
    epochs = 20
    input_shape = (28, 28, 1)
    
    model = Sequential()
    model.add(Conv2D(32, kernel_size=(3, 3),activation='relu',kernel_initializer='he_normal',input_shape=input_shape))
    model.add(Conv2D(32, kernel_size=(3, 3),activation='relu',kernel_initializer='he_normal'))
    model.add(MaxPool2D((2, 2)))
    model.add(Dropout(0.20))
    model.add(Conv2D(64, (3, 3), activation='relu',padding='same',kernel_initializer='he_normal'))
    model.add(Conv2D(64, (3, 3), activation='relu',padding='same',kernel_initializer='he_normal'))
    model.add(MaxPool2D(pool_size=(2, 2)))
    model.add(Dropout(0.25))
    model.add(Conv2D(128, (3, 3), activation='relu',padding='same',kernel_initializer='he_normal'))
    model.add(Dropout(0.25))
    model.add(Flatten())
    model.add(Dense(128, activation='relu'))
    model.add(BatchNormalization())
    model.add(Dropout(0.25))
    model.add(Dense(num_classes, activation='softmax'))
    
    model.compile(loss=keras.losses.categorical_crossentropy,
                  optimizer=keras.optimizers.RMSprop(),
                  metrics=['accuracy'])
    
    learning_rate_reduction = ReduceLROnPlateau(monitor='val_acc', 
                                                patience=3, 
                                                verbose=1, 
                                                factor=0.5, 
                                                min_lr=0.00001)
    
    
    
    datagen = ImageDataGenerator(
            featurewise_center=False,  # set input mean to 0 over the dataset
            samplewise_center=False,  # set each sample mean to 0
            featurewise_std_normalization=False,  # divide inputs by std of the dataset
            samplewise_std_normalization=False,  # divide each input by its std
            zca_whitening=False,  # apply ZCA whitening
            rotation_range=10,  # randomly rotate images in the range (degrees, 0 to 180)
            zoom_range = 0.1, # Randomly zoom image 
            width_shift_range=0.1,  # randomly shift images horizontally (fraction of total width)
            height_shift_range=0.1,  # randomly shift images vertically (fraction of total height)
            horizontal_flip=False,  # randomly flip images
            vertical_flip=False)  # randomly flip images
    
    
    datagen.fit(x_train)
    
    fitted_model = model.fit_generator(datagen.flow(x_train,y_train, batch_size=batch_size),
                                  epochs = epochs, validation_data = (x_val,y_val),
                                  verbose = 2, steps_per_epoch=x_train.shape[0] // batch_size
                                  , callbacks=[learning_rate_reduction])
    
    train_score = model.evaluate(x_train, y_train, verbose=0)
    test_score = model.evaluate(X_test, Y_test, verbose=0)

    return fitted_model, train_score, test_score

x_train, x_val, y_train, y_val, X_test, Y_train, Y_test  = pre_preprocessing()
fitted_model, train_score, test_score = architecture_1(x_train, x_val, y_train, y_val, X_test, Y_train, Y_test)

fitted_model_df = pd.DataFrame(fitted_model.history)
fitted_model_df.to_csv('architecture_4.csv')




