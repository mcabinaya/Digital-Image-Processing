from __future__ import print_function

import os
import cv2
import numpy as np

def load_images(img_list_filename, img_dir, tsize):
    images = []
    with open(img_list_filename, 'r') as f:
        for line in f:
            img_filename = os.path.join(img_dir, line.strip() + '.jpg')
            img = cv2.imread(img_filename)
            img = cv2.resize(img, tsize)
            img = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)
            images.append(img)
    return np.array(images)

