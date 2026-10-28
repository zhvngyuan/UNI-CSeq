#!/usr/bin/env python3
"""
extract_false_assertions.py
提取所有被验证为FALSE的断言程序，并生成分类报告
"""

import os
import re
from collections import defaultdict
from datetime import datetime

# 日志文件路径
log_files = {
    "CBMC": "/home/dell/zyworkspace/unichecker/Experiments/ComExp_Split/results_cbmc.log",
    "CPAchecker": "/home/dell/zyworkspace/unichecker/Experiments/ComExp_Split/results_cpachecker.log",
    "UAutomizer": "/home/dell/zyworkspace/unichecker/Experiments/ComExp_Split/results_uautomizer.log",
    "UNI-CSeq": "/home/dell/zyworkspace/unichecker/Experiments/ComExp_Split_unicseq/results_unicseq.log",
    "CBMC+CPAchecker": "/home/dell/zyworkspace/unichecker/Experiments/ComExp_Split_unicseq_CC/results_unicseq_cbmc-cpachecker.log",
    "CBMC+UAutomizer": "/home/dell/zyworkspace/unichecker/Experiments/ComExp_Split_unicseq_CA/results_unicseq_cbmc-uautomizer.log",
    "Sequential": "/home/dell/zyworkspace/unichecker/Experiments/ComExp_Split_unicseq_CCA/results_unicseq_sequential.log"
}

def extract_filename_key(filepath):
    """从文件路径中提取关键标识"""
    parts = filepath.split('/')
    # 查找benchmark类别
    for i, part in enumerate(parts):
        if part in ["Idv-races", "pthread", "racebench2.1", "rw_benchmark"]:
            if i + 2 < len(parts):
                # 返回 "类别/子目录/文件名"
                return "/".join(parts[i:i+3])
    # 如果没找到，返回最后三部分
    if len(parts) >= 3:
        return "/".join(parts[-3:])
    return filepath

def parse_unicseq_log(logfile):
    """解析UNI-CSeq格式的日志"""
    results = {}
    if not os.path.exists(logfile):
        print(f"[WARNING] File not found: {logfile}")
        return results
    
    with open(logfile, "r", encoding="utf-8") as f:
        content = f.read()
    
    # 去除ANSI颜色码
    content = re.sub(r'\x1b\[[;0-9]+m', '', content)
    
    # 分割成各个检测块
    blocks = re.split(r'={10,}.*?UnicSeq Checking', content)
    
    for block in blocks:
        # 查找文件路径
        file_match = re.search(r':\s+([^\s]+\.c)', block)
        if not file_match:
            continue
        
        filepath = file_match.group(1)
        file_key = extract_filename_key(filepath)
        
        # 查找验证结果
        result_match = re.search(r'Final verification results:\s*([A-Z]+)', block)
        if result_match:
            result = result_match.group(1).strip().upper()
            results[file_key] = result
    
    return results

def parse_single_tool_log(logfile):
    """解析单个工具的日志"""
    results = {}
    if not os.path.exists(logfile):
        print(f"[WARNING] File not found: {logfile}")
        return results
    
    with open(logfile, "r", encoding="utf-8") as f:
        for line in f:
            # 去除颜色码
            line = re.sub(r'\x1b\[[;0-9]+m', '', line)
            # 匹配结果行
            match = re.search(r'([^,]+\.c),\s*([A-Z]+|TIMEOUT|UNKNOWN)', line)
            if match:
                filepath = match.group(1).strip()
                result = match.group(2).strip().upper()
                file_key = extract_filename_key(filepath)
                results[file_key] = result
    
    return results

def main():
    # 收集所有结果
    all_results = {}
    all_files = set()
    
    for tool_name, logfile in log_files.items():
        if "unicseq" in logfile.lower() or "sequential" in tool_name.lower() or "CBMC+" in tool_name:
            results = parse_unicseq_log(logfile)
        else:
            results = parse_single_tool_log(logfile)
        
        all_results[tool_name] = results
        all_files.update(results.keys())
        print(f"[INFO] {tool_name}: Found {len(results)} results")
    
    # 分类文件
    definitely_false = set()  # 确定为FALSE的（至少有一个工具检测为FALSE）
    all_true = set()          # 所有工具都检测为TRUE
    mixed_true_unknown = set() # TRUE和UNKNOWN混合
    all_unknown = set()       # 所有工具都是UNKNOWN
    has_timeout_error = set() # 有TIMEOUT或ERROR的
    
    # 按类别组织
    by_category = defaultdict(lambda: {
        'false': [],
        'true': [],
        'mixed': [],
        'unknown': []
    })
    
    for file_key in sorted(all_files):
        results_for_file = {}
        for tool_name in log_files.keys():
            if file_key in all_results[tool_name]:
                results_for_file[tool_name] = all_results[tool_name][file_key]
            else:
                results_for_file[tool_name] = "NOT_FOUND"
        
        # 提取类别
        category = file_key.split('/')[0] if '/' in file_key else "other"
        
        # 统计结果
        has_false = any(r == "FALSE" for r in results_for_file.values())
        has_true = any(r == "TRUE" for r in results_for_file.values())
        has_unknown = any(r in ["UNKNOWN", "TIMEOUT", "ERROR", "NOT_FOUND"] for r in results_for_file.values())
        
        # 构建结果字符串
        result_str = f"{file_key}\n"
        for tool, res in results_for_file.items():
            result_str += f"  {tool:20s}: {res}\n"
        
        # 分类
        if has_false:
            definitely_false.add(file_key)
            by_category[category]['false'].append((file_key, results_for_file))
        elif has_true and not has_unknown:
            all_true.add(file_key)
            by_category[category]['true'].append((file_key, results_for_file))
        elif has_true and has_unknown:
            mixed_true_unknown.add(file_key)
            by_category[category]['mixed'].append((file_key, results_for_file))
        else:
            all_unknown.add(file_key)
            by_category[category]['unknown'].append((file_key, results_for_file))
    
    # 生成报告
    report_file = "assertion_analysis_report.txt"
    with open(report_file, "w", encoding="utf-8") as f:
        f.write("=" * 80 + "\n")
        f.write("断言验证结果分析报告\n")
        f.write(f"生成时间: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
        f.write("=" * 80 + "\n\n")
        
        # 统计摘要
        f.write("【统计摘要】\n")
        f.write(f"总程序数: {len(all_files)}\n")
        f.write(f"确定为FALSE (断言违反): {len(definitely_false)}\n")
        f.write(f"所有工具都为TRUE: {len(all_true)}\n")
        f.write(f"TRUE和UNKNOWN混合: {len(mixed_true_unknown)}\n")
        f.write(f"所有工具都为UNKNOWN: {len(all_unknown)}\n")
        f.write("\n")
        
        # 按类别详细列表
        f.write("=" * 80 + "\n")
        f.write("【确定为FALSE的程序】（可以跳过人工检查）\n")
        f.write("=" * 80 + "\n\n")
        
        for category in ["Idv-races", "pthread", "racebench2.1", "rw_benchmark"]:
            if category in by_category and by_category[category]['false']:
                f.write(f"\n{category} ({len(by_category[category]['false'])} 个):\n")
                f.write("-" * 40 + "\n")
                for file_key, results in sorted(by_category[category]['false']):
                    f.write(f"\n{file_key}\n")
                    # 只显示检测为FALSE的工具
                    false_tools = [t for t, r in results.items() if r == "FALSE"]
                    f.write(f"  检测为FALSE的工具: {', '.join(false_tools)}\n")
        
        # 需要人工检查的程序
        f.write("\n" + "=" * 80 + "\n")
        f.write("【需要人工检查的程序】\n")
        f.write("=" * 80 + "\n\n")
        
        # 所有工具都为TRUE的
        f.write("\n[1] 所有工具都检测为TRUE ({} 个):\n".format(len(all_true)))
        f.write("-" * 40 + "\n")
        for category in ["Idv-races", "pthread", "racebench2.1", "rw_benchmark"]:
            if category in by_category and by_category[category]['true']:
                f.write(f"\n{category} ({len(by_category[category]['true'])} 个):\n")
                for file_key, _ in sorted(by_category[category]['true']):
                    f.write(f"  {file_key}\n")
        
        # TRUE和UNKNOWN混合的
        f.write("\n[2] TRUE和UNKNOWN混合 ({} 个):\n".format(len(mixed_true_unknown)))
        f.write("-" * 40 + "\n")
        for category in ["Idv-races", "pthread", "racebench2.1", "rw_benchmark"]:
            if category in by_category and by_category[category]['mixed']:
                f.write(f"\n{category} ({len(by_category[category]['mixed'])} 个):\n")
                for file_key, results in sorted(by_category[category]['mixed']):
                    true_tools = [t for t, r in results.items() if r == "TRUE"]
                    f.write(f"  {file_key}\n")
                    f.write(f"    TRUE: {', '.join(true_tools)}\n")
        
        # 详细结果表（用于参考）
        f.write("\n" + "=" * 80 + "\n")
        f.write("【详细结果表】\n")
        f.write("=" * 80 + "\n\n")
        
        # 创建一个简化的表格
        f.write("说明: C=CBMC, P=CPAchecker, U=UAutomizer, S=UNI-CSeq, CC=CBMC+CPA, CA=CBMC+UA, Seq=Sequential\n")
        f.write("结果: T=TRUE, F=FALSE, U=UNKNOWN, -=NOT_FOUND\n\n")
        
        f.write(f"{'File':<50} {'C':<3} {'P':<3} {'U':<3} {'S':<3} {'CC':<3} {'CA':<3} {'Seq':<3} {'判定':<10}\n")
        f.write("-" * 90 + "\n")
        
        tool_abbr = {
            "CBMC": "C",
            "CPAchecker": "P",
            "UAutomizer": "U",
            "UNI-CSeq": "S",
            "CBMC+CPAchecker": "CC",
            "CBMC+UAutomizer": "CA",
            "Sequential": "Seq"
        }
        
        for file_key in sorted(all_files):
            short_file = file_key.split('/')[-1] if '/' in file_key else file_key
            if len(short_file) > 45:
                short_file = short_file[:42] + "..."
            
            row = f"{short_file:<50}"
            
            for tool_name in ["CBMC", "CPAchecker", "UAutomizer", "UNI-CSeq", "CBMC+CPAchecker", "CBMC+UAutomizer", "Sequential"]:
                if file_key in all_results[tool_name]:
                    res = all_results[tool_name][file_key]
                    if res == "TRUE":
                        row += " T  "
                    elif res == "FALSE":
                        row += " F  "
                    elif res in ["UNKNOWN", "TIMEOUT", "ERROR"]:
                        row += " U  "
                    else:
                        row += " ?  "
                else:
                    row += " -  "
            
            # 判定
            if file_key in definitely_false:
                row += " FALSE(确定)"
            elif file_key in all_true:
                row += " TRUE(待查)"
            elif file_key in mixed_true_unknown:
                row += " 混合(待查)"
            else:
                row += " 未知"
            
            f.write(row + "\n")
    
    print(f"\n[SUCCESS] 报告已生成: {report_file}")
    
    # 生成FALSE程序的简单列表（便于复制粘贴）
    false_list_file = "definitely_false_programs.txt"
    with open(false_list_file, "w", encoding="utf-8") as f:
        f.write("# 确定为FALSE的程序列表\n")
        f.write(f"# 共 {len(definitely_false)} 个程序\n")
        f.write("# 可以在人工检查时跳过这些程序\n\n")
        for file_key in sorted(definitely_false):
            f.write(f"{file_key}\n")
    
    print(f"[SUCCESS] FALSE程序列表已生成: {false_list_file}")
    
    # 打印摘要到控制台
    print("\n" + "=" * 60)
    print("分析摘要:")
    print(f"  总程序数: {len(all_files)}")
    print(f"  确定为FALSE: {len(definitely_false)} 个 (可跳过人工检查)")
    print(f"  所有工具都为TRUE: {len(all_true)} 个 (需人工确认)")
    print(f"  TRUE和UNKNOWN混合: {len(mixed_true_unknown)} 个 (需人工确认)")
    print(f"  所有工具都为UNKNOWN: {len(all_unknown)} 个")
    print("=" * 60)

if __name__ == "__main__":
    main()