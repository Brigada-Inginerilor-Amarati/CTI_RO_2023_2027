# Prelucrarea Imaginilor (Image Processing) - Laboratory & Coursework

This repository contains materials, solutions, and exercises for the **Image Processing (Prelucrarea Imaginilor - PI)** course. It primarily focuses on deep learning techniques applied to computer vision tasks using the **PyTorch** framework.

## Topics Covered

The coursework covers a range of fundamental and advanced topics in deep learning and image processing, demonstrated through interactive Jupyter Notebooks:

*   **PyTorch & Mathematical Fundamentals**:
    *   **Data Manipulation**: Tensors, reshapes, broadcasting, and indexing.
    *   **Linear Algebra**: Vector/matrix operations, norms, and proper dimensionality handling.
    *   **Automatic Differentiation**: Using `autograd`, backpropagation, and computational graphs.
*   **Machine Learning Basics**:
    *   **Linear Regression**: Implementation from scratch and using `nn.Linear`.
    *   **Softmax Regression**: Multi-class classification for FashionMNIST.
    *   **Optimization**: Stochastic Gradient Descent (SGD), loss functions (MSE, Cross-Entropy).
*   **Convolutional Neural Networks (CNNs)**:
    *   **Core Concepts**: Cross-correlation, padding, stride, and pooling layers.
    *   **Architectures**: Implementation of LeNet, concepts from AlexNet/VGG.
    *   **Training Dynamics**: Batch normalization, dropout, and residual connections.
*   **Recurrent Neural Networks (RNNs)**:
    *   **Sequence Modeling**: RNNs built from scratch and using `nn.RNN`.
    *   **Advanced Architectures**: Gated Recurrent Units (GRUs) for handling long-term dependencies.
    *   **Applications**: Character-level text generation and language modeling.
*   **Attention Mechanisms & Transformers**:
    *   **Attention Scoring**: Nadaraya-Watson kernel regression, additive/scaled dot-product attention.
    *   **Transformers**: Self-attention, Multi-head attention, and Encoder blocks.
    *   **Image Captioning**: Encoder-Decoder architectures combining CNNs and RNNs with attention.
*   **Object Detection**:
    *   **Single Shot Detectors (SSD)**: Anchor box generation, IoU calculation, and multi-scale feature maps.
    *   **Loss Functions**: Focal loss and Smooth L1 loss for bounding boxes.
    *   **Post-processing**: Non-Maximum Suppression (NMS).
*   **Semantic Segmentation**:
    *   **Fully Convolutional Networks (FCN)**: Transposed convolutions (upsampling) and pixel-wise classification.
    *   **Classical Techniques**: K-Means clustering and Watershed algorithm.
*   **Generative Models**:
    *   **GANs**: Generative Adversarial Networks, training stability, and Discriminator-Generator interplay.
*   **Video Processing**:
    *   **Video Classification**: Handling 3D video data (HMDB51 dataset) and video specific pipelines.

## Project Structure

The repository is organized as follows:

*   **`Curs/`**: Contains theoretical course materials and slides (PDFs).
*   **`Laborator/`**: The main directory for practical work.
    *   **`Paul/`**: Paul's personal laboratory solutions and experiments.
    *   **`Daria/`**: Daria's laboratory solutions.
    *   **`Teorie/`**: Reference implementations and theory notebooks explaining core concepts.
    *   **`Exercitii/`**: Practice problems and assignments.
    *   **`Slide-uri/`**: Slides specific to laboratory sessions.
    *   **`data/`**: Directory for storing local datasets (e.g., FashionMNIST, Pascal VOC).

## Prerequisites & Dependencies

The core projects rely on the following Python libraries:

*   **Python** 3.x
*   **PyTorch** (`torch`): The primary deep learning framework.
*   **Torchvision** (`torchvision`): For datasets, model architectures, and image transforms.
*   **NumPy** (`numpy`): For numerical operations.
*   **Matplotlib** (`matplotlib`): For visualizing data and results.
*   **Jupyter**: For running the `.ipynb` notebooks.

## How to Run

### Google Colab (Recommended)

Google Colab is highly recommended for running these notebooks, as it provides free access to GPU resources which significantly speeds up training.

1.  **Open Colab**: Go to [colab.research.google.com](https://colab.research.google.com/).
2.  **Upload/Open Notebook**:
    *   **From GitHub**: Select the "GitHub" tab and paste the URL of this repository or a specific notebook file.
    *   **Upload**: Download the `.ipynb` file from this repo and upload it to Colab.
3.  **Enable GPU**:
    *   Go to **Runtime** > **Change runtime type**.
    *   Under **Hardware accelerator**, select **T4 GPU** (or any available GPU).
    *   Click **Save**.
4.  **Run Cells**: Execute the cells sequentially. Most notebooks are self-contained and will download necessary datasets automatically.

### Local Installation

To run the projects locally, ensure you have a Python environment set up:

1.  **Clone the repository**:
    ```bash
    git clone <repository-url>
    cd Prelucrarea-Imaginilor
    ```
2.  **Install dependencies** (recommended to use a virtual environment):
    ```bash
    pip install torch torchvision numpy matplotlib jupyter
    ```
    *(Note: Visit [pytorch.org](https://pytorch.org/) for the specific installation command tailored to your system and CUDA version)*
3.  **Start Jupyter**:
    ```bash
    jupyter notebook
    ```
4.  **Open a Notebook**: Navigate to `Laborator/Paul/` (or any other folder) and open an `.ipynb` file.
