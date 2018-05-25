import pandas as pd
import numpy as np

import torch
import torch.utils.data as Data
import torch.nn as nn
import torch.nn.functional as F
import scipy.io as io
from torch.autograd import Variable

data = io.loadmat("Indian_pines.mat")['indian_pines']
label = io.loadmat("Indian_pines_gt.mat")['indian_pines_gt']
#data_train = pd.read_csv("data_train.csv")
#data_test  = pd.read_csv("data_test.csv")
class GISDataset(Data.Dataset):
    def __init__(self, data, label):
        self.data = data
        self.label = label
    def __getitem__(self, item):
        data_item = self.data.iloc[item, :-1].as_matrix()
        data_item = np.array([data_item])
        data_label = self.data.iloc[item, -1]
        return data_item, data_label
    def __len__(self):
        return len(self.data)

dataset_train = GISDataset(data.reshape(145*145, 220), label.reshape(145*145, 1))


train_loader = Data.DataLoader(
    dataset=dataset_train,
    batch_size=50,
    shuffle=True,
)

class CNN1d(nn.Module):
    def __init__(self):
        super(CNN1d, self).__init__()
        self.Conv = nn.Sequential(
            nn.Conv1d(1, 20, 21),
            nn.Tanh(),
            nn.MaxPool1d(5),
        )
        self.Fc = nn.Sequential(
            nn.Linear(36*20, 100),
            nn.Tanh(),
            nn.Linear(100, 8),
            nn.Tanh(),
        )

    def forward(self, x):
        x = self.Conv(x)
        x = x.view(-1, 36*20)
        x = self.Fc(x)
        return x

net = CNN1d()

optimizer = torch.optim.SGD(net.parameters(), lr=0.01)
loss_func = nn.CrossEntropyLoss()

for epoch in range(10):
    for i, (x, y) in enumerate(train_loader):
        b_x = (Variable(x).float()-2733)/6783
        b_y = Variable(y)

        out = net(b_x)
        loss = loss_func(out, b_y)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if i % 50 == 0:
            accuracy = sum(torch.max(out, 1)[1].data == b_y.data) / float(b_y.size(0))
            print("EPOCH: ", epoch, "LOSS: ", loss.data[0], "ACCURACY: ", accuracy)

