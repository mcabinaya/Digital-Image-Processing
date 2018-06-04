from __future__ import print_function

import numpy as np
import tensorflow as tf

class SaakModel(object):

    def __init__(self, trainable=False):
        self.trainable = trainable

    def load(self, anchors):
        self.anchors = anchors

    def build(self):
        pass

    def _create_kernel(self, kernel, name):
        with tf.name_scope(name):
            if self.trainable:
                w = tf.Variable(kernel, name='w')
            else:
                w = tf.constant(kernel, name='w')
        return w

    def inference(self, data, layer=None):
        """
        @ data: a placeholder for image batch
        @       [batch_size, height, width, channel]
        """
        if self.anchors is None:
            raise Exception('No initialization for Saak model!')
        if layer is None:
            layer = len(self.anchors)
        out = data
        for i, kernel in enumerate(self.anchors):
            w = self._create_kernel(kernel, 'stage%d' % (i + 1, ))
            out = tf.nn.conv2d(out, w, strides=[1, 2, 2, 1], padding='SAME')
            out = tf.nn.relu(out)
            if i == layer:
                break
        return out
