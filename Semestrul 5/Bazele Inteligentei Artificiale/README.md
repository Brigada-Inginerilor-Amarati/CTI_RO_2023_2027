# Bazele Inteligentei Artificiale (BIA)

This repository contains materials, laboratory work, and projects for the "Bazele Inteligentei Artificiale" (Fundamentals of Artificial Intelligence) course. It serves as a comprehensive resource for understanding the core concepts of Machine Learning, implemented primarily in Python.

## Topics Covered

## Topics Covered

The laboratory work utilizes a series of Jupyter notebooks, organized into key thematic areas:

*   **Python & Machine Learning Foundations**:
    *   **Python Essentials**: Basic data types, control structures, and NumPy integration (Lab 1).
    *   **Supervised Learning**: Linear Regression (NumPy), k-Nearest Neighbors (KNN), and Decision Trees (Labs 2, 3, 4).
    *   **Unsupervised Learning**: Principal Component Analysis (PCA) for dimensionality reduction and K-means Clustering (Labs 5, 6).
*   **Deep Learning with PyTorch**:
    *   **PyTorch Fundamentals**: Data manipulation, tensors, vector/matrix operations, and broadcasting (Lab 7).
    *   **Neural Network Basics**: Implementing Linear Regression from scratch using PyTorch tensors (Lab 8).
*   **Advanced Deep Learning Architectures**:
    *   **Computer Vision**: Convolutional Neural Networks (CNNs) for image processing (Lab 9).
    *   **Sequence Modeling**: Recurrent Neural Networks (RNNs) for text and time-series data (Lab 10).
    *   **Attention Mechanisms**: Visualization of attention weights and heatmaps (Lab 11).

## Project Structure

The project is organized efficiently to separate course theory from practical implementations:

```
├── Curs/                    # Course lecture slides and theoretical materials
├── Laborator/
│   ├── Paul/               # Student lab solutions and personal implementations
│   ├── Daria/              # Additional student solutions
│   ├── Teorie/             # Core theory notebooks demonstrating algorithms
│   ├── Exercitii/          # Problem sets and exercise PDFs
│   └── Slide-uri/          # Presentation slides for laboratory sessions
└── README.md
```

## How to Run

You can run the code in this repository either locally or using cloud-based platforms like Google Colab.

### Option 1: Google Colab (Recommended for GPU)

We primarily used **Google Colab** for this project to leverage free GPU acceleration, which significantly speeds up training for complex models (especially when working with larger datasets or SVMs with RBF kernels).

1.  **Open Colab**: Go to [colab.research.google.com](https://colab.research.google.com).
2.  **Upload/Import**: 
    *   Upload the `.ipynb` file you want to run (from `Laborator/Paul/` or `Laborator/Teorie/`).
    *   Or, you can authorize Colab to access your GitHub and open files directly from this repository.
3.  **Enable GPU**:
    *   Go to **Runtime** > **Change runtime type**.
    *   Under **Hardware accelerator**, select **GPU** (e.g., T4 GPU).
    *   Click **Save**.
4.  **Run**: Execute the cells (Shift+Enter).

### Option 2: Local Installation

To run the notebooks locally, you need a Python environment with Jupyter installed.

1.  **Clone the repository**:
    ```bash
    git clone <repository-url>
    cd Bazele-Inteligentei-Artificiale
    ```

2.  **Install Dependencies**:
    It is recommended to use a virtual environment.
    ```bash
    pip install numpy scikit-learn matplotlib jupyter notebook
    ```

3.  **Launch Jupyter**:
    ```bash
    jupyter notebook
    ```
    This will open your browser. Navigate to `Laborator/Paul/` and open any `.ipynb` file to run it.

## Libraries Used

*   **NumPy**: The fundamental package for scientific computing.
*   **scikit-learn**: Simple and efficient tools for predictive data analysis.
*   **Matplotlib**: Comprehensive library for creating static, animated, and interactive visualizations.
