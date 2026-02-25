# Exerciții - Dimensionality Reduction (Laborator 5)

## Exercițiu 1 - PCA with make_circles

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.1,
    noise=0.01,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the PCA algorithm with 2 components, on the train set.
Compute the components, the explained variance ratio, and the inverse transformation of the 11th sample in the test set.

**Expected output:**

```
(array([[-0.76930085, 0.63888669], [ 0.63888669, 0.76930085]]), array([0.50537804, 0.49462196]), array([-0.5139503, 0.82538319]))
```

---

## Exercițiu 2 - PCA with Classification Dataset

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
Apply the PCA algorithm with 3 components on the train set.
Compute the components, the explained variance ratio, and the transformation of the 10th sample in the test set.

---

## Exercițiu 3 - PCA with Variance Preservation

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=10,
    n_informative=8,
    n_redundant=2,
    n_classes=3,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the PCA algorithm to preserve 95% of the variance on the train set.
Compute the number of components needed, the explained variance ratio, and the transformation of the 5th sample in the test set.

---

## Exercițiu 4 - PCA with Regression Dataset

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=6,
    noise=1,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the PCA algorithm with 4 components on the train set.
Compute the components, the explained variance ratio, and the inverse transformation of the 15th sample in the test set.

---

## Exercițiu 5 - PCA with make_blobs

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=4,
    centers=3,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the PCA algorithm with 2 components on the train set.
Compute the components, the explained variance ratio, and the transformation of the 8th sample in the test set.

---

## Exercițiu 6 - PCA with make_moons

Use the following code to generate a classification dataset:

```python
X, y = make_moons(
    n_samples=1000,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the PCA algorithm with 1 component on the train set.
Compute the component, the explained variance ratio, and the transformation of the 12th sample in the test set.

---

## Exercițiu 7 - Locally Linear Embedding (LLE) with S-curve

Use the following code to generate an S-shaped curve dataset:

```python
X, y = make_s_curve(
    n_samples=1000,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the locally linear embedding algorithm with 3 components and 6 neighbors, on the train set.
Compute the transformation of the 11th sample in the test set.

**Expected output:**

```
array([-0.04161236, 0.04043414, 0.01098724])
```

---

## Exercițiu 8 - LLE with Swiss Roll

Use the following code to generate a Swiss roll dataset:

```python
X, t = make_swiss_roll(
    n_samples=1000,
    noise=0.2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the locally linear embedding algorithm with 2 components and 10 neighbors on the train set.
Compute the transformation of the 20th sample in the test set.

---

## Exercițiu 9 - LLE with make_circles

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.3,
    noise=0.05,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the locally linear embedding algorithm with 2 components and 8 neighbors on the train set.
Compute the transformation of the 15th sample in the test set.

---

## Exercițiu 10 - LLE with make_moons

Use the following code to generate a classification dataset:

```python
X, y = make_moons(
    n_samples=800,
    noise=0.15,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the locally linear embedding algorithm with 2 components and 5 neighbors on the train set.
Compute the transformation of the 10th sample in the test set.

---

## Exercițiu 11 - LLE with Different Number of Neighbors

Use the following code to generate an S-shaped curve dataset:

```python
X, y = make_s_curve(
    n_samples=1000,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the locally linear embedding algorithm with 2 components and 12 neighbors on the train set.
Compute the transformation of the 5th sample in the test set.

---

## Exercițiu 12 - t-SNE with Swiss Roll

Use the following code to generate a Swiss roll dataset:

```python
X, t = make_swiss_roll(
    n_samples=1000,
    noise=0.2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the t-SNE algorithm with 2 components on the train set.
Compute the transformation of the 25th sample in the test set.

---

## Exercițiu 13 - t-SNE with make_circles

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.2,
    noise=0.05,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the t-SNE algorithm with 2 components on the train set.
Compute the transformation of the 18th sample in the test set.

---

## Exercițiu 14 - t-SNE with make_blobs

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=5,
    centers=4,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the t-SNE algorithm with 2 components on the train set.
Compute the transformation of the 30th sample in the test set.

---

## Exercițiu 15 - PCA vs LLE Comparison

Use the following code to generate a Swiss roll dataset:

```python
X, t = make_swiss_roll(
    n_samples=1000,
    noise=0.2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply both PCA with 2 components and LLE with 2 components and 10 neighbors on the train set.
Compute the transformation of the 15th sample in the test set for both methods.

---

## Exercițiu 16 - PCA with High Dimensional Data

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=20,
    n_informative=15,
    n_redundant=5,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the PCA algorithm to preserve 90% of the variance on the train set.
Compute the number of components needed, the explained variance ratio, and the transformation of the 7th sample in the test set.

---

## Exercițiu 17 - LLE with make_s_curve (Different Parameters)

Use the following code to generate an S-shaped curve dataset:

```python
X, y = make_s_curve(
    n_samples=1200,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the locally linear embedding algorithm with 2 components and 15 neighbors on the train set.
Compute the transformation of the 22nd sample in the test set.

---

## Exercițiu 18 - PCA Inverse Transformation

Use the following code to generate a classification dataset:

```python
X, y = make_classification(
    n_samples=1000,
    n_features=6,
    n_informative=6,
    n_redundant=0,
    n_classes=2,
    n_clusters_per_class=1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the PCA algorithm with 3 components on the train set.
Compute the transformation of the 9th sample in the test set, then compute its inverse transformation, and finally compute the reconstruction error for this sample.

---

## Exercițiu 19 - t-SNE with make_moons

Use the following code to generate a classification dataset:

```python
X, y = make_moons(
    n_samples=1000,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the t-SNE algorithm with 2 components on the train set.
Compute the transformation of the 14th sample in the test set.

---

## Exercițiu 20 - PCA Components and Explained Variance

Use the following code to generate a regression dataset:

```python
X, y = make_regression(
    n_samples=1000,
    n_features=8,
    noise=1.5,
    bias=2,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the PCA algorithm with 5 components on the train set.
Compute the components, the explained variance ratio, and verify that the sum of explained variance ratios is less than or equal to 1.0.

---

## Note pentru rezolvare

- Pentru PCA: `from sklearn.decomposition import PCA`
- Pentru LLE: `from sklearn.manifold import LocallyLinearEmbedding`
- Pentru t-SNE: `from sklearn.manifold import TSNE`
- Pentru dataset generation:
  - `from sklearn.datasets import make_classification, make_regression, make_circles, make_moons, make_blobs, make_s_curve, make_swiss_roll`
- Pentru split: `from sklearn.model_selection import train_test_split`
- Componentele PCA se accesează prin `.components_`
- Explained variance ratio se accesează prin `.explained_variance_ratio_`
- Pentru transformare: folosiți `.transform()` sau `.fit_transform()`
- Pentru inverse transform: folosiți `.inverse_transform()`
- Pentru PCA cu variance preservation: `PCA(n_components=0.95)` (unde 0.95 = 95% variance)
- Numărul de componente găsite se accesează prin `.n_components_` (când folosiți variance preservation)
- Pentru LLE, parametrul `n_neighbors` controlează numărul de vecini folosiți
- t-SNE este mai lent decât PCA și LLE, deci folosiți-l doar pentru vizualizare sau dataset-uri mici
- t-SNE nu are `inverse_transform()` - este doar pentru reducerea dimensionalității, nu pentru reconstrucție
- PCA centrarează automat datele, dar dacă implementați manual, trebuie să centrați: `X_centered = X - X.mean(axis=0)`
