#!/usr/bin/env python3
"""
运行脚本：
python3 gen_compare_table.py

Assertions：源文件静态扫描（用户断言站点）。
#Vio：CBMC ** Results: 按身份键塌缩后的违反数；同一函数内表达式相同的多条源断言分开计。
时间列：前四包读 output_cbmc.log / output_NIChecker.log；
rw_benchmark 的 Time 与 gen_rw_package_table.py 相同，解析
    compare_with_intAbs_cbmc/runExp.log 与 compare_intAbs_ver_nichecker/runExp_nichecker.log。
NIChecker 的 u/r、UNI-CSeq 的 u：从上述日志解析检测该包时使用的 unwind / rounds；
Total 行不汇总这三列。
Reference only 列：CPAchecker / Portfolio 均按 FALSE 判决按包计数
（CPAchecker 读 ComExp_Split 简单日志，Portfolio 读 cbmc-cpachecker UnicSeq 日志）。
"""

import re
import os
from collections import defaultdict

from assertion_stats import analyze_test_dir
from gen_rw_package_table import (
    NICHECKER_LOG,
    PACKAGES,
    UNICSEQ_LOG,
    parse_nichecker_log,
    parse_unicseq_log,
    require_program,
)
from score_table_all_correctness import get_package_name, normalize_filename

CUR_DIR = os.path.dirname(os.path.abspath(__file__))
EXPERIMENTS_DIR = os.path.abspath(os.path.join(CUR_DIR, ".."))
output_file = os.path.join(CUR_DIR, "compare_table.tex")

packages = [
    {
        "name": "Idv-races",
        "path": os.path.join(EXPERIMENTS_DIR, "svcomp2022", "Idv-races")
    },
    {
        "name": "pthread",
        "path": os.path.join(EXPERIMENTS_DIR, "svcomp2022", "pthread")
    },
    {
        "name": "goblint-regression",
        "path": os.path.join(EXPERIMENTS_DIR, "svcomp2022", "goblint-regression")
    },
    {
        "name": "racebench2.1",
        "path": os.path.join(EXPERIMENTS_DIR, "racebench2.1")
    }
]

packages_data = {
    "racebench2.1": {"LOC": 1753},
    "Idv-races": {"LOC": 211},
    "pthread": {"LOC": 486},
    "goblint-regression": {"LOC": 2066}
}

Total_Files = 0
Total_LOC = 0
Total_Assertions = 0
Total_nic_violations = 0
Total_ni_time = 0.0
Total_uni_violations = 0
Total_uni_time = 0.0
Total_cpachecker_violations = 0
Total_portfolio_violations = 0

CPACHECKER_LOGS = [
    os.path.join(EXPERIMENTS_DIR, "ComExp_Split", "results_cpachecker.log"),
    os.path.join(
        EXPERIMENTS_DIR, "ComExp_Split",
        "results_goblint-regression_cpachecker.log",
    ),
]
PORTFOLIO_LOGS = [
    os.path.join(
        EXPERIMENTS_DIR, "ComExp_Split_unicseq_CC",
        "results_unicseq_cbmc-cpachecker.log",
    ),
    os.path.join(
        EXPERIMENTS_DIR, "ComExp_Split_unicseq_CC",
        "results_unicseq_goblint-regression_cbmc-cpachecker.log",
    ),
]


def latex_escape(text):
    """对 LaTeX 特殊字符做最基本转义"""
    return text.replace('_', r'\_')


def parse_testdirs(testdirs_path):
    """解析 testdirs.sh，返回目录名列表"""
    with open(testdirs_path, 'r', encoding='utf-8', errors='ignore') as f:
        txt = f.read()
    m = re.search(r'(BENCHMARK_DIRS|TEST_DIRS)=([\'"])(.*?)\2', txt, re.DOTALL)
    if not m:
        raise ValueError(f"testdirs.sh 格式不正确: {testdirs_path}")
    dir_lines = m.group(3).strip().splitlines()
    dirs = [d.strip() for d in dir_lines if d.strip()]
    return dirs


def get_package_src_stats(base_path, testdirs):
    """源断言站点数 + 源级违例数（循环展开副本塌缩，重复源断言站点分开计）。"""
    assertion_count = 0
    uni_violations = 0
    nic_violations = 0
    for subdir in testdirs:
        test_dir = os.path.join(base_path, subdir)
        stats = analyze_test_dir(test_dir, subdir)
        assertion_count += stats["src_assertions"]
        uni_violations += len(stats["uni"]["failed_keys"])
        if stats["nic"]["source"] == "counterexample_fallback":
            nic_violations += stats["nic"].get("fallback_counterexample") or 0
        else:
            nic_violations += len(stats["nic"]["failed_keys"])
    return assertion_count, uni_violations, nic_violations


_ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")


def _strip_ansi(text):
    return _ANSI_RE.sub("", text)


def parse_unicseq_unwind(log_path):
    """Parse UNI-CSeq unwind from a package log (header, banner, or cbmc command)."""
    if not os.path.isfile(log_path):
        return None
    checking_re = re.compile(r"Checking\s+\S+\s+\(unwind=(\d+)")
    header_re = re.compile(r"backend=cbmc\s+unwind=(\d+)", re.I)
    cmd_re = re.compile(r"\bcbmc\b.*--unwind\s+(\d+)")
    with open(log_path, encoding="utf-8", errors="ignore") as f:
        for line in f:
            text = _strip_ansi(line)
            m = checking_re.search(text)
            if m:
                return int(m.group(1))
            m = header_re.search(text)
            if m:
                return int(m.group(1))
            m = cmd_re.search(text)
            if m:
                return int(m.group(1))
    return None


def parse_nichecker_params(log_path):
    """Parse (unwind, rounds) used by NIChecker from a package log."""
    if not os.path.isfile(log_path):
        return None, None
    banner_re = re.compile(r"unwind=(\d+)\s+rounds=(\d+)")
    unwind_re = re.compile(r"--unwind\s+(\d+)")
    rounds_re = re.compile(r"--rounds\s+(\d+)")
    unwind = rounds = None
    with open(log_path, encoding="utf-8", errors="ignore") as f:
        for line in f:
            text = _strip_ansi(line)
            m = banner_re.search(text)
            if m:
                return int(m.group(1)), int(m.group(2))
            if unwind is None:
                m = unwind_re.search(text)
                if m:
                    unwind = int(m.group(1))
            if rounds is None:
                m = rounds_re.search(text)
                if m:
                    rounds = int(m.group(1))
            if unwind is not None and rounds is not None:
                return unwind, rounds
    return unwind, rounds


def format_bound(value):
    """Format unwind/rounds for a table cell; empty if unknown."""
    return "" if value is None else str(value)


def parse_output_cbmc(cbmc_log_path):
    """解析 output_cbmc.log，返回 UNI-CSeq time 总和"""
    total_time = 0.0
    pattern = re.compile(
        r'\.c,\s*(?:\x1b\[[0-9;]*m)?(FALSE|TRUE|UNKNOWN|TIMEOUT)(?:\x1b\[[0-9;]*m)?,\s*([0-9.]+)'
    )
    if not os.path.isfile(cbmc_log_path):
        return 0.0
    with open(cbmc_log_path, 'r', encoding='utf-8') as f:
        for line in f:
            m = pattern.search(line)
            if m:
                total_time += float(m.group(2))
    return total_time


def parse_output_NIChecker(NIChecker_log_path):
    """解析 output_NIChecker.log，返回 time 总和（#Vio 不再用 counterexample）。"""
    total_time = 0.0
    pattern = re.compile(r'counterexample:\s*(\d+),\s*time:\s*([0-9.]+)\s*s')
    if not os.path.isfile(NIChecker_log_path):
        return 0.0
    with open(NIChecker_log_path, 'r', encoding='utf-8', errors='ignore') as f:
        for line in f:
            m = pattern.search(line)
            if m:
                total_time += float(m.group(2))
    return total_time


def format_speedup(nic_time, uni_time):
    """格式化 SpeedUp: NIChecker Time / UNI-CSeq Time，保留一位小数并加 X"""
    if uni_time == 0:
        return "0.0X"
    return f"{nic_time / uni_time:.1f}X"


def rw_benchmark_times():
    """Sum NIChecker / UNI-CSeq times over 18 rw programs (same logs as gen_rw_package_table)."""
    nichecker = parse_nichecker_log(NICHECKER_LOG)
    unicseq_time = parse_unicseq_log(UNICSEQ_LOG)
    nic_time = 0.0
    uni_time = 0.0
    for _pkg, progs in PACKAGES:
        for name in progs:
            nic_time += require_program(nichecker, name, "NIChecker")[1]
            uni_time += require_program(unicseq_time, name, "UNI-CSeq")
    return nic_time, uni_time


def _false_counts_by_package(f2res):
    """Count FALSE verdicts per package from a file→result map."""
    counts = defaultdict(int)
    for fname, result in f2res.items():
        if result == "FALSE":
            counts[get_package_name(fname)] += 1
    return counts


def parse_unicseq_false_by_package(logfiles, kind):
    """Count FALSE verdicts per package from UnicSeq-style logs.

    Same log format as score_table_all_correctness.parse_unicseq_log.
    """
    ansi = re.compile(r"\x1b\[[;0-9]+m")
    file_re = re.compile(r"UnicSeq Checking(?:\s+\([^)]+\))?\s*:\s+([^\s=]+)")
    res_re = re.compile(r"Final verification results:\s*([A-Z]+)")
    f2res = {}
    for logfile in logfiles:
        if not os.path.isfile(logfile):
            raise FileNotFoundError("missing %s log: %s" % (kind, logfile))
        current_file = None
        with open(logfile, encoding="utf-8", errors="ignore") as f:
            for line in f:
                text = ansi.sub("", line)
                mfile = file_re.search(text)
                if mfile:
                    current_file = normalize_filename(mfile.group(1).strip())
                    continue
                mres = res_re.search(text)
                if mres and current_file:
                    f2res[current_file] = mres.group(1).strip().upper()
                    current_file = None
    return _false_counts_by_package(f2res)


def parse_simple_false_by_package(logfiles, kind):
    """Count FALSE verdicts per package from simple 'file, RESULT, time' logs.

    Same log format as score_table_all_correctness.parse_simple_log.
    """
    ansi = re.compile(r"\x1b\[[;0-9]+m")
    line_re = re.compile(
        r"([^,]+),\s*([A-Z]+|TIMEOUT|UNKNOWN|ERROR),\s*([-.\d]+)"
    )
    f2res = {}
    for logfile in logfiles:
        if not os.path.isfile(logfile):
            raise FileNotFoundError("missing %s log: %s" % (kind, logfile))
        with open(logfile, encoding="utf-8", errors="ignore") as f:
            for line in f:
                text = ansi.sub("", line)
                m = line_re.search(text)
                if not m:
                    continue
                fname = normalize_filename(m.group(1).strip())
                f2res[fname] = m.group(2).strip().upper()
    return _false_counts_by_package(f2res)


def portfolio_violations_by_package():
    """Count FALSE verdicts per package from CBMC + CPAchecker (Parallel) logs."""
    return parse_unicseq_false_by_package(PORTFOLIO_LOGS, "portfolio")


def cpachecker_violations_by_package():
    """Count FALSE verdicts per package from CPAchecker logs (same rule as portfolio)."""
    return parse_simple_false_by_package(CPACHECKER_LOGS, "cpachecker")


rows = []
cpachecker_vio = cpachecker_violations_by_package()
portfolio_vio = portfolio_violations_by_package()
for pkg in packages:
    pkg_name = pkg["name"]
    base_path = pkg["path"]

    testdirs_file = os.path.join(base_path, "testdirs.sh")
    cbmc_log = os.path.join(base_path, "output_cbmc.log")
    NIChecker_log = os.path.join(base_path, "output_NIChecker.log")

    testdirs = parse_testdirs(testdirs_file)
    assertion_count, uni_violations, nic_violations = get_package_src_stats(
        base_path, testdirs
    )

    files_count = len(testdirs)
    uni_time = parse_output_cbmc(cbmc_log)
    ni_time = parse_output_NIChecker(NIChecker_log)
    nic_u, nic_r = parse_nichecker_params(NIChecker_log)
    uni_u = parse_unicseq_unwind(cbmc_log)
    speedup = format_speedup(ni_time, uni_time)
    pkg_cpachecker = cpachecker_vio.get(pkg_name, 0)
    pkg_portfolio = portfolio_vio.get(pkg_name, 0)

    rows.append((
        pkg_name,
        files_count,
        packages_data[pkg_name]["LOC"],
        assertion_count,
        nic_u,
        nic_r,
        nic_violations,
        ni_time,
        uni_u,
        uni_violations,
        uni_time,
        speedup,
        pkg_cpachecker,
        pkg_portfolio
    ))

    Total_Files += files_count
    Total_LOC += packages_data[pkg_name]["LOC"]
    Total_Assertions += assertion_count
    Total_nic_violations += nic_violations
    Total_ni_time += ni_time
    Total_uni_violations += uni_violations
    Total_uni_time += uni_time
    Total_cpachecker_violations += pkg_cpachecker
    Total_portfolio_violations += pkg_portfolio

# rw_benchmark：files/LOC/assertions/#Vio 仍用论文口径硬编码；
# Time 解析 runExp.log / runExp_nichecker.log，与 gen_rw_package_table.py 一致。
rw_nic_time, rw_uni_time = rw_benchmark_times()
extra_row = {
        "name": r"rw\_benchmark",
        "files": 18,
        "loc": 11084,
        "assertions": 78,
        "nic_violations": 40,
        "nic_time": rw_nic_time,
        "uni_violations": 40,
        "uni_time": rw_uni_time,
        "cpachecker_violations": cpachecker_vio.get("rw_benchmark", 0),
        "portfolio_violations": portfolio_vio.get("rw_benchmark", 0),
}

extra_speedup = format_speedup(extra_row["nic_time"], extra_row["uni_time"])
extra_nic_u, extra_nic_r = parse_nichecker_params(NICHECKER_LOG)
extra_uni_u = parse_unicseq_unwind(UNICSEQ_LOG)

rows.append((
        extra_row["name"],
        extra_row["files"],
        extra_row["loc"],
        extra_row["assertions"],
        extra_nic_u,
        extra_nic_r,
        extra_row["nic_violations"],
        extra_row["nic_time"],
        extra_uni_u,
        extra_row["uni_violations"],
        extra_row["uni_time"],
        extra_speedup,
        extra_row["cpachecker_violations"],
        extra_row["portfolio_violations"]
))

Total_Files += extra_row["files"]
Total_LOC += extra_row["loc"]
Total_Assertions += extra_row["assertions"]
Total_nic_violations += extra_row["nic_violations"]
Total_ni_time += extra_row["nic_time"]
Total_uni_violations += extra_row["uni_violations"]
Total_uni_time += extra_row["uni_time"]
Total_cpachecker_violations += extra_row["cpachecker_violations"]
Total_portfolio_violations += extra_row["portfolio_violations"]

Total_speedup = format_speedup(Total_ni_time, Total_uni_time)

with open(output_file, 'w') as f:
    f.write(r"""\begin{table*}[ht]
\centering
\caption{Comparison of NIChecker and UNI-CSeq (with CBMC as backend) on five benchmark suites.}
\label{tab:compare_with_NIChecker}
\setlength{\tabcolsep}{4pt}
\resizebox{\textwidth}{!}{
\begin{threeparttable}
\begin{tabular}{l
      S[table-format=3.0] % Files
      S[table-format=5.0] % LOC
      S[table-format=3.0] % Assertions
      S[table-format=1.0] % NIChecker u
      S[table-format=1.0] % NIChecker r
      S[table-format=3.0] % NIChecker Violations
      S[table-format=3.1] % NIChecker time
      S[table-format=1.0] % UNI-CSeq u
      S[table-format=3.0] % UNI-CSeq Violations
      S[table-format=3.1] % UNI-CSeq time
      c
      S[table-format=3.0] % CPAchecker
      S[table-format=3.0] % Portfolio
      }
""")

    f.write(r"""        \toprule[1pt]
      \multicolumn{1}{l}{\multirow{2}{*}{Packages}} & \multicolumn{1}{c}{\multirow{2}{*}{Files}} & \multicolumn{1}{c}{\multirow{2}{*}{LOC}} & \multicolumn{1}{c}{\multirow{2}{*}{Assertions}}  &\multicolumn{4}{c}{\multirow{1}{*}{NIChecker \cite{nichecker}}} &\multicolumn{3}{c}{\multirow{1}{*}{UNI-CSeq}} &\multicolumn{1}{l}{\multirow{2}{*}{SpeedUp}} & \multicolumn{2}{c}{\multirow{1}{*}{Reference only$^{*}$}}\\ \cmidrule(lr){5-8} \cmidrule(lr){9-11} \cmidrule(lr){13-14}
    
       & & & & \multicolumn{1}{c}{u} & \multicolumn{1}{c}{r} & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Time (s)} & \multicolumn{1}{c}{u} & \multicolumn{1}{c}{Violations} & \multicolumn{1}{c}{Time (s)} & & \multicolumn{1}{c}{CPAchecker} & \multicolumn{1}{c}{Portfolio}\\ \midrule
""")

    for row in rows:
        f.write(
            "{} & {} & {} & {} & {} & {} & {} & {:.1f} & {} & {} & {:.1f} & {} & {} & {}\\\\\n".format(
                row[0],
                row[1],
                row[2],
                row[3],
                format_bound(row[4]),
                format_bound(row[5]),
                row[6],
                row[7],
                format_bound(row[8]),
                row[9],
                row[10],
                row[11],
                row[12],
                row[13],
            )
        )

    f.write(r"""\midrule
""")

    f.write(
        "Total & {} & {} & {} & \\multicolumn{{1}}{{c}}{{}} & \\multicolumn{{1}}{{c}}{{}} & {} & {:.1f} & \\multicolumn{{1}}{{c}}{{}} & {} & {:.1f} & {} & {} & {}\\\\\n".format(
            Total_Files,
            Total_LOC,
            Total_Assertions,
            Total_nic_violations,
            Total_ni_time,
            Total_uni_violations,
            Total_uni_time,
            Total_speedup,
            Total_cpachecker_violations,
            Total_portfolio_violations,
        )
    )

    f.write(r"""        \bottomrule[1pt]
\end{tabular}

\begin{tablenotes}
{\small $^{*}$The CPAchecker and Portfolio columns report the number of violations detected by the CPAchecker and CBMC + CPAchecker (Parallel) configurations evaluated in Table~\ref{tab:Cooperation_Verification}.}
\end{tablenotes}
\end{threeparttable}
}
\end{table*}
""")

print(f"[INFO] 输出已保存到 {output_file}")
