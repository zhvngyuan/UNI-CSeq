import os
import re
import csv
import glob

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, "..", ".."))

# CBMC 和 CPAChecker 结果log路径
cbmc_logs = [
    os.path.join(CUR_DIR, "ComExp_Split_u2", "results_cbmc_unwind2.log"),
    os.path.join(CUR_DIR, "ComExp_Split_u4", "results_cbmc_unwind4.log"),
    os.path.join(CUR_DIR, "ComExp_Split_u8", "results_cbmc_unwind8.log"),
    os.path.join(CUR_DIR, "ComExp_Split_u16", "results_cbmc_unwind16.log"),
    os.path.join(CUR_DIR, "ComExp_Split_u32", "results_cbmc_unwind32.log"),
]
cpachecker_logs = [
    os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split", "results_cpachecker.log"),
    os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split", "results_goblint-regression_cpachecker.log"),
]

# ANSI颜色清理
ansi_escape = re.compile(r'\x1b\[[0-9;]*m')

def clean_ansi(s):
    return ansi_escape.sub('', s)

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
    """Look ahead for WALLTIME until the next case marker."""
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

def parse_result_line(line):
    # 匹配: 路径, 结果, 时间
    # 例如: /path/to/file.c, TRUE, 0.44
    line = clean_ansi(line)
    m = re.match(r'(.+?),\s*(TRUE|FALSE|UNKNOWN|TIMEOUT),\s*([0-9.]+)', line)
    if m:
        return m.group(1).strip(), m.group(2), float(m.group(3))
    # 有些可能有颜色码包裹如 [92mTRUE[0m
    m = re.match(r'(.+?),\s*\[?9[123]m?(TRUE|FALSE|UNKNOWN|TIMEOUT)\[?0*m?,\s*([0-9.]+)', line)
    if m:
        return m.group(1).strip(), m.group(2), float(m.group(3))
    # 有些 UNKNOWN/TIMEOUT 可能没时间
    m = re.match(r'(.+?),\s*(TRUE|FALSE|UNKNOWN|TIMEOUT)', line)
    if m:
        return m.group(1).strip(), m.group(2), None
    return None

def extract_cbmc(logfile):
    unwind = re.search(r'unwind(\d+)', logfile)
    unwind = unwind.group(1) if unwind else ''
    results = []
    with open(logfile, encoding='utf8') as f:
        lines = f.readlines()
    i = 0
    while i < len(lines):
        if 'Analysis result:' in lines[i] and i + 1 < len(lines):
            info = parse_result_line(lines[i + 1])
            if info:
                case_path, result, time_val = info
                case_path = clean_ansi(case_path)
                wall = peek_walltime(lines, i + 2, ('Analysis result:', '========== Checking:'))
                if wall is not None:
                    time_val = wall
                time_val = sanitize_time(time_val)
                m = re.search(r'ComExp_Split_u\d+/(.*?)/', case_path)
                benchmark = m.group(1) if m else ''
                case = '/'.join(case_path.split('/')[-3:])
                results.append({
                    'tool': 'CBMC',
                    'unwind': unwind,
                    'benchmark': benchmark,
                    'case': case,
                    'result': result,
                    'time': time_val
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
                case_path = clean_ansi(case_path)
                wall = peek_walltime(lines, i + 2, ('Analysis result:', '========== Checking:'))
                if wall is not None:
                    time_val = wall
                time_val = sanitize_time(time_val)
                m = re.search(r'ComExp_Split/(.*?)/', case_path)
                benchmark = m.group(1) if m else ''
                case = '/'.join(case_path.split('/')[-3:])
                results.append({
                    'tool': 'CPAchecker',
                    'unwind': '',
                    'benchmark': benchmark,
                    'case': case,
                    'result': result,
                    'time': time_val
                })
            i += 2
            continue
        i += 1
    return results

# 主流程
all_results = []
for cbmc_log in cbmc_logs:
    all_results.extend(extract_cbmc(cbmc_log))
for cpachecker_log in cpachecker_logs:
    all_results.extend(extract_cpachecker(cpachecker_log))

# 按case、tool、unwind排序
all_results.sort(key=lambda x: (x['case'], x['tool'], x['unwind']))

# 导出为csv
with open('all_results.csv', 'w', newline='', encoding='utf8') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=['tool', 'unwind', 'benchmark', 'case', 'result', 'time'])
    writer.writeheader()
    for row in all_results:
        writer.writerow(row)

print('Done! 结果已输出到 all_results.csv')