from __future__ import print_function

import argparse
import os
import sys
import time

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt


from tensorflow.contrib.learn.python.learn.datasets.mnist import read_data_sets
# from scipy.misc import imresize
from cv2 import resize

from network import *

# from network.model import SaakModel
# from network.util import get_saak_anchors

DATA_DIR = '/home/yeji/dataset/PASCAL12/VOCdevkit/VOC2012/JPEGImages'
IMG_LIST = '/home/yeji/dataset/PASCAL12/VOCdevkit/VOC2012/ImageSets/Segmentation/train.txt'
MODEL_DIR = './model-voc12-train-32x32.npy'
RESTORE_MODEL_FROM = None
SAAK_COEF_DIR = './coef-voc12-test-32x32.npy'
RESTORE_COEF_FROM = None

def get_argument():
    parser = argparse.ArgumentParser(description="Compute Saak Coefficient for MNIST")
    parser.add_argument("--data-dir", type=str, default=DATA_DIR,
            help="directory to store VOC12 dataset")
    parser.add_argument("--img-list", type=str, default=IMG_LIST,
            help="file to store VOC12 image names")
    parser.add_argument("--model-dir", type=str, default=MODEL_DIR,
            help="directory to store extracted Saak anchor vectors")
    parser.add_argument("--restore-model-from", type=str, default=RESTORE_MODEL_FROM,
            help="stored saak model file (there will be no training if this parameter is provided)")
    parser.add_argument("--restore-coef-from", type=str, default=RESTORE_COEF_FROM,
            help="stored saak coefficients file (there will be no computation if this parameter is provided)")
    parser.add_argument("--saak-coef-dir", type=str, default=SAAK_COEF_DIR,
            help="di")
    return parser.parse_args()

def main():
    args = get_argument()

    # initialize tf session
    sess = tf.Session()

    # load MNIST data
    # images = voc12.load_images(args.img_list, args.data_dir, (32,32))
    # print("Input VOC12 image shape: " + str(images.shape))
    # np.save('images_voc12_train_32x32_lab.npy', images)
    images = np.load('images_voc12_train_32x32_lab.npy')

    train_images = np.array(images, dtype=np.float32) / 255.
    # print(train_images)

    # extract saak anchors
    if args.restore_model_from is None:
        anchors = get_saak_anchors(train_images, sess, max_layer=1, vis='scatter_all.png')
        np.save(args.model_dir, {'anchors': anchors})
    else:
        print("\nRestore from existing model:")
        data = np.load(args.restore_model_from).item()
        anchors = data['anchors']
        print("Restoration succeed!\n")

    # extract context adaptive saak anchors
    get_content_adaptive_saak(images, vis='scatter_ca')

    return

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
        train_coef = data['train']
        test_coef = data['test']


    # fit svm classifier
    train_coef = np.reshape(train_coef, [train_coef.shape[0], -1])
    test_coef = np.reshape(test_coef, [test_coef.shape[0], -1])
    print("Saak feature dimension: " + str(train_coef.shape[1]))

    print("\nDo classification using SVM")
    accuracy = classify_svm(train_coef, mnist.train.labels, test_coef, mnist.test.labels)
    print("Accuracy: %.3f" % accuracy)

if __name__ == "__main__":
    main()
