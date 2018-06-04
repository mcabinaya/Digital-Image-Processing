from __future__ import print_function

import time
import sys
import os

import numpy as np

from sklearn.cluster import KMeans
from sklearn.cluster import MeanShift

class LayerKmeans(object):

    def __init__(self, kernel_size=2, n_clusters=5):
        self.ks = kernel_size
        self.nc = n_clusters
        self.ready = False
    
    def train(self, images):

        def cluster(images):
            patches = _gather_patches(images, self.ks)
            kmeans = KMeans(n_clusters=self.nc)
            kmeans.fit(patches)
            return kmeans, patches

        time_start = time.clock()
        kmeans_L1, patches_L1 = cluster(images)
        print('kmeans on L1 clustering cost: %.3f sec' % 
                (time.clock() - time_start, ))

        images_ds = _downsample(images, self.ks)
        print('down sample shape: ' + str(images_ds.shape))

        time_start = time.clock()
        kmeans_L2, patches_L2 = cluster(images_ds)
        print('kmeans on L2 clustering cost: %.3f sec' % 
                (time.clock() - time_start, ))

        label_L2 = np.expand_dims(kmeans_L2.labels, axis=1)
        label_L2 = np.tile(label_L2, [1,ks*ks])
        label_L2 = np.reshape(label_L2, [-1])

        Saak = [[None] * self.nc for i in range(self.nc)]

        for i in range(self.nc):
            for j in range(self.nc):
                ind = np.logical_and(kmeans_L1.labels_ == i,
                        label_L2 == j)
                patches = patches_L1[ind,:]
                Saak[i][j] = SaakStage(patches, self.ks)

        self.kmeans = [kmeans_L1, kmeans_L2]
        print('kmeans done!')

    def test_patches(self, patches, layer):
        # assert self.ready
        assert layer == 1 or layer == 2
        return self.kmeans[layer - 1].predict(patches)

    def test_images(self, images):
        # get images shape
        n, h, w, ch = images.shape
        ks = self.ks
        nc = self.nc

        # get downsampled images
        images_ds = _downsample(images, ks)
        # n_ds, h_ds, w_ds, ch_ds = images_ds.shape
        
        # get L2
        patches_L2 = _gather_patches(images_ds, ks)
        # indices_L2 = np.arange(len(patches_L2))
        label_L2 = self.test_patches(patches_L2, layer=2)
        label_L2_up = np.expand_dims(label_L2, axis=1)
        label_L2_up = np.tile(label_L2, [1, ks*ks])
        # np.save('p1_3.npy', label_L2_up)
        label_L2_up = np.reshape(label_L2_up, [-1])
        # label_L2_reshaped = _reshape_patches(label_L2, h, w, ch)
        print('label L2 shape: ' + str(label_L2.shape))
        print('label L2 up shape: ' + str(label_L2_up.shape))

        # get L1
        patches_L1 = _gather_patches(images, ks)
        # indices_L1 = np.arange(len(patches_L1))
        label_L1 = self.test_patches(patches_L1, layer=1)
        print('label L1 shape: ' + str(label_L1.shape))


        # np.save('p2.npy', label_L1)

        # np.save('p1.npy', label_L2_up)
        # np.save('p1_2.npy', label_L2)

        result = patches
        for i in range(nc):
            for j in range(nc):
                ind = np.logical_and(label_L1 == i, label_L2_up == j)
                patches = patches_L1[ind,:]
                print('L1 = %d L2 = %d: %d' 
                        % (i, j, len(patches)))
                # indices = indices_L1[ind]
        

def _gather_patches(images, ks):
    n, h, w, ch = images.shape
    p = np.array(
            [np.reshape(images[:,i:i+ks,j:j+ks,:],[-1,ks*ks*ch])
                for i in range(0, h, ks)
                for j in range(0, w, ks)
                ]
            )
    print('patch shape: ' + str(p.shape))

    p = p.transpose([1,0,2])
    print('patch shape: ' + str(p.shape))

    p = np.reshape(p, [-1,ks*ks*ch])
    print('patch shape: ' + str(p.shape))

    return p


def _reshape_patches(patches, h, w, ch):
    images = np.reshape(patches, [-1, h, w, ch])
    return images

def _downsample(images, scale):
    n, h, w, ch = images.shape
    patches = _gather_patches(images, ks=scale)
    k = len(patches)
    patches = np.reshape(patches, [k, -1, ch])
    patches = np.mean(patches, axis=1)
    images_ds = _reshape_patches(patches, h / scale, w / scale, ch)
    return images_ds


if __name__ == '__main__':
    lk = LayerKmeans()

    images = np.load('images_voc12_train_32x32_lab.npy')
    L = np.expand_dims(images[:,:,:,0], axis=3)
    A = np.expand_dims(images[:,:,:,1], axis=3)
    B = np.expand_dims(images[:,:,:,2], axis=3)

    lk.train(L)
    lk.test_images(L)

