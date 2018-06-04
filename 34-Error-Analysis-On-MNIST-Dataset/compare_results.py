#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 29 17:38:46 2018

@author: abinaya
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score, confusion_matrix

df = pd.read_csv('SAAK_CNN_best.csv')

print "SAAK Accuracy Score (%): ",accuracy_score(df['Actual'], df['SAAK_Predicted'])*100
print "CNN Accuracy Score (%): ",accuracy_score(df['Actual'], df['CNN_Predicted'])*100

print "\n------------------"

cnn_error = df.loc[df['Actual']!=df['CNN_Predicted']]
print "Count of CNN Misclassified: ", len(cnn_error)
cnn_error_saak_correct = cnn_error.loc[cnn_error['Actual'] == cnn_error['SAAK_Predicted']]
print "Count of CNN Misclassified that SAAK Predicted Correctly: ", len(cnn_error_saak_correct)
print "About "+str((float(len(cnn_error_saak_correct)) / float(len(cnn_error)))*100)+"% of CNN Misclassified, SAAK predicted correctly"
print "Image Labels of this category: ", cnn_error_saak_correct['ImageId'].values

print "\n------------------"

saak_error = df.loc[df['Actual']!=df['SAAK_Predicted']]
print "Count of SAAK Misclassified: ", len(saak_error)
saak_error_cnn_correct = saak_error.loc[saak_error['Actual'] == saak_error['CNN_Predicted']]
print "Count of SAAK Misclassified that CNN Predicted Correctly: ", len(saak_error_cnn_correct)
print "About "+str((float(len(saak_error_cnn_correct)) / float(len(saak_error)))*100)+"% of SAAK Misclassified, CNN predicted correctly"
print "Image Labels of this category: ", saak_error_cnn_correct['ImageId'].values

print "\n------------------"

both_missed = df.loc[df['Actual']!=df['CNN_Predicted']]
both_missed = both_missed.loc[both_missed['Actual']!=both_missed['SAAK_Predicted']]
print "Count that Both CNN and SAAK Misclassified: ", len(both_missed)
print "Percentage of the MNIST DATASET that both Misclassified: "+str((float(len(both_missed))/float(len(df)))*100)+"%"
print "Image Labels of this category: ", both_missed['ImageId'].values

print "\n------------------"

print "Confusion Matrix for SAAK Prediction:\n", confusion_matrix(df['Actual'].values, df['SAAK_Predicted'].values)
plt.figure()
plt.imshow(confusion_matrix(df['Actual'].values, df['SAAK_Predicted'].values))
plt.colorbar()
plt.title('Confusion Matrix for Saak Predictions')
plt.ylabel('Actual Labels')
plt.xlabel('Predicted Labels')

print "\nConfusion Matrix for CNN Prediction:\n", confusion_matrix(df['Actual'].values, df['CNN_Predicted'].values)
plt.figure()
plt.imshow(confusion_matrix(df['Actual'].values, df['CNN_Predicted'].values))
plt.colorbar()
plt.title('Confusion Matrix for CNN Predictions')
plt.ylabel('Actual Labels')
plt.xlabel('Predicted Labels')