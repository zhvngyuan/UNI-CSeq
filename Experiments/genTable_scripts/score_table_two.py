#!/usr/bin/env python3
"""
使用: python3 score_table_two.py
使用真实的ground truth来计算分数
功能：统计cbmc和cpachecker两个验证后端（portfolio）顺序和并行的验证结果
"""

import os
import re
from collections import defaultdict

# 动态获取工程根目录
CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, "..", ".."))  # repo root


# 结果文件路径
base = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split")
base_unicseq = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split_unicseq")
base_cc = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split_unicseq_CC")
base_ca = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split_unicseq_CA")
base_seq = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split_unicseq_SEQ")


log_file_map = {
    "cbmc": os.path.join(base, "results_cbmc.log"),
    "cpachecker": os.path.join(base, "results_cpachecker.log"),
    "cbmc-cpachecker": os.path.join(base_cc, "results_unicseq_cbmc-cpachecker.log"),
    "sequential": os.path.join(base_seq, "results_unicseq_sequential.log"),  
}

verifier_names = [
    "cbmc", "cpachecker",
    "sequential",
    "cbmc-cpachecker"
    
]

# 结果标签
POSITIVE = {"TRUE", "true"}
NEGATIVE = {"FALSE", "false"}
UNKNOWN = {"UNKNOWN", "unknown", "TIMEOUT", "timeout", "ERROR", "error"}

# ===== 真实的 Ground Truth =====
# 保持原有的 REAL_GROUND_TRUTH 字典不变
REAL_GROUND_TRUTH = {
    "Idv-races/svp_simple_300_001/svp_simple_300_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_300_001/svp_simple_300_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_300_001/svp_simple_300_001_assert4.c": "FALSE",
    "Idv-races/svp_simple_301_001/svp_simple_301_001_assert1.c": "FALSE",
    "Idv-races/svp_simple_301_001/svp_simple_301_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_301_001/svp_simple_301_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_301_001/svp_simple_301_001_assert4.c": "FALSE",
    "Idv-races/svp_simple_302_001/svp_simple_302_001_assert1.c": "FALSE",
    "Idv-races/svp_simple_302_001/svp_simple_302_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_302_001/svp_simple_302_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_302_001/svp_simple_302_001_assert4.c": "FALSE",
    "Idv-races/svp_simple_303_001/svp_simple_303_001_assert1.c": "FALSE",
    "Idv-races/svp_simple_303_001/svp_simple_303_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_303_001/svp_simple_303_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_303_001/svp_simple_303_001_assert4.c": "FALSE",
    "Idv-races/svp_simple_304_001/svp_simple_304_001_assert1.c": "FALSE",
    "Idv-races/svp_simple_304_001/svp_simple_304_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_304_001/svp_simple_304_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_304_001/svp_simple_304_001_assert4.c": "FALSE",
    "pthread/svp_simple_304_001/svp_simple_304_001_assert1.c": "FALSE",
    "pthread/svp_simple_324_001/svp_simple_324_001_assert1.c": "FALSE",
    "pthread/svp_simple_325_001/svp_simple_325_001_assert1.c": "FALSE",
    "pthread/svp_simple_326_001/svp_simple_326_001_assert1.c": "FALSE",
    "racebench2.1/svp_simple_001/svp_simple_001_assert2.c": "FALSE",
    "racebench2.1/svp_simple_002/svp_simple_002_assert1.c": "FALSE",
    "racebench2.1/svp_simple_003/svp_simple_003_assert1.c": "FALSE",
    "racebench2.1/svp_simple_004/svp_simple_004_assert1.c": "FALSE",
    "racebench2.1/svp_simple_005/svp_simple_005_assert1.c": "FALSE",
    "racebench2.1/svp_simple_006/svp_simple_006_assert1.c": "FALSE",
    "racebench2.1/svp_simple_007/svp_simple_007_assert1.c": "FALSE",
    "racebench2.1/svp_simple_013/svp_simple_013_assert1.c": "FALSE",
    "racebench2.1/svp_simple_015/svp_simple_015_assert1.c": "FALSE",
    "racebench2.1/svp_simple_015/svp_simple_015_assert2.c": "FALSE",
    "racebench2.1/svp_simple_016/svp_simple_016_assert1.c": "FALSE",
    "racebench2.1/svp_simple_017/svp_simple_017_assert1.c": "FALSE",
    "racebench2.1/svp_simple_019/svp_simple_019_assert1.c": "FALSE",
    "racebench2.1/svp_simple_020/svp_simple_020_assert1.c": "FALSE",
    "racebench2.1/svp_simple_020/svp_simple_020_assert2.c": "FALSE",
    "racebench2.1/svp_simple_021/svp_simple_021_assert1.c": "FALSE",
    "racebench2.1/svp_simple_022/svp_simple_022_assert1.c": "FALSE",
    "racebench2.1/svp_simple_026/svp_simple_026_assert1.c": "FALSE",
    "racebench2.1/svp_simple_026/svp_simple_026_assert2.c": "FALSE",
    "racebench2.1/svp_simple_027/svp_simple_027_assert1.c": "FALSE",
    "racebench2.1/svp_simple_027/svp_simple_027_assert3.c": "FALSE",
    "racebench2.1/svp_simple_028/svp_simple_028_assert1.c": "FALSE",
    "rw_benchmark/blink1/main_n_assert1.c": "FALSE",
    "rw_benchmark/blink1/main_n_assert2.c": "FALSE",
    "rw_benchmark/blink2/main_n_assert1.c": "FALSE",
    "rw_benchmark/blink2/main_n_assert2.c": "FALSE",
    "rw_benchmark/blink3/main_n_assert1.c": "FALSE",
    "rw_benchmark/blink3/main_n_assert2.c": "FALSE",
    "rw_benchmark/blink3/main_n_assert3.c": "FALSE",
    "rw_benchmark/brake1/main_n_assert5.c": "FALSE",
    "rw_benchmark/brake2/main_n_assert1.c": "FALSE",
    "rw_benchmark/brake2/main_n_assert3.c": "FALSE",
    "rw_benchmark/brake2/main_n_assert4.c": "FALSE",
    "rw_benchmark/brake3/main_n_assert1.c": "FALSE",
    "rw_benchmark/brake3/main_n_assert3.c": "FALSE",
    "rw_benchmark/brake3/main_n_assert4.c": "FALSE",
    "rw_benchmark/brake3/main_n_assert5.c": "FALSE",
    "rw_benchmark/wdt_pci_2/main_n_assert4.c": "FALSE",
    "rw_benchmark/wdt_pci_3/main_n_assert3.c": "FALSE",
    "rw_benchmark/wdt_pci_3/main_n_assert4.c": "FALSE",
    "rw_benchmark/wdt_pci_3/main_n_assert5.c": "FALSE",
    "rw_benchmark/i8xx_tco_1/main_n_assert1.c": "TRUE",
    "rw_benchmark/i8xx_tco_2/main_n_assert1.c": "FALSE",
    "rw_benchmark/i8xx_tco_3/main_n_assert1.c": "TRUE",
    "Idv-races/svp_simple_300_001/svp_simple_300_001_assert1.c": "TRUE",
    "pthread/svp_simple_327_001/svp_simple_327_001_assert1.c": "TRUE",
    "pthread/svp_simple_328_001/svp_simple_328_001_assert1.c": "TRUE",
    "pthread/svp_simple_329_001/svp_simple_329_001_assert1.c": "TRUE",
    "pthread/svp_simple_330_001/svp_simple_330_001_assert1.c": "TRUE",
    "pthread/svp_simple_331_001/svp_simple_331_001_assert1.c": "TRUE",
    "pthread/svp_simple_332_001/svp_simple_332_001_assert1.c": "TRUE",
    "racebench2.1/svp_simple_001/svp_simple_001_assert1.c": "TRUE",
    "racebench2.1/svp_simple_002/svp_simple_002_assert2.c": "TRUE",
    "racebench2.1/svp_simple_006/svp_simple_006_assert2.c": "TRUE",
    "racebench2.1/svp_simple_006/svp_simple_006_assert3.c": "TRUE",
    "racebench2.1/svp_simple_006/svp_simple_006_assert4.c": "TRUE",
    "racebench2.1/svp_simple_008/svp_simple_008_assert1.c": "TRUE",
    "racebench2.1/svp_simple_010/svp_simple_010_assert1.c": "TRUE",
    "racebench2.1/svp_simple_010/svp_simple_010_assert2.c": "TRUE",
    "racebench2.1/svp_simple_018/svp_simple_018_assert1.c": "TRUE",
    "racebench2.1/svp_simple_027/svp_simple_027_assert2.c": "TRUE",
    "racebench2.1/svp_simple_028/svp_simple_028_assert2.c": "TRUE",
    "racebench2.1/svp_simple_028/svp_simple_028_assert3.c": "TRUE",
    "racebench2.1/svp_simple_029/svp_simple_029_assert1.c": "TRUE",
    "racebench2.1/svp_simple_030/svp_simple_030_assert1.c": "TRUE",
    "racebench2.1/svp_simple_030/svp_simple_030_assert2.c": "TRUE",
    "rw_benchmark/blink1/main_n_assert3.c": "TRUE",
    "rw_benchmark/blink2/main_n_assert3.c": "TRUE",
    "rw_benchmark/blink3/main_n_assert4.c": "TRUE",
    "rw_benchmark/brake1/main_n_assert1.c": "TRUE",
    "rw_benchmark/brake1/main_n_assert2.c": "TRUE",
    "rw_benchmark/brake1/main_n_assert3.c": "TRUE",
    "rw_benchmark/brake1/main_n_assert4.c": "TRUE",
    "rw_benchmark/brake2/main_n_assert2.c": "TRUE",
    "rw_benchmark/brake3/main_n_assert2.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_1/main_n_assert2.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert2.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert2.c": "TRUE",
    "rw_benchmark/logger1/main_n_assert1.c": "TRUE",
    "rw_benchmark/logger2/main_n_assert1.c": "TRUE",
    "rw_benchmark/logger2/main_n_assert2.c": "TRUE",
    "rw_benchmark/logger2/main_n_assert3.c": "TRUE",
    "rw_benchmark/logger3/main_n_assert1.c": "TRUE",
    "rw_benchmark/logger3/main_n_assert2.c": "TRUE",
    "rw_benchmark/logger3/main_n_assert3.c": "TRUE",
    "rw_benchmark/logger3/main_n_assert4.c": "TRUE",
    "rw_benchmark/wdt_pci_1/main_n_assert1.c": "TRUE",
    "rw_benchmark/wdt_pci_1/main_n_assert2.c": "TRUE",
    "rw_benchmark/wdt_pci_1/main_n_assert3.c": "TRUE",
    "rw_benchmark/wdt_pci_2/main_n_assert1.c": "TRUE",
    "rw_benchmark/wdt_pci_2/main_n_assert2.c": "TRUE",
    "rw_benchmark/wdt_pci_2/main_n_assert3.c": "TRUE",
    "rw_benchmark/wdt_pci_3/main_n_assert1.c": "TRUE",
    "rw_benchmark/wdt_pci_3/main_n_assert2.c": "TRUE",
    "racebench2.1/svp_simple_004/svp_simple_004_assert2.c": "TRUE",
    "racebench2.1/svp_simple_009/svp_simple_009_assert1.c": "TRUE",
    "racebench2.1/svp_simple_009/svp_simple_009_assert2.c": "TRUE",
    "racebench2.1/svp_simple_013/svp_simple_013_assert2.c": "FALSE",
    "racebench2.1/svp_simple_013/svp_simple_013_assert3.c": "TRUE",
    "racebench2.1/svp_simple_014/svp_simple_014_assert1.c": "FALSE",
    "racebench2.1/svp_simple_014/svp_simple_014_assert2.c": "FALSE",
    "racebench2.1/svp_simple_018/svp_simple_018_assert2.c": "FALSE",
    "racebench2.1/svp_simple_011/svp_simple_011_assert1.c": "TRUE",
    "racebench2.1/svp_simple_011/svp_simple_011_assert2.c": "TRUE",
    "racebench2.1/svp_simple_012/svp_simple_012_assert1.c": "TRUE",
    "racebench2.1/svp_simple_023/svp_simple_023_assert1.c": "FALSE",
    "racebench2.1/svp_simple_024/svp_simple_024_assert1.c": "TRUE",
    "racebench2.1/svp_simple_025/svp_simple_025_assert1.c": "FALSE",
    "racebench2.1/svp_simple_031/svp_simple_031_assert1.c": "FALSE",
    "racebench2.1/svp_simple_031/svp_simple_031_assert2.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_1/main_n_assert1.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert1.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert1.c": "FALSE",
}


def normalize_filename(filepath):
    """标准化文件路径，提取关键的文件标识部分"""
    basename = os.path.basename(filepath)
    parts = filepath.split('/')
    
    key_parts = []
    found_key = False
    for i, part in enumerate(parts):
        if part in ["Idv-races", "pthread", "racebench2.1", "rw_benchmark"]:
            key_parts = parts[i:]
            found_key = True
            break
    
    if found_key and len(key_parts) >= 3:
        return "/".join(key_parts[-3:])
    else:
        if len(parts) >= 2:
            return "/".join(parts[-2:])
        else:
            return basename

def parse_unicseq_log(logfile, tool_name):
    """解析 unicseq 格式的日志文件"""
    f2res = {}
    current_file = None
    true_cnt, false_cnt, unknown_cnt, total_time = 0, 0, 0, 0.0
    
    if not os.path.exists(logfile):
        print(f"[WARNING] File not found: {logfile}")
        return f2res
    
    with open(logfile, "r", encoding="utf-8") as f:
        lines = f.readlines()
    
    for idx, line in enumerate(lines):
        line = re.sub(r'\x1b\[[;0-9]+m', '', line)
        
        mfile = re.search(r'UnicSeq Checking(?:\s+\([^)]+\))?\s*:\s+([^\s=]+)', line)
        if mfile:
            current_file = mfile.group(1).strip()
            current_file = normalize_filename(current_file)
            continue
        
        mres = re.search(r'Final verification results:\s*([A-Z]+)', line)
        if mres and current_file:
            result = mres.group(1).strip().upper()
            for j in range(1, 8):
                if idx + j < len(lines):
                    time_line = re.sub(r'\x1b\[[;0-9]+m', '', lines[idx+j])
                    mtime = re.search(r'Total running time:\s*([0-9.]+)', time_line)
                    if mtime:
                        t = float(mtime.group(1))
                        f2res[current_file] = (result, t)
                        if result == "TRUE":
                            true_cnt += 1
                        elif result == "FALSE":
                            false_cnt += 1
                        else:
                            unknown_cnt += 1
                        total_time += t
                        break
            current_file = None
    
    print(f"[DEBUG][{tool_name}] {logfile}: TRUE={true_cnt}, FALSE={false_cnt}, UNKNOWN={unknown_cnt}, TotalTime={total_time:.1f}")
    return f2res

def parse_one_log(logfile, tool):
    """解析单个工具的日志文件"""
    f2res = {}
    true_cnt, false_cnt, unknown_cnt, total_time = 0, 0, 0, 0.0
    
    if not os.path.exists(logfile):
        print(f"[WARNING] File not found: {logfile}")
        return f2res
    
    with open(logfile, "r", encoding="utf-8") as f:
        lines = f.readlines()
    
    for idx, line in enumerate(lines):
        text = re.sub(r'\x1b\[[;0-9]+m', '', line)
        m2 = re.search(r'([^,]+),\s*([A-Z]+|TIMEOUT|UNKNOWN),\s*([-.\d]+)', text)
        if m2:
            fname = m2.group(1).strip()
            fname = normalize_filename(fname)
            result = m2.group(2).strip().upper()
            time = float(m2.group(3))
            f2res[fname] = (result, time)
            if result == "TRUE":
                true_cnt += 1
            elif result == "FALSE":
                false_cnt += 1
            else:
                unknown_cnt += 1
            total_time += time
    
    print(f"[DEBUG][{tool}] {logfile}: TRUE={true_cnt}, FALSE={false_cnt}, UNKNOWN={unknown_cnt}, TotalTime={total_time:.1f}")
    return f2res

def build_full_map():
    all_files = set()
    fullmap = defaultdict(dict)
    
    for vn in verifier_names:
        log = log_file_map[vn]
        
        if "unicseq" in vn or vn in ["cbmc-cpachecker", "sequential"]:  # 去除 cbmc-uautomizer
            f2res = parse_unicseq_log(log, vn)
        else:
            f2res = parse_one_log(log, vn)
        
        for f in f2res:
            fullmap[f][vn] = f2res[f]
            all_files.add(f)
    
    return all_files, fullmap

def determine_ground_truth(file_key, tool2res):
    """
    确定ground truth
    优先使用真实的ground truth，如果没有则使用多数投票
    """
    # 首先检查是否有真实的ground truth
    if file_key in REAL_GROUND_TRUTH:
        return REAL_GROUND_TRUTH[file_key], "REAL"
    
    # 如果没有真实ground truth，使用多数投票（但标记为推测）
    counts = {"TRUE": 0, "FALSE": 0}
    base_tools = ["cbmc", "cpachecker"]  # 去除 uautomizer
    for tool in base_tools:
        if tool in tool2res:
            r, _ = tool2res[tool]
            if r in POSITIVE:
                counts["TRUE"] += 1
            elif r in NEGATIVE:
                counts["FALSE"] += 1
    
    if counts["TRUE"] > counts["FALSE"]:
        return "TRUE", "VOTE"
    elif counts["FALSE"] > counts["TRUE"]:
        return "FALSE", "VOTE"
    else:
        return None, "UNKNOWN"

def judge_score(gt, tool_res):
    """计算分数"""
    result, _ = tool_res
    if result in POSITIVE:
        if gt in POSITIVE:
            return (2, 1, 0, 0, 0, 0)  # correct_proof
        else:
            return (-32, 0, 0, 1, 0, 0)  # wrong_proof
    elif result in NEGATIVE:
        if gt in NEGATIVE:
            return (1, 0, 1, 0, 0, 0)  # correct_alarm
        else:
            return (-16, 0, 0, 0, 1, 0)  # wrong_alarm
    else:
        return (0, 0, 0, 0, 0, 1)  # unknown

