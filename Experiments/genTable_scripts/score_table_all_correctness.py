#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
使用: python3 score_table_all_correctness.py

功能:
1. 统计 cbmc / cpachecker / cbmc-cpachecker 在
   - 原 ComExp_Split 实验
   - 新增 goblint-regression 实验
   上的验证结果
2. 使用 ground truth 统计:
   - Correct verdicts
   - Incorrect verdicts
   - Unknown
   - Timeout
   - Total time
3. 输出 LaTeX 表格与 CSV 明细

注意:
- 若某文件没有 ground truth，则不能计入 correct/incorrect，只能记为 unlabelled
- 日志中标为 UNKNOWN/ERROR，但用时达到或超过实验 timelimit 的案例计入 Timeout，不计入 Unknown
"""

import os
import re
import csv
from collections import defaultdict

# =========================
# 路径配置
# =========================
CUR_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(CUR_DIR, "..", ".."))

base = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split")
base_cc = os.path.join(PROJECT_ROOT, "Experiments", "ComExp_Split_unicseq_CC")

# =========================
# 日志路径
# 原实验 + goblint-regression 新实验
# =========================
log_file_map = {
    "cbmc": [
        os.path.join(base, "results_cbmc.log"),
        os.path.join(base, "results_goblint-regression_cbmc.log"),
    ],
    "cpachecker": [
        os.path.join(base, "results_cpachecker.log"),
        os.path.join(base, "results_goblint-regression_cpachecker.log"),
    ],
    "cbmc-cpachecker": [
        os.path.join(base_cc, "results_unicseq_cbmc-cpachecker.log"),
        os.path.join(base_cc, "results_unicseq_goblint-regression_cbmc-cpachecker.log"),
    ],
}

verifier_names = [
    "cbmc",
    "cpachecker",
    "cbmc-cpachecker",
]

POSITIVE = {"TRUE", "true"}
NEGATIVE = {"FALSE", "false"}
UNKNOWN_SET = {"UNKNOWN", "unknown", "ERROR", "error"}
TIMEOUT_SET = {"TIMEOUT", "timeout"}
# 与 run_scripts/run_third_Experiment.sh 默认 timelimit 一致
TIMELIMIT_SEC = 850.0


def reclassify_unknown_timeout(result, used_time):
    """UNKNOWN/ERROR 且用时达到 timelimit 时记为 TIMEOUT。"""
    r = (result or "").strip().upper()
    try:
        t = float(used_time)
    except (TypeError, ValueError):
        t = 0.0
    if r in UNKNOWN_SET and t >= TIMELIMIT_SEC:
        return "TIMEOUT"
    return r if r else "UNKNOWN"


REAL_GROUND_TRUTH = {
    "Idv-races/svp_simple_300_001/svp_simple_300_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_300_001/svp_simple_300_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_300_001/svp_simple_300_001_assert4.c": "FALSE",
    "Idv-races/svp_simple_301_001/svp_simple_301_001_assert1.c": "FALSE",
    "Idv-races/svp_simple_301_001/svp_simple_301_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_301_001/svp_simple_301_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_301_001/svp_simple_301_001_assert4.c": "FALSE",
    "Idv-races/svp_simple_302_001/svp_simple_302_001_assert1.c": "FALSE",
    "Idv-races/svp_simple_302_001/svp_simple_302_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_302_001/svp_simple_302_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_302_001/svp_simple_302_001_assert4.c": "FALSE",
    "Idv-races/svp_simple_303_001/svp_simple_303_001_assert1.c": "FALSE",
    "Idv-races/svp_simple_303_001/svp_simple_303_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_303_001/svp_simple_303_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_303_001/svp_simple_303_001_assert4.c": "FALSE",
    "Idv-races/svp_simple_304_001/svp_simple_304_001_assert1.c": "FALSE",
    "Idv-races/svp_simple_304_001/svp_simple_304_001_assert2.c": "FALSE",
    "Idv-races/svp_simple_304_001/svp_simple_304_001_assert3.c": "FALSE",
    "Idv-races/svp_simple_304_001/svp_simple_304_001_assert4.c": "FALSE",
    "pthread/svp_simple_304_001/svp_simple_304_001_assert1.c": "FALSE",
    "pthread/svp_simple_324_001/svp_simple_324_001_assert1.c": "FALSE",
    "pthread/svp_simple_325_001/svp_simple_325_001_assert1.c": "FALSE",
    "pthread/svp_simple_326_001/svp_simple_326_001_assert1.c": "TRUE",
    "racebench2.1/svp_simple_001/svp_simple_001_assert2.c": "FALSE",
    "racebench2.1/svp_simple_002/svp_simple_002_assert1.c": "FALSE",
    "racebench2.1/svp_simple_003/svp_simple_003_assert1.c": "TRUE",
    "racebench2.1/svp_simple_004/svp_simple_004_assert1.c": "FALSE",
    "racebench2.1/svp_simple_005/svp_simple_005_assert1.c": "FALSE",
    "racebench2.1/svp_simple_006/svp_simple_006_assert1.c": "FALSE",
    "racebench2.1/svp_simple_007/svp_simple_007_assert1.c": "FALSE",
    "racebench2.1/svp_simple_013/svp_simple_013_assert1.c": "FALSE",
    "racebench2.1/svp_simple_015/svp_simple_015_assert1.c": "FALSE",
    "racebench2.1/svp_simple_015/svp_simple_015_assert2.c": "FALSE",
    "racebench2.1/svp_simple_016/svp_simple_016_assert1.c": "FALSE",
    "racebench2.1/svp_simple_017/svp_simple_017_assert1.c": "FALSE",
    "racebench2.1/svp_simple_019/svp_simple_019_assert1.c": "FALSE",
    "racebench2.1/svp_simple_020/svp_simple_020_assert1.c": "FALSE",
    "racebench2.1/svp_simple_020/svp_simple_020_assert2.c": "FALSE",
    "racebench2.1/svp_simple_021/svp_simple_021_assert1.c": "FALSE",
    "racebench2.1/svp_simple_022/svp_simple_022_assert1.c": "FALSE",
    "racebench2.1/svp_simple_026/svp_simple_026_assert1.c": "FALSE",
    "racebench2.1/svp_simple_026/svp_simple_026_assert2.c": "FALSE",
    "racebench2.1/svp_simple_027/svp_simple_027_assert1.c": "FALSE",
    "racebench2.1/svp_simple_027/svp_simple_027_assert3.c": "FALSE",
    "racebench2.1/svp_simple_028/svp_simple_028_assert1.c": "TRUE",
    "rw_benchmark/blink1/main_n_assert1.c": "FALSE",
    "rw_benchmark/blink1/main_n_assert2.c": "FALSE",
    "rw_benchmark/blink2/main_n_assert1.c": "FALSE",
    "rw_benchmark/blink2/main_n_assert2.c": "FALSE",
    "rw_benchmark/blink3/main_n_assert1.c": "FALSE",
    "rw_benchmark/blink3/main_n_assert2.c": "FALSE",
    "rw_benchmark/blink3/main_n_assert3.c": "FALSE",
    "rw_benchmark/brake1/main_n_assert5.c": "FALSE",
    "rw_benchmark/brake2/main_n_assert1.c": "FALSE",
    "rw_benchmark/brake2/main_n_assert3.c": "FALSE",
    "rw_benchmark/brake2/main_n_assert4.c": "FALSE",
    "rw_benchmark/brake3/main_n_assert1.c": "FALSE",
    "rw_benchmark/brake3/main_n_assert3.c": "FALSE",
    "rw_benchmark/brake3/main_n_assert4.c": "FALSE",
    "rw_benchmark/brake3/main_n_assert5.c": "FALSE",
    "rw_benchmark/wdt_pci_1/main_n_assert1.c": "TRUE",
    "rw_benchmark/wdt_pci_1/main_n_assert2.c": "TRUE",
    "rw_benchmark/wdt_pci_2/main_n_assert1.c": "TRUE",
    "rw_benchmark/wdt_pci_2/main_n_assert2.c": "TRUE",
    "rw_benchmark/wdt_pci_2/main_n_assert3.c": "FALSE",
    "rw_benchmark/wdt_pci_3/main_n_assert1.c": "TRUE",
    "rw_benchmark/wdt_pci_3/main_n_assert2.c": "FALSE",
    "rw_benchmark/wdt_pci_3/main_n_assert3.c": "FALSE",
    "rw_benchmark/wdt_pci_3/main_n_assert4.c": "FALSE",
    "rw_benchmark/i8xx_tco_1/main_n_assert1.c": "TRUE",
    "rw_benchmark/i8xx_tco_1/main_n_assert2.c": "TRUE",
    "rw_benchmark/i8xx_tco_2/main_n_assert1.c": "FALSE",
    "rw_benchmark/i8xx_tco_2/main_n_assert2.c": "TRUE",
    "rw_benchmark/i8xx_tco_3/main_n_assert1.c": "TRUE",
    "rw_benchmark/i8xx_tco_3/main_n_assert2.c": "TRUE",
    "rw_benchmark/i8xx_tco_3/main_n_assert3.c": "TRUE",
    "Idv-races/svp_simple_300_001/svp_simple_300_001_assert1.c": "TRUE",
    "pthread/svp_simple_327_001/svp_simple_327_001_assert1.c": "FALSE",
    "pthread/svp_simple_328_001/svp_simple_328_001_assert1.c": "TRUE",
    "pthread/svp_simple_329_001/svp_simple_329_001_assert1.c": "TRUE",
    "pthread/svp_simple_330_001/svp_simple_330_001_assert1.c": "TRUE",
    "pthread/svp_simple_331_001/svp_simple_331_001_assert1.c": "TRUE",
    "pthread/svp_simple_332_001/svp_simple_332_001_assert1.c": "TRUE",
    "racebench2.1/svp_simple_001/svp_simple_001_assert1.c": "TRUE",
    "racebench2.1/svp_simple_002/svp_simple_002_assert2.c": "TRUE",
    "racebench2.1/svp_simple_006/svp_simple_006_assert2.c": "FALSE",
    "racebench2.1/svp_simple_006/svp_simple_006_assert3.c": "TRUE",
    "racebench2.1/svp_simple_006/svp_simple_006_assert4.c": "TRUE",
    "racebench2.1/svp_simple_008/svp_simple_008_assert1.c": "TRUE",
    "racebench2.1/svp_simple_010/svp_simple_010_assert1.c": "TRUE",
    "racebench2.1/svp_simple_010/svp_simple_010_assert2.c": "TRUE",
    "racebench2.1/svp_simple_018/svp_simple_018_assert1.c": "TRUE",
    "racebench2.1/svp_simple_027/svp_simple_027_assert2.c": "TRUE",
    "racebench2.1/svp_simple_028/svp_simple_028_assert2.c": "FALSE",
    "racebench2.1/svp_simple_028/svp_simple_028_assert3.c": "FALSE",
    "racebench2.1/svp_simple_029/svp_simple_029_assert1.c": "TRUE",
    "racebench2.1/svp_simple_030/svp_simple_030_assert1.c": "FALSE",
    "racebench2.1/svp_simple_030/svp_simple_030_assert2.c": "FALSE",
    "rw_benchmark/blink1/main_n_assert3.c": "TRUE",
    "rw_benchmark/blink2/main_n_assert3.c": "TRUE",
    "rw_benchmark/blink3/main_n_assert4.c": "TRUE",
    "rw_benchmark/brake1/main_n_assert1.c": "TRUE",
    "rw_benchmark/brake1/main_n_assert2.c": "TRUE",
    "rw_benchmark/brake1/main_n_assert3.c": "TRUE",
    "rw_benchmark/brake1/main_n_assert4.c": "TRUE",
    "rw_benchmark/brake2/main_n_assert2.c": "TRUE",
    "rw_benchmark/brake3/main_n_assert2.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_1/main_n_assert1.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_1/main_n_assert2.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_1/main_n_assert3.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_1/main_n_assert4.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_1/main_n_assert5.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_1/main_n_assert6.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert1.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert2.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert3.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert4.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert5.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert6.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert7.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert8.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert9.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_2/main_n_assert10.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert1.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert2.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert3.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert4.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert5.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert6.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert7.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert8.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert9.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert10.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert11.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert12.c": "FALSE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert13.c": "TRUE",
    "rw_benchmark/i2c_pca_isa_3/main_n_assert14.c": "TRUE",
    "rw_benchmark/logger1/main_n_assert1.c": "TRUE",
    "rw_benchmark/logger2/main_n_assert1.c": "TRUE",
    "rw_benchmark/logger2/main_n_assert2.c": "TRUE",
    "rw_benchmark/logger2/main_n_assert3.c": "TRUE",
    "rw_benchmark/logger3/main_n_assert1.c": "TRUE",
    "rw_benchmark/logger3/main_n_assert2.c": "TRUE",
    "rw_benchmark/logger3/main_n_assert3.c": "TRUE",
    "rw_benchmark/logger3/main_n_assert4.c": "TRUE",
    "racebench2.1/svp_simple_004/svp_simple_004_assert2.c": "TRUE",
    "racebench2.1/svp_simple_009/svp_simple_009_assert1.c": "TRUE",
    "racebench2.1/svp_simple_009/svp_simple_009_assert2.c": "TRUE",
    "racebench2.1/svp_simple_013/svp_simple_013_assert2.c": "FALSE",
    "racebench2.1/svp_simple_013/svp_simple_013_assert3.c": "TRUE",
    "racebench2.1/svp_simple_014/svp_simple_014_assert1.c": "FALSE",
    "racebench2.1/svp_simple_014/svp_simple_014_assert2.c": "FALSE",
    "racebench2.1/svp_simple_018/svp_simple_018_assert2.c": "FALSE",
    "racebench2.1/svp_simple_011/svp_simple_011_assert1.c": "TRUE",
    "racebench2.1/svp_simple_011/svp_simple_011_assert2.c": "TRUE",
    "racebench2.1/svp_simple_012/svp_simple_012_assert1.c": "TRUE",
    "racebench2.1/svp_simple_023/svp_simple_023_assert1.c": "FALSE",
    "racebench2.1/svp_simple_024/svp_simple_024_assert1.c": "FALSE",
    "racebench2.1/svp_simple_025/svp_simple_025_assert1.c": "FALSE",
    "racebench2.1/svp_simple_031/svp_simple_031_assert1.c": "FALSE",
    "racebench2.1/svp_simple_031/svp_simple_031_assert2.c": "FALSE",
    "goblint-regression/svp_simple_500_001/svp_simple_500_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_504_001/svp_simple_504_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_505_001/svp_simple_505_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_506_001/svp_simple_506_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_506_001/svp_simple_506_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_507_001/svp_simple_507_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_509_001/svp_simple_509_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_510_001/svp_simple_510_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_511_001/svp_simple_511_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_512_001/svp_simple_512_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_513_001/svp_simple_513_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_518_001/svp_simple_518_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_518_001/svp_simple_518_001_assert2.c": "FALSE",
    "goblint-regression/svp_simple_519_001/svp_simple_519_001_assert2.c": "FALSE",
    "goblint-regression/svp_simple_519_001/svp_simple_519_001_assert3.c": "FALSE",
    "goblint-regression/svp_simple_520_001/svp_simple_520_001_assert2.c": "FALSE",
    "goblint-regression/svp_simple_521_001/svp_simple_521_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_522_001/svp_simple_522_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_524_001/svp_simple_524_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_529_001/svp_simple_529_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_536_001/svp_simple_536_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_537_001/svp_simple_537_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_538_001/svp_simple_538_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_542_001/svp_simple_542_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_542_001/svp_simple_542_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_545_001/svp_simple_545_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_545_001/svp_simple_545_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_547_001/svp_simple_547_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_548_001/svp_simple_548_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_560_001/svp_simple_560_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_597_001/svp_simple_597_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_598_001/svp_simple_598_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_600_001/svp_simple_600_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_600_001/svp_simple_600_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_600_001/svp_simple_600_001_assert3.c": "TRUE",
    "goblint-regression/svp_simple_600_001/svp_simple_600_001_assert4.c": "TRUE",
    "goblint-regression/svp_simple_601_001/svp_simple_601_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_601_001/svp_simple_601_001_assert2.c": "FALSE",
    "goblint-regression/svp_simple_601_001/svp_simple_601_001_assert3.c": "FALSE",
    "goblint-regression/svp_simple_602_001/svp_simple_602_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_602_001/svp_simple_602_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_603_001/svp_simple_603_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_604_001/svp_simple_604_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_605_001/svp_simple_605_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_606_001/svp_simple_606_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_607_001/svp_simple_607_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_608_001/svp_simple_608_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_608_001/svp_simple_608_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_609_001/svp_simple_609_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_610_001/svp_simple_610_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_611_001/svp_simple_611_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_612_001/svp_simple_612_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_613_001/svp_simple_613_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_613_001/svp_simple_613_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_614_001/svp_simple_614_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_614_001/svp_simple_614_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_616_001/svp_simple_616_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_616_001/svp_simple_616_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_617_001/svp_simple_617_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_617_001/svp_simple_617_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_617_001/svp_simple_617_001_assert3.c": "TRUE",
    "goblint-regression/svp_simple_618_001/svp_simple_618_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_619_001/svp_simple_619_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_620_001/svp_simple_620_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_620_001/svp_simple_620_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_621_001/svp_simple_621_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_622_001/svp_simple_622_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_623_001/svp_simple_623_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_624_001/svp_simple_624_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_625_001/svp_simple_625_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_626_001/svp_simple_626_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_627_001/svp_simple_627_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_628_001/svp_simple_628_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_631_001/svp_simple_631_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_632_001/svp_simple_632_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_633_001/svp_simple_633_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_634_001/svp_simple_634_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_634_001/svp_simple_634_001_assert2.c": "FALSE",
    "goblint-regression/svp_simple_635_001/svp_simple_635_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_636_001/svp_simple_636_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_637_001/svp_simple_637_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_639_001/svp_simple_639_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_640_001/svp_simple_640_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_641_001/svp_simple_641_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_643_001/svp_simple_643_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_643_001/svp_simple_643_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_643_001/svp_simple_643_001_assert4.c": "FALSE",
    "goblint-regression/svp_simple_644_001/svp_simple_644_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_668_001/svp_simple_668_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_668_001/svp_simple_668_001_assert2.c": "TRUE",
    "goblint-regression/svp_simple_696_001/svp_simple_696_001_assert1.c": "TRUE",
    "goblint-regression/svp_simple_697_001/svp_simple_697_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_698_001/svp_simple_698_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_699_001/svp_simple_699_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_700_001/svp_simple_700_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_700_001/svp_simple_700_001_assert2.c": "FALSE",
    "goblint-regression/svp_simple_700_001/svp_simple_700_001_assert3.c": "FALSE",
    "goblint-regression/svp_simple_700_001/svp_simple_700_001_assert4.c": "FALSE",
    "goblint-regression/svp_simple_701_001/svp_simple_701_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_701_001/svp_simple_701_001_assert2.c": "FALSE",
    "goblint-regression/svp_simple_701_001/svp_simple_701_001_assert3.c": "FALSE",
    "goblint-regression/svp_simple_702_001/svp_simple_702_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_702_001/svp_simple_702_001_assert2.c": "FALSE",
    "goblint-regression/svp_simple_702_001/svp_simple_702_001_assert3.c": "TRUE",
    "goblint-regression/svp_simple_703_001/svp_simple_703_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_508_001/svp_simple_508_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_519_001/svp_simple_519_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_520_001/svp_simple_520_001_assert1.c": "FALSE",
    "goblint-regression/svp_simple_643_001/svp_simple_643_001_assert3.c": "FALSE",
    "goblint-regression/svp_simple_696_001/svp_simple_696_001_assert2.c": "FALSE",
}

# =========================
# 路径标准化
# =========================
def normalize_filename(filepath):
    filepath = filepath.replace("\\", "/")
    parts = filepath.split("/")

    keys = ["Idv-races", "pthread", "racebench2.1", "rw_benchmark", "goblint-regression"]
    for i, part in enumerate(parts):
        if part in keys:
            return "/".join(parts[i:])

    if len(parts) >= 3:
        return "/".join(parts[-3:])
    elif len(parts) >= 2:
        return "/".join(parts[-2:])
    else:
        return os.path.basename(filepath)


# =========================
# Ground truth 分组统计
# =========================
PACKAGE_KEYS = [
    "goblint-regression",
    "Idv-races",
    "pthread",
    "racebench2.1",
    "rw_benchmark",
]

def get_package_name(filepath):
    filepath = filepath.replace("\\", "/")
    for key in PACKAGE_KEYS:
        if filepath.startswith(key + "/") or filepath == key:
            return key
    return "OTHER"

def count_ground_truth_by_package():
    pkg_count = {pkg: 0 for pkg in PACKAGE_KEYS}
    pkg_count["OTHER"] = 0

    for f in REAL_GROUND_TRUTH:
        pkg = get_package_name(f)
        pkg_count[pkg] += 1

    return pkg_count
# =========================
# 日志解析
# =========================
def strip_ansi(s):
    return re.sub(r'\x1b\[[;0-9]+m', '', s)

def parse_unicseq_log(logfile, tool_name):
    """
    解析 unicseq 风格日志:
      UnicSeq Checking : xxx.c
      Final verification results: TRUE/FALSE/UNKNOWN
      Total running time: x
    """
    f2res = {}

    if not os.path.exists(logfile):
        print(f"[WARNING] File not found: {logfile}")
        return f2res

    with open(logfile, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()

    current_file = None
    true_cnt = false_cnt = unknown_cnt = timeout_cnt = 0
    total_time = 0.0

    for idx, line in enumerate(lines):
        text = strip_ansi(line)

        mfile = re.search(r'UnicSeq Checking(?:\s+\([^)]+\))?\s*:\s+([^\s=]+)', text)
        if mfile:
            current_file = normalize_filename(mfile.group(1).strip())
            continue

        mres = re.search(r'Final verification results:\s*([A-Z]+)', text)
        if mres and current_file:
            result = mres.group(1).strip().upper()
            used_time = 0.0

            for j in range(1, 10):
                if idx + j < len(lines):
                    tline = strip_ansi(lines[idx + j])
                    mtime = re.search(r'Total running time:\s*([0-9.]+)', tline)
                    if mtime:
                        used_time = float(mtime.group(1))
                        break

            result = reclassify_unknown_timeout(result, used_time)
            f2res[current_file] = (result, used_time)

            if result == "TRUE":
                true_cnt += 1
            elif result == "FALSE":
                false_cnt += 1
            elif result == "TIMEOUT":
                timeout_cnt += 1
            else:
                unknown_cnt += 1

            total_time += used_time
            current_file = None

    print(f"[DEBUG][{tool_name}] {logfile}: TRUE={true_cnt}, FALSE={false_cnt}, UNKNOWN={unknown_cnt}, TIMEOUT={timeout_cnt}, TotalTime={total_time:.1f}")
    return f2res

def parse_simple_log(logfile, tool_name):
    """
    解析简单格式日志:
      file, RESULT, time
    """
    f2res = {}

    if not os.path.exists(logfile):
        print(f"[WARNING] File not found: {logfile}")
        return f2res

    with open(logfile, "r", encoding="utf-8", errors="ignore") as f:
        lines = f.readlines()

    true_cnt = false_cnt = unknown_cnt = timeout_cnt = 0
    total_time = 0.0

    for line in lines:
        text = strip_ansi(line)
        m = re.search(r'([^,]+),\s*([A-Z]+|TIMEOUT|UNKNOWN|ERROR),\s*([-.\d]+)', text)
        if not m:
            continue

        fname = normalize_filename(m.group(1).strip())
        result = m.group(2).strip().upper()
        used_time = float(m.group(3))
        result = reclassify_unknown_timeout(result, used_time)

        f2res[fname] = (result, used_time)

        if result == "TRUE":
            true_cnt += 1
        elif result == "FALSE":
            false_cnt += 1
        elif result == "TIMEOUT":
            timeout_cnt += 1
        else:
            unknown_cnt += 1

        total_time += used_time

    print(f"[DEBUG][{tool_name}] {logfile}: TRUE={true_cnt}, FALSE={false_cnt}, UNKNOWN={unknown_cnt}, TIMEOUT={timeout_cnt}, TotalTime={total_time:.1f}")
    return f2res

def load_all_results():
    """
    返回:
      all_files: 全部文件集合
      fullmap[file][tool] = (result, time)
    """
    all_files = set()
    fullmap = defaultdict(dict)

    for tool in verifier_names:
        merged = {}
        for logfile in log_file_map[tool]:
            if tool in ["cbmc-cpachecker"]:
                part = parse_unicseq_log(logfile, tool)
            else:
                part = parse_simple_log(logfile, tool)
            merged.update(part)

        for f, res in merged.items():
            fullmap[f][tool] = res
            all_files.add(f)

    return all_files, fullmap

# =========================
# 正确性判断
# =========================
def classify_verdict(gt, result):
    """
    返回:
      correct_true / correct_false / incorrect_true / incorrect_false / unknown / timeout
    """
    r = result.upper()
    gt = gt.upper()

    if r in TIMEOUT_SET:
        return "timeout"
    if r in UNKNOWN_SET:
        return "unknown"
    if r in POSITIVE:
        return "correct_true" if gt in POSITIVE else "incorrect_true"
    if r in NEGATIVE:
        return "correct_false" if gt in NEGATIVE else "incorrect_false"
    return "unknown"

def init_stat():
    return {
        "Total files": 0,
        "Labelled files": 0,
        "Unlabelled files": 0,
        "Correct verdicts": 0,
        "Incorrect verdicts": 0,
        "Correct proof": 0,
        "Correct alarm": 0,
        "InCorrect proof": 0,
        "InCorrect alarm": 0,
        "Unknown": 0,
        "Timeout": 0,
        "Total time": 0.0,
    }


def build_paper_table(stats):
    """LaTeX for tab:Cooperation_Verification (no \\revise)."""
    def count_cells(key):
        return " & ".join(str(stats[tool][key]) for tool in verifier_names)

    cbmc_time = r"\text{(%.1f)}$^{1}$" % stats["cbmc"]["Total time"]
    cpa_time = "%.1f" % stats["cpachecker"]["Total time"]
    par_time = "%.1f" % stats["cbmc-cpachecker"]["Total time"]

    return "\n".join([
        r"\begin{table*}[ht]",
        r"\centering",
        r"\caption{Evaluation results for RQ3 on the complete benchmark set. For uniform measurement, each original program containing multiple assertions is transformed into multiple single-assertion instances. }",
        r"\label{tab:Cooperation_Verification}",
        r"\setlength{\tabcolsep}{12pt}",
        r"\resizebox{0.65\textwidth}{!}{",
        r"    \begin{threeparttable}",
        r"    \begin{tabular}{",
        r"        l *{3}{S[table-format=3.0]}}",
        r"        \toprule[1pt]",
        r"        \multicolumn{1}{c}{\multirow{2}{*}{Metric}} & \multicolumn{3}{c}{\multirow{1}{*}{Backend Configuration}} \\\cmidrule(lr){2-4}",
        r"        & \multicolumn{1}{c}{CBMC} & \multicolumn{1}{c}{CPAchecker} & \multicolumn{1}{c}{CBMC + CPAchecker (Parallel)} \\\midrule",
        r"        Correct verdicts & %s \\" % count_cells("Correct verdicts"),
        r"        \quad Safe & %s \\" % count_cells("Correct proof"),
        r"        \quad Unsafe & %s \\" % count_cells("Correct alarm"),
        r"        Incorrect verdicts & %s \\" % count_cells("Incorrect verdicts"),
        r"        \quad Safe & %s \\" % count_cells("InCorrect proof"),
        r"        \quad Unsafe & %s \\" % count_cells("InCorrect alarm"),
        r"        Unknown & %s \\" % count_cells("Unknown"),
        r"        Timeout & %s \\\midrule" % count_cells("Timeout"),
        r"        Total time (s) & %s & %s & %s \\" % (cbmc_time, cpa_time, par_time),
        r"        \bottomrule[1pt]",
        r"    \end{tabular}",
        r"    \begin{tablenotes}",
        r"\item[$^{1}$] { Although CBMC achieves the shortest total runtime, its safe verdicts are valid only under the selected unwinding bound.}",
        r"\end{tablenotes}",
        r"\end{threeparttable}",
        r"}",
        r"\end{table*}",
        "",
    ])


def main():
    all_files, fullmap = load_all_results()

    stats = {tool: init_stat() for tool in verifier_names}
    detail_rows = []

    # 新增：记录所有未标注 ground truth 的文件
    unlabeled_files = set()
    # 新增：记录与 ground truth 不一致的文件
    inconsistent_files = {tool: [] for tool in verifier_names}

    # 新增：记录 Unknown / Timeout 的文件
    unknown_files = {tool: [] for tool in verifier_names}
    timeout_files = {tool: [] for tool in verifier_names}

    for f in sorted(all_files):
        gt = REAL_GROUND_TRUTH.get(f, None)

        if gt is None:
            unlabeled_files.add(f)

        for tool in verifier_names:
            result, used_time = fullmap[f].get(tool, ("UNKNOWN", 0.0))
            stats[tool]["Total files"] += 1
            stats[tool]["Total time"] += used_time

            if gt is None:
                stats[tool]["Unlabelled files"] += 1
                if result.upper() in TIMEOUT_SET:
                    stats[tool]["Timeout"] += 1
                    timeout_files[tool].append((f, result, used_time))
                elif result.upper() in UNKNOWN_SET:
                    stats[tool]["Unknown"] += 1
                    unknown_files[tool].append((f, result, used_time))

                detail_rows.append({
                    "file": f,
                    "tool": tool,
                    "ground_truth": "UNLABELLED",
                    "result": result,
                    "time": used_time,
                    "classification": "unlabelled",
                })
                continue

            stats[tool]["Labelled files"] += 1
            cls = classify_verdict(gt, result)

            if cls == "correct_true":
                stats[tool]["Correct verdicts"] += 1
                stats[tool]["Correct proof"] += 1
            elif cls == "correct_false":
                stats[tool]["Correct verdicts"] += 1
                stats[tool]["Correct alarm"] += 1
            elif cls == "incorrect_true":
                stats[tool]["Incorrect verdicts"] += 1
                stats[tool]["InCorrect proof"] += 1
                inconsistent_files[tool].append((f, gt, result))
            elif cls == "incorrect_false":
                stats[tool]["Incorrect verdicts"] += 1
                stats[tool]["InCorrect alarm"] += 1
                inconsistent_files[tool].append((f, gt, result))
            elif cls == "timeout":
                stats[tool]["Timeout"] += 1
                timeout_files[tool].append((f, result, used_time))
            else:
                stats[tool]["Unknown"] += 1
                unknown_files[tool].append((f, result, used_time))

            detail_rows.append({
                "file": f,
                "tool": tool,
                "ground_truth": gt,
                "result": result,
                "time": used_time,
                "classification": cls,
            })

    # 输出摘要
    print("\n[SUMMARY]")
    for tool in verifier_names:
        s = stats[tool]
        print(
            f"{tool:18s} | "
            f"Labelled={s['Labelled files']:4d}, "
            f"Correct={s['Correct verdicts']:4d}, "
            f"Incorrect={s['Incorrect verdicts']:4d}, "
            f"Unknown={s['Unknown']:4d}, "
            f"Timeout={s['Timeout']:4d}, "
            f"Unlabelled={s['Unlabelled files']:4d}, "
            f"Time={s['Total time']:.1f}s"
        )

    paper_table = build_paper_table(stats)
    print("\n" + paper_table)

    # 新增：输出未标注文件列表
    if unlabeled_files:
        print("\n[UNLABELLED FILES]")
        for f in sorted(unlabeled_files):
            print(f)

    # 新增：输出 REAL_GROUND_TRUTH 中各数据包的键数量
    gt_pkg_count = count_ground_truth_by_package()
    print("\n[GROUND TRUTH COUNTS BY PACKAGE]")
    total_gt = 0
    for pkg in PACKAGE_KEYS:
        cnt = gt_pkg_count[pkg]
        total_gt += cnt
        print(f"{pkg:20s}: {cnt}")
    if gt_pkg_count["OTHER"] > 0:
        print(f"{'OTHER':20s}: {gt_pkg_count['OTHER']}")
        total_gt += gt_pkg_count["OTHER"]
    print(f"{'TOTAL':20s}: {total_gt}")

    # 新增：输出检测结果与 REAL_GROUND_TRUTH 不一致的文件
    has_inconsistent = any(inconsistent_files[tool] for tool in verifier_names)
    if has_inconsistent:
        print("\n[INCONSISTENT FILES AGAINST GROUND TRUTH]")
        for tool in verifier_names:
            if not inconsistent_files[tool]:
                continue
            print(f"\n[{tool}]")
            for f, gt, result in inconsistent_files[tool]:
                print(f"{f} | GT={gt} | RESULT={result}")
    # 新增：输出 Unknown 文件
    has_unknown = any(unknown_files[tool] for tool in verifier_names)
    if has_unknown:
        print("\n[UNKNOWN FILES]")
        for tool in verifier_names:
            if not unknown_files[tool]:
                continue
            print(f"\n[{tool}]")
            for f, result, used_time in unknown_files[tool]:
                print(f"{f} | RESULT={result} | TIME={used_time:.2f}")

    # 新增：输出 Timeout 文件
    has_timeout = any(timeout_files[tool] for tool in verifier_names)
    if has_timeout:
        print("\n[TIMEOUT FILES]")
        for tool in verifier_names:
            if not timeout_files[tool]:
                continue
            print(f"\n[{tool}]")
            for f, result, used_time in timeout_files[tool]:
                print(f"{f} | RESULT={result} | TIME={used_time:.2f}")

    # 写 LaTeX 文件
    latex_out = os.path.join(CUR_DIR, "compare_correctness_table.txt")
    with open(latex_out, "w", encoding="utf-8") as f:
        f.write(paper_table)

    # 写 CSV 明细
    csv_out = os.path.join(CUR_DIR, "compare_correctness_detail.csv")
    with open(csv_out, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["file", "tool", "ground_truth", "result", "time", "classification"]
        )
        writer.writeheader()
        writer.writerows(detail_rows)

    print(f"\n[INFO] LaTeX table saved to: {latex_out}")
    print(f"[INFO] Detail CSV saved to: {csv_out}")

if __name__ == "__main__":
    main()