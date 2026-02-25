# Exerciții - Decision Trees și Ensemble Methods (Laborator 4)

## Exercițiu 1 - Decision Tree Classification

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

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the decision tree algorithm, with a minimum of 5 samples in each leaf on the train set.
Compute the feature importances, the accuracy on the test set, and the output probability distribution for the 9th sample in the test set.

**Expected output:**

```
(array([0.15505821, 0.20425957, 0.35449143, 0.28619079]), 0.852, array([[0.33333333, 0.55555556, 0.11111111]]))
```

---

## Exercițiu 2 - Decision Tree Classification (Multiclass)

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
Apply the decision tree algorithm with max_depth = 3 on the train set.
Compute the feature importances, the accuracy on the test set, and the output probability distribution for the 9th sample in the test set.

---

## Exercițiu 3 - Decision Tree Regression

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
Apply the decision tree regression algorithm with max_depth = 4 and min_samples_leaf = 5 on the train set.
Compute the mean squared error on the test set and the predicted value for the 10th sample in the test set.

---

## Exercițiu 4 - Decision Tree Regression (Different Parameters)

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=2,
    noise=1,
    bias=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the decision tree regression algorithm with max_depth = 5 and min_samples_split = 10 on the train set.
Compute the mean squared error on the test set.

---

## Exercițiu 5 - Hard Voting Ensemble

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
Apply a hard voting ensemble formed of a logistic regression algorithm, a random forest algorithm with 100 estimators, and an SVM algorithm with RBF kernel (γ = 'scale') on the train set.
Compute the accuracy on the test set.

---

## Exercițiu 6 - Soft Voting Ensemble

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
Apply a soft voting ensemble formed of a logistic regression algorithm, a random forest algorithm with 200 estimators, and a Gaussian RBF kernel SVM algorithm with γ = 1.5, on the train set.
Compute the accuracy on the test set and the output probability distribution of the 9th sample in the test set.

**Expected output:**

```
(0.912, array([[0.57070994, 0.21619792, 0.21309213]]))
```

---

## Exercițiu 7 - Soft Voting Ensemble (Binary Classification)

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=800,
    n_features=3,
    n_informative=3,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply a soft voting ensemble formed of a logistic regression algorithm, a decision tree algorithm with max_depth = 5, and a random forest algorithm with 150 estimators on the train set.
Compute the accuracy on the test set and the output probability distribution for the 15th sample in the test set.

---

## Exercițiu 8 - Bagging Classifier

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
Apply a bagging classifier with 500 decision trees, each trained on 100 samples with replacement (bootstrap = True) on the train set.
Compute the accuracy on the test set and the out-of-bag score.

---

## Exercițiu 9 - Bagging Classifier (Pasting)

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

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply a pasting classifier (bootstrap = False) with 300 decision trees, each trained on 150 samples on the train set.
Compute the accuracy on the test set.

---

## Exercițiu 10 - Random Forest Classification

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
Apply a random forest algorithm with 500 estimators and max_leaf_nodes = 16 on the train set.
Compute the feature importances, the accuracy on the test set, and the output probability distribution for the 9th sample in the test set.

---

## Exercițiu 11 - Random Forest Classification (Different Parameters)

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=5,
    n_informative=5,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply a random forest algorithm with 200 estimators, max_depth = 10, and min_samples_leaf = 4 on the train set.
Compute the feature importances and the accuracy on the test set.

---

## Exercițiu 12 - Random Forest Regression

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

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply a random forest regression algorithm with 300 estimators and max_depth = 8 on the train set.
Compute the mean squared error on the test set and the feature importances.

---

## Exercițiu 13 - Extra Trees Classifier

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
Apply an extra trees classifier with 400 estimators and max_leaf_nodes = 20 on the train set.
Compute the accuracy on the test set and the feature importances.

---

