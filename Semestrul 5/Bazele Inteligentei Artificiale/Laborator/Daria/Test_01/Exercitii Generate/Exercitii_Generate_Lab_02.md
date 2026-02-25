# Exerciții - Regresie și Clasificare

## Exercițiu 1 - Ridge Regression

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=2,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the ridge regression algorithm with λ = 0.2 on the train set.
Compute w, w0, and the mean squared error on the test set.

**Expected output:**

```
(array([16.72745169]), 2.981569554579661, 4.315212551575999)
```

---

## Exercițiu 2 - SGD Regression with L2 Regularization

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=0.5,
    bias=3,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 15% of the initial dataset.
Apply the stochastic gradient descent regression algorithm with ℓ2 regularization with λ = 0.01, for 150 epochs, with a constant learning rate η = 0.005 on the train set.
Compute w, w0, and the mean squared error on the test set.

**Expected output:**

```
(array([16.5730716]), array([2.96446862]), 0.2826888309401727)
```

---

## Exercițiu 3 - SGD Regression without Regularization

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=1,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the stochastic gradient descent regression algorithm with no regularization for 100 epochs with a constant learning rate η = 0.005 on the train set.
Compute w, w0, and the mean squared error on the test set.

**Expected output:**

```
(array([16.74232235]), array([1.98795322]), 1.0791838748150104)
```

---

## Exercițiu 4 - Lasso Regression

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=0.1,
    bias=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the lasso regression algorithm with λ = 0.01 on the train set.
Compute w, w0, and the mean squared error on the test set.

**Expected output:**

```
(array([16.73813334]), 0.9998273193495221, 0.010476633888361446)
```

---

## Exercițiu 5 - Ridge Regression (Different Parameters)

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1500,
    n_features=1,
    noise=1.5,
    bias=2.5,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the ridge regression algorithm with λ = 0.5 on the train set.
Compute w, w0, and the mean squared error on the test set.

---

## Exercițiu 6 - SGD Regression with L2 Regularization (Different Learning Rate)

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=0.8,
    bias=1.5,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the stochastic gradient descent regression algorithm with ℓ2 regularization with λ = 0.05, for 200 epochs, with a constant learning rate η = 0.01 on the train set.
Compute w, w0, and the mean squared error on the test set.

---

## Exercițiu 7 - Lasso Regression (Higher Regularization)

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=0.3,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the lasso regression algorithm with λ = 0.1 on the train set.
Compute w, w0, and the mean squared error on the test set.

---

## Exercițiu 8 - Elastic Net Regression

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=0.5,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the elastic net regression algorithm with λ = 0.1 and l1_ratio = 0.5 on the train set.
Compute w, w0, and the mean squared error on the test set.

---

## Exercițiu 9 - SGD Regression with L1 Regularization

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=1.2,
    bias=1.8,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the stochastic gradient descent regression algorithm with ℓ1 regularization with λ = 0.02, for 120 epochs, with a constant learning rate η = 0.008 on the train set.
Compute w, w0, and the mean squared error on the test set.

---

## Exercițiu 10 - Binary Classification with Logistic Regression

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the logistic regression algorithm with C = 1.0 (default) on the train set.
Compute the accuracy, precision, recall, and F1 score on the test set.

---

## Exercițiu 11 - Binary Classification with Regularized Logistic Regression

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_classes=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the logistic regression algorithm with ℓ2 regularization (C = 0.1, which corresponds to λ = 10) on the train set.
Compute the accuracy, precision, recall, and F1 score on the test set.

---

## Exercițiu 12 - Multiclass Classification with Softmax Regression

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=4,
    n_informative=4,
    n_redundant=0,
    n_classes=3,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the softmax regression algorithm (LogisticRegression with multi_class="multinomial") with C = 10 on the train set.
Compute the accuracy and the confusion matrix on the test set.

---

## Exercițiu 13 - Binary Classification (Different Dataset Parameters)

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1500,
    n_features=3,
    n_informative=3,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the logistic regression algorithm with C = 0.5 on the train set.
Compute the accuracy, precision, recall, and F1 score on the test set.

---

## Exercițiu 14 - Ridge Regression with Multiple Features

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=3,
    noise=1,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the ridge regression algorithm with λ = 0.1 on the train set.
Compute w (all coefficients), w0, and the mean squared error on the test set.

---

## Exercițiu 15 - SGD Regression with Early Stopping

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=0.5,
    bias=2,
    random_state=42,
)
```

Split the data into a train, validation, and test split. The validation split should be 15% and the test split should be 20% of the initial dataset.
Apply the stochastic gradient descent regression algorithm with ℓ2 regularization with λ = 0.01, with a constant learning rate η = 0.005 on the train set.
Use early stopping based on the validation set (stop when validation error stops improving for 10 consecutive epochs).
Compute w, w0, and the mean squared error on the test set using the best model.

---

## Exercițiu 16 - Polynomial Regression

Use the following code to generate a regression dataset:

```python
np.random.seed(42)
n = 200
X = 6 * np.random.rand(n, 1) - 3
y = 0.5 * X**2 + X + 2 + np.random.randn(n, 1).ravel()
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply polynomial regression with degree = 2 on the train set.
Compute the coefficients (including the polynomial features), the intercept, and the mean squared error on the test set.

---

## Exercițiu 17 - Ridge Regression with Polynomial Features

Use the following code to generate a regression dataset:

```python
np.random.seed(42)
n = 200
X = 6 * np.random.rand(n, 1) - 3
y = 0.5 * X**2 + X + 2 + np.random.randn(n, 1).ravel()
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply ridge regression with polynomial features (degree = 2) and λ = 0.1 on the train set.
Compute the coefficients, the intercept, and the mean squared error on the test set.

---

## Exercițiu 18 - Batch Gradient Descent Implementation

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=500,
    n_features=1,
    noise=1,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Implement batch gradient descent manually (without using sklearn) with learning rate η = 0.1 for 1000 epochs on the train set.
Compute w, w0, and the mean squared error on the test set.

---

## Exercițiu 19 - Mini-Batch Gradient Descent

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=1,
    noise=0.8,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Implement mini-batch gradient descent manually with batch_size = 32, learning rate η = 0.05 for 500 epochs on the train set.
Compute w, w0, and the mean squared error on the test set.

---

## Exercițiu 20 - Normal Equation Solution

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=500,
    n_features=2,
    noise=1,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Solve the linear regression problem using the normal equation (closed-form solution) on the train set.
Compute w (all coefficients), w0, and the mean squared error on the test set.

---

## Note pentru rezolvare

- Pentru regresie, folosiți `from sklearn.datasets import make_regression`
- Pentru clasificare, folosiți `from sklearn.datasets import make_classification`
- Pentru split, folosiți `from sklearn.model_selection import train_test_split`
- Pentru metrici, folosiți `from sklearn.metrics import mean_squared_error, accuracy_score, precision_score, recall_score, f1_score, confusion_matrix`
- Pentru Ridge: `from sklearn.linear_model import Ridge`
- Pentru Lasso: `from sklearn.linear_model import Lasso`
- Pentru Elastic Net: `from sklearn.linear_model import ElasticNet`
- Pentru SGD: `from sklearn.linear_model import SGDRegressor` (pentru regresie) sau `SGDClassifier` (pentru clasificare)
- Pentru Logistic Regression: `from sklearn.linear_model import LogisticRegression`
- Pentru Polynomial Features: `from sklearn.preprocessing import PolynomialFeatures`
