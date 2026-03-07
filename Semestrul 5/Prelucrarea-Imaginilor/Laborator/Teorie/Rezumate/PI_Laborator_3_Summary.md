# Laboratory 3: Multilayer Perceptrons - Summary

## Overview

This lab covers building and training multilayer perceptron (MLP) neural networks using PyTorch, focusing on practical implementation of deep learning concepts.

---

## Key Topics Covered

### 1. Linear Regression in PyTorch

#### Creating Synthetic Dataset

Creating synthetic datasets with the formula: **y = Xw + b + ε**

```python
def synthetic_data(w, b, num_examples):
    \"\"\"Generate y = Xw + b + noise.\"\"\"
    X = torch.normal(0, 1, (num_examples, len(w)))
    y = X @ w + b
    y += torch.normal(0, 0.01, y.shape)
    return X, y.reshape(-1, 1)

true_w = torch.tensor([2, -3.4])
true_b = 4.2
features, labels = synthetic_data(true_w, true_b, 1000)
```

**Result**: y = 2x₁ - 3.4x₂ + 4.2 + ε; X ∈ ℝ^(1000×2)

#### Data Loading

Using `DataLoader` for mini-batch training - shuffle the dataset and access it in mini-batches:

```python
def load_array(data_arrays, batch_size, is_train=True):
    \"\"\"Construct a PyTorch data iterator.\"\"\"
    dataset = torch.utils.data.TensorDataset(*data_arrays)
    return torch.utils.data.DataLoader(dataset, batch_size, shuffle=is_train)

batch_size = 10
data_iter = load_array((features, labels), batch_size)
```

#### Model Definition

Define the linear regression model, initialize parameters, specify loss function and optimizer:

```python
net = nn.Sequential(nn.Linear(2, 1))

net[0].weight.data.normal_(0, 0.01)
net[0].bias.data.fill_(0)

loss = nn.MSELoss()

optimizer = torch.optim.SGD(net.parameters(), lr=0.03)
```

**Note**: `nn.MSELoss` class computes the mean squared error (without ½ factor); it returns the average loss over examples.

#### Training Loop

Steps for training the linear regression model:

1. Generate predictions (net(X)) and compute the loss (forward propagation)
2. Calculate gradients by running the backpropagation, using the backward() function on the loss
3. Update the model parameters using optimizer.step()

The update formula: **w ← w - η∇_w L(w)**

```python
num_epochs = 3
for epoch in range(num_epochs):
    for X, y in data_iter:
        l = loss(net(X), y)
        optimizer.zero_grad()
        l.backward()
        optimizer.step()
    l = loss(net(features), labels)
    print(f'Epoch {epoch + 1}, Loss {l:f}')
```

---

### 2. Softmax Regression in PyTorch

#### Dataset

Fashion-MNIST dataset (28 × 28 images, 10 classes, 60000 training images, 10000 test images)

```python
def load_data_fashion_mnist(batch_size, resize=None):
    \"\"\"Download the Fashion-MNIST dataset and then load it into memory.\"\"\"
    trans = [transforms.ToTensor()]
    if resize:
        trans.insert(0, transforms.Resize(resize))
    trans = transforms.Compose(trans)

    mnist_train = torchvision.datasets.FashionMNIST(
        root=\"../data\", train=True, transform=trans, download=True)
    mnist_test = torchvision.datasets.FashionMNIST(
        root=\"../data\", train=False, transform=trans, download=True)

    return (torch.utils.data.DataLoader(mnist_train, batch_size, shuffle=True),
            torch.utils.data.DataLoader(mnist_test, batch_size, shuffle=False))

batch_size = 256
train_iter, test_iter = load_data_fashion_mnist(batch_size)
```

**Splits**:

- train set: 50000
- validation set: 10000
- test set: 10000

#### Model Definition

Define the softmax regression model:

```python
net = nn.Sequential(nn.Flatten(), nn.Linear(784, 10))

def init_weights(m):
    if type(m) == nn.Linear:
        nn.init.normal_(m.weight, std=0.01)

net.apply(init_weights)

loss = nn.CrossEntropyLoss()

optimizer = torch.optim.SGD(net.parameters(), lr=0.1)
```

**Architecture**:

- 784 = 28 × 28 (flattened image)
- 10 classes → output dimension of 10

---

### 3. Softmax Regression Training Process

#### Training Methods

The training process employs the following methods:

- `evaluate_accuracy`: computes the accuracy for a model on a dataset
- `train_epoch`: trains the model for one epoch
- `train`: trains the model for multiple epochs

#### Evaluate Accuracy Function

```python
def evaluate_accuracy(net, data_iter):
    \"\"\"Compute the accuracy for a model on a dataset.\"\"\"
    total_loss = 0
    total_hits = 0
    total_samples = 0
    net.eval()  # Set to evaluation mode
    for X, y in data_iter:
        X_hat = net(X)
        l = loss(X_hat, y)
        y_hat_class = torch.argmax(X_hat, dim=1)
        total_loss += loss(X_hat, y).item() * y.numel()
        total_hits += (y_hat_class == y).sum().item()
        total_samples += y.numel()

    return total_loss / total_samples, total_hits / total_samples
```

**Result**: total_hits = number of correct predictions

#### Train Epoch Function

```python
def train_epoch(net, train_iter, loss, optimizer):
    \"\"\"Train the model for one epoch.\"\"\"
    net.train()  # Set to training mode
    total_loss = 0
    total_hits = 0
    total_samples = 0
    for X, y in train_iter:
        # Compute gradients and update parameters
        y_hat = net(X)
        l = loss(y_hat, y)
        optimizer.zero_grad()
        l.backward()
        optimizer.step()

        total_loss += l.item() * y.numel()
        total_hits += (torch.argmax(y_hat, dim=1) == y).sum().item()
        total_samples += y.numel()

    # Return training loss (red_loss_all) and training accuracy (val_acc_all)
    return total_loss / total_samples, total_hits / total_samples
```

#### Train Function

Train the model for multiple epochs, which is specified by num_epochs:

```python
def train(net, train_iter, val_iter, loss, num_epochs, optimizer):
    \"\"\"Train a model.\"\"\"
    train_loss_all = []
    train_acc_all = []
    val_loss_all = []
    val_acc_all = []

    for epoch in range(num_epochs):
        train_loss, train_acc = train_epoch(net, train_iter, loss, optimizer)
        train_loss_all.append(train_loss)
        train_acc_all.append(train_acc)

        val_loss, val_acc = evaluate_accuracy(net, val_iter)
        val_loss_all.append(val_loss)
        val_acc_all.append(val_acc)

    return train_loss_all, train_acc_all, val_loss_all, val_acc_all
```

#### Training Execution

Train the model for 10 epochs:

```python
num_epochs = 10
train_loss_all, train_acc_all, val_loss_all, val_acc_all = train(net, train_iter, val_iter, loss, num_epochs, optimizer)
```

---

### 4. Multilayer Perceptrons (MLPs)

#### Architecture

A **multilayer perceptron (MLP)** is a fully-connected multilayer neural network.

The outputs **O** ∈ ℝ^(n×q) of the one-hidden-layer MLP are computed as follows:

**H** = σ(**XW**⁽¹⁾ + **b**⁽¹⁾)  
**O** = **HW**⁽²⁾ + **b**⁽²⁾

where:

1. **X** ∈ ℝ^(n×d) is the matrix of n examples, where each example has d features
2. **H** ∈ ℝ^(n×h) represents the outputs of the hidden layer
3. σ(·) is the activation function
4. **W**⁽¹⁾ ∈ ℝ^(d×h), **b**⁽¹⁾ ∈ ℝ^(1×h) are the hidden-layer weights and biases
5. **W**⁽²⁾ ∈ ℝ^(h×q), **b**⁽²⁾ ∈ ℝ^(1×q) are the output-layer weights and biases

**Note**: Conventionally, we do not consider the input layer when counting layers, L = 2 layers in Figure 1.

#### Common Activation Functions

**1. Rectified Linear Unit (ReLU)**:

```
ReLU(x) = max(x, 0)
```

**2. Parameterized ReLU (pReLU)**:

```
pReLU(x) = max(0, x) + α·min(0, x)
```

**3. Sigmoid**:

```
sigmoid(x) = 1/(1 + e^(-x)) ∈ (0, 1)
```

**4. Hyperbolic Tangent (tanh)**:

```
tanh(x) = (1 - e^(-2x))/(1 + e^(-2x))
```

---

### 5. MLPs in PyTorch

#### Example MLP Architecture

MLP with two hidden layers using ReLU activation function:

```python
net = nn.Sequential(
    nn.Flatten(),
    nn.Linear(784, 256),
    nn.ReLU(),
    nn.Dropout(0.2),
    nn.Linear(256, 64),
    nn.ReLU(),
    nn.Dropout(0.3),
    nn.Linear(64, 10)
)

print(net)
```

**Output structure**:

```
Sequential(
  (0): Flatten(start_dim=1, end_dim=-1)
  (1): Linear(in_features=784, out_features=256, bias=True)
  (2): ReLU()
  (3): Dropout(p=0.2, inplace=False)
  (4): Linear(in_features=256, out_features=64, bias=True)
  (5): ReLU()
  (6): Dropout(p=0.3, inplace=False)
  (7): Linear(in_features=64, out_features=10, bias=True)
)
```

This creates:

- MLP with two hidden layers
- ReLU activation function is employed
- Dropout regularization (20% after first layer, 30% after second layer)

---

### 6. Model Selection, Overfitting, and Underfitting

#### Key Concepts

**Goal of Machine Learning**:

- The goal of machine learning algorithms is to **discover patterns** in the training dataset (images, text, sounds, etc.)

**Generalization**:

- The fundamental problem of machine learning is to discover patterns that **generalize** (i.e., successfully assess the performance for never encountered samples (test data))

**Overfitting**:

- The phenomenon of fitting the training data more closely than we fit the underlying distribution is **overfitting**
- The techniques used to prevent overfitting are **regularization techniques**

**Model Selection**:

- **Model selection** is the process of selecting the final model after evaluating several candidate models
- For example, with MLPs we wish to compare models with different number of hidden layers, different number of hidden units, various choices of activation functions

**Underfitting**:

- If the generalization gap between our training and validation errors is small, we have reason to believe that we could use a more complex model
- This phenomenon is known as **underfitting**

**Validation Dataset**:

- A **validation dataset** is employed for selecting the final model

---

### 7. Regularization Techniques

#### Weight Decay (L₂ Regularization)

**Weight decay** (ℓ₂ regularization) technique replaces the original objective, minimizing the prediction loss on the training labels, with the new objective, minimizing the sum of the prediction loss and the penalty term.

For example, consider the MSE loss given by:

```
L(w) = (1/n) Σᵢ₌₁ⁿ (1/2)(ŷ⁽ⁱ⁾ - y⁽ⁱ⁾)²
```

For the one-hidden-layer MLP (Figure 1), the new objective is:

```
L(w) + (λ/2)(||W⁽¹⁾||²_F + ||W⁽²⁾||²_F)
```
