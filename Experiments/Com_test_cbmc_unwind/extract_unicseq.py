import os
import re
import csv

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, "..", ".."))
unicseq_log = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split_unicseq", "results_unicseq.log")
output_csv = "unicseq_results.csv"

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

def extract_unicseq(logfile):
    results = []
    with open(logfile, encoding='utf8') as f:
        lines = f.readlines()

    i = 0
    while i < len(lines):
        line = clean_ansi(lines[i])
        if "UnicSeq Checking:" in line:
            m = re.search(r'UnicSeq Checking: (.*)', line)
            if m:
                case_path = m.group(1).strip()
                benchmark_m = re.search(r'ComExp_Split_unicseq/(.*?)/', case_path)
                benchmark = benchmark_m.group(1) if benchmark_m else ''
                case = '/'.join(case_path.split('/')[-3:])
                # 跳到"Final verification results:"
                while i < len(lines) and "Final verification results:" not in lines[i]:
                    i += 1
                if i < len(lines):
                    final_result = clean_ansi(lines[i]).split(":")[-1].strip()
                else:
                    final_result = ""
                # Backend results
                while i < len(lines) and "Backend results:" not in lines[i]:
                    i += 1
                # cbmc/cpachecker结果可选
                if i < len(lines):
                    backend_line = clean_ansi(lines[i])
                # Total running time
                while i < len(lines) and "Total running time:" not in lines[i]:
                    i += 1
                if i < len(lines):
                    t_m = re.search(r'Total running time:\s*([0-9.]+)', lines[i])
                    time = sanitize_time(t_m.group(1) if t_m else None)
                else:
                    time = None
                j = i + 1
                while j < len(lines):
                    cl = clean_ansi(lines[j])
                    if "UnicSeq Checking:" in cl:
                        break
                    wall = parse_walltime(cl)
                    if wall is not None:
                        time = wall
                        break
                    j += 1
                results.append({
                    'tool': 'UnicSeq',
                    'unwind': '',
                    'benchmark': benchmark,
                    'case': case,
                    'result': final_result,
                    'time': time
                })
        i += 1
    return results

results = extract_unicseq(unicseq_log)
with open(output_csv, 'w', newline='', encoding='utf8') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=['tool', 'unwind', 'benchmark', 'case', 'result', 'time'])
    writer.writeheader()
    for row in results:
        writer.writerow(row)

print(f"已提取UnicSeq并行实验结果，输出到 {output_csv}")