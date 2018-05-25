import pandas as pd
import numpy as np

import torch
import torch.utils.data as Data
import torch.nn as nn
import torch.nn.functional as F
from torch.autograd import Variable

file = "data_all.csv"

data = pd.read_csv(file)

class GISDataset(Data.Dataset):
    def __init__(self, data):
        self.data = data
    def __getitem__(self, item):
        data_item = self.data.iloc[item, :-1].as_matrix()
        return data_item
    def __len__(self):
        return len(self.data)

dataset = GISDataset(data)

train_loader = Data.DataLoader(
    dataset=dataset,
    batch_size=1,
    shuffle=True,
)

class AutoEncoder(nn.Module):
    def __init__(self):
        super(AutoEncoder, self).__init__()

        self.encoder = nn.Sequential(
            nn.Linear(200, 100),
            nn.Tanh(),
            nn.Linear(100, 50),
            nn.Tanh(),
            nn.Linear(50, 10),
        )

        self.decoder = nn.Sequential(
            nn.Linear(10, 50),
            nn.Tanh(),
            nn.Linear(50, 100),
            nn.Tanh(),
            nn.Linear(100, 200),
        )

    def forward(self, x):
        encoded  = self.encoder(x)
        decoded  = self.decoder(encoded)
        return encoded, decoded

autoencoder = AutoEncoder()

optimizer = torch.optim.Adam(autoencoder.parameters(), lr=0.01)
loss_func = nn.MSELoss()

for epoch in range(3):
    for step, x in enumerate(train_loader):
        inp = Variable(x).float()/6000
        encoded, decoded = autoencoder(inp)
        loss = loss_func(decoded, inp)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if step % 100 == 0:
            print("Epoch:", epoch, "|train loss %.4f" %loss.data[0])

out1 = pd.DataFrame(columns=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 'class'])

for i in range(len(data)):
    inp = Variable(torch.FloatTensor(data.iloc[i,:-1].as_matrix()))/6000
    encoded, decoded = autoencoder(inp)
    out1.loc[i] = np.append(encoded.data.numpy(),data.iloc[i,-1])

out1.to_csv("To10_"+file)

out2 = pd.DataFrame(columns=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 'class'])
file = "data_train.csv"
data = pd.read_csv(file)

for i in range(len(data)):
    inp = Variable(torch.FloatTensor(data.iloc[i,:-1].as_matrix()))/6000
    encoded, decoded = autoencoder(inp)
    out2.loc[i] = np.append(encoded.data.numpy(),data.iloc[i,-1])

out2.to_csv("To10_"+file)

out3 = pd.DataFrame(columns=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 'class'])
file = "data_test.csv"
data = pd.read_csv(file)

for i in range(len(data)):
    inp = Variable(torch.FloatTensor(data.iloc[i,:-1].as_matrix()))/6000
    encoded, decoded = autoencoder(inp)
    out3.loc[i] = np.append(encoded.data.numpy(),data.iloc[i,-1])

out3.to_csv("To10_"+file)

