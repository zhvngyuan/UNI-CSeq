#!/usr/bin/env python3
# Date: 2025-09-08
# Description: 批量拆分ComExp_Split下全部C文件，每个assert一份，适配run_ComExp.sh的用例结构

import os
import re
import copy

ROOT = '/home/dell/zyworkspace/unichecker/Experiments/Com_test_cbmc_unwind/ComExp_Split'
GROUPS = ['Idv-races', 'pthread', 'racebench2.1', 'rw_benchmark']

def is_assert_uncommented(lines, idx):
    """判断第idx行assert是否被注释（支持//和/*...*/）"""
    line = lines[idx]
    # 单行注释
    if re.match(r'^\s*//', line):
        return False
    # 行内有//，assert在//后也算注释
    before = line.split('//')[0]
    if 'assert' not in before:
        return False
    # 检查行上方是否在块注释
    in_block = False
    count = 0
    for i in range(idx, -1, -1):
        if '*/' in lines[i]:
            count += lines[i].count('*/')
        if '/*' in lines[i]:
            count -= lines[i].count('/*')
    if count > 0:
        return False
    return True

def find_uncommented_asserts(lines):
    """返回未被注释的assert语句行号区间列表 [(start, end), ...]"""
    pattern = re.compile(r'assert\s*\(')
    asserts = []
    i = 0
    while i < len(lines):
        if pattern.search(lines[i]) and is_assert_uncommented(lines, i):
            start = i
            # 括号配对，支持多行assert
            content = lines[i]
            left = content.count('(')
            right = content.count(')')
            end = i
            while left > right and end + 1 < len(lines):
                end += 1
                l = lines[end]
                if not is_assert_uncommented(lines, end):
                    break
                left += l.count('(')
                right += l.count(')')
            asserts.append((start, end))
            i = end + 1
        else:
            i += 1
    return asserts

def split_one_cfile(full_path):
    """把一个C文件按assert拆成多份，每份只保留一个assert，命名为xxx_assertN.c"""
    with open(full_path, 'r') as f:
        lines = f.readlines()
    asserts = find_uncommented_asserts(lines)
    if not asserts:
        return 0
    basepath, ext = os.path.splitext(full_path)
    basefile = os.path.basename(basepath)
    dirpath = os.path.dirname(full_path)
    for idx, (a_start, a_end) in enumerate(asserts):
        new_lines = copy.deepcopy(lines)
        for j, (b_start, b_end) in enumerate(asserts):
            if j != idx:
                for k in range(b_start, b_end+1):
                    if not new_lines[k].lstrip().startswith('//'):
                        new_lines[k] = '// ' + new_lines[k]
        new_name = f"{basefile}_assert{idx+1}{ext}"
        out_path = os.path.join(dirpath, new_name)
        with open(out_path, 'w') as fout:
            fout.writelines(new_lines)
    return len(asserts)

def batch_split():
    total_files = 0
    total_new = 0
    for group in GROUPS:
        group_dir = os.path.join(ROOT, group)
        if not os.path.isdir(group_dir):
            print(f"Warning: {group_dir} not found, skip.")
            continue
        for case in sorted(os.listdir(group_dir)):
            case_path = os.path.join(group_dir, case)
            if not os.path.isdir(case_path):
                continue
            # 检查所有c文件
            for file in os.listdir(case_path):
                if file.endswith('.c'):
                    full_path = os.path.join(case_path, file)
                    n = split_one_cfile(full_path)
                    total_files += 1
                    total_new += n
                    print(f"{full_path}: 拆分出 {n} 个assert")
    print(f"\n批量处理完毕，共处理 {total_files} 个C文件，生成 {total_new} 个单断言程序。")

if __name__ == "__main__":
    batch_split()