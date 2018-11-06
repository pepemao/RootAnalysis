# -*- coding: utf-8 -*-
"""NeuralNetwork_svfit.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/115tg28iGM8AjLbZPAa9gtpvPYgL_p0di
"""

from numpy.random import seed
seed(1)
from tensorflow import set_random_seed
set_random_seed(2)
validation_split_seed = 3

import tensorflow as tf
import numpy as np
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import pickle

def load_data():
    with open("htt_features_train.pkl", "rb") as input:
        legs, jets, global_params, properties =pickle.load(input)
    print("no of legs: ", len(legs))
    print("no of jets: ", len(jets))
    print("params: ", global_params.keys(), properties.keys())
    return legs, jets, global_params, properties

#preparing flat data and target numpy arrays
def prepare_data(legs, jets, global_params, properties, to_predict):
    data = []
    def add_legs():
        for leg in legs:
            for prop in leg:
                data.append(prop)
    def add_jets():
        for leg in jets:
            for prop in leg:
                data.append(prop)
    def add_globals(labels):
        for key in global_params:
            if key!=to_predict and key in labels:
                data.append(global_params[key])
    def add_properties(labels):
        for key in properties:
            if key!=to_predict and key in labels:
                data.append(properties[key])
    add_legs()
    add_jets()
    global_features = global_params.keys()  - ["caMass"]
    print("global_features:",global_features)
    add_globals(global_features)
    add_properties(properties.keys())    
    data = np.array(data)
    data = np.transpose(data)
    
    if to_predict in global_params.keys(): target = np.array(global_params[to_predict])
    elif to_predict in properties.keys(): target = np.array(properties[to_predict])
    else:
        raise ValueError("`to_predict`: (" + to_predict + ") does not match any key")
    target = np.transpose(target)
    print("data.shape : ", data.shape)
    print("target.shape : ", target.shape)
    return data, target

#model definition
def get_model():
    model = tf.keras.Sequential()
    model.add(tf.keras.layers.Dense(64, input_dim = data.shape[1], activation="relu"))
    model.add(tf.keras.layers.Dense(64, input_dim = data.shape[1], activation="relu"))
    model.add(tf.keras.layers.Dense(64, input_dim = data.shape[1], activation="relu"))
    model.add(tf.keras.layers.Dense(1, activation="linear"))
    # beta1 is decay added to improve stability
    model.compile(optimizer=tf.train.AdamOptimizer(beta1=0.99),
                  loss='mse')
    print(model.summary())
    return model

def plot_preds(x_train, x_val, y_train, y_val, model):
    y_train_pred = model.predict(x_train)
    plt.scatter(y_train,y_train_pred, c="g",label="training")
    y_val_pred = model.predict(x_val)
    plt.scatter(y_val,model.predict(x_val), c="b",label="validation")
    plt.plot(y_train, y_train)
    plt.legend()
    plt.xlabel("target mass")
    plt.ylabel("predicted mass")
    plt.show()

    y_val_pred = np.reshape(y_val_pred, y_val.shape)
    error = (y_val_pred - y_val)/y_val
    plt.hist(error, bins=60, range=(-0.5,0.5))
    plt.xlabel("(y_pred - y_target)/y_target")
    plt.show()

history = np.empty((2,0))
def clean_history():
    global history
    history = np.empty((2,0))
def update_history(h):
    global history
    history = np.append(history, [h.history['loss'], h.history['val_loss']],axis=1)
def plot_history():
    plt.plot(history[0], label='train')
    plt.plot(history[1], label='validation')
    plt.title('model loss')
    plt.ylabel('loss')
    plt.xlabel('epoch')
    plt.legend()
    plt.show()

#data preparation
legs, jets, global_params, properties = load_data()
to_predict = "genMass"
data, target = prepare_data(legs, jets, global_params, properties, to_predict)
#splitting data between train and validation set
x_train, x_val, y_train, y_val = train_test_split(data, target, train_size=0.9, random_state=validation_split_seed)

# training parameters

plot_steps = 4
epochs_per_plot_step = 15

#training and plotting

model = get_model()
clean_history()

plot_preds(x_train, x_val, y_train, y_val, model)

for plot_step in range(plot_steps):
    h = model.fit(x=x_train, y=y_train, epochs=epochs_per_plot_step, verbose=1, batch_size=64, callbacks=None, validation_data=(x_val,y_val))
    plot_preds(x_train, x_val, y_train, y_val, model)
    update_history(h)
    plot_history()

