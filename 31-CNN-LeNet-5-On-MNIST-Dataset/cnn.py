#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 22 16:02:15 2018

@author: abinaya
"""
from __future__ import print_function
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import keras
from keras.datasets import mnist
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten, Activation
from keras.layers import Conv2D, MaxPooling2D
from keras import backend as K

class LeNet_5_MNIST_Dataset():
    
    def __init__(self, img_rows, img_cols, num_classes, activation_func, dropout_value, optimizer, 
                 learning_rate_val, decay_val, weight_initialization, epochs_val):
        self.img_rows = img_rows
        self.img_cols = img_cols
        self.num_classes = num_classes
        
        self.activation_func = activation_func
        self.dropout_value = dropout_value
        
        self.optimizer = optimizer
        self.learning_rate_val = learning_rate_val
        self.decay_val = decay_val
        self.weight_initialization = weight_initialization
    
        self.epochs_val = epochs_val
        self.batch_size_val = 512
    
    def load_dataset(self):
        (self.x_train, self.y_train), (self.x_test, self.y_test) = mnist.load_data()

    def preprocess_dataset(self):
        if K.image_data_format() == 'channels_first':
            self.x_train = self.x_train.reshape(self.x_train.shape[0], 1, self.img_rows, self.img_cols)
            self.x_test = self.x_test.reshape(self.x_test.shape[0], 1, self.img_rows, self.img_cols)
            self.input_shape = (1, self.img_rows, self.img_cols)
        else:
            self.x_train = self.x_train.reshape(self.x_train.shape[0], self.img_rows, self.img_cols, 1)
            self.x_test = self.x_test.reshape(self.x_test.shape[0], self.img_rows, self.img_cols, 1)
            self.input_shape = (self.img_rows, self.img_cols, 1)

        self.x_train = self.x_train.astype('float32')
        self.x_test = self.x_test.astype('float32')
        self.x_train /= 255
        self.x_test /= 255

        print('x_train shape:', self.x_train.shape)
        print(self.x_train.shape[0], 'train samples')
        print(self.x_test.shape[0], 'test samples')
        
        self.y_train = keras.utils.to_categorical(self.y_train, self.num_classes)
        self.y_test = keras.utils.to_categorical(self.y_test, self.num_classes)

    def fit_model(self):
        filter_size = 5
        max_pool_size = 2
        
        num_filters_conv_layer1 = 6
        num_filters_conv_layer2 = 16
        num_filters_fc_layer1 = 120
        num_filters_fc_layer2 = 84
        num_filters_fc_layer3 = self.num_classes
        
        
        ### Define model
        self.model = Sequential()
        
        self.model.add(Conv2D(num_filters_conv_layer1, kernel_size=(filter_size,filter_size), padding='same',
                              activation=self.activation_func, kernel_initializer=self.weight_initialization, input_shape=self.input_shape))
        self.model.add(MaxPooling2D(pool_size=(max_pool_size,max_pool_size)))
        self.model.add(Dropout(self.dropout_value)) 
        
        self.model.add(Conv2D(num_filters_conv_layer2, kernel_size=(filter_size,filter_size), activation=self.activation_func, kernel_initializer=self.weight_initialization))
        self.model.add(MaxPooling2D(pool_size=(max_pool_size,max_pool_size)))
        self.model.add(Dropout(self.dropout_value)) 

        self.model.add(Flatten())
        
        self.model.add(Dense(num_filters_fc_layer1, activation=self.activation_func, kernel_initializer=self.weight_initialization,))
         
        self.model.add(Dense(num_filters_fc_layer2, activation=self.activation_func, kernel_initializer=self.weight_initialization,))
         
        self.model.add(Dense(num_filters_fc_layer3, activation='softmax', kernel_initializer=self.weight_initialization))
        
        ### Compile and fit
        
        if self.optimizer == 'SGD':
            self.model.compile(loss=keras.losses.categorical_crossentropy, 
                           optimizer=keras.optimizers.SGD(lr=self.learning_rate_val, momentum=0.9, decay=self.decay_val),
                           metrics=['accuracy'])
            
        elif self.optimizer == 'RMSprop':
            self.model.compile(loss=keras.losses.categorical_crossentropy, 
                           optimizer=keras.optimizers.RMSprop(lr=self.learning_rate_val, decay=self.decay_val),
                           metrics=['accuracy'])
            
        elif self.optimizer == 'Adagrad':
            self.model.compile(loss=keras.losses.categorical_crossentropy, 
                           optimizer=keras.optimizers.Adagrad(lr=self.learning_rate_val, decay=self.decay_val),
                           metrics=['accuracy'])
            
        elif self.optimizer == 'Adadelta':
            self.model.compile(loss=keras.losses.categorical_crossentropy, 
                           optimizer=keras.optimizers.Adadelta(lr=self.learning_rate_val, decay=self.decay_val),
                           metrics=['accuracy'])
            
        elif self.optimizer == 'Adam':
            self.model.compile(loss=keras.losses.categorical_crossentropy, 
                           optimizer=keras.optimizers.Adam(lr=self.learning_rate_val, decay=self.decay_val),
                           metrics=['accuracy'])
            
        self.fitted_model = self.model.fit(self.x_train, self.y_train, batch_size=self.batch_size_val, epochs=self.epochs_val, verbose=1, validation_data=(self.x_test, self.y_test))
        
        self.train_score = self.model.evaluate(self.x_train, self.y_train, verbose=1)
        self.test_score = self.model.evaluate(self.x_test, self.y_test, verbose=1)
        
        return self.fitted_model, self.train_score, self.test_score



activation_list = ['linear', 'selu', 'relu', 'tanh', 'sigmoid']
dropout_list = [0.2, 0.5]
optmizer_list = ['SGD', 'Adadelta', 'Adam', 'Adagrad', 'RMSprop']
lr_decay_list = [0.01, 0.1, 0.5]
weight_initialization_list = ['glorot_uniform','RandomUniform']
max_epochs = 1

count = 100
result_df = pd.DataFrame(columns=['Activation','Dropout','Optimizer','lr_decay_val','Weight_Initialization','Train_loss', 'Train_accuracy', 'Test_loss', 'Test_accuracy'])

### Run for different activation functions
for activation in activation_list:
    for dropout_val in dropout_list:
        for optmizer in optmizer_list:
            for lr_decay_val in lr_decay_list:
                for weight_initialization in weight_initialization_list:
                    
                    my_LeNet5 = LeNet_5_MNIST_Dataset(img_rows=28, img_cols=28, num_classes=10, activation_func=activation, dropout_value=dropout_val, optimizer=optmizer,
                                          learning_rate_val=lr_decay_val, decay_val=lr_decay_val,weight_initialization = weight_initialization, epochs_val=max_epochs)
                    my_LeNet5.load_dataset()
                    my_LeNet5.preprocess_dataset()
                    fitted_model, train_score, test_score = my_LeNet5.fit_model()
                    
                    fitted_model_df = pd.DataFrame(fitted_model.history)
                    fitted_model_df.to_csv('drive/CNN/fitted_model_df_history_'+str(count)+'.csv')
                    
                    result_df.loc[count,'Activation'] = activation
                    result_df.loc[count,'Dropout'] = dropout_val
                    result_df.loc[count,'Optimizer'] = optmizer
                    result_df.loc[count,'lr_decay_val'] = lr_decay_val
                    result_df.loc[count,'Weight_Initialization'] = weight_initialization
                    result_df.loc[count,'Train_loss'] = train_score[0]
                    result_df.loc[count,'Train_accuracy'] = train_score[1]
                    result_df.loc[count,'Test_loss'] = test_score[0]
                    result_df.loc[count,'Test_accuracy'] = test_score[1]
                    result_df.to_csv('drive/CNN/result_df_'+str(count)+'.csv')
                    
                    count+=1
