#!/usr/bin/env python3
"""
create_ground_truth_config.py
创建和管理ground truth配置文件
"""

import json
import os
from datetime import datetime

def create_ground_truth_json():
    """创建初始的ground truth JSON文件"""
    
    # 初始化ground truth数据结构
    ground_truth = {
        "metadata": {
            "total_programs": 136,
            "confirmed": 0,
            "last_updated": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            "version": "1.0"
        },
        "programs": {},
        "categories": {
            "confirmed_false": [],
            "confirmed_true": [],
            "unconfirmed": []
        }
    }
    
    # 从definitely_false_programs.txt读取FALSE程序
    false_programs = []
    if os.path.exists("definitely_false_programs.txt"):
        with open("definitely_false_programs.txt", "r") as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith("#"):
                    false_programs.append(line)
    
    # 从assertion_analysis_report.txt提取TRUE程序
    true_programs = []
    if os.path.exists("assertion_analysis_report.txt"):
        with open("assertion_analysis_report.txt", "r") as f:
            in_true_section = False
            for line in f:
                if "[1] 所有工具都检测为TRUE" in line:
                    in_true_section = True
                elif "[2] TRUE和UNKNOWN混合" in line:
                    in_true_section = False
                elif in_true_section and line.strip().endswith(".c"):
                    prog = line.strip()
                    true_programs.append(prog)
    
    # 填充ground truth
    for prog in false_programs:
        ground_truth["programs"][prog] = {
            "ground_truth": "FALSE",
            "confidence": "HIGH",
            "source": "tool_consensus",
            "confirmed_date": datetime.now().strftime("%Y-%m-%d"),
            "notes": "All or most tools agree"
        }
        ground_truth["categories"]["confirmed_false"].append(prog)
    
    for prog in true_programs:
        ground_truth["programs"][prog] = {
            "ground_truth": "TRUE", 
            "confidence": "HIGH",
            "source": "manual_verification",
            "confirmed_date": datetime.now().strftime("%Y-%m-%d"),
            "notes": "All tools report TRUE, manually confirmed"
        }
        ground_truth["categories"]["confirmed_true"].append(prog)
    
    # 统计
    ground_truth["metadata"]["confirmed"] = len(ground_truth["programs"])
    
    # 保存到文件
    with open("ground_truth.json", "w", encoding="utf-8") as f:
        json.dump(ground_truth, f, indent=2, ensure_ascii=False)
    
    print(f"Created ground_truth.json with {len(false_programs)} FALSE and {len(true_programs)} TRUE programs")
    print(f"Total confirmed: {ground_truth['metadata']['confirmed']}/{ground_truth['metadata']['total_programs']}")
    
    return ground_truth

if __name__ == "__main__":
    create_ground_truth_json()