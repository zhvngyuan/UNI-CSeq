#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re
import os

base_dir_with_cbmc = "/home/dell/zyworkspace/unichecker/Experiments/compare_with_intAbs_cbmc"
base_dir_with_cpa = "/home/dell/zyworkspace/unichecker/Experiments/compare_with_intAbs_cpachecker"
log_file_with_cbmc = base_dir_with_cbmc + "/runExp.log"
log_file_with_cpa = base_dir_with_cpa + "/runExp.log"
dirs_file = base_dir_with_cbmc + "/testdirs.sh"
output_file = base_dir_with_cbmc + "/table.txt"

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
# 引用自intAbs工具的实验数据
table_data = {
    "logger1":    {"LOC": 161,  "Interrupts": 2, "Assertions": 1,  "Warnings": 0, "Proofs": 1, "Time": 0.27},
    "logger2":    {"LOC": 183,  "Interrupts": 3, "Assertions": 3,  "Warnings": 0, "Proofs": 3, "Time": 0.39},
    "logger3":    {"LOC": 195,  "Interrupts": 4, "Assertions": 4,  "Warnings": 0, "Proofs": 4, "Time": 0.43},
    "blink1":     {"LOC": 164,  "Interrupts": 3, "Assertions": 3,  "Warnings": 2, "Proofs": 1, "Time": 0.18},
    "blink2":     {"LOC": 174,  "Interrupts": 4, "Assertions": 3,  "Warnings": 2, "Proofs": 1, "Time": 0.30},
    "blink3":     {"LOC": 194,  "Interrupts": 5, "Assertions": 4,  "Warnings": 3, "Proofs": 1, "Time": 0.46},
    "brake1":     {"LOC": 819,  "Interrupts": 2, "Assertions": 5,  "Warnings": 1, "Proofs": 4, "Time": 0.98},
    "brake2":     {"LOC": 818,  "Interrupts": 3, "Assertions": 4,  "Warnings": 3, "Proofs": 1, "Time": 1.91},
    "brake3":     {"LOC": 833,  "Interrupts": 4, "Assertions": 5,  "Warnings": 4, "Proofs": 1, "Time": 3.48},
    "i2c_pca_isa_1": {"LOC": 321, "Interrupts": 4, "Assertions": 6,  "Warnings": 0, "Proofs": 6, "Time": 0.29},
    "i2c_pca_isa_2": {"LOC": 341, "Interrupts": 6, "Assertions": 10, "Warnings": 8, "Proofs": 2, "Time": 1.05},
    "i2c_pca_isa_3": {"LOC": 363, "Interrupts": 8, "Assertions": 14, "Warnings": 12, "Proofs": 2, "Time": 2.48},
    "i8xx_tco_1":    {"LOC": 757, "Interrupts": 3, "Assertions": 2,  "Warnings": 0, "Proofs": 2, "Time": 0.35},
    "i8xx_tco_2":    {"LOC": 949, "Interrupts": 4, "Assertions": 2,  "Warnings": 1, "Proofs": 1, "Time": 0.54},
    "i8xx_tco_3":    {"LOC": 944, "Interrupts": 6, "Assertions": 3,  "Warnings": 0, "Proofs": 3, "Time": 1.04},
    "wdt_pci_1":     {"LOC": 1239,"Interrupts": 4, "Assertions": 2,  "Warnings": 0, "Proofs": 2, "Time": 0.61},
    "wdt_pci_2":     {"LOC": 1290,"Interrupts": 6, "Assertions": 3,  "Warnings": 1, "Proofs": 2, "Time": 1.45},
    "wdt_pci_3":     {"LOC": 1339,"Interrupts": 8, "Assertions": 4,  "Warnings": 3, "Proofs": 1, "Time": 3.21},
}

# 解析log，收集每个目录的结果
results = {}
results_cpa = {}

