import time, sys, csv
from sklearn.ensemble import RandomForestClassifier
from sklearn.datasets import make_classification

if __name__ == "__main__":
    Sizes = [10_000, 50_000, 100_000, 200_000]
    with open(sys.argv[1], 'w', newline='') as f:
        w = csv.writer(f)
        w.writerow(["samples","time_s"])
        for n in Sizes:
            X, y = make_classification(n_samples=n, n_features=20)
            clf = RandomForestClassifier(n_estimators=10)
            clf.fit(X, y)

            t0 = time.time()
            clf.predict(X)
            t1 = time.time()
            elapsed = t1 - t0

            w.writerow([n, f"{elapsed:.6f}"])
            print(f"{n},{elapsed:.6f}")
