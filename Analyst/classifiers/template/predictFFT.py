import tensorflow as tf
import numpy as np
import os
import argparse
import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 5006


#set up a socket for UDP logging
sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP

parser = argparse.ArgumentParser(description='FFT ML prediction')
#filepredict ="samples-3mHhnbFPxa8iuJj6.npy"
parser.add_argument('filepredict', action="store")
results = parser.parse_args()

classes = [d for d in os.listdir('training_data') if os.path.isdir(os.path.join('training_data', d))]
num_classes = len(classes)

samples = []
iq_samples = np.load(results.filepredict)
iq_samples = np.fft.fft(iq_samples)
iq_samples = np.reshape(iq_samples, (-1, 128, 1))
samples.append(iq_samples)
samples = np.array(samples)

x_batch = samples.reshape(1, 500, 128, 1)

sess = tf.Session()
saver = tf.train.import_meta_graph('model.meta')
saver.restore(sess, tf.train.latest_checkpoint('./'))

graph = tf.get_default_graph()
y_pred = graph.get_tensor_by_name("y_pred:0")
x = graph.get_tensor_by_name("x:0")
y_true = graph.get_tensor_by_name("y_true:0")
y_test_samples = np.zeros((1, num_classes))

feed_dict_testing = {x: x_batch, y_true: y_test_samples}
result = sess.run(y_pred, feed_dict=feed_dict_testing)

print()
print(classes)
print(result)

str1 = ",".join(str(x) for x in classes)
str2 = ",".join(str(x) for x in result)

str3 = str1 + ":" + str2
sock.sendto(str3, (UDP_IP, UDP_PORT))