pattern_cbmc = re.compile(
    r'Experiments/compare_with_intAbs_cbmc/([^/]+)/main\_n\.c,\s*(?:\x1b\[[0-9;]*m)?([A-Z]+|TIMEOUT|UNKNOWN)(?:\x1b\[[0-9;]*m)?,\s*([0-9.]+)'
)
pattern_cpa = re.compile(
    r'Experiments/compare_with_intAbs_cpachecker/([^/]+)/main\_n\.c,\s*(?:\x1b\[[0-9;]*m)?([A-Z]+|TIMEOUT|UNKNOWN)(?:\x1b\[[0-9;]*m)?,\s*([0-9.]+)'
)
with open(log_file_with_cbmc, 'r') as f:
    for line in f:
        m = pattern_cbmc.search(line)
        if m:
            name, result, timestr = m.group(1), m.group(2), m.group(3)
            results[name] = (result, timestr)

with open(log_file_with_cpa, 'r') as f:
    for line in f:
        m = pattern_cpa.search(line)
        if m:
            name, result_cpa, timestr_cpa = m.group(1), m.group(2), m.group(3)
            results_cpa[name] = (result_cpa, timestr_cpa)

def count_failures(cbmc_log_path):
    """统计cbmc log文件中FAILURE出现次数"""
    if not os.path.isfile(cbmc_log_path):
        return 0
    cnt = 0
    with open(cbmc_log_path, 'r') as f:
        for line in f:
            if "FAILURE" in line:
                cnt += 1
    return cnt

def safe_float(x):
    try:
        return float(x)
    except:
        return 0.0
    
total_LOC = 0
total_Interrupts = 0
total_Assertions = 0
total_Warnings = 0
total_Proofs = 0
total_Time_intAbs = 0.0
total_Violations = 0
total_Time_cbmc = 0.0
total_Remaining = 0
total_Proofs_cpa = 0
total_Time_cpa = 0.0

# 生成latex表格代码
with open(output_file, 'w') as f:
    f.write("\\begin{table*}[ht]\n")
    f.write("\\centering\n")
    f.write("\\caption{Experimental results with CBMC}\n")
    f.write("\\resizebox{\\textwidth}{!}{\n")
    # f.write("\\begin{tabular}{lccccccccccc}\n")
    # f.write("\\toprule[1pt]\n")
    # f.write("\multirow{2}{*}{Name} & \multicolumn{1}{c}{\multirow{2}{*}{LOC}} & \multicolumn{1}{c}{\multirow{2}{*}{ISRs}} & \multicolumn{1}{c}{\multirow{2}{*}{Assertions}} &\multicolumn{3}{c}{intAbs} &\multicolumn{2}{c}{Unichecker+CBMC} &\multicolumn{2}{c}{Unichecker+CPAChecker}  & \multicolumn{1}{c}{\multirow{2}{*}{All Time}}\\\\\\cmidrule(lr){5-7} \\cmidrule(lr){8-9} \\cmidrule(lr){10-11}\n")
    # f.write(" & & & & Warnings & Proofs & Time & Violations & Time  & Proofs & Time &\\\\\\midrule\n")

    # No all time
    f.write("\\begin{tabular}{lccccccccccc}\n")
    f.write("\\toprule[1pt]\n")
    f.write("\multirow{3}{*}{Name} & \multicolumn{1}{c}{\multirow{3}{*}{LOC}} & \multicolumn{1}{c}{\multirow{3}{*}{ISRs}} & \multicolumn{1}{c}{\multirow{3}{*}{Assertions}} &\multicolumn{3}{c}{\multirow{1}{*}{intAbs}} &\multicolumn{5}{c}{Unichecker}\\\\\\cmidrule(lr){5-7}\\cmidrule(lr){8-12}\n")
    f.write("& & & &\multirow{2}{*}{Warnings} & \multirow{2}{*}{Proofs} & \multirow{2}{*}{Time} &\multicolumn{2}{c}{+ CBMC} &\multicolumn{2}{c}{+ CPAChecker} &\multicolumn{1}{c}{\multirow{2}{*}{Proofs}} \\\\ \\cmidrule(lr){8-9} \\cmidrule(lr){10-11}\n")
    # f.write("\multirow{2}{*}{Name} & \multicolumn{1}{c}{\multirow{2}{*}{LOC}} & \multicolumn{1}{c}{\multirow{2}{*}{ISRs}} & \multicolumn{1}{c}{\multirow{2}{*}{Assertions}} &\multicolumn{3}{c}{intAbs} &\multicolumn{2}{c}{\\makecell{Unichecker\\\\+ CBMC}} &\multicolumn{2}{c}{\\makecell{Unichecker\\\\+ CPAChecker}} & \multicolumn{1}{c}{\multirow{2}{*}{Proofs}}\\\\\\cmidrule(lr){5-7} \\cmidrule(lr){8-9} \\cmidrule(lr){10-11}\n")
    f.write(" & & & & & & & Violations & Time  & Validations & Time \\\\\\midrule\n")
    for name in TEST_DIRS:
        latex_name = name.replace('_', '\\_')
        result, timestr = results.get(name, ('-', '-')) # result记录true or false
        result_cpa, timestr_cpa = results_cpa.get(name, ('-', '-'))
        # 拼接正确的cbmc log文件名
        cbmc_log_path = os.path.join(base_dir_with_cbmc, name, "_cseq_main_n.c.cbmc.log")
        num_violations = count_failures(cbmc_log_path)
        timestr_sum = safe_float(timestr) + safe_float(timestr_cpa)
        remaining = table_data[name]["Assertions"] - num_violations
        # f.write("{} & {} & {} & {} \\\\\n".format(latex_name, result, num_violations, timestr))
        # f.write("{} & {} & {} & {} & {} & {} & {:.1f} & {} & {:.1f}& {} & {:.1f} & {}\\\\\n".format(latex_name, table_data[name]["LOC"], table_data[name]["Interrupts"], table_data[name]["Assertions"], table_data[name]["Warnings"], table_data[name]["Proofs"], table_data[name]["Time"], num_violations, safe_float(timestr), remaining, safe_float(timestr_cpa), table_data[name]["Assertions"]))
        f.write("{} & {} & {} & {} & {} & {} & {:.1f} & {} & {} & {:.1f} & {}\\\\\n".format(latex_name, table_data[name]["LOC"], table_data[name]["Interrupts"], table_data[name]["Assertions"], table_data[name]["Warnings"], table_data[name]["Proofs"], table_data[name]["Time"], num_violations, remaining, timestr_sum, table_data[name]["Assertions"]))

        # 累加
        total_LOC += table_data[name]["LOC"]
        total_Interrupts += table_data[name]["Interrupts"]
        total_Assertions += table_data[name]["Assertions"]
        total_Warnings += table_data[name]["Warnings"]
        total_Proofs += table_data[name]["Proofs"]
        total_Time_intAbs += table_data[name]["Time"]
        total_Violations += num_violations
        total_Time_cbmc += safe_float(timestr)
        total_Remaining += remaining
        total_Time_cpa += safe_float(timestr_cpa)

    f.write("\\midrule\n")
    f.write("Total & {} & {} & {} & {} & {} & {:.1f} & {} & {:.1f} & {} & {:.1f} & {} \\\\\n".format(
        total_LOC,
        total_Interrupts,
        total_Assertions,
        total_Warnings,
        total_Proofs,
        total_Time_intAbs,
        total_Violations,
        total_Time_cbmc,
        total_Remaining,
        total_Time_cpa,
        total_Assertions
    ))
    f.write("\\bottomrule[1pt]\n")
    f.write("\\end{tabular}\n")
    f.write("}\n")
    f.write("\\end{table*}\n")