#!/usr/bin/env bash
# Usage: monitor_sys.sh <interval_s> <out_csv> <pid_to_watch>
# Logs timestamp,cpu_percent,mem_used_mb

interval=$1; out=$2; pid=$3
echo "timestamp,cpu_pct,mem_mb" > "$out"
while kill -0 "$pid" 2>/dev/null; do
  ts=$(date +%s)
            # overall CPU busy% (100- idle%)
  cpu=$(grep '^cpu ' /proc/stat \
        | awk '{idle=$5; total=$2+$3+$4+$5+$6+$7+$8; printf("%.1f", (1 - idle/total)*100)}')
  # resident mem in MB
  mem=$(awk '/VmRSS:/ {printf("%.1f", $2/1024)}' /proc/$pid/status)
  echo "$ts,$cpu,$mem" >> "$out"
  sleep "$interval"
done
