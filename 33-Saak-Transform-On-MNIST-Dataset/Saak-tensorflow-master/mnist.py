from __future__ import print_function

import argparse
import os
import sys
import time
import csv
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score
from sklearn.feature_selection import f_classif
from tensorflow.contrib.learn.python.learn.datasets.mnist import read_data_sets
from sklearn.ensemble import RandomForestClassifier
from sklearn.svm import SVC
from sklearn.decomposition import PCA
from cv2 import resize

from network import *

DATA_DIR = './data/'
MODEL_DIR = './model-mnist-train-32x32.npy'
RESTORE_MODEL_FROM = None
SAAK_COEF_DIR = './coef-mnist-test-32x32.npy'
RESTORE_COEF_FROM = None

def get_argument():
    parser = argparse.ArgumentParser(description="Compute Saak Coefficient for MNIST")
    parser.add_argument("--data-dir", type=str, default=DATA_DIR,
            help="directory to store mnist dataset")
    parser.add_argument("--model-dir", type=str, default=MODEL_DIR,
            help="directory to store extracted Saak anchor vectors")
    parser.add_argument("--restore-model-from", type=str, default=RESTORE_MODEL_FROM,
            help="stored saak model file (there will be no training if this parameter is provided)")
    parser.add_argument("--restore-coef-from", type=str, default=RESTORE_COEF_FROM,
            help="stored saak coefficients file (there will be no computation if this parameter is provided)")
    parser.add_argument("--saak-coef-dir", type=str, default=SAAK_COEF_DIR,
            help="di")
    return parser.parse_args()

def return_selected_features_by_Ftest(train_coef, labels, thr=0.999):
    f_value, p_value = f_classif(train_coef, labels)
    low_conf = p_value > 0.05
    f_value[low_conf] = 0
    where_are_NaNs = np.isnan(f_value)
    f_value[where_are_NaNs] = 0
    idx = f_value > np.sort(f_value)[::-1][int(np.count_nonzero(f_value) * thr) - 1]
    selected_feat = train_coef[:, idx]
    print('Shape of Selected Features using F-test Score'.format(selected_feat.shape))
    return selected_feat, idx
    
def return_reduced_feature_dim(feat, dim):
    pca_model = PCA(svd_solver='full', n_components=dim)
    reduced_feat = pca_model.fit_transform(feat)
    print('pca reduced feature shape is {}'.format(reduced_feat.shape))
    return reduced_feat, pca_model

def random_forest_classifier(feat, y):
    clf = RandomForestClassifier()
    print('Fit - Random Forest')
    clf.fit(feat, y)
    print('Data fitted')
    return clf

def svm_classifier(feat, y, kernel='rbf'):
    clf = SVC(kernel=kernel)
    print('Fit - SVC')
    clf.fit(feat, y)
    print('Data fitted')
    return clf

def main():
    args = get_argument()

    # initialize tf session
    sess = tf.Session()

    # load MNIST data
    mnist = read_data_sets(args.data_dir, reshape=False, validation_size=20000)
    print("Input MNIST image shape: " + str(mnist.train.images.shape))

    # resize MNIST images to 32x32
    train_images = [resize(img,(32,32)) for img in mnist.train.images]
    train_images = np.expand_dims(train_images, axis=3)
    print("Resized MNIST images: " + str(train_images.shape))

    # extract saak anchors
    if args.restore_model_from is None:
        #hari change 1
        anchors = get_saak_anchors(train_images, sess)
        np.save(args.model_dir, {'anchors': anchors})
    else:
        print("\nRestore from existing model:")
        data = np.load(args.restore_model_from).item()
        anchors = data['anchors']
        print("Restoration succeed!\n")

    # build up saak model
    print("Build up Saak model")
    model = SaakModel()
    model.load(anchors)

    # prepare testing images
    print("Prepare testing images")
    input_data = tf.placeholder(tf.float32)
    test_images = [resize(img,(32,32)) for img in mnist.test.images]
    test_images = np.expand_dims(test_images, axis=3)

    # compute saak coefficients for testing images
    if args.restore_coef_from is None:
        print("Compute saak coefficients")
        out = model.inference(input_data, layer=0)
        test_coef = sess.run(out, feed_dict={input_data: test_images})
        train_coef = sess.run(out, feed_dict={input_data: train_images})
        # save saak coefficients
        print("Save saak coefficients")
        np.save(args.saak_coef_dir, {'train': train_coef, 'test': test_coef})
    else:
        print("Restore saak coefficients from existing file")
        data = np.load(args.restore_coef_from).item()
        #reshape and save it as csv - last batch has both train and test
        train_coef = data['train']
        print(len(train_coef))
        test_coef = data['test']


    train_coef = np.reshape(train_coef, [train_coef.shape[0], -1])
    test_coef = np.reshape(test_coef, [test_coef.shape[0], -1])
    print("Saak feature dimension: " + str(train_coef.shape[1]))

    print("-- Select Features by F-test Score")
    selected_train_features, index = return_selected_features_by_Ftest(train_coef, mnist.train.labels, 0.999)
    
    print("-- Reduce Feature Dimension")
    reduced_train_features, pca_model = return_reduced_feature_dim(selected_train_features, dim = 32)
    
    print("-- Classification done by Classifier")
    clf = svm_classifier(reduced_train_features, mnist.train.labels)
    #clf = random_forest_classifier(reduced_train_feat, mnist.train.labels)
    
    predicted_train = clf.predict(reduced_train_features)
    train_acc = accuracy_score(mnist.train.labels,predicted_train )
    print('Train Accuracy: '.format(train_acc))
    
    selected_test_features = test_coef[:,index]
    reduced_test_features = pca_model.transform(selected_test_features)
    
    print("\nDo classification using SVM previousss ")
    accuracy = classify_svm(reduced_train_features, mnist.train.labels, reduced_test_features, mnist.test.labels)
    print("Test Accuracy: " % accuracy)


#################################################

if __name__ == "__main__":
    main()
