# Reproducing the UNI-CSeq Experiments

This document is the full reproduction sequence for the paper experiments. All paths are relative to the repository root.

Do not modify the sequentialization implementation in `unichecker.py`, `unicseq.py`, `bin/`, or `modules/`. The steps below only invoke the existing batch and table scripts.

Reproduction order:

```
Environment
  -> Regression Test
  -> Experiment 1 (18 real-world interrupt programs)
  -> Experiment 2 (bug detection vs NIChecker; iCBMC on rw_benchmark)
  -> Experiment 3 (single backends + parallel portfolio)
  -> Experiment 3 CDF
  -> Interrupt-masking ablation (full racebench 2.1)
  -> LaTeX tables / figure
```

---

## 0. Environment

- `unichecker.py` (single-backend sequentialization + verification) requires **Python 2.7**. On a typical server: `conda activate py27`
- `unicseq.py` (portfolio) and the scripts under `Experiments/genTable_scripts/` require **Python 3**
- Portfolio scripts need `psutil`: `pip install psutil` (in the Python 3 environment that runs `unicseq.py`)
- Backends must be on `PATH`: `cbmc` and CPAchecker
- The RQ2 iCBMC run (Section 3.3) is Linux-only and uses the `./cbmc` binary inside each `Experiments/icbmc/<dir>/`, not the `cbmc` on `PATH`
- All batch scripts live in `run_scripts/`. Run them from the repository root, for example:

```bash
./run_scripts/runRW_vs_intAbs.sh 900 cbmc
```

Paper numbers use a **900-second** time limit unless noted. Some scripts default to 60 seconds; pass `900` (or `3600` if you want a longer Experiment 3 budget) explicitly.

**External tools (not part of this repository):**

| Variable | Used by | Meaning |
| --- | --- | --- |
| `NICHECKER` | Experiment 2 (`run_second_Experiment.sh`) | Absolute path to `nichecker.py`. Required for the `run_nic` stage. Invoke it from the directory that contains `nichecker.py` (that tree must include `Cseq/`). |
| `UL_CSEQ_CBMC_DIR` | Experiment 1 table (`gen_table.py`) | Directory of an external UL-CSeq CBMC run that contains `runExp.log`. Optional: if unset, the UL-CSeq column is left empty and the script prints a warning. |

```bash
export NICHECKER=/path/to/nichecker.py
export UL_CSEQ_CBMC_DIR=/path/to/ul-cseq/cbmc/results
```

---

## 1. Regression Test

Directory: `Experiments/Regression_Test/`

Four small C programs check ISR-local variables under re-dispatch, preemption/resume, and loop-local re-initialization. This step is not a paper table. The runner calls `unichecker.py` with CBMC and `RespCount=2`.

| Source file | What it checks |
| --- | --- |
| `local_init_reinvoke.c` | Initialized local is rebuilt on the next dispatch; CBMC must report `VERIFICATION SUCCESSFUL` |
| `local_uninit_reinvoke.c` | Uninitialized local is havoc'd on the next dispatch; CBMC must report `VERIFICATION FAILED` |
| `local_init_preempt_resume.c` | Local state is preserved across a higher-priority preemption; CBMC must report `VERIFICATION SUCCESSFUL` |
| `local_init_loop.c` | Loop-local variables are rebuilt each iteration; CBMC must report `VERIFICATION SUCCESSFUL` |

```bash
cd Experiments/Regression_Test
./run_local_regression_test.sh 60 8
```

- `timelimit` default: 60 seconds
- `unwind` default: 8 (the scheduler `while(1)` needs unwind > 1; `local_init_loop.c` needs unwind ≥ 5)
- Requires `python2` (conda env `py27`) and `cbmc` on `PATH`

Expected: `Summary: 4/4 passed, 0 failed`. The full transcript is written to `Experiments/Regression_Test/test_result.txt`. A FAIL exits with code 1; fix the regression before running the paper experiments.

---

## 2. Experiment 1: Safety assertions on 18 real-world interrupt programs

**Goal:** Evaluate UNI-CSeq on safety assertions against intAbs, NIChecker, and UL-CSeq.  
**Paper table:** `tab:compare_with_intAbs`

### 2.1 Dataset

A subset of the intAbs real-world suite (18 C programs: `logger1`–`logger3`, `blink1`–`blink3`, `brake1`–`brake3`, `i2c_pca_isa_1`–`3`, `i8xx_tco_1`–`3`, `wdt_pci_1`–`3`). Two copies keep backend artifacts from overwriting each other:

- CBMC: `Experiments/compare_with_intAbs_cbmc/` (`main_n.c` in each subdirectory)
- CPAchecker: `Experiments/compare_with_intAbs_cpachecker/`

### 2.2 Run UNI-CSeq

From the repository root:

```bash
conda activate py27
./run_scripts/runRW_vs_intAbs.sh 900 cbmc
./run_scripts/runRW_vs_intAbs.sh 900 cpachecker
```

- CBMC: `-u 2 --RespCount 2`
- CPAchecker: `--RespCount 2` (no unwind flag)
- Logs: `Experiments/compare_with_intAbs_cbmc/runExp.log` and `Experiments/compare_with_intAbs_cpachecker/runExp.log`

### 2.3 Comparison-tool data (not re-run by this repository)

| Tool | Source |
| --- | --- |
| intAbs | Hard-coded in `gen_table.py` (`table_data`) |
| NIChecker | `Experiments/compare_intAbs_ver_nichecker/runExp_nichecker.log` |
| UL-CSeq | External log directory given by `UL_CSEQ_CBMC_DIR` (must contain `runExp.log`) |

### 2.4 Generate the LaTeX table

```bash
cd Experiments/genTable_scripts
python3 gen_table.py
```

Output: `Experiments/genTable_scripts/gen_table.txt`

---

## 3. Experiment 2: Bug detection with CBMC (vs NIChecker)

**Goal:** Compare UNI-CSeq (CBMC) with NIChecker on five benchmark packages, and compare iCBMC / NIChecker / UNI-CSeq on the 18-program `rw_benchmark` suite.  
**Paper tables:** `tab:compare_with_NIChecker` (Section 3.2) and `tab:rw_package` (Section 3.3)

Use `run_scripts/run_second_Experiment.sh` for the five-package table. It covers five packages, uses the same per-package unwind as Experiment 3, and runs NIChecker with matching unwind except `racebench2.1` (NIChecker unwind 2). Only `racebench2.1` adds `--loopAbs` / `--LA`. `rw_benchmark` uses `Experiments/compare_with_intAbs_cbmc/` (`main_n.c`).

### 3.1 Dataset

| Package | Path | Source files |
| --- | --- | --- |
| Idv-races | `Experiments/svcomp2022/Idv-races/` | `<dir>/<dir>.c` |
| pthread | `Experiments/svcomp2022/pthread/` | same |
| goblint-regression | `Experiments/svcomp2022/goblint-regression/` | same |
| racebench2.1 | `Experiments/racebench2.1/` | same |
| rw_benchmark | `Experiments/compare_with_intAbs_cbmc/` | `<dir>/main_n.c` |

### 3.2 One-click run

Stages:

```
clean (UNI-CSeq/CBMC artifacts only)
  -> run (unichecker.py + CBMC)
  -> run_nic (nichecker.py)
  -> table (gen_compare_table.py)
```

`run` overwrites Experiment 1's CBMC summary log `runExp.log` in `compare_with_intAbs_cbmc/` (same unwind `-u 2`). `run_nic` writes `output_NIChecker.log` in that directory and does **not** overwrite Experiment 1's `compare_intAbs_ver_nichecker/runExp_nichecker.log`. The table's `rw_benchmark` Time cells are parsed from `runExp.log` and `runExp_nichecker.log`; `files` / `LOC` / `assertions` / `#Vio` remain hard-coded (18 / 11084 / 78 / 40 / 40).

| Package | UNI-CSeq `-u` | NIChecker `--unwind` | `--loopAbs` / `--LA` | NIChecker `--rounds` |
| --- | --- | --- | --- | --- |
| pthread, goblint-regression | 3 | 3 | no | 2 |
| Idv-races | 2 | 2 | no | 2 |
| racebench2.1 | 3 | 2 | **yes** | 2 |
| rw_benchmark | 2 | 2 | no | 2 |

`--RespCount` is 2. Default time limit is 900 seconds (shared by UNI-CSeq and NIChecker). Set `NICHECKER` before `run_nic`.

From the repository root:

```bash
conda activate py27
export NICHECKER=/path/to/nichecker.py
./run_scripts/run_second_Experiment.sh                  # 900s, through table
./run_scripts/run_second_Experiment.sh 900
./run_scripts/run_second_Experiment.sh 900 --until run  # UNI-CSeq only
./run_scripts/run_second_Experiment.sh --from run_nic --until table
./run_scripts/run_second_Experiment.sh --from run --until table
```

| Argument | Meaning | Default |
| --- | --- | --- |
| first number | time limit in seconds | `900` |
| `--from {clean\|run\|run_nic\|table}` | start stage | `clean` |
| `--until {clean\|run\|run_nic\|table}` | stop after this stage | `table` |

Stages run as the closed interval `[--from, --until]`. Missing `testdirs.sh` or missing `nichecker.py` (when `run_nic` runs) exits with code 1; a missing source file is skipped with a warning.

`run` logs:

| Package | Summary log | Per-case CBMC log |
| --- | --- | --- |
| Idv-races / pthread / goblint-regression | `Experiments/svcomp2022/<pkg>/output_cbmc.log` | `<pkg>/<subdir>/*.c.cbmc.log` |
| racebench2.1 | `Experiments/racebench2.1/output_cbmc.log` | same pattern |
| rw_benchmark | `Experiments/compare_with_intAbs_cbmc/runExp.log` | `<subdir>/_cseq_cbmc_main_n.c.cbmc.log` |

`run_nic` writes `<package>/output_NIChecker.log` (`rw_benchmark`: `Experiments/compare_with_intAbs_cbmc/output_NIChecker.log`).

`table` writes `Experiments/genTable_scripts/compare_table.tex`.

You can also regenerate the table later:

```bash
cd Experiments/genTable_scripts
python3 gen_compare_table.py
```

### 3.3 iCBMC on the 18 real-world programs (RQ2)

**Goal:** Reproduce the iCBMC comment-and-recheck loop on the same 18 `rw_benchmark` programs, then compare iCBMC / NIChecker / UNI-CSeq by package.  
**Paper table:** `tab:rw_package`  
**Script:** `run_scripts/run_icbmc_reproduce.sh`

This step is **Linux-only** (`timeout` plus a per-program iCBMC binary). It does **not** use `unichecker.py` or the `cbmc` on `PATH`. Each subdirectory of `Experiments/icbmc/` must contain an executable `./cbmc` and the original `main.c`. The original `main.c` is never edited; working copies and per-round logs go to `<dir>/_icbmc_repro/`.

Dataset (same 18 names as Experiment 1): `logger1`–`logger3`, `blink1`–`blink3`, `brake1`–`brake3`, `i2c_pca_isa_1`–`3`, `i8xx_tco_1`–`3`, `wdt_pci_1`–`3`, listed in `Experiments/icbmc/realworld18dirs.sh`.

For each program the runner:

1. Copies `main.c` to `_icbmc_repro/main.c`
2. Runs `./cbmc --mm irq --unwind 2 _icbmc_repro/main.c` under `timeout <timelimit>`
3. On `VERIFICATION FAILED`, comments the violated assertion (or the expanding macro call) with `run_scripts/icbmc_comment_assert.py` and starts the next round
4. Stops on `VERIFICATION SUCCESSFUL`, timeout, parse/comment error, or 80 rounds

Wall time is the sum of `real` times from `_icbmc_repro/runtime*.out`. `Vio` is the number of successfully commented lines; `Val=1` only if the last result is `SUCCESS`.

From the repository root:

```bash
./run_scripts/run_icbmc_reproduce.sh 900
```

The time-limit argument is required (paper setting: 900 seconds per iCBMC invocation). A missing `main.c` or non-executable `./cbmc` is skipped with a warning.

Outputs:

| File | Role |
| --- | --- |
| `Experiments/icbmc/run_icbmc.log` | full transcript |
| `Experiments/icbmc/_icbmc_repro_summary.csv` | per-program `Name,rounds,Vio,Val,Time,last_result,commented_lines` |
| `Experiments/icbmc/<dir>/_icbmc_repro/` | working `main.c`, `runtimeK.out`, and status files |

Generate the package table after this run **and** after Experiment 1 logs exist (UNI-CSeq CBMC `runExp.log` and NIChecker `runExp_nichecker.log`). Experiment 2's `run` stage overwrites the UNI-CSeq CBMC log with the same `-u 2`; either log is fine for Time.

```bash
cd Experiments/genTable_scripts
python3 gen_rw_package_table.py
```

Output: `Experiments/genTable_scripts/rw_package_table.tex`

The table aggregates the 18 programs into six packages (`logger`, `blink`, `brake`, `i2c_pca_isa`, `i8xx_tco`, `wdt_pci`). iCBMC Time comes from the CSV; iCBMC Violations are counted from the comment-loop line numbers (as source assertion sites). For `i8xx_tco_*` the table uses the UNI-CSeq/NIChecker violation count instead of the comment loop. `LOC` / `ISRs` / `Assertions` reuse the Experiment 1 hard-coded counts (`u=2`).

---

## 4. Experiment 3: Sequentialization with different backends (portfolio)

**Goal:** Compare single backends with a **parallel** CBMC+CPAchecker portfolio.  
**Paper table:** `tab:Cooperation_Verification`  
(Each multi-assert program is split into single-assert instances.)

Use `run_scripts/run_third_Experiment.sh`. It covers five packages, per-package unwind, and the parallel portfolio only (no Sequential column).

### 4.1 Dataset (assertions already split)

| Configuration | Directory | Used for the main table |
| --- | --- | --- |
| Single-run CBMC / CPAchecker | `Experiments/ComExp_Split/` | yes |
| Parallel CBMC+CPA (`--mode cbmc-cpachecker`) | `Experiments/ComExp_Split_unicseq_CC/` | yes |

Packages: `Idv-races`, `pthread`, `racebench2.1`, `rw_benchmark`, `goblint-regression`.

The one-click script re-splits if you start from `clean`/`split`. `split_asserts.py` uses its own directory as `ROOT`.

### 4.2 One-click run

Stages:

```
clean (top-level clean.sh in ComExp_Split and ComExp_Split_unicseq_CC)
  -> split (both split_asserts.py copies; count check)
  -> run (single-backend CBMC/CPAchecker + parallel portfolio)
  -> table (score_table_two.py + score_table_all_correctness.py)
```

| Package | CBMC `-u` / `--cbmc-unwinding` | `--loopAbs` (CBMC, CPAchecker, and the portfolio) |
| --- | --- | --- |
| goblint-regression, pthread | 3 | no |
| Idv-races, rw_benchmark | 2 | no |
| racebench2.1 | 3 | **yes** |

CPAchecker single-run does not take `-u`. The portfolio passes `--cbmc-unwinding` only to CBMC.

From the repository root:

```bash
./run_scripts/run_third_Experiment.sh                       # default 900s, through table
./run_scripts/run_third_Experiment.sh 900
./run_scripts/run_third_Experiment.sh 3600                  # optional longer budget
./run_scripts/run_third_Experiment.sh 900 --until split
./run_scripts/run_third_Experiment.sh 900 --until run
./run_scripts/run_third_Experiment.sh --from run --until table
```

| Argument | Meaning | Default |
| --- | --- | --- |
| first number | `unichecker` / `unicseq` time limit (seconds) | `900` |
| `--from {clean\|split\|run\|table}` | start stage | `clean` |
| `--until {split\|run\|table}` | stop after this stage | `table` |

After `--until split`, continue with `--from run` so `clean` does not delete the freshly split files. `--from split` does not delete original `.c` files; it removes existing `*_assert*.c` and `_cseq_*` first to avoid `*_assert1_assert1.c`.

Split checks (failure exits with code 1):

- no `*_assert*_assert*.c`
- single-assert counts (excluding `_cseq_`): Idv-races 20, pthread 10, racebench2.1 53, rw_benchmark 78, goblint-regression 110 (271 total)

`run` logs:

| Packages | Single-backend logs | Parallel portfolio log |
| --- | --- | --- |
| four packages | `ComExp_Split/results_{cbmc,cpachecker}.log` | `ComExp_Split_unicseq_CC/results_unicseq_cbmc-cpachecker.log` |
| goblint-regression | `ComExp_Split/results_goblint-regression_{cbmc,cpachecker}.log` | `..._CC/results_unicseq_goblint-regression_cbmc-cpachecker.log` |

`table` writes under `Experiments/genTable_scripts/`:

- `compare_two_table.txt` (legacy four-package table; Sequential is empty/UNKNOWN in this reproduction)
- `compare_correctness_table.txt` (paper table `tab:Cooperation_Verification`)
- `compare_correctness_detail.csv`

You can also regenerate the paper table later:

```bash
cd Experiments/genTable_scripts
python3 score_table_all_correctness.py
```

---

## 5. Experiment 3 figure (verification-time CDF)

The paper CDF is produced by `Experiments/genTable_scripts/gen_cfdfig.py` from the same 271 single-assert tasks as `tab:Cooperation_Verification`.

After Section 4 logs are complete (no extra experiment run):

```bash
cd Experiments/genTable_scripts
python3 gen_cfdfig.py
```

Output: `Experiments/genTable_scripts/exp3_runtime_cdf.png`

| Curve | Logs |
| --- | --- |
| CBMC | `ComExp_Split/results_cbmc.log`, `results_goblint-regression_cbmc.log` |
| CPAchecker | `ComExp_Split/results_cpachecker.log`, `results_goblint-regression_cpachecker.log` |
| CBMC+CPA Parallel | `ComExp_Split_unicseq_CC/results_unicseq_cbmc-cpachecker.log`, `results_unicseq_goblint-regression_cbmc-cpachecker.log` |

Time convention (`TIME_LIMIT = 900`): prefer `WALLTIME` in a case block, otherwise the tool time; times ≥ 900 are plotted at 900; missing / non-positive times are omitted. TRUE / FALSE / UNKNOWN / TIMEOUT are included when a valid time exists.

---

## 6. Interrupt-masking ablation (full racebench 2.1)

**Goal:** Compare the default encoding with `--ignore-masking` on all 31 Racebench 2.1 programs.  
**Script:** `run_scripts/run_masking_ablation_all.sh`

| Variant | Directory | UNI-CSeq flag |
| --- | --- | --- |
| default encoding | `Experiments/Masking_Isolation/racebench2.1` | none |
| ignore masking | `Experiments/Masking_Isolation/racebench2.1_nomasking` | `--ignore-masking` |

Both runs use `unicseq.py --mode cbmc-cpachecker` (same parallel portfolio as Experiment 3), unwind 3, `RespCount=2`, and `--loopAbs` on CBMC and CPAchecker. Split uses the Experiment 3 convention (53 single-assert files).

Stages:

```
clean -> split -> run_ignore -> run_mask -> table
```

- `run_ignore` writes `Experiments/Masking_Isolation/output_cbmc_all_ignore_masking.log`
- `run_mask` writes `Experiments/Masking_Isolation/output_cbmc_all.log`
- `table` scores Violations / Proofs / FP / Unknown from `Experiments/Masking_Isolation/GT_rachench21.csv` (times summed over all asserts of the same program)

From the repository root:

```bash
./run_scripts/run_masking_ablation_all.sh                  # default 900s, through table
./run_scripts/run_masking_ablation_all.sh 900
./run_scripts/run_masking_ablation_all.sh 900 --until split
./run_scripts/run_masking_ablation_all.sh --from table --until table
```

| Argument | Meaning | Default |
| --- | --- | --- |
| first number | `unicseq` time limit (seconds) | `900` |
| `--from {clean\|split\|run_ignore\|run_mask\|table}` | start stage | `clean` |
| `--until {clean\|split\|run_ignore\|run_mask\|table}` | stop after this stage | `table` |

Outputs:

- `Experiments/Masking_Isolation/masking_ablation_all_table.tex` (31 programs)
- `Experiments/Masking_Isolation/masking_ablation_differing_cases.tex` (programs whose FP is non-zero)

---

## 7. Paper table / figure scripts

| Experiment | Paper artifact | Script | Output |
| --- | --- | --- | --- |
| Regression Test | none | none | `Experiments/Regression_Test/test_result.txt` |
| Experiment 1 | `tab:compare_with_intAbs` | `Experiments/genTable_scripts/gen_table.py` | `Experiments/genTable_scripts/gen_table.txt` |
| Experiment 2 | `tab:compare_with_NIChecker` | `Experiments/genTable_scripts/gen_compare_table.py` | `Experiments/genTable_scripts/compare_table.tex` |
| Experiment 2 (iCBMC) | `tab:rw_package` | `run_scripts/run_icbmc_reproduce.sh` + `Experiments/genTable_scripts/gen_rw_package_table.py` | `Experiments/icbmc/_icbmc_repro_summary.csv`, `Experiments/genTable_scripts/rw_package_table.tex` |
| Experiment 3 | `tab:Cooperation_Verification` | `Experiments/genTable_scripts/score_table_all_correctness.py` | `Experiments/genTable_scripts/compare_correctness_table.txt` |
| Experiment 3 figure | CDF | `Experiments/genTable_scripts/gen_cfdfig.py` | `Experiments/genTable_scripts/exp3_runtime_cdf.png` |
| Masking ablation | ablation tables | `run_scripts/run_masking_ablation_all.sh` (`table` stage) | `Experiments/Masking_Isolation/masking_ablation_all_table.tex`, `masking_ablation_differing_cases.tex` |

After the corresponding logs exist:

```bash
cd Experiments/genTable_scripts
python3 gen_table.py
python3 gen_compare_table.py
python3 gen_rw_package_table.py
python3 score_table_all_correctness.py
python3 gen_cfdfig.py
```

The masking tables are produced by the ablation runner's `table` stage, not by a script in `genTable_scripts/`.