## Exercițiu 14 - AdaBoost Classification

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

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply an AdaBoost classifier with 200 decision stumps (max_depth = 1) and learning_rate = 0.5 on the train set.
Compute the accuracy on the test set and the output probability distribution for the 10th sample in the test set.

---

## Exercițiu 15 - AdaBoost Classification (Different Learning Rate)

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=800,
    n_features=4,
    n_informative=4,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply an AdaBoost classifier with 150 decision stumps and learning_rate = 1.0 on the train set.
Compute the accuracy on the test set.

---

## Exercițiu 16 - Gradient Boosting Classification

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
Apply a gradient boosting ensemble algorithm formed of 200 decision trees, each tree having a maximum depth of 3, with a learning rate of 1.2 on the train set.
Compute the feature importances, the accuracy on the test set, and the output probability distribution of the 11th sample in the test set.

**Expected output:**

```
(array([0.13183207, 0.18527228, 0.34405552, 0.33884012]), 0.892, array([[8.55051214e-14, 2.46194816e-14, 1.00000000e+00]]))
```

---

## Exercițiu 17 - Gradient Boosting Regression

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=500,
    n_features=2,
    noise=0.5,
    bias=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply a gradient boosting regression algorithm with 100 decision trees, each tree having max_depth = 2, and learning_rate = 0.1 on the train set.
Compute the mean squared error on the test set.

---

## Exercițiu 18 - Gradient Boosting Regression (Early Stopping)

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

Split the data into a train, validation, and test split. The validation split should be 20% and the test split should be 25% of the initial dataset.
Apply a gradient boosting regression algorithm with max_depth = 2, learning_rate = 0.1, and use early stopping (stop when validation error does not improve for 5 consecutive iterations) on the train set.
Compute the optimal number of trees, the mean squared error on the test set, and the feature importances.

---

## Exercițiu 19 - Decision Tree with Regularization

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

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the decision tree algorithm with max_depth = 4, min_samples_split = 10, and min_samples_leaf = 5 on the train set.
Compute the feature importances, the accuracy on the test set, and the number of leaf nodes.

---

## Exercițiu 20 - Comparison: Single Tree vs Random Forest

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
Apply both a single decision tree (with default parameters) and a random forest with 500 estimators on the train set.
Compute and compare the accuracy of both algorithms on the test set.

---

## Note pentru rezolvare

- Pentru Decision Trees: `from sklearn.tree import DecisionTreeClassifier, DecisionTreeRegressor`
- Pentru Voting: `from sklearn.ensemble import VotingClassifier`
- Pentru Bagging: `from sklearn.ensemble import BaggingClassifier, BaggingRegressor`
- Pentru Random Forest: `from sklearn.ensemble import RandomForestClassifier, RandomForestRegressor`
- Pentru Extra Trees: `from sklearn.ensemble import ExtraTreesClassifier, ExtraTreesRegressor`
- Pentru AdaBoost: `from sklearn.ensemble import AdaBoostClassifier, AdaBoostRegressor`
- Pentru Gradient Boosting: `from sklearn.ensemble import GradientBoostingClassifier, GradientBoostingRegressor`
- Pentru dataset generation: `from sklearn.datasets import make_classification, make_regression`
- Pentru split: `from sklearn.model_selection import train_test_split`
- Pentru metrici: `from sklearn.metrics import accuracy_score, mean_squared_error`
- Pentru hard voting: `VotingClassifier(estimators=[...], voting='hard')`
- Pentru soft voting: `VotingClassifier(estimators=[...], voting='soft')` (necesită `predict_proba()` pentru toți estimatorii)
- Pentru SVM cu probabilități: `SVC(probability=True)`
- Feature importances se accesează prin `.feature_importances_`
- Pentru probabilități: folosiți `.predict_proba()` pentru clasificare
- Pentru out-of-bag score: `BaggingClassifier(..., oob_score=True)` și accesați prin `.oob_score_`
- Pentru early stopping în gradient boosting: folosiți `warm_start=True` și verificați eroarea de validare la fiecare iterație
