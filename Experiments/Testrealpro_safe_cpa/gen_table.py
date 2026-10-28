#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re

base_dir = "/home/dell/zyworkspace/unichecker/Experiments/Testrealpro_safe_cpa"
log_file = base_dir + "/runRW.log"
dirs_file = base_dir + "/realworld18dirs.sh"
output_file = base_dir + "/table.txt"

TEST_DIRS = [
    "logger1",
    "logger2",
    "logger3",
    "blink1",
    "blink2",
    "blink3",
    "brake1",
    "brake2",
    "brake3",
    "i2c_pca_isa_1",
    "i2c_pca_isa_2",
    "i2c_pca_isa_3",
    "i8xx_tco_1",
    "i8xx_tco_2",
    "i8xx_tco_3",
    "wdt_pci_1",
    "wdt_pci_2",
    "wdt_pci_3"
]

# # 读取目录列表顺序
# with open(dirs_file, 'r') as f:
#     for line in f:
#         if line.startswith('TEST_DIRS='):
#             # 兼容 TEST_DIRS="a\nb\nc" 或 TEST_DIRS="a b c" 风格
#             dirs_str = line.split('=',1)[1].strip()
#             dirs_str = dirs_str.lstrip('"').rstrip('"').replace('\n',' ')
#             test_dirs = [d.strip() for d in dirs_str.split() if d.strip()]
#             break

# 解析log，收集每个目录的结果
results = {}

pattern = re.compile(
    r'Experiments/Testrealpro_safe_cpa/([^/]+)/main\.c,\s*(?:\x1b\[[0-9;]*m)?([A-Z]+|TIMEOUT|UNKNOWN)(?:\x1b\[[0-9;]*m)?,\s*([0-9.]+)'
)
with open(log_file, 'r') as f:
    for line in f:
        m = pattern.search(line)
        if m:
            name, result, timestr = m.group(1), m.group(2), m.group(3)
            results[name] = (result, timestr)
print("Parsed results:", results)
# 生成latex表格代码
with open(output_file, 'w') as f:
    f.write("\\begin{tabular}{|l|c|c|}\n")
    f.write("\\hline\n")
    f.write("Name & Result & Time \\\\\n")
    f.write("\\hline\n")
    for name in TEST_DIRS:
        latex_name = name.replace('_', '\\_')
        result, timestr = results.get(name, ('-', '-'))
        f.write("{} & {} & {} \\\\\n".format(latex_name, result, timestr))
    f.write("\\hline\n")
    f.write("\\end{tabular}\n")

