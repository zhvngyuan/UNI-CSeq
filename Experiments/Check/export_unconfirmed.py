#!/usr/bin/env python3
"""
export_unconfirmed.py
导出需要人工确认的程序列表
"""

import json
import os

def export_unconfirmed_programs():
    """导出未确认的程序到文本文件，便于人工标注"""
    
    # 收集所有已确认的程序
    confirmed = set()
    
    # 从definitely_false_programs.txt读取
    if os.path.exists("definitely_false_programs.txt"):
        with open("definitely_false_programs.txt", "r") as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith("#"):
                    confirmed.add(line)
    
    # 已知的TRUE程序（根据您的描述，所有工具都为TRUE的52个）
    true_programs = [
        "Idv-races/svp_simple_300_001/svp_simple_300_001_assert1.c",
        # ... 其他TRUE程序
    ]
    
    confirmed.update(true_programs)
    
    # 需要确认的22个程序（TRUE和UNKNOWN混合 + 所有UNKNOWN）
    unconfirmed = [
        "racebench2.1/svp_simple_004/svp_simple_004_assert2.c",
        "racebench2.1/svp_simple_009/svp_simple_009_assert1.c",
        "racebench2.1/svp_simple_009/svp_simple_009_assert2.c",
        "racebench2.1/svp_simple_013/svp_simple_013_assert2.c",
        "racebench2.1/svp_simple_013/svp_simple_013_assert3.c",
        "racebench2.1/svp_simple_014/svp_simple_014_assert1.c",
        "racebench2.1/svp_simple_014/svp_simple_014_assert2.c",
        "racebench2.1/svp_simple_018/svp_simple_018_assert2.c",
        # 所有UNKNOWN的程序
        "racebench2.1/svp_simple_011/svp_simple_011_assert1.c",
        "racebench2.1/svp_simple_011/svp_simple_011_assert2.c",
        "racebench2.1/svp_simple_012/svp_simple_012_assert1.c",
        "racebench2.1/svp_simple_023/svp_simple_023_assert1.c",
        "racebench2.1/svp_simple_024/svp_simple_024_assert1.c",
        "racebench2.1/svp_simple_025/svp_simple_025_assert1.c",
        "racebench2.1/svp_simple_031/svp_simple_031_assert1.c",
        "racebench2.1/svp_simple_031/svp_simple_031_assert2.c",
        # rw_benchmark中的UNKNOWN
        "rw_benchmark/i2c_pca_isa_1/main_n_assert1.c",
        "rw_benchmark/i2c_pca_isa_2/main_n_assert1.c",
        "rw_benchmark/i2c_pca_isa_3/main_n_assert1.c",
        "rw_benchmark/logger1/main_n_assert1.c",
        "rw_benchmark/logger2/main_n_assert1.c",
        "rw_benchmark/logger3/main_n_assert1.c",
    ]
    
    # 创建待确认文件
    with open("programs_to_confirm.txt", "w") as f:
        f.write("# Programs to manually confirm\n")
        f.write("# Format: program_path,TRUE/FALSE,notes\n")
        f.write("# Example: racebench2.1/svp_simple_004/svp_simple_004_assert2.c,TRUE,manually verified\n")
        f.write("#\n")
        for prog in unconfirmed:
            f.write(f"{prog},,\n")
    
    print(f"Created programs_to_confirm.txt with {len(unconfirmed)} programs")
    print("Please edit the file and fill in TRUE/FALSE for each program")
    print("Then run: python update_ground_truth.py batch programs_to_confirm.txt")

if __name__ == "__main__":
    export_unconfirmed_programs()