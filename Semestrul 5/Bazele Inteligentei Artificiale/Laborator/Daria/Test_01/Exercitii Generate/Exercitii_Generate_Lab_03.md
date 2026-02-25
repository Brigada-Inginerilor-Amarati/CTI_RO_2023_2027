# Exerciții - k-NN și SVM (Laborator 3)

## Exercițiu 1 - k-Nearest Neighbors Classification

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=4,
    n_informative=4,
    n_redundant=0,
    n_classes=3,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the k-nearest neighbors algorithm with k = 5 on the train set.
Compute the accuracy on the test set.

---

## Exercițiu 2 - k-NN with Different k Values

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the k-nearest neighbors algorithm with k = 3 on the train set.
Compute the accuracy on the test set and the predicted class for the 10th sample in the test set.

---

## Exercițiu 3 - Linear Hard Margin SVM

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=500,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the linear hard margin SVM algorithm (C = +∞) on the train set.
Compute w, b, the number of support vectors, and the accuracy on the test set.

---

## Exercițiu 4 - Linear Soft Margin SVM

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the linear soft margin SVM algorithm with C = 100 for 100000 epochs on the train set.
Compute w, b, the second support vector, the accuracy on the test set, and the output probability distribution for the 8th sample in the test set.

**Expected output:**

```
(array([[-0.94011825, 2.42225277]]), array([1.82388098]), array([2.1141893, -0.33704769]), 0.912, array([[0.22098076, 0.77901924]]))
```

---

## Exercițiu 5 - Linear Soft Margin SVM with Different C

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the linear soft margin SVM algorithm with C = 0.1 on the train set.
Compute w, b, the number of support vectors, and the accuracy on the test set.

---

## Exercițiu 6 - Polynomial Kernel SVM for Classification

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=4,
    n_informative=4,
    n_redundant=0,
    n_classes=3,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the polynomial kernel SVM algorithm with degree = 3, coefficient = 1, C = 10, and epsilon = 1 for 10000 epochs on the train set.
Compute the third support vector, the accuracy on the test set, and the output probability distribution for the 9th sample in the test set.

**Expected output:**

```
(array([-1.69489734, -1.34942283, 0.1541163, 0.55650619]), 0.9, array([[0.4477966, 0.3628446, 0.1893588]]))
```

---

## Exercițiu 7 - Polynomial Kernel SVM for Regression

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=2,
    noise=1,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the polynomial kernel SVM algorithm with degree = 2, coefficient = 0.5, C = 2, and epsilon = 1 for 5000 epochs on the train set.
Compute the second support vector and the mean squared error on the test set.

**Expected output:**

```
(array([0.11422765, 0.15030176]), 0.9818168401064361)
```

---

## Exercițiu 8 - Polynomial Kernel SVM Regression (Different Parameters)

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=5,
    noise=1,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the polynomial kernel SVM algorithm with degree 2, coefficient 0.5, C = 2 and gamma = 1 for MNIST dataset on the train set.
Compute the second support vector and the mean squared error on the test set.

**Expected output:**

```
(array([[0.11426769, 3.11010176]]), 0.9511148401064861)
```

---

## Exercițiu 9 - Gaussian RBF Kernel SVM for Regression

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=2,
    noise=2,
    bias=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the Gaussian RBF kernel SVM algorithm with γ = 0.0005, C = 1000, and ε = 1 for 4000 epochs on the train set.
Compute the third support vector and the mean squared error on the test set.

**Expected output:**

```
(array([1.15811087, 0.79166269]), 3.9410634511101237)
```

---

## Exercițiu 10 - Gaussian RBF Kernel SVM for Classification

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=3,
    n_informative=3,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the Gaussian RBF kernel SVM algorithm with γ = 0.1, C = 100 on the train set.
Compute the accuracy on the test set and the number of support vectors.

---

## Exercițiu 11 - Linear SVM Regression

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=500,
    n_features=1,
    noise=0.5,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the linear SVM regression algorithm with ε = 0.5, C = 100 on the train set.
Compute the number of support vectors and the mean squared error on the test set.

---

## Exercițiu 12 - Linear SVM Regression with Different Epsilon

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=500,
    n_features=1,
    noise=0.5,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the linear SVM regression algorithm with ε = 1.5, C = 100 on the train set.
Compute the number of support vectors and the mean squared error on the test set.

---

## Exercițiu 13 - Polynomial Kernel SVM Regression (High Degree)

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=2,
    noise=1.5,
    bias=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the polynomial kernel SVM regression algorithm with degree = 4, coefficient = 2, C = 5, and ε = 0.5 for 3000 epochs on the train set.
Compute the first support vector and the mean squared error on the test set.

---

## Exercițiu 14 - k-NN with Distance Weighting

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=3,
    n_informative=3,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the k-nearest neighbors algorithm with k = 7 and weights = 'distance' on the train set.
Compute the accuracy on the test set and the predicted probabilities for the 5th sample in the test set.

---

## Exercițiu 15 - Gaussian RBF Kernel SVM with Different Gamma

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the Gaussian RBF kernel SVM algorithm with γ = 5, C = 0.001 on the train set.
Compute the accuracy on the test set and the number of support vectors.

---

## Exercițiu 16 - Linear SVM with SGD

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the linear SVM using stochastic gradient descent with loss = 'hinge', penalty = 'l2', alpha = 0.1, and max_iter = 1000 on the train set.
Compute w, b, and the accuracy on the test set.

---

## Exercițiu 17 - Polynomial Kernel SVM Classification (Binary)

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=800,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the polynomial kernel SVM algorithm with degree = 3, coefficient = 1, C = 5 on the train set.
Compute the accuracy on the test set and the predicted class probabilities for the 15th sample in the test set.

---

## Exercițiu 18 - k-NN Regression

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=2,
    noise=1,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the k-nearest neighbors regression algorithm with k = 5 on the train set.
Compute the mean squared error on the test set and the predicted value for the 10th sample in the test set.

---

## Exercițiu 19 - Gaussian RBF Kernel SVM Regression (Different Parameters)

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=3,
    noise=1.5,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the Gaussian RBF kernel SVM regression algorithm with γ = 0.01, C = 100, and ε = 0.5 for 5000 epochs on the train set.
Compute the second support vector and the mean squared error on the test set.

---

## Exercițiu 20 - Comparison: k-NN vs Linear SVM

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=4,
    n_informative=4,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply both the k-nearest neighbors algorithm with k = 5 and the linear soft margin SVM algorithm with C = 1 on the train set.
Compute and compare the accuracy of both algorithms on the test set.

---

## Note pentru rezolvare

- Pentru k-NN: `from sklearn.neighbors import KNeighborsClassifier, KNeighborsRegressor`
- Pentru Linear SVM: `from sklearn.svm import LinearSVC, LinearSVR, SVC`
- Pentru Kernel SVM: `from sklearn.svm import SVC, SVR`
- Pentru SGD SVM: `from sklearn.linear_model import SGDClassifier`
- Pentru dataset generation: `from sklearn.datasets import make_classification, make_regression`
- Pentru split: `from sklearn.model_selection import train_test_split`
- Pentru metrici: `from sklearn.metrics import accuracy_score, mean_squared_error`
- Pentru hard margin SVM: folosiți `SVC(kernel='linear', C=float('inf'))`
- Pentru soft margin SVM: folosiți `LinearSVC(C=value, loss='hinge')` sau `SVC(kernel='linear', C=value)`
- Pentru polynomial kernel: `SVC(kernel='poly', degree=d, coef0=coef, C=c)` sau `SVR(kernel='poly', degree=d, coef0=coef, C=c, epsilon=eps)`
- Pentru RBF kernel: `SVC(kernel='rbf', gamma=gamma, C=c)` sau `SVR(kernel='rbf', gamma=gamma, C=c, epsilon=eps)`
- Support vectors se accesează prin `.support_vectors_`
- Coeficienții w se accesează prin `.coef_` și interceptul b prin `.intercept_`
- Pentru probabilități: folosiți `.predict_proba()` pentru clasificare
