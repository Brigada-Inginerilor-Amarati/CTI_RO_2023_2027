# Exerciții - Clustering (Laborator 6)

## Exercițiu 1 - Full K-means Clustering

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.5,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the full K-means clustering algorithm with K = 5, and a maximum of 10 iterations, on the train set.
Compute the label of the 5th sample in the test set, the third cluster center, the inertia on the train set, the negative inertia on the test set, and the silhouette score.

**Expected output:**

```
(0, array([-0.21019163, 0.67227348]), 104.42381022725004, -33.16508490326328, 0.08178833442790581)
```

---

## Exercițiu 2 - K-means Clustering (K=3)

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.6,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the K-means clustering algorithm with K = 3 on the train set.
Compute the label of the 11th sample in the test set, the first cluster center, the inertia on the train set, the negative inertia on the test set, and the normalized mutual information score.

**Expected output:**

```
(2, array([0.24530604, 0.53353481]), 186.75691886796457, -58.722482875379455, 0.0023875255667463614)
```

---

## Exercițiu 3 - K-means with Random Initialization

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.5,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the K-means clustering algorithm with K = 4, random initialization, and 15 consecutive initializations, on the train set.
Compute the label of the 9th sample in the test set, the second cluster center, the inertia on the train set, the negative inertia on the test set, and the adjusted Rand score.

**Expected output:**

```
(1, array([-0.6731441, -0.07718862]), 132.22416031964735, -40.94325371413339, -0.0031247277429594074)
```

---

## Exercițiu 4 - Mini-batch K-means Clustering

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.5,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the mini-batch K-means clustering algorithm with K = 3 on the train set.
Compute the label of the 8th sample in the test set, the first cluster center, the inertia on the train set, the negative inertia on the test set, and the adjusted Rand score.

**Expected output:**

```
(1, array([-0.47651268, -0.41297484]), 188.93622125753416, -59.56111648796079, -0.004755512475520349)
```

---

## Exercițiu 5 - Agglomerative Clustering (Single Linkage)

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.5,
    noise=0.1,
    random_state=42,
)
```

Apply the agglomerative clustering algorithm with 5 clusters and single linkage on this dataset.
Compute the label of the 5th sample in the dataset and the normalized mutual information score.

**Expected output:**

```
(0, 0.007673110475351361)
```

---

## Exercițiu 6 - K-means with make_blobs

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=2,
    centers=4,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the K-means clustering algorithm with K = 4 on the train set.
Compute the label of the 10th sample in the test set, the second cluster center, the inertia on the train set, and the silhouette score.

---

## Exercițiu 7 - Agglomerative Clustering (Average Linkage)

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=2,
    centers=3,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the agglomerative clustering algorithm with 3 clusters and average linkage on the train set.
Compute the label of the 15th sample in the test set and the adjusted Rand score.

---

## Exercițiu 8 - Agglomerative Clustering (Complete Linkage)

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=800,
    factor=0.4,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the agglomerative clustering algorithm with 4 clusters and complete linkage on the train set.
Compute the label of the 12th sample in the test set and the normalized mutual information score.

---

## Exercițiu 9 - DBSCAN Clustering

Use the following code to generate a classification dataset:

```python
X, y = make_moons(
    n_samples=1000,
    noise=0.05,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the DBSCAN algorithm with eps = 0.2 and min_samples = 5 on the train set.
Compute the number of clusters found, the number of noise points, and the adjusted Rand score.

---

## Exercițiu 10 - DBSCAN with Different Parameters

Use the following code to generate a classification dataset:

```python
X, y = make_moons(
    n_samples=1000,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the DBSCAN algorithm with eps = 0.15 and min_samples = 10 on the train set.
Compute the number of clusters found, the number of core samples, and the normalized mutual information score.

---

## Exercițiu 11 - K-means with make_moons

Use the following code to generate a classification dataset:

```python
X, y = make_moons(
    n_samples=1000,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the K-means clustering algorithm with K = 2 on the train set.
Compute the label of the 7th sample in the test set, the first cluster center, the inertia on the train set, and the silhouette score.

---

## Exercițiu 12 - Mini-batch K-means with make_blobs

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1500,
    n_features=2,
    centers=5,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the mini-batch K-means clustering algorithm with K = 5 on the train set.
Compute the label of the 20th sample in the test set, the third cluster center, the inertia on the train set, and the adjusted Rand score.

---

## Exercițiu 13 - Agglomerative Clustering (Ward Linkage)

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=2,
    centers=4,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the agglomerative clustering algorithm with 4 clusters and ward linkage on the train set.
Compute the label of the 18th sample in the test set and the normalized mutual information score.

---

## Exercițiu 14 - K-means with Maximum Iterations

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.5,
    noise=0.1,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the full K-means clustering algorithm with K = 6, random initialization, and a maximum of 5 iterations on the train set.
Compute the label of the 13th sample in the test set, the fourth cluster center, the inertia on the train set, and the silhouette score.

---

## Exercițiu 15 - DBSCAN on make_circles

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.3,
    noise=0.05,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the DBSCAN algorithm with eps = 0.1 and min_samples = 8 on the train set.
Compute the number of clusters found, the number of noise points, and the adjusted Rand score.

---

## Exercițiu 16 - K-means with K-means++ Initialization

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=2,
    centers=3,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the K-means clustering algorithm with K = 3 and k-means++ initialization (default) on the train set.
Compute the label of the 9th sample in the test set, all cluster centers, the inertia on the train set, and the silhouette score.

---

## Exercițiu 17 - Agglomerative Clustering (Single Linkage, Different K)

Use the following code to generate a classification dataset:

```python
X, y = make_circles(
    n_samples=1000,
    factor=0.5,
    noise=0.1,
    random_state=42,
)
```

Apply the agglomerative clustering algorithm with 3 clusters and single linkage on this dataset.
Compute the label of the 10th sample in the dataset and the adjusted Rand score.

---

## Exercițiu 18 - Mini-batch K-means with More Iterations

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=2,
    centers=4,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply the mini-batch K-means clustering algorithm with K = 4, batch_size = 100, and max_iter = 100 on the train set.
Compute the label of the 14th sample in the test set, the second cluster center, the inertia on the train set, and the normalized mutual information score.

---

## Exercițiu 19 - DBSCAN on make_blobs

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=2,
    centers=3,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 25% of the initial dataset.
Apply the DBSCAN algorithm with eps = 0.5 and min_samples = 5 on the train set.
Compute the number of clusters found, the number of core samples, and the silhouette score.

---

## Exercițiu 20 - Comparison: K-means vs Agglomerative Clustering

Use the following code to generate a classification dataset:

```python
X, y = make_blobs(
    n_samples=1000,
    n_features=2,
    centers=4,
    random_state=42,
)
```

Split the data into a train and test split, the test split being 20% of the initial dataset.
Apply both K-means with K = 4 and agglomerative clustering with 4 clusters and average linkage on the train set.
Compute and compare the inertia, silhouette score, and adjusted Rand score for both algorithms.

---

## Note pentru rezolvare

- Pentru K-means: `from sklearn.cluster import KMeans`
- Pentru Mini-batch K-means: `from sklearn.cluster import MiniBatchKMeans`
- Pentru Agglomerative Clustering: `from sklearn.cluster import AgglomerativeClustering`
- Pentru DBSCAN: `from sklearn.cluster import DBSCAN`
- Pentru dataset generation: `from sklearn.datasets import make_circles, make_moons, make_blobs`
- Pentru split: `from sklearn.model_selection import train_test_split`
- Pentru metrici: 
  - `from sklearn.metrics import silhouette_score, adjusted_rand_score, normalized_mutual_info_score`
- Pentru K-means full algorithm: `KMeans(algorithm='full', init='random', n_init=1, max_iter=value)`
- Pentru K-means cu multiple initializations: `KMeans(n_init=value)` (default este 10)
- Pentru K-means++ initialization: `KMeans(init='k-means++')` (default)
- Inertia se accesează prin `.inertia_`
- Negative inertia se accesează prin `.score(X)` (returnează -inertia)
- Cluster centers se accesează prin `.cluster_centers_`
- Labels se accesează prin `.labels_` sau prin `.predict(X)`
- Pentru agglomerative clustering, linkage poate fi: `'single'`, `'average'`, `'complete'`, `'ward'`
- Pentru DBSCAN:
  - `eps`: distanța maximă între două puncte pentru a fi considerați în același neighborhood
  - `min_samples`: numărul minim de puncte într-un neighborhood pentru a fi considerat core point
  - Noise points au label = -1
  - Core samples se accesează prin `.core_sample_indices_`
  - Components (core samples) se accesează prin `.components_`
- Pentru silhouette score: `silhouette_score(X, labels)`
- Pentru adjusted Rand score: `adjusted_rand_score(y_true, y_pred)` (necesită ground truth)
- Pentru normalized mutual information: `normalized_mutual_info_score(y_true, y_pred)` (necesită ground truth)
- K-means și Mini-batch K-means pot face predict pe date noi cu `.predict()`
- Agglomerative clustering și DBSCAN nu pot face predict pe date noi, folosiți `.fit_predict()` pe setul de antrenare

