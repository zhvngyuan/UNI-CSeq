#!/usr/bin/env python3
"""
update_ground_truth.py
用于更新ground truth的交互式工具
"""

import json
import os
from datetime import datetime
import sys

class GroundTruthManager:
    def __init__(self, filename="ground_truth.json"):
        self.filename = filename
        self.data = self.load_ground_truth()
    
    def load_ground_truth(self):
        """加载现有的ground truth数据"""
        if os.path.exists(self.filename):
            with open(self.filename, "r") as f:
                return json.load(f)
        else:
            print(f"Warning: {self.filename} not found. Creating new one.")
            return {
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
    
    def save_ground_truth(self):
        """保存ground truth数据"""
        self.data["metadata"]["last_updated"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.data["metadata"]["confirmed"] = len(self.data["programs"])
        
        # 更新分类
        self.data["categories"]["confirmed_false"] = []
        self.data["categories"]["confirmed_true"] = []
        for prog, info in self.data["programs"].items():
            if info["ground_truth"] == "FALSE":
                self.data["categories"]["confirmed_false"].append(prog)
            elif info["ground_truth"] == "TRUE":
                self.data["categories"]["confirmed_true"].append(prog)
        
        with open(self.filename, "w") as f:
            json.dump(self.data, f, indent=2, ensure_ascii=False)
        print(f"Saved to {self.filename}")
    
    def add_program(self, program_path, ground_truth, confidence="HIGH", notes=""):
        """添加或更新一个程序的ground truth"""
        if ground_truth not in ["TRUE", "FALSE"]:
            print(f"Error: ground_truth must be TRUE or FALSE, got {ground_truth}")
            return False
        
        self.data["programs"][program_path] = {
            "ground_truth": ground_truth,
            "confidence": confidence,
            "source": "manual_verification",
            "confirmed_date": datetime.now().strftime("%Y-%m-%d"),
            "notes": notes
        }
        return True
    
    def batch_add_from_file(self, filename):
        """从文件批量添加ground truth
        文件格式: 每行一个 "program_path,TRUE/FALSE,notes(可选)"
        """
        if not os.path.exists(filename):
            print(f"Error: File {filename} not found")
            return
        
        added = 0
        with open(filename, "r") as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                if not line or line.startswith("#"):
                    continue
                
                parts = line.split(",")
                if len(parts) < 2:
                    print(f"Line {line_num}: Invalid format, skipping")
                    continue
                
                prog_path = parts[0].strip()
                gt = parts[1].strip().upper()
                notes = parts[2].strip() if len(parts) > 2 else ""
                
                if self.add_program(prog_path, gt, notes=notes):
                    added += 1
                    print(f"Added: {prog_path} -> {gt}")
        
        if added > 0:
            self.save_ground_truth()
            print(f"\nTotal added: {added} programs")
    
    def show_unconfirmed(self):
        """显示待确认的程序列表"""
        # 这里需要先获取所有程序列表
        # 简化起见，我们从已有的报告中提取
        all_programs = set()
        
        # 读取assertion_analysis_report.txt获取所有程序
        if os.path.exists("assertion_analysis_report.txt"):
            with open("assertion_analysis_report.txt", "r") as f:
                for line in f:
                    line = line.strip()
                    # 寻找文件路径模式
                    if "/" in line and line.endswith(".c"):
                        # 提取文件路径
                        if "  " in line:
                            prog = line.split()[0]
                            all_programs.add(prog)
        
        confirmed = set(self.data["programs"].keys())
        unconfirmed = all_programs - confirmed
        
        print(f"\nUnconfirmed programs ({len(unconfirmed)}):")
        print("-" * 60)
        for prog in sorted(unconfirmed):
            print(prog)
        
        return list(unconfirmed)
    
    def interactive_mode(self):
        """交互式添加ground truth"""
        unconfirmed = self.show_unconfirmed()
        
        if not unconfirmed:
            print("\nAll programs have been confirmed!")
            return
        
        print("\n" + "="*60)
        print("Interactive Ground Truth Confirmation")
        print("Enter 'T' for TRUE, 'F' for FALSE, 'S' to skip, 'Q' to quit")
        print("="*60)
        
        for prog in unconfirmed:
            print(f"\nProgram: {prog}")
            while True:
                choice = input("Ground truth (T/F/S/Q): ").upper()
                if choice == 'Q':
                    self.save_ground_truth()
                    print("Saved and quit.")
                    return
                elif choice == 'S':
                    print("Skipped.")
                    break
                elif choice in ['T', 'F']:
                    gt = "TRUE" if choice == 'T' else "FALSE"
                    notes = input("Notes (optional): ").strip()
                    self.add_program(prog, gt, notes=notes)
                    print(f"Recorded: {prog} -> {gt}")
                    break
                else:
                    print("Invalid input. Please enter T, F, S, or Q.")
        
        self.save_ground_truth()
        print("\nAll unconfirmed programs processed!")

def main():
    if len(sys.argv) < 2:
        print("Usage:")
        print("  python update_ground_truth.py interactive    # Interactive mode")
        print("  python update_ground_truth.py batch <file>   # Batch mode from file")
        print("  python update_ground_truth.py add <prog> <T/F> [notes]  # Add single")
        print("  python update_ground_truth.py show           # Show unconfirmed")
        return
    
    manager = GroundTruthManager()
    command = sys.argv[1]
    
    if command == "interactive":
        manager.interactive_mode()
    elif command == "batch" and len(sys.argv) > 2:
        manager.batch_add_from_file(sys.argv[2])
    elif command == "add" and len(sys.argv) > 3:
        prog = sys.argv[2]
        gt = sys.argv[3].upper()
        notes = " ".join(sys.argv[4:]) if len(sys.argv) > 4 else ""
        if manager.add_program(prog, gt, notes=notes):
            manager.save_ground_truth()
            print(f"Added: {prog} -> {gt}")
    elif command == "show":
        manager.show_unconfirmed()
    else:
        print("Invalid command or missing arguments")

if __name__ == "__main__":
    main()