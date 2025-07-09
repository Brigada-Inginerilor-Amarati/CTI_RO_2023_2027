import os
import pandas as pd
import matplotlib.pyplot as plt

BASE = os.path.dirname(os.path.abspath(__file__))
CSV_PATH = os.path.normpath(os.path.join(BASE, os.pardir, 'results', 'processed', 'all_results.csv'))
OUT_DIR = BASE
os.makedirs(OUT_DIR, exist_ok=True)

df = pd.read_csv(CSV_PATH)

for bm in df.benchmark.unique():
    sub = df[df.benchmark == bm]
    # pick columns based on what's available
    if 'ops' in sub.columns and 'time_s' in sub.columns:
        xcol, ycol = 'ops', 'time_s'
    elif 'size_mb' in sub.columns and 'time_ns' in sub.columns:
        xcol, ycol = 'size_mb', 'time_ns'
    elif 'rows' in sub.columns and 'time_s' in sub.columns:
        xcol, ycol = 'rows', 'time_s'
    elif 'samples' in sub.columns and 'time_s' in sub.columns:
        xcol, ycol = 'samples', 'time_s'
    else:
        # fallback to first two numeric columns
        nums = sub.select_dtypes(include='number').columns
        xcol, ycol = nums[0], nums[1]

    plt.figure()
    if len(sub) == 1:
        plt.scatter(sub[xcol], sub[ycol], s=100)
    else:
        plt.plot(sub[xcol], sub[ycol], marker='o')

    plt.xlabel(xcol)
    plt.ylabel(ycol)
    plt.title(f"{bm} performance")
    plt.savefig(os.path.join(OUT_DIR, f"{bm}.png"))
    plt.close()

print(f"Plots written to {OUT_DIR}")