def main():
    all_files, fullmap = build_full_map()
    
    # 初始化统计
    stat = {}
    for vn in verifier_names:
        stat[vn] = {
            "Score": 0,
            "Correct": 0,
            "Correct proof": 0,
            "Correct alarm": 0,
            "Incorrect": 0,
            "Incorrect proof": 0,
            "Incorrect alarm": 0,
            "Unknown": 0,
            "Total time": 0.0
        }
    
    # 记录ground truth来源统计
    gt_source_stats = {"REAL": 0, "VOTE": 0, "UNKNOWN": 0}
    
    # 记录错误的案例
    error_cases = defaultdict(list)
    # 记录unknown的案例
    unknown_cases = defaultdict(list)  
    
    # 统计每个文件
    for f in sorted(all_files):
        tool2res = {}
        for vn in verifier_names:
            if vn in fullmap[f]:
                tool2res[vn] = fullmap[f][vn]
            else:
                tool2res[vn] = ("UNKNOWN", 0)
        
        # 确定ground truth
        gt, source = determine_ground_truth(f, tool2res)
        gt_source_stats[source] += 1
        
        # 统计每个工具的结果
        for vn in verifier_names:
            res, t = tool2res[vn]
            if gt is None or res in UNKNOWN:
                stat[vn]["Unknown"] += 1
                unknown_cases[vn].append(
                    (f, 
                    f"GT={gt if gt is not None else 'UNKNOWN'}", 
                    f"Result={res}")
                )
            else:
                score, cp, ca, wp, wa, unk = judge_score(gt, (res, t))
                stat[vn]["Score"] += score
                stat[vn]["Correct"] += cp + ca
                stat[vn]["Correct proof"] += cp
                stat[vn]["Correct alarm"] += ca
                stat[vn]["Incorrect"] += wp + wa
                stat[vn]["Incorrect proof"] += wp
                stat[vn]["Incorrect alarm"] += wa
                
                # 记录错误案例
                if wp > 0:
                    error_cases[vn].append((f, "Wrong Proof", f"GT={gt}, Result={res}"))
                elif wa > 0:
                    error_cases[vn].append((f, "Wrong Alarm", f"GT={gt}, Result={res}"))
            
            stat[vn]["Total time"] += t
    
    print(f"\n[Ground Truth Sources]")
    print(f"  Real GT: {gt_source_stats['REAL']} files")
    print(f"  Voted GT: {gt_source_stats['VOTE']} files")
    print(f"  Unknown GT: {gt_source_stats['UNKNOWN']} files")
    
    # 输出错误案例
    print("\n[Error Cases]")
    for vn in verifier_names:
        if error_cases[vn]:
            print(f"\n{vn}:")
            for file, error_type, details in error_cases[vn][:5]:  # 只显示前5个
                print(f"  {file}: {error_type} ({details})")
            if len(error_cases[vn]) > 5:
                print(f"  ... and {len(error_cases[vn])-5} more")

    # 输出 unknown 案例
    print("\n[Unknown Cases]")
    for vn in verifier_names:
        if unknown_cases[vn]:
            print(f"\n{vn}:")
            for file, gt_info, res_info in unknown_cases[vn][:6]:  # 只显示前5个
                print(f"  {file}: {gt_info}, {res_info}")
            if len(unknown_cases[vn]) > 6:
                print(f"  ... and {len(unknown_cases[vn])-5} more")
    
    # 生成表格
    metric_list = [
        "Score", "Correct", "Correct proof", "Correct alarm",
        "Incorrect", "Incorrect proof", "Incorrect alarm", "Unknown", "Total time"
    ]
    
    latex_header = "\\begin{tabular}{l" + "c" * len(verifier_names) + "}\n"
    latex_header += "\\toprule\n"
    latex_header += "Metric & CBMC & CPAchecker & Sequential & CBMC+CPA  \\\\\n"  # 去除 UAutomizer 和 CBMC+UA
    latex_header += "\\midrule\n"
    
    table_content = []
    for metric in metric_list:
        row = [metric]
        for vn in verifier_names:
            if metric == "Total time":
                row.append(f"{stat[vn][metric]:.1f}")
            else:
                row.append(str(stat[vn][metric]))
        table_content.append(" & ".join(row) + " \\\\")
    
    latex_footer = "\\bottomrule\n\\end{tabular}"
    
    # 输出到终端
    print("\n" + latex_header, end='')
    for row in table_content:
        print(row)
    print(latex_footer)
    
    # 保存到文件
    output_file = "compare_two_table.txt"
    with open(output_file, "w") as f:
        f.write(f"# Ground Truth Sources: Real={gt_source_stats['REAL']}, Voted={gt_source_stats['VOTE']}, Unknown={gt_source_stats['UNKNOWN']}\n\n")
        f.write(latex_header)
        for row in table_content:
            f.write(row + "\n")
        f.write(latex_footer)
    
    print(f"\n[INFO] Table saved to {output_file}")
    
    print("\n[SUMMARY]")
    for vn in verifier_names:
        print(f"{vn:20s}: Score={stat[vn]['Score']:4d}, Correct={stat[vn]['Correct']:3d}, "
              f"Incorrect={stat[vn]['Incorrect']:3d}, Unknown={stat[vn]['Unknown']:3d}, "
              f"Time={stat[vn]['Total time']:.1f}s")

if __name__ == '__main__':
    main()