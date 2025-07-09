#!/usr/bin/env bash
set -e

mkdir -p ../results/raw ../results/processed ../plots

# Compile microbenchmarks
gcc -O3 ../microbenchmarks/integer_throughput.c -o ../microbenchmarks/integer_throughput
gcc -O3 ../microbenchmarks/float_throughput.c -o ../microbenchmarks/float_throughput -lm
gcc -O3 ../microbenchmarks/mem_latency.c -o ../microbenchmarks/mem_latency
gcc -O3 ../microbenchmarks/mem_bandwidth.c -o ../microbenchmarks/mem_bandwidth
gcc -O3 -fopenmp ../microbenchmarks/thread_scalability.c -o ../microbenchmarks/thread_scalability
# gcc -O3 ../microbenchmarks/cache_latency.c -o ../microbenchmarks/cache_latency
gcc -Wall -o ../microbenchmarks/cache_latency ../microbenchmarks/cache_latency.c -lm

# convenience function to run a binary under CPU monitor
run_cpu_mon() {
  bench="$1"    # path to bench executable
  outcsv="$2"   # where to write bench CSV
  mon="$3"      # base name for sys monitor CSV (no path)
  #
  "$bench" > "../results/raw/$outcsv" &
  pid=$!
  bash monitor_sys.sh 1 "../results/raw/${mon}_sys.csv" $pid &
  mon_pid=$!
  wait $pid
  kill $mon_pid
}

# 2) Run microbenchmarks with CPU monitoring
run_cpu_mon "../microbenchmarks/integer_throughput"   int.csv       int
run_cpu_mon "../microbenchmarks/float_throughput"     flt.csv       flt
run_cpu_mon "../microbenchmarks/mem_latency"          lat.csv       lat
run_cpu_mon "../microbenchmarks/mem_bandwidth"        bw.csv        bw
run_cpu_mon "../microbenchmarks/cache_latency"        cache_latency.csv cache
run_cpu_mon "../microbenchmarks/thread_scalability"   thread_scalability.csv thread


# # Run microbenchmarks
# ./../microbenchmarks/integer_throughput > ../results/raw/int.csv
# ./../microbenchmarks/float_throughput  > ../results/raw/flt.csv
# ./../microbenchmarks/mem_latency       > ../results/raw/lat.csv
# ./../microbenchmarks/mem_bandwidth     > ../results/raw/bw.csv
# ./../microbenchmarks/cache_latency > ../results/raw/cache_latency.csv
# ./../microbenchmarks/thread_scalability > ../results/raw/thread_scalability.csv


# -------------------------
# 3) Run workloads
# -------------------------

# SORT benchmark (CPU only)
python3 ../workloads/sort_benchmark.py ../results/raw/sort.csv &
pid=$!
./monitor_sys.sh 1 ../results/raw/sort_sys.csv $pid &
mon=$!
wait $pid
kill $mon

# SQL benchmark (CPU only)
python3 ../workloads/sql_benchmark.py ../results/raw/sql.csv &
pid=$!
./monitor_sys.sh 1 ../results/raw/sql_sys.csv $pid &
mon=$!
wait $pid
kill $mon

# ML inference (CPU + GPU)
python3 ../workloads/ml_inference.py ../results/raw/ml.csv &
pid=$!
./monitor_sys.sh 1 ../results/raw/ml_sys.csv $pid &
cpu_mon=$!
./monitor_gpu.sh 1 ../results/raw/ml_gpu.csv &
gpu_mon=$!
wait $pid
kill $cpu_mon $gpu_mon


# # Run workloads
# python3 ../workloads/sort_benchmark.py ../results/raw/sort.csv
# python3 ../workloads/sql_benchmark.py  ../results/raw/sql.csv
# python3 ../workloads/ml_inference.py  ../results/raw/ml.csv

#   ML inference: monitor both CPU and GPU
python3 ../workloads/ml_inference.py > ../results/raw/ml.csv &
pid=$!
bash monitor_sys.sh 1 ../results/raw/ml_sys.csv $pid &
sys_mon=$!
bash monitor_gpu.sh 1 ../results/raw/ml_gpu.csv &
gpu_mon=$!
wait $pid
kill $sys_mon $gpu_mon

# Merge results
python3 ../harness/parse_results.py

#Generate plots
python3 ../plots/generate_plots.py


echo "All benchmarks done."
