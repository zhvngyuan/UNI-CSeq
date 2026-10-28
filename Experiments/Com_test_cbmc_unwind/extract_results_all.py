"""
extract_results_all.py

本脚本是对 extract_results.py 的扩展版本，用于统一整合 UNI-CSeq 实验中的
CBMC 与 CPAchecker 结果日志，并导出为 all_results.csv。

【来源说明】
五包 CBMC unwind 结果已写在各 ComExp_Split_uN/results_cbmc_unwindN.log 中，
不要再读旧的 results_cbmc_unwind_goblint-regression_*.log，否则 goblint 会双计。
CPAchecker 的四包在 results_cpachecker.log，goblint 在
results_goblint-regression_cpachecker.log，两份都要读。

【主要功能】
1. 提取五份合并后的 CBMC unwind 日志；
2. 提取 CPAchecker 四包日志与 goblint 日志；
3. 统一解析 benchmark、case、result、time 等字段；
4. 将所有结果合并导出为 CSV，便于后续统计分析；
5. 保留 source_log 字段，便于追踪每条记录的数据来源。

【使用方法】
运行命令：
    python3 extract_results_all.py

运行前请检查脚本顶部的路径配置是否与当前实验目录一致。

【维护建议】
后续如有新的补充实验，建议继续在本脚本上扩展，而不是修改旧版
extract_results.py，以保持结果整合逻辑的一致性。
"""

import re
import csv
import glob
import os

# =========================
# 路径配置
# =========================

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, "..", ".."))
CBMC_BASE = CUR_DIR
COMEXP_SPLIT = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split")
CPACHECKER_LOGS = [
    os.path.join(COMEXP_SPLIT, "results_cpachecker.log"),
    os.path.join(COMEXP_SPLIT, "results_goblint-regression_cpachecker.log"),
]
OUTPUT_CSV = "all_results.csv"

# 五包已合并进 results_cbmc_unwindN.log，不要再读 goblint 专用 unwind 日志
CBMC_LOG_PATTERNS = [
    os.path.join(CBMC_BASE, "ComExp_Split_u2", "results_cbmc_unwind2.log"),
    os.path.join(CBMC_BASE, "ComExp_Split_u4", "results_cbmc_unwind4.log"),
    os.path.join(CBMC_BASE, "ComExp_Split_u8", "results_cbmc_unwind8.log"),
    os.path.join(CBMC_BASE, "ComExp_Split_u16", "results_cbmc_unwind16.log"),
    os.path.join(CBMC_BASE, "ComExp_Split_u32", "results_cbmc_unwind32.log"),
]

# ANSI 颜色清理
ansi_escape = re.compile(r'\x1b\[[0-9;]*m')

def clean_ansi(s):
    return ansi_escape.sub('', s)

def parse_result_line(line):
    """
    匹配类似:
      /path/to/file.c, TRUE, 0.44
      /path/to/file.c, FALSE, 1.23
      /path/to/file.c, UNKNOWN
    """
    line = clean_ansi(line).strip()

    # 标准：路径, 结果, 时间
    m = re.match(r'(.+?),\s*(TRUE|FALSE|UNKNOWN|TIMEOUT),\s*([0-9.]+)', line)
    if m:
        return m.group(1).strip(), m.group(2), float(m.group(3))

    # 只有路径, 结果
    m = re.match(r'(.+?),\s*(TRUE|FALSE|UNKNOWN|TIMEOUT)', line)
    if m:
        return m.group(1).strip(), m.group(2), None

    return None

def extract_benchmark_and_case(case_path):
    """
    从完整路径中提取 benchmark 和 case。
    例如：
      /.../ComExp_Split/goblint-regression/svp_simple_613_001/svp_simple_613_001_assert2.c
    提取为：
      benchmark = goblint-regression
      case = goblint-regression/svp_simple_613_001/svp_simple_613_001_assert2.c

    或者：
      /.../ComExp_Split_u2/array-examples/foo/foo.c
    提取为：
      benchmark = array-examples
      case = array-examples/foo/foo.c
    """
    case_path = clean_ansi(case_path)

    parts = case_path.split('/')

    # 优先找 ComExp_Split 或 ComExp_Split_uN 之后的路径
    split_idx = None
    for i, p in enumerate(parts):
        if p == "ComExp_Split" or re.match(r"ComExp_Split_u\d+", p):
            split_idx = i
            break

    if split_idx is not None and split_idx + 1 < len(parts):
        rel_parts = parts[split_idx + 1:]
        benchmark = rel_parts[0] if len(rel_parts) >= 1 else ''
        case = '/'.join(rel_parts)
        return benchmark, case

    # 回退策略：取最后三级
    benchmark = parts[-3] if len(parts) >= 3 else ''
    case = '/'.join(parts[-3:]) if len(parts) >= 3 else case_path
    return benchmark, case

