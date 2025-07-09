#!/usr/bin/env bash
# Usage: monitor_gpu.sh <interval_s> <out_csv>
interval=$1; out=$2
echo "timestamp,util_gpu_pct,util_mem_pct" > "$out"
while true; do
  ts=$(date +%s)
  read gpu mem <<<$(nvidia-smi --query-gpu=utilization.gpu,utilization.memory \
    --format=csv,noheader,nounits | awk '{print $1, $2}')
  echo "$ts,$gpu,$mem" >> "$out"
  sleep "$interval"
  
done
