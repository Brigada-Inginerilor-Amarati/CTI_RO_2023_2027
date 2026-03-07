# Laboratory 4: Convolutional Neural Networks

## 1. Introduction to CNNs

A **convolutional neural network (CNN or ConvNet)** is a class of neural networks designed specifically for processing image data.

### Typical CNN Structure

A CNN typically includes three layers:

1. **Convolutional layer**
2. **Pooling layer**
3. **Fully-connected layer**

The convolutional layer is the first layer of a convolutional network. While convolutional layers can be followed by additional convolutional layers or pooling layers, the fully-connected layer is the final layer.

---

## 2. Convolutions for Images

### Core Concept

The **convolutional layer** is the core building block of a CNN, where the majority of computation occurs.

In a convolutional layer, an **input tensor** and a **kernel tensor** are combined to produce an **output tensor** through a **cross-correlation operation**.

### Cross-Correlation Operation

- Begin with the kernel positioned at the upper-left corner of the input tensor
- Slide it across the input tensor, both from left to right and top to bottom
- When the kernel is applied to an area of the input, a dot product is calculated between the input elements and the kernel
- The final output from the series of dot products is known as a **feature map**, **activation map**, or **convolved feature**

### Output Size Formula

For an input of size `nₕ × nw` and a kernel of size `kₕ × kw`:

**Output size = (nₕ - kₕ + 1) × (nw - kw + 1)**

### Example

- Input tensor: 3 × 3
- Kernel: 2 × 2
- First output element: 0×0 + 1×1 + 3×2 + 4×3 = 19

---

## 3. Padding and Stride

### Stride

**Stride** is the distance that the kernel moves over the input matrix.

- With larger strides, the output size is reduced
- Padding can be added to maintain consistent dimensions

### PyTorch Implementation

#### Padding Example

```python
X = torch.rand(1, 1, 8, 8)
conv2d = nn.Conv2d(1, 1, kernel_size=3, padding=1)
# With padding=1, one row/column is added on either side
# Total of 2 rows or columns are added
conv2d(X).shape
# Output: torch.Size([1, 1, 8, 8])
```

#### Stride Example

```python
X = torch.rand(1, 1, 8, 8)
conv2d = nn.Conv2d(1, 1, kernel_size=3, padding=1, stride=2)
conv2d(X).shape
# Output: torch.Size([1, 1, 4, 4])
```

---

## 4. Multiple Input and Output Channels

### Multiple Input Channels

When working with multiple input channels (e.g., RGB images with 3 channels), the convolution operation is performed separately on each channel, and the results are summed.

**Example:** Cross-correlation with 2 input channels (cᵢₙ = 2)

### Multiple Output Channels

A convolutional layer can have multiple output channels. Each output channel has its own kernel.

**Example:** 1 × 1 kernel with 3 input channels and 2 output channels (cᵢₙ = 3 and cₒᵤₜ = 2)

---

## 5. Pooling Layer

### Purpose

The **pooling layer** makes the representations smaller and more manageable.

### Key Characteristics

- The pooling layer contains **no parameters** (there is no kernel to learn)
- Reduces spatial dimensions

### Maximum Pooling

Takes the maximum value from a pooling window.

**Example:** 2 × 2 Max Pooling

- Input: 3 × 3 matrix
- Output: 2 × 2 matrix
- First output element: max(0, 1, 3, 4) = 4

### PyTorch Implementation

```python
X = torch.arange(16, dtype=torch.float32).reshape((1, 1, 4, 4))
print(X)

pool2d = nn.MaxPool2d(3)
pool2d(X)
# Output: tensor([[[[10.]]]])
```

**Note:** The stride and pooling window in the `nn.MaxPool2d` class have the same shape. In the example above, a pooling window of shape 3 × 3 results in a stride shape of 3 × 3 by default.

---

## 6. LeNet Architecture

**LeNet** – the first convolutional network

### Architecture Details

LeNet contains eight layers:

- **First five layers:** Convolutional
- **Remaining three layers:** Fully-connected

### PyTorch Implementation

```python
net = nn.Sequential(
    nn.Conv2d(1, 6, kernel_size=5, padding=2), nn.Sigmoid(),
    nn.AvgPool2d(kernel_size=2, stride=2),
    nn.Conv2d(6, 16, kernel_size=5), nn.Sigmoid(),
    nn.AvgPool2d(kernel_size=2, stride=2),
    nn.Flatten(),
    nn.Linear(16 * 5 * 5, 120), nn.Sigmoid(),
    nn.Linear(120, 84), nn.Sigmoid(),
    nn.Linear(84, 10)
)
```

### Testing the Network

Pass a single-channel 28 × 28 image through the network and print the output shape at each layer:

```python
X = torch.rand(1, 1, 28, 28)
for layer in net:
    X = layer(X)
    print(layer.__class__.__name__, 'output shape:\ ', X.shape)
```

**Output:**

- Conv2d: `[1, 6, 28, 28]`
- Sigmoid: `[1, 6, 28, 28]`
- AvgPool2d: `[1, 6, 14, 14]`
- Conv2d: `[1, 16, 10, 10]`
- Sigmoid: `[1, 16, 10, 10]`
- AvgPool2d: `[1, 16, 5, 5]`
- Flatten: `[1, 400]`
- Linear: `[1, 120]`
- Sigmoid: `[1, 120]`
- Linear: `[1, 84]`
- Sigmoid: `[1, 84]`
- Linear: `[1, 10]`

---

## 7. AlexNet

**Reference:** A. Krizhevsky, I. Sutskever, G. Hinton, \"ImageNet Classification with Deep Convolutional Neural Networks\", _NIPS_, 2012.

### Architecture

AlexNet contains **eight layers**:

- **First five layers:** Convolutional
- **Remaining three layers:** Fully-connected

### PyTorch Implementation

```python
net = nn.Sequential(
    # Larger 11 × 11 window with stride 4 for object capture
    nn.Conv2d(1, 96, kernel_size=11, stride=4, padding=1), nn.ReLU(),
    nn.MaxPool2d(kernel_size=3, stride=2),
    # Smaller convolution window with padding for consistent dimensions
    nn.Conv2d(96, 256, kernel_size=5, padding=2), nn.ReLU(),
    nn.MaxPool2d(kernel_size=3, stride=2),
    # Three successive convolutional layers with smaller windows
    nn.Conv2d(256, 384, kernel_size=3, padding=1), nn.ReLU(),
    nn.Conv2d(384, 384, kernel_size=3, padding=1), nn.ReLU(),
    nn.Conv2d(384, 256, kernel_size=3, padding=1), nn.ReLU(),
    nn.MaxPool2d(kernel_size=3, stride=2),
    nn.Flatten(),
    # Larger fully-connected layer outputs with dropout to mitigate overfitting
    nn.Linear(6400, 4096), nn.ReLU(),
    nn.Dropout(p=0.5),
    nn.Linear(4096, 4096), nn.ReLU(),
    nn.Dropout(p=0.5),
    # Output layer (10 classes for Fashion-MNIST instead of 1000)
    nn.Linear(4096, 10)
)
```

---

## 8. Networks Using Blocks (VGG)

### VGG Building Block

The basic building block of classic CNNs is a sequence of:

1. A convolutional layer with padding to maintain resolution
2. A nonlinearity such as ReLU
3. A pooling layer such as maximum pooling

### VGG Block

One VGG block consists of:

- A sequence of convolutional layers
- Followed by a maximum pooling layer for spatial downsampling

### VGG Block Function

```python
def vgg_block(num_convs, in_channels, out_channels):
    layers = []
    for _ in range(num_convs):
        layers.append(nn.Conv2d(in_channels, out_channels,
                                kernel_size=3, padding=1))
        layers.append(nn.ReLU())
        in_channels = out_channels
    layers.append(nn.MaxPool2d(kernel_size=2, stride=2))
    return nn.Sequential(*layers)
```

### VGG Architecture

```python
conv_arch = ((1, 64), (1, 128), (2, 256), (2, 512), (2, 512))

def vgg(conv_arch):
    conv_blks = []
    in_channels = 1
    # Convolutional part
    for (num_convs, out_channels) in conv_arch:
        conv_blks.append(vgg_block(num_convs, in_channels, out_channels))
        in_channels = out_channels

    return nn.Sequential(
        *conv_blks, nn.Flatten(),
        # Fully-connected part
        nn.Linear(out_channels * 7 * 7, 4096), nn.ReLU(), nn.Dropout(0.5),
        nn.Linear(4096, 4096), nn.ReLU(), nn.Dropout(0.5),
        nn.Linear(4096, 10)
    )

net = vgg(conv_arch)
```

---

## 9. Batch Normalization

### Motivation

- Training deep neural networks is difficult
- Getting them to converge in a reasonable amount of time can be challenging
- **Batch normalization** accelerates the convergence of deep networks

### How It Works

Batch normalization is applied to individual layers and works as follows:

1. In each training iteration, normalize the inputs by subtracting their mean and dividing by their standard deviation
2. Both mean and standard deviation are estimated based on the statistics of the current mini-batch
3. Apply a scale coefficient and a scale offset

### Formula

For an input **x** from a mini-batch **B**, batch normalization transforms **x** according to:

**BN(x) = γ ⊙ (x - μ̂ᵦ) / σ̂ᵦ + β**

Where:

- **μ̂ᵦ** is the sample mean: μ̂ᵦ = (1/|B|) Σ x
- **σ̂ᵦ** is the sample standard deviation: σ̂ᵦ² = (1/|B|) Σ (x - μ̂ᵦ)² + ε (ε > 0)
- **γ** and **β** are learnable parameters (scale and shift)

### Application

#### Fully-Connected Layers

```
h = φ(BN(Wx + b))
```

Where **x** is the input, **Wx + b** is the affine transformation, and **φ** is the activation function.

#### Convolutional Layers

- Batch normalization can be applied after convolution and before nonlinear activation
- When convolution has multiple output channels, batch normalization is needed for each channel
- Each channel has its own scale and shift parameters (both are scalars)

### PyTorch Implementation

#### BatchNorm2d (for convolutional layers)

```python
nn.Conv2d(1, 6, kernel_size=5), nn.BatchNorm2d(6), nn.Sigmoid()
```

#### BatchNorm1d (for fully-connected layers)

```python
nn.Linear(256, 120), nn.BatchNorm1d(120), nn.Sigmoid()
```

**Note:** The first parameter represents the number of output channels of the previous layer.

### Example Network with Batch Normalization

```python
net = nn.Sequential(
    nn.Conv2d(1, 6, kernel_size=5), nn.BatchNorm2d(6), nn.Sigmoid(),
    nn.AvgPool2d(kernel_size=2, stride=2),
    nn.Conv2d(6, 16, kernel_size=5), nn.BatchNorm2d(16), nn.Sigmoid(),
    nn.AvgPool2d(kernel_size=2, stride=2), nn.Flatten(),
    nn.Linear(256, 120), nn.BatchNorm1d(120), nn.Sigmoid(),
    nn.Linear(120, 84), nn.BatchNorm1d(84), nn.Sigmoid(),
    nn.Linear(84, 10)
)
```

---

## 10. Residual Networks (ResNet)

### Residual Connection

The solid line carrying the layer input **x** to the addition operator is called a **residual connection** (or **shortcut connection**).

### Architecture Comparison

- **Regular block (left):** Input → Weight layers → Activation functions → Output
- **Residual block (right):** Input → Weight layers → (+) → Activation function → Output
  - The input **x** is added directly before the final activation

### ResNet Block in PyTorch

```python
class Residual(nn.Module):
    \"\"\"The Residual block of ResNet.\"\"\"
    def __init__(self, input_channels, num_channels,
                 use_1x1conv=False, strides=1):
        super().__init__()
        self.conv1 = nn.Conv2d(input_channels, num_channels,
                               kernel_size=3, padding=1, stride=strides)
        self.bn1 = nn.BatchNorm2d(num_channels)
        self.conv2 = nn.Conv2d(num_channels, num_channels,
                               kernel_size=3, padding=1)
        self.bn2 = nn.BatchNorm2d(num_channels)
        if use_1x1conv:
            self.conv3 `

```
