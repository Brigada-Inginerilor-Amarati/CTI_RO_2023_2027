import numpy as np, time, sys, csv

def benchmark(n):
    data = np.random.rand(n)
    t0 = time.time()
    np.sort(data)
    t1 = time.time()
    return t1 - t0

if __name__ == "__main__":
    ns = [10**6, 5*10**6, 10**7]
    with open(sys.argv[1], "w", newline='') as f:
        writer = csv.writer(f)
        writer.writerow(["n","time_s"])
        for n in ns:
            t = benchmark(n)
            print(f"{n},{t:.6f}")
            writer.writerow([n, f"{t:.6f}"])