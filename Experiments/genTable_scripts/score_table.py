import os
import re
from collections import defaultdict

'''
使用: python3 score_table.py
功能：统计不同验证后端单独检测的实验结果
'''

# 动态获取工程根目录
CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, "..", ".."))  # repo root


# 结果文件路径
base = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split")
base_unicseq = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split_unicseq")

log_files = [
    os.path.join(base, "results_cbmc.log"),
    os.path.join(base, "results_cpachecker.log"),
    os.path.join(base, "results_uautomizer.log"),
    os.path.join(base_unicseq, "results_unicseq.log"),
]
verifier_names = ["cbmc", "cpachecker", "uautomizer", "unicseq"]

# 结果标签
POSITIVE = {"TRUE", "true"}
NEGATIVE = {"FALSE", "false"}
UNKNOWN = {"UNKNOWN", "unknown", "TIMEOUT", "timeout", "ERROR", "error"}

# 结果统计结构
result_map = {}  # result_map[file][tool] = (result, time)

def parse_unicseq_log(logfile):
    f2res = {}
    current_file = None
    true_cnt, false_cnt, unknown_cnt, total_time = 0, 0, 0, 0.0
    with open(logfile, "r", encoding="utf-8") as f:
        lines = f.readlines()
    for idx, line in enumerate(lines):
        mfile = re.search(r'UnicSeq Checking:\s+([^\s=]+)', line)
        if mfile:
            current_file = mfile.group(1).strip()
            continue
        mres = re.search(r'Final verification results:\s*([A-Z]+)', line)
        if mres and current_file:
            result = mres.group(1).strip().upper()
            for j in range(1, 8):
                if idx + j < len(lines):
                    mtime = re.search(r'Total running time:\s*([0-9.]+)', lines[idx+j])
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
    print(f"[DEBUG][unicseq] {logfile}: TRUE={true_cnt}, FALSE={false_cnt}, UNKNOWN={unknown_cnt}, TotalTime={total_time:.1f}")
    return f2res


def parse_one_log(logfile, tool):
    f2res = {}
    current_file = None
    true_cnt, false_cnt, unknown_cnt, total_time = 0, 0, 0, 0.0
    with open(logfile, "r", encoding="utf-8") as f:
        lines = f.readlines()
    for idx, line in enumerate(lines):
        # 剥离颜色码
        text = re.sub(r'\x1b\[[;0-9]+m', '', line)
        m2 = re.search(r'([^,]+),\s*([A-Z]+|TIMEOUT|UNKNOWN),\s*([-.\d]+)', text)
        if m2:
            fname = m2.group(1).strip()
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
    for idx, log in enumerate(log_files):
        tool = verifier_names[idx]
        if tool == "unicseq":
            f2res = parse_unicseq_log(log)
        else:
            f2res = parse_one_log(log, tool)
        for f in f2res:
            fullmap[f][tool] = f2res[f]
            all_files.add(f)
    return all_files, fullmap


def judge_score(gt, tool_res):
    # gt: ground truth (TRUE or FALSE), tool_res: result by tool
    # 返回(score, correct_proof, correct_alarm, wrong_proof, wrong_alarm, unknown)
    # SV-COMP规则：2分（正确proof），1分（正确alarm），-32（错误proof），-16（错误alarm）
    # TRUE: proof, FALSE: alarm
    result, _ = tool_res
    if result in POSITIVE:
        if gt in POSITIVE:
            return (2, 1, 0, 0, 0, 0)  # correct_proof
        else:
            return (-32, 0, 0, 1, 0, 0) # wrong_proof
    elif result in NEGATIVE:
        if gt in NEGATIVE:
            return (1, 0, 1, 0, 0, 0) # correct_alarm
        else:
            return (-16, 0, 0, 0, 1, 0) # wrong_alarm
    else:
        return (0, 0, 0, 0, 0, 1) # unknown

def main():
    all_files, fullmap = build_full_map()

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

    # 统计ground truth
    for f in sorted(all_files):
        tool2res = {}
        for vn in verifier_names:
            if vn in fullmap[f]:
                tool2res[vn] = fullmap[f][vn]
            else:
                tool2res[vn] = ("UNKNOWN", 0)
        counts = {"TRUE":0, "FALSE":0}
        for (r,_) in tool2res.values():
            if r in POSITIVE:
                counts["TRUE"] += 1
            elif r in NEGATIVE:
                counts["FALSE"] += 1
        if counts["TRUE"] > counts["FALSE"]:
            gt = "TRUE"
        elif counts["FALSE"] > counts["TRUE"]:
            gt = "FALSE"
        else:
            gt = None

        for vn in verifier_names:
            res, t = tool2res[vn]
            if gt is None or res in UNKNOWN:
                stat[vn]["Unknown"] += 1
            else:
                score, cp, ca, wp, wa, unk = judge_score(gt, (res, t))
                stat[vn]["Score"] += score
                stat[vn]["Correct"] += cp + ca
                stat[vn]["Correct proof"] += cp
                stat[vn]["Correct alarm"] += ca
                stat[vn]["Incorrect"] += wp + wa
                stat[vn]["Incorrect proof"] += wp
                stat[vn]["Incorrect alarm"] += wa
            stat[vn]["Total time"] += t
    metric_list = [
        "Score", "Correct", "Correct proof", "Correct alarm",
        "Incorrect", "Incorrect proof", "Incorrect alarm", "Unknown", "Total time"
    ]
    latex_names = {
        "cbmc": "CBMC",
        "cpachecker": "CPAchecker",
        "uautomizer": "UAutomizer",
        "unicseq": "UNI-CSeq"
    }
    print("\\begin{tabular}{lcccc}")
    print("\\toprule")
    print("Metric & CBMC & CPAchecker & UAutomizer & UNI-CSeq \\\\")
    print("\\midrule")
    for metric in metric_list:
        vals = [stat[vn][metric] if metric != "Total time" else f"{stat[vn][metric]:.1f}" for vn in verifier_names]
        print("{} & {} & {} & {} & {} \\\\".format(
            metric, *vals
        ))
    print("\\bottomrule")
    print("\\end{tabular}")

if __name__ == '__main__':
    main()