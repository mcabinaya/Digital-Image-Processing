from __future__ import print_function

from itertools import product

import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt
import cv2

import scipy.misc

import pickle as cPickle

from sklearn.decomposition import PCA
from sklearn.svm import SVC
from sklearn.cluster import KMeans
from sklearn.ensemble import RandomForestClassifier

def _extract_batches(images, ks):
    (num_img, height, width, channel) = images.shape

    idx = range(0, height - ks + 1, ks) # in case index of overflow
    idy = range(0, width - ks + 1, ks)
    id_iter = [(x, y) for x in idx for y in idy]

    batches = np.array([images[:,i:i+ks,j:j+ks,:] for (i, j) in id_iter])
    print("Extracted image batch shape: " + str(batches.shape))

    batches = np.reshape(batches, [-1, ks*ks*channel])
    print("Processed image batch shape: " + str(batches.shape))

    return batches

def _fit_anchor_vectors(i , batches, ks, channel_in, lossy_rate=1, augment=True):
    # remove mean
    # print("Image mean: " + str(np.mean(batches, axis=0)))
    batches = batches - np.mean(batches, axis=0)
    # print("Image mean after removal: " + str(np.mean(batches, axis=0)))

    # fit anchor vectors
    pca = PCA()
    pca.fit(batches)

    if i==0:
        components_to_keep = 3
    elif i==1:
        components_to_keep = 4
    elif i==2:
        components_to_keep = 7
    elif i==3:
        components_to_keep = 6
    else:
        components_to_keep = 8
    
    components = pca.components_[:components_to_keep,:]
    print("Anchor vector shape: " + str(components.shape))
    print(ks * ks * channel_in )
    assert ks * ks * channel_in == components.shape[1]

    if augment:
        components = np.concatenate([components, -components], axis=0)
        components_to_keep = components_to_keep * 2
        #print("Augmented anchor vector shape: " + str(components.shape))

    # reshape anchor vectors
    components = np.reshape(components, [-1, ks, ks, channel_in])

    #print("Reshaped anchor shape: " + str(components.shape))

    # transpose anchor vectors to tensorflow format 
    # [ks, ks, channel_in, channel_out]
    components = components.transpose(1, 2, 3, 0)

    #print("Tensorflow formated anchor shape: " + str(components.shape))

    # augment anchors
    return components, components_to_keep

def conv_and_relu(images, anchors, sess, ks):
    kernel = tf.constant(anchors)
    out = tf.nn.conv2d(images, kernel, strides=[1, 2, 2, 1], padding='SAME')
    out = tf.nn.relu(out)
    result = sess.run(out)
    print("Saak coefficients shape: " + str(result.shape))
    return result


def get_saak_anchors(images, _sess=None, ks=2, max_layer=5, vis=None):
    if _sess is None:
        sess = tf.Session()
    else:
        sess = _sess

    if images.dtype == 'uint8':
        images = images.astype(np.float32)
        images = images / 255.

    anchors = []
    channel_in = images.shape[3]
    print("imageshape here")
    print(channel_in)

    rf_size = []
    n = min(images.shape[1], images.shape[2])
    while n >= ks and len(rf_size) < max_layer:
        n = n // ks
        rf_size.append(n)

    print("Start to extract Saak anchors:\n")

    # np.save('p4.npy', images)

    for i, _ in enumerate(rf_size):
        print("Stage %d start:" % (i + 1, ))
        batches = _extract_batches(images, ks)
        anchor, channel_out = _fit_anchor_vectors(i , batches, ks, channel_in)
        anchors.append(anchor)
        images = conv_and_relu(images, anchor, sess, ks)
        channel_in = channel_out

        if vis is not None:
            ind = range(len(batches))
            np.random.shuffle(ind)
            ind = ind[:1000]
            projection = np.matmul([batches[k,:] for k in ind], np.reshape(anchor[:,:,:,:2], [-1,2]))
            # np.save('p.npy', projection)
            # np.save('p2.npy', anchor)
            # np.save('p3.npy', batches)
            print("projection shape " + str(projection.shape))
            # plt.plot(projection[:,0], projection[:,1], 'o')
            plt.scatter(projection[:,0], projection[:,1])
            # plt.show()
            plt.savefig('images/' + vis)

        print("Stage %d end\n" % (i + 1, )) 

    if _sess is None:
        sess.close()

    return anchors


def display_kmeans(batches, kmeans, m=20, suffix=''):
    n = batches.shape[0]
    n_clusters = kmeans.n_clusters
    res = []
    for i in range(n_clusters):
        imgs = []
        while len(imgs) < m:
            index = np.random.randint(n)
            if kmeans.labels_[index] == i:
                # img_index = index % 256
                # patch_x = index / 256 / 16
                # patch_y = index / 256 % 16
                imgs.append(cv2.cvtColor(
                    np.reshape(batches[index,:],[2,2,3]),
                    cv2.COLOR_LAB2BGR
                    ))
        new_img = np.concatenate(imgs, axis=1)
        res.append(new_img)
        cv2.imwrite('images/voc_kmeans%s_lab_nc%d_%d.png' % (suffix, n_clusters, i), new_img)
    new_img = np.concatenate(res, axis=0)
    cv2.imwrite('images/voc_kmeans%s_lab_nc%d_all.png' % (suffix, n_clusters, ), new_img)
    img2 = cv2.imread('images/voc_kmeans%s_lab_nc%d_all.png' % (suffix, n_clusters, ))
    img2 = cv2.resize(img2, None, fx=10, fy=10, interpolation=cv2.INTER_NEAREST)
    cv2.imwrite('images/voc_kmeans%s_lab_nc%d_all_resized.png' % (suffix, n_clusters, ), img2)

    return res

def display2_kmeans(images, kmeans, kmeans2, m=20, suffix='_ca'):
    n, h, w, ch = images.shape
    nc = kmeans.n_clusters
    nc2 = kmeans2.n_clusters
    res = []
    res2 = []
    for (i,j) in product(range(nc),range(nc2)):
        imgs = []
        imgs2 = []
        while len(imgs) < m:
            index = np.random.randint(n)
            x = np.random.randint(h / 2) * 2
            y = np.random.randint(w / 2) * 2
            x2 = x / 4 * 4
            y2 = y / 4 * 4
            img1 = images[index,x:x+2,y:y+2,:]
            img2_o = images[index,x2:x2+4,y2:y2+4,:]
            img2 = cv2.resize(images[index,x2:x2+4,y2:y2+4,:],(2,2))
            img1 = np.reshape(img1, [1,12])
            img2 = np.reshape(img2, [1,12])
            lb1 = kmeans.predict(img1)
            lb2 = kmeans.predict(img2)
            if lb1 == i and lb2 == j:
                # img_index = index % 256
                # patch_x = index / 256 / 16
                # patch_y = index / 256 % 16
                imgs.append(cv2.cvtColor(
                    np.reshape(img1,[2,2,3]),
                    cv2.COLOR_LAB2BGR
                    ))
                imgs2.append(cv2.cvtColor(
                    img2_o,
                    cv2.COLOR_LAB2BGR
                    ))
        new_img = np.concatenate(imgs, axis=1)
        new_img_2 = np.concatenate(imgs2, axis=1)
        res.append(new_img)
        res2.append(new_img_2)
        cv2.imwrite('images/voc_kmeans%s_lab_nc%d_%d.png' % (suffix, nc, i), new_img)
        cv2.imwrite('images/voc_kmeans%s_lab_nc%d_%d_context.png' % (suffix, nc, i), new_img_2)

    new_img = np.concatenate(res, axis=0)
    new_img_2 = np.concatenate(res2, axis=0)

    cv2.imwrite('images/voc_kmeans%s_lab_nc%d_all.png' % (suffix, nc, ), new_img)
    img2 = cv2.imread('images/voc_kmeans%s_lab_nc%d_all.png' % (suffix, nc, ))
    img2 = cv2.resize(img2, None, fx=10, fy=10, interpolation=cv2.INTER_NEAREST)
    cv2.imwrite('images/voc_kmeans%s_lab_nc%d_all_resized.png' % (suffix, nc, ), img2)

    cv2.imwrite('images/voc_kmeans%s_lab_nc%d_all_context.png' % (suffix, nc2, ), new_img_2)
    img2 = cv2.imread('images/voc_kmeans%s_lab_nc%d_all_context.png' % (suffix, nc2, ))
    img2 = cv2.resize(img2, None, fx=10, fy=10, interpolation=cv2.INTER_NEAREST)
    cv2.imwrite('images/voc_kmeans%s_lab_nc%d_all_resized_context.png' % (suffix, nc2, ), img2)
    

def get_content_adaptive_saak_old(images, _sess=None, ks=2, n_clusters=5, vis=None):
    n, h, w, ch = images.shape

    batches = _extract_batches(images, ks)

    kmeans = KMeans(n_clusters=n_clusters)
    kmeans.fit(batches)

    # print(kmeans.labels_)

    print(kmeans.cluster_centers_)
    # display_kmeans(batches, kmeans)

    if vis is not None:
        cluster = [[] for i in range(n_clusters)]
        for k, b in enumerate(batches):
            cluster[kmeans.labels_[k]].append(b)
        for k in range(n_clusters):
            cluster[k] = np.concatenate(np.expand_dims(cluster[k], axis=0), axis=0)
            print(cluster[k].shape)
            ch = 3
            anchor, _ = _fit_anchor_vectors(cluster[k], ks, ch, augment=False)
            anchor = np.array(anchor)
            print('anchor shape: ' + str(anchor.shape))
            ind = range(len(cluster[k]))
            np.random.shuffle(ind)
            ind = ind[:200]
            t_batches = [cluster[k][l,:] for l in ind]
            # t_batches = np.concatenate(t_batches, axis=0)
            anchor = np.reshape(anchor[:,:,:,:2], [-1,2])
            proj = np.matmul(t_batches, anchor)
            plt.figure()
            plt.scatter(proj[:,0], proj[:,1])
            plt.savefig('images/%s_%d.png' % (vis, k))



    # images_ds = [cv2.resize(img, None, fx=.5, fy=.5) for img in images]
    # images_ds = np.array(images_ds)
    # batches_ds = _extract_batches(images_ds, ks)
    # kmeans2 = KMeans(n_clusters=n_clusters)
    # kmeans2.fit(batches_ds)
    # display_kmeans(batches_ds, kmeans2, suffix='_ds')

    # display2_kmeans(images, kmeans, kmeans2)

    

def classify_svm(train_feature, train_label, test_feature, test_label):
    assert train_feature.shape[1] == test_feature.shape[1]
    assert train_feature.shape[0] == train_label.shape[0]
    assert test_feature.shape[0] == test_label.shape[0]
    svc = RandomForestClassifier()
    svc.fit(train_feature, train_label)
    accuracy = svc.score(test_feature, test_label)
    return accuracy
    

