# harness/parse_results.py
import pandas as pd
import os

# list of (benchmark name, raw csv path, its two column names)
files = [
    ("int",  "../results/raw/int.csv",  ["ops",     "time_s"]),
    ("flt",  "../results/raw/flt.csv",  ["ops",     "time_s"]),
    ("lat",  "../results/raw/lat.csv",  ["size_mb", "time_ns"]),
    ("bw",   "../results/raw/bw.csv",   ["size_mb", "time_ns"]),
    ("sort", "../results/raw/sort.csv", ["n",       "time_s"]),
    ("sql",  "../results/raw/sql.csv",  ["rows",    "time_s"]),
    ("ml",   "../results/raw/ml.csv",   ["samples", "time_s"]),
    ("cache","../results/raw/cache_latency.csv",       ["size_kb",     "latency_ns"]),
    ("thread_scalability","../results/raw/thread_scalability.csv", ["threads",     "time_s"]),  # or ["threads,ops","time_s"] if you want to plot ops vs time

]

# read and normalize timing data
timing_frames = []
for name, path, cols in files:
    df = pd.read_csv(path)
    df = df.rename(columns={cols[0]: "x", cols[1]: "y"})
    df["benchmark"] = name
    timing_frames.append(df[["benchmark","x","y"]])
timing_df = pd.concat(timing_frames, ignore_index=True)

# 2) System‐monitor summaries
# we’ll add avg_cpu_pct, max_mem_mb, and optionally avg_gpu_pct, avg_gpu_mem_pct
timing_df["avg_cpu_pct"]     = None
timing_df["max_mem_mb"]      = None
timing_df["avg_gpu_pct"]     = None
timing_df["avg_gpu_mem_pct"] = None

for bm in timing_df.benchmark.unique():
    # CPU monitor log
    cpu_log = f"../results/raw/{bm}_sys.csv"
    if os.path.exists(cpu_log):
        sysdf = pd.read_csv(cpu_log)
        timing_df.loc[timing_df.benchmark==bm, "avg_cpu_pct"] = sysdf.cpu_pct.mean()
        timing_df.loc[timing_df.benchmark==bm, "max_mem_mb"]  = sysdf.mem_mb.max()
    # GPU monitor log
    gpu_log = f"../results/raw/{bm}_gpu.csv"
    if os.path.exists(gpu_log):
        gpudf = pd.read_csv(gpu_log)
        timing_df.loc[timing_df.benchmark==bm, "avg_gpu_pct"]     = gpudf.util_gpu_pct.mean()
        timing_df.loc[timing_df.benchmark==bm, "avg_gpu_mem_pct"] = gpudf.util_mem_pct.mean()

# 3) Write out the fully‐processed table
os.makedirs("../results/processed", exist_ok=True)
timing_df.to_csv("../results/processed/all_results.csv", index=False)
print("Wrote merged results + utilization to results/processed/all_results.csv")