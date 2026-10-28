#!/usr/bin/env python3
import re
import sys

if len(sys.argv) < 2:
    print("Usage: python count_total.py <logfile>")
    sys.exit(1)

filename = sys.argv[1]

counterexample_sum = 0
feeder_sum = 0.0
time_sum = 0.0
memory_sum = 0.0

with open(filename, encoding='utf-8', errors='ignore') as f:
    for line in f:
        # counterexample: 后是整数
        m = re.search(r'counterexample:\s*(\d+)', line)
        if m:
            counterexample_sum += int(m.group(1))
        # feeder 后是浮点数
        m = re.search(r'feeder\s+([0-9.]+)', line)
        if m:
            feeder_sum += float(m.group(1))
        # time: 后是浮点数
        m = re.search(r'time:\s*([0-9.]+)', line)
        if m:
            time_sum += float(m.group(1))
        # memory: 后是浮点数
        m = re.search(r'memory:\s*([0-9.]+)', line)
        if m:
            memory_sum += float(m.group(1))

print(f"counterexample 总和: {counterexample_sum}")
print(f"feeder 总和: {feeder_sum:.2f}")
print(f"time 总和: {time_sum:.2f} s")
print(f"memory 总和: {memory_sum:.2f} MB")