def sanitize_time(t):
    if t is None:
        return None
    try:
        t = float(t)
    except (TypeError, ValueError):
        return None
    if t < 0:
        return None
    return t

def parse_walltime(line):
    m = re.search(r'WALLTIME\s+([0-9.]+)', clean_ansi(line))
    if m:
        return sanitize_time(m.group(1))
    return None

def peek_walltime(lines, start, stop_markers):
    j = start
    while j < len(lines):
        cl = clean_ansi(lines[j])
        if any(m in cl for m in stop_markers):
            break
        wall = parse_walltime(cl)
        if wall is not None:
            return wall
        j += 1
    return None

def extract_unwind_from_logfile(logfile):
    """
    从日志文件名或目录中提取 unwind 值。
    """
    logfile = os.path.basename(logfile)

    m = re.search(r'_(\d+)\.log$', logfile)
    if m:
        return m.group(1)

    m = re.search(r'unwind(\d+)', logfile)
    if m:
        return m.group(1)

    m = re.search(r'ComExp_Split_u(\d+)', logfile)
    if m:
        return m.group(1)

    return ''

def extract_cbmc(logfile):
    results = []
    unwind = extract_unwind_from_logfile(logfile)

    with open(logfile, encoding='utf8') as f:
        lines = f.readlines()
    i = 0
    while i < len(lines):
        if 'Analysis result:' in lines[i] and i + 1 < len(lines):
            info = parse_result_line(lines[i + 1])
            if info:
                case_path, result, time_val = info
                wall = peek_walltime(lines, i + 2, ('Analysis result:', '========== Checking:'))
                if wall is not None:
                    time_val = wall
                time_val = sanitize_time(time_val)
                benchmark, case = extract_benchmark_and_case(case_path)
                results.append({
                    'tool': 'CBMC',
                    'unwind': unwind,
                    'benchmark': benchmark,
                    'case': case,
                    'result': result,
                    'time': time_val,
                    'source_log': logfile
                })
            i += 2
            continue
        i += 1
    return results

def extract_cpachecker(logfile):
    results = []
    with open(logfile, encoding='utf8') as f:
        lines = f.readlines()
    i = 0
    while i < len(lines):
        if 'Analysis result:' in lines[i] and i + 1 < len(lines):
            info = parse_result_line(lines[i + 1])
            if info:
                case_path, result, time_val = info
                wall = peek_walltime(lines, i + 2, ('Analysis result:', '========== Checking:'))
                if wall is not None:
                    time_val = wall
                time_val = sanitize_time(time_val)
                benchmark, case = extract_benchmark_and_case(case_path)
                results.append({
                    'tool': 'CPAchecker',
                    'unwind': '',
                    'benchmark': benchmark,
                    'case': case,
                    'result': result,
                    'time': time_val,
                    'source_log': logfile
                })
            i += 2
            continue
        i += 1
    return results

def main():
    all_results = []

    # 收集 CBMC 日志
    cbmc_logs = []
    for p in CBMC_LOG_PATTERNS:
        cbmc_logs.extend(glob.glob(p))
    cbmc_logs = sorted(set(cbmc_logs))

    print("Found CBMC logs:")
    for log in cbmc_logs:
        print("  ", log)

    for cbmc_log in cbmc_logs:
        all_results.extend(extract_cbmc(cbmc_log))

    # 收集 CPAchecker 日志（四包 + goblint）
    print("Found CPAchecker logs:")
    for cpachecker_log in CPACHECKER_LOGS:
        if os.path.exists(cpachecker_log):
            print("  ", cpachecker_log)
            all_results.extend(extract_cpachecker(cpachecker_log))
        else:
            print("Warning: CPAchecker log not found:", cpachecker_log)

    # 排序
    all_results.sort(key=lambda x: (x['case'], x['tool'], x['unwind']))

    # 导出 CSV
    fieldnames = ['tool', 'unwind', 'benchmark', 'case', 'result', 'time', 'source_log']
    with open(OUTPUT_CSV, 'w', newline='', encoding='utf8') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        for row in all_results:
            writer.writerow(row)

    print(f"Done! 结果已输出到 {OUTPUT_CSV}")
    print(f"Total rows: {len(all_results)}")

if __name__ == "__main__":
    main()