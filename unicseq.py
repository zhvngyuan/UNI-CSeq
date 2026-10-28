#!/usr/bin/env python3
# Author: Yuan Zhang
# Date: 2025-09-07
# Description: Combined parallel verification script for C programs.
#   This script runs CBMC and CPAchecker in parallel,
#   and returns the final verification result based on a composite policy.
#   It also outputs the total runtime and peak memory usage for benchmarking purposes.

import sys
import getopt
import multiprocessing
import subprocess
import re
import os
import time

import psutil
import threading

# Global configuration class for all script parameters
class Config(object):
    input_file = ''
    cbmc_unwinding = 2
    timelimit = 60
    RespCount = 1
    mode = 'parallel'
    mode_choices = ['parallel', 'cbmc-cpachecker', 'sequential']
    loopAbs = False
    ignore_masking = False

def strip_ansi_codes(s):
    """Remove ANSI color codes from a string."""
    ansi_escape = re.compile(r'\x1b\[[0-9;]*m')
    return ansi_escape.sub('', s)

def usage(cmd, errormsg='', showhelp=False):
    """Print usage information and exit if needed."""
    if showhelp or errormsg:
        print()
        print("***  UNI-CSeq | Combined C Verification Script  ***")
        print()
        print("Usage: ")
        print("   python3 %s -i <input.c> [options]" % cmd)
        print()
        print("Options:")
        print("   -h, --help                  Display this help and exit")
        print("   -i <file>, --input=<file>   Input C file")
        print("   -u <N>, --cbmc-unwinding=<N>    Unwinding parameter for CBMC (default: 2)")
        print("   -t <N>, --timelimit=<N>     Time limit in seconds (default: 60)")
        print("   -m <mode>, --mode=<mode>    Verification mode: parallel (default), cbmc-cpachecker, or sequential")
        print("   --RespCount=<N>             Count of interrupt responses to monitor (default: 1)")
        print("   --loopAbs                   enable loop abstraction (default: False)")
        print("   --ignore-masking            ignore interrupt masking encoding (default: off)")
        print()
    if errormsg:
        print(errormsg + '\n')
    if showhelp or errormsg:
        sys.exit(1)

def parse_args():
    """Parse command line arguments and store them in Config."""
    cmd = os.path.basename(sys.argv[0])
    shortopts = "hi:u:t:m:"
    longopts = ["help", "input=", "cbmc-unwinding=", "timelimit=", "mode=", "RespCount=", "loopAbs", "ignore-masking"]

    try:
        opts, args = getopt.getopt(sys.argv[1:], shortopts, longopts)
    except getopt.GetoptError as err:
        usage(cmd, "error: " + str(err), showhelp=True)
        sys.exit(2)

    for o, a in opts:
        if o in ("-h", "--help"):
            usage(cmd, '', showhelp=True)
        elif o in ("-i", "--input"):
            Config.input_file = a
        elif o in ("--RespCount"):
            Config.RespCount = int(a)
        elif o in ("-u", "--cbmc-unwinding"):
            try:
                Config.cbmc_unwinding = int(a)
            except:
                usage(cmd, "error: cbmc-unwinding must be integer")
        elif o in ("-t", "--timelimit"):
            try:
                Config.timelimit = int(a)
            except:
                usage(cmd, "error: timelimit must be integer")
        elif o in ("-m", "--mode"):
            if a not in Config.mode_choices:
                usage(cmd, "error: unknown mode: %s" % a)
            Config.mode = a
        elif o in ("--loopAbs"):
            Config.loopAbs = True
        elif o in ("--ignore-masking"):
            Config.ignore_masking = True

    if Config.input_file == '':
        usage(cmd, "error: input file not specified", showhelp=True)

def run_unicseq(backend):
    """
    Run unichecker.py as a subprocess for the given backend.
    Returns the combined stdout and stderr output.
    """
    cmd = ['python2', 'unichecker.py',
           '-i', Config.input_file,
           '-b', backend,
           '--timelimit', str(Config.timelimit),
           '--RespCount', str(Config.RespCount)]
    if backend == 'cbmc' and Config.cbmc_unwinding:
        cmd += ['-u', str(Config.cbmc_unwinding)]
    if Config.loopAbs:
        cmd += ['--loopAbs']
    if Config.ignore_masking:
        cmd += ['--ignore-masking']
    script_dir = os.path.dirname(os.path.abspath(__file__))
    try:
        proc = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            encoding='utf-8',
            timeout=Config.timelimit + 5,
            cwd=script_dir
        )
        # print(f"[DEBUG] {backend} stdout:\n{proc.stdout}")
        # print(f"[DEBUG] {backend} stderr:\n{proc.stderr}")
        return proc.stdout + proc.stderr
    except subprocess.TimeoutExpired:
        print(f"[ERROR] {backend} TimeoutExpired")
        return 'TIMEOUT'
    except Exception as e:
        print(f"[ERROR] {backend} Exception: {e}")
        return f'ERROR: {str(e)}'

def parse_unicseq_result(backend, raw_output):
    """
    Parse the output of unichecker.py and extract the verification result (TRUE, FALSE, etc.)
    """
    raw_output = strip_ansi_codes(raw_output)
    lines = raw_output.splitlines()
    for i, line in enumerate(lines):
        if 'Analysis result:' in line:
            result_part = line.split('Analysis result:')[1].strip()
            if result_part:
                after = result_part
            else:
                after = ""
                for next_line in lines[i+1:]:
                    if next_line.strip():
                        after = next_line.strip()
                        break
            parts = after.split(',')
            if len(parts) >= 2:
                result = parts[1].strip().upper()
                if result == 'TRUE':
                    return 'TRUE'
                elif result == 'FALSE':
                    return 'FALSE'
                elif result == 'UNKNOWN':
                    return 'UNKNOWN'
                else:
                    return 'ERROR'
    if 'Timeout' in raw_output or 'TIMEOUT' in raw_output:
        return 'TIMEOUT'
    if 'ERROR' in raw_output or 'Error' in raw_output:
        return 'ERROR'
    return 'UNKNOWN'

def backend_worker(backend, conn):
    """
    Worker function to run unichecker backend in a subprocess for parallel verification.
    Sends the result through a pipe connection.
    """
    output = run_unicseq(backend)
    result = parse_unicseq_result(backend, output)
    conn.send((backend, result))
    conn.close()

def parallel_verify():
    """
    Run CBMC and CPAchecker in parallel.
    Implements the composite policy for result selection.
    """
    processes = []
    parent_conns = []
    backends = ['cbmc', 'cpachecker']
    for backend in backends:
        parent_conn, child_conn = multiprocessing.Pipe()
        p = multiprocessing.Process(target=backend_worker, args=(backend, child_conn))
        processes.append(p)
        parent_conns.append(parent_conn)
        p.start()

    results = {}
    finished = set()
    cbmc_returned = False
    cbmc_result = None

    while len(finished) < 2:
        for idx, conn in enumerate(parent_conns):
            if idx in finished:
                continue
            if conn.poll():
                backend, result = conn.recv()
                results[backend] = result
                finished.add(idx)
                # Policy: if CBMC returns FALSE, terminate all and return FALSE
                if backend == 'cbmc' and result == 'FALSE':
                    for i, p in enumerate(processes):
                        if i != idx and i not in finished:
                            p.terminate()
                    return 'FALSE', results
                # Policy: if CBMC returns TRUE, wait for CPAchecker
                if backend == 'cbmc' and result == 'TRUE':
                    cbmc_returned = True
                    cbmc_result = 'TRUE'
                    if 'cpachecker' in results:
                        if results['cpachecker'] == 'TRUE':
                            for i, p in enumerate(processes):
                                if i != idx and i not in finished:
                                    p.terminate()
                            return 'TRUE', results
                        elif results['cpachecker'] == 'FALSE':
                            for i, p in enumerate(processes):
                                if i != idx and i not in finished:
                                    p.terminate()
                            return 'FALSE', results
                    continue
                # Policy: if CPAchecker returns TRUE before CBMC, return TRUE
                if backend == 'cpachecker' and result == 'TRUE':
                    if not cbmc_returned:
                        for i, p in enumerate(processes):
                            if i != idx and i not in finished:
                                p.terminate()
                        return 'TRUE', results
                    elif cbmc_result == 'TRUE':
                        for i, p in enumerate(processes):
                            if i != idx and i not in finished:
                                p.terminate()
                        return 'TRUE', results
                # Policy: if CPAchecker returns FALSE after CBMC TRUE, return FALSE
                if backend == 'cpachecker' and result == 'FALSE':
                    if cbmc_returned and cbmc_result == 'TRUE':
                        for i, p in enumerate(processes):
                            if i != idx and i not in finished:
                                p.terminate()
                        return 'FALSE', results
    if all(r == 'TRUE' for r in results.values()):
        return 'TRUE', results
    if any(r == 'FALSE' for r in results.values()):
        return 'FALSE', results
    return 'UNKNOWN', results

def cbmc_cpachecker_verify():
    """
    CBMC + CPAchecker parallel verification.
    """
    processes = []
    parent_conns = []
    backends = ['cbmc', 'cpachecker']
    for backend in backends:
        parent_conn, child_conn = multiprocessing.Pipe()
        p = multiprocessing.Process(target=backend_worker, args=(backend, child_conn))
        processes.append(p)
        parent_conns.append(parent_conn)
        p.start()

    results = {}
    finished = set()
    cbmc_returned = False
    cbmc_result = None

    while len(finished) < 2:
        for idx, conn in enumerate(parent_conns):
            if idx in finished:
                continue
            if conn.poll():
                backend, result = conn.recv()
                results[backend] = result
                finished.add(idx)
                if backend == 'cbmc' and result == 'FALSE':
                    for i, p in enumerate(processes):
                        if i != idx and i not in finished:
                            p.terminate()
                    return 'FALSE', results
                if backend == 'cbmc' and result == 'TRUE':
                    cbmc_returned = True
                    cbmc_result = 'TRUE'
                    if 'cpachecker' in results:
                        if results['cpachecker'] == 'TRUE':
                            return 'TRUE', results
                        elif results['cpachecker'] == 'FALSE':
                            return 'FALSE', results
                if backend == 'cpachecker' and cbmc_returned:
                    if cbmc_result == 'TRUE':
                        if result == 'TRUE':
                            return 'TRUE', results
                        elif result == 'FALSE':
                            return 'FALSE', results
    if 'cbmc' in results and 'cpachecker' in results:
        if results['cbmc'] == 'TRUE' and results['cpachecker'] == 'TRUE':
            return 'TRUE', results
        elif results['cbmc'] == 'FALSE' or results['cpachecker'] == 'FALSE':
            return 'FALSE', results
    return 'UNKNOWN', results

def sequential_verify():
    """
    Sequentially run CPAchecker and CBMC on the input file.
    """
    backends = ['cpachecker', 'cbmc']
    results = {}
    for backend in backends:
        print(f"[SEQUENTIAL] Running {backend}...")
        output = run_unicseq(backend)
        result = parse_unicseq_result(backend, output)
        results[backend] = result
        print(f"[SEQUENTIAL] {backend} result: {result}")
    # If both tools agree, return that result
    if all(r == 'TRUE' for r in results.values()):
        return 'TRUE', results
    elif any(r == 'FALSE' for r in results.values()):
        return 'FALSE', results
    else:
        return 'UNKNOWN', results

def monitor_memory(pid, interval=0.1):
    """
    Monitor the memory usage of the main process.
    Returns the peak RSS (resident set size) in MB.
    """
    process = psutil.Process(pid)
    peak = 0
    while True:
        try:
            mem = process.memory_info().rss / 1024 / 1024
            if mem > peak:
                peak = mem
            time.sleep(interval)
        except psutil.NoSuchProcess:
            break
        except Exception:
            break
    return peak

if __name__ == "__main__":
    parse_args()

    if not os.path.isfile(Config.input_file):
        print("The file does not exist:", Config.input_file)
        exit(1)

    print(f"[UNICSEQ] Start {Config.mode.upper()} Verification...")
    start_time = time.time()

    # Start a thread to monitor peak memory usage
    peak_memory = 0
    this_pid = os.getpid()
    mem_result = {'peak': 0}
    def mem_monitor():
        process = psutil.Process(this_pid)
        while True:
            try:
                cur = process.memory_info().rss / 1024 / 1024
                if cur > mem_result['peak']:
                    mem_result['peak'] = cur
                time.sleep(0.1)
            except psutil.NoSuchProcess:
                break
            except Exception:
                break

    mem_thread = threading.Thread(target=mem_monitor, daemon=True)
    mem_thread.start()

    # Select and run the specified verification mode
    if Config.mode == 'parallel':
        result, detail = parallel_verify()
    elif Config.mode == 'cbmc-cpachecker':
        result, detail = parallel_verify()
    elif Config.mode == 'sequential':
        result, detail = sequential_verify()

    end_time = time.time()
    elapsed_time = end_time - start_time

    # Wait a moment to ensure memory monitoring catches the final peak
    time.sleep(0.2)

    print("Final verification results:", result)
    print("Backend results:", detail)
    print("Total running time: {:.2f} seconds".format(elapsed_time))
    print("Peak memory usage: {:.2f} MB".format(mem_result['peak']))