#!/home/dell/anaconda3/envs/py27/bin/python2.7
# -*- coding: utf-8 -*-

# -----------------------------------------------------------------------------
# NAME = abs_feeder
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   Wrapper for abs translation
#       1. Translation
#       2. Invoke backend to analyser
# TODO:
#
# Changelog:
#   2016.05.11   Add VVT as a backends
#   2016.05.07   Add CPA-BAM and Seahorn as backends
#   2016.05.05   Add UAutomizer and UKojak as proving correctness backends
# -----------------------------------------------------------------------------

import os
import os.path
import sys
import getopt
import time
import subprocess
import shlex

from time import gmtime, strftime
from bin import utils

import psutil
import threading


'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

                  Options & parameters below.

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
# Name of the executable file to run, by backend.
backendFilename = {}
backendFilename['cbmc'] = 'cbmc'
backendFilename['esbmc'] = 'esbmc'
backendFilename['llbmc'] = 'llbmc'
backendFilename['2ls'] = '2ls'
# backendFilename['cpachecker'] = './backends/CPAchecker/scripts/cpa.sh'
backendFilename['cpachecker'] = '/home/dell/zyworkspace/CPAchecker-4.0/bin/cpachecker'
backendFilename['cpabam'] = './backends/CPA-BAM/scripts/cpa.sh'
# backendFilename['uautomizer'] = './Ultimate.py'
backendFilename['uautomizer'] = '/home/dell/zyworkspace/unichecker/backends/UAutomizer_linux/Ultimate.py'
backendFilename['seahorn'] = './sea_svcomp'
backendFilename['ukojak'] = './Ultimate.py'
backendFilename['vvt'] = './vvt-svcomp-bench.sh'

# Command-line parameters, by backend.
cmdLineOptions = {}
cmdLineOptions['cbmc'] = ' --no-unwinding-assertions '
cmdLineOptions['esbmc'] = ' --no-slice --no-bounds-check --no-div-by-zero-check --no-pointer-check --no-unwinding-assertions '
cmdLineOptions['llbmc'] = ' -no-max-function-call-depth-checks -no-memory-free-checks -no-shift-checks -no-memcpy-disjoint-checks -no-memory-access-checks -no-memory-allocation-checks --no-max-loop-iterations-checks --ignore-missing-function-bodies -no-overflow-checks -no-div-by-zero-checks --max-loop-iterations='
# cmdLineOptions['cpachecker'] = ' -32 -timelimit 86400 -heap 15000M -stats -preprocess -'
cmdLineOptions['cpachecker'] = ' --64 --heap 15000M --stats --preprocess --'
cmdLineOptions['2ls'] = ' --32 --k-induction '
# cmdLineOptions['uautomizer'] = ' ALL.prp 32bit '
# cmdLineOptions['uautomizer'] = ' --spec /home/dell/zyworkspace/unichecker/backends/UAutomizer_linux/config/AutomizerReachWitnessValidation.xml --architecture 32bit '
cmdLineOptions['uautomizer'] = ' --spec /home/dell/zyworkspace/unichecker/backends/UAutomizer_linux/config/AutomizerReach.xml --architecture 64bit '
# cmdLineOptions['uautomizer'] = ' --spec /home/dell/zyworkspace/INT_ComboSeq/backends/UAutomizer_linux/unreach-call.prp --architecture 64bit --file '
cmdLineOptions['ukojak'] = ' ALL.prp 32bit '
cmdLineOptions['cpabam'] = ' -32 -sv-comp16-bam -disable-java-assertions -heap 15000m -preprocess '
cmdLineOptions['seahorn'] = ' -m 32 --spec=ALL.prp -p '
cmdLineOptions['vvt'] = ' '

# Command-line parameters, by backend - when no sequentialisation is performed.
cmdLineOptionsNOSEQ = {}
cmdLineOptionsNOSEQ['cbmc'] = ' --no-unwinding-assertions --unwind '
cmdLineOptionsNOSEQ['esbmc'] = ' --no-slice --no-bounds-check --no-div-by-zero-check --no-pointer-check --no-unwinding-assertions --unwind '
cmdLineOptionsNOSEQ['llbmc'] = ' -no-max-function-call-depth-checks -no-memory-free-checks -no-shift-checks -no-memcpy-disjoint-checks -no-memory-access-checks -no-memory-allocation-checks --no-max-loop-iterations-checks --ignore-missing-function-bodies -no-overflow-checks -no-div-by-zero-checks '
# cmdLineOptionsNOSEQ['cpachecker'] = ' -timelimit 86400 -heap 12000M -stats -preprocess -'
cmdLineOptionsNOSEQ['cpachecker'] = ' --heap 12000M --stats --preprocess --'
# cmdLineOptionsNOSEQ['cpachecker'] = ' --heap 15000M --stack 4m --stats --preprocess --'
cmdLineOptionsNOSEQ['2ls'] = ' --inline '
# cmdLineOptionsNOSEQ['uautomizer'] = ' ALL.prp 32bit '
cmdLineOptions['uautomizer'] = ' --spec /home/dell/zyworkspace/unichecker/backends/UAutomizer_linux/config/AutomizerReach.xml --architecture 64bit --file '
# cmdLineOptions['uautomizer'] = ' --spec /home/dell/zyworkspace/unichecker/backends/UAutomizer_linux/config/AutomizerReachWitnessValidation.xml --architecture 32bit --file '
cmdLineOptionsNOSEQ['ukojak'] = ' ALL.prp 32bit '
cmdLineOptionsNOSEQ['cpabam'] = ' -32 -sv-comp16-bam -disable-java-assertions -heap 15000m -preprocess '
cmdLineOptionsNOSEQ['seahorn'] = ' -m 32 --spec=ALL.prp -p '
cmdLineOptionsNOSEQ['vvt'] = ' '

# Expressions to check for from the log to see whether verification went fine.
verificationOK = {}
verificationOK['cbmc'] = 'VERIFICATION SUCCESSFUL\n'
verificationOK['esbmc'] = 'VERIFICATION SUCCESSFUL\n'
verificationOK['llbmc'] = 'No error detected.\n'
verificationOK['cpachecker'] = 'Verification result: TRUE'
verificationOK['2ls'] = 'VERIFICATION SUCCESSFUL\n'
verificationOK['uautomizer'] = 'TRUE\n'
verificationOK['ukojak'] = 'TRUE\n'
verificationOK['cpabam'] = 'Verification result: TRUE'
verificationOK['seahorn'] = 'BRUNCH_STAT Result TRUE'
verificationOK['vvt'] = 'No bug found.'

# Expressions to check for from the log to check whether verification failed.
verificationFAIL = {}
verificationFAIL['cbmc'] = 'VERIFICATION FAILED\n'
verificationFAIL['esbmc'] = 'VERIFICATION FAILED\n'
verificationFAIL['llbmc'] = 'Error detected.\n'
verificationFAIL['cpachecker'] = 'Verification result: FALSE'
verificationFAIL['2ls'] = 'VERIFICATION FAILED\n'
verificationFAIL['uautomizer'] = 'FALSE(NONE)\n'
verificationFAIL['ukojak'] = 'FALSE\n'
verificationFAIL['cpabam'] = 'Verification result: FALSE'
verificationFAIL['seahorn'] = 'BRUNCH_STAT Result FALSE'
verificationFAIL['vvt'] = 'Bug found:'


def usage(cmd, errormsg='', showhelp=False):
    if showhelp:
        print ""
        print "***  UNIChecker  |  Unbounded Lazy C Sequentialiser for IDP (extended from UL-CSeq )  ***"
        print "***           |  October 2025                          ***"
        print ""
        print "Usage: "
        print ""
        print "   %s -i [input.c] [options]" % cmd
        print ""
        print "   options:"
        print "   -h, --help                  display this help screen"
        print ""
        print "   -c, --cex                   output counterexample from the backend"
        # print "   -S, --skip                  do not sequentialize: analyse original file"
        print "   -V, --verbose               display extra information"
        print "   -D, --debug                 debug mode"
        print ""
        print "   -i<file>, --input=<file>    input filename"
        print "   -p<path>, --path=<path>     path to backend executable file (custom if default is failed)"
        print "   -b<fmt>, --backend=<fmt>    backend (cpachecker, cbmc, esbmc, llbmc, seahorn, uautomizer, vvt), default: cpachecker"
        print "   -u<X>, --unwind=<X>         unwinding parameter for BMC backend"
        print "   -r<X>, --round=<X>          round parameter for BMC backend"
        # print "   -a<X>, --extra=<X>          extra command line parameters for CPAChecker"
        # print "   --clang-path=<X>            clang 3.3 path required for llbmc backend"
        print ""
        print "   -t<X>, --threads=<X>        max number of threads (default: auto)"
        print "   -W, --witness=<logfile>     log file from backend model checker"
        print "   -E<X>, --error-label=<X>    error label"
        print "   -s, --spec=<specfile>       SV-COMP specification file"
        print ''
        print "   -T, --timelimit=<X>         time limit (in seconds, default: no limit)"
        print "   -M, --memorylimit=<X>       memory limit (in megabytes, default: no limit)"
        print " --RespCount=<X>               count of interrupt responses to monitor (default: 1)" # add by zy
        print " --loopAbs                     enable loop abstraction (default: False)" # add by zy
        print " --ignore-masking              ignore interrupt masking encoding (default: off)"
        print ""
    if errormsg:
        print errormsg + '\n'
    sys.exit(1)


peak_mem_mb = [0]

def monitor_memory(pid, interval=0.1):
    try:
        p = psutil.Process(pid)
        peak = 0
        while True:
            mem = p.memory_info().rss / 1024.0 / 1024.0
            if mem > peak:
                peak = mem
                peak_mem_mb[0] = peak  # 记录到全局变量
            time.sleep(interval)
    except Exception:
        pass

def geterrorlabel(specfile):
    error_label = 'ERROR'  # default error label
    inp = open(specfile, "r")
    for line in inp.readlines():
        i_label = line.find("label")
        if i_label >= 0:
            line = line[i_label:]
            i_label = line.find("(",)
            line = line[i_label + 1:]
            i_label = line.find(")",)
            error_label = line[:i_label]
        # else:
        #     i_call = line.find('call')
        #     if i_call >= 0:
        #         line = line[i_call:]
        #         i_call = line.find("(",)
        #         line = line[i_label+1:]
        #         i_call = line.find(")",)
        #         function_error = line[:i_label]
        #         if not function_error.startswith('__VERIFIER_error'):
        #             print 'There may be something wrong in spec file\n'
    inp.close()
    return error_label


def printStats(file, result, time):
    if result == 'UNKNOWN':
        result = utils.colors.YELLOW + result + utils.colors.NO
    elif result == 'TRUE':
        result = utils.colors.GREEN + result + utils.colors.NO
    elif result == 'FALSE':
        result = utils.colors.RED + result + utils.colors.NO
    print "%s, %s, %0.2f" % (file, result, time)





def main(args):
    realstarttime = time.time()    # save wall time
    # zhangyuan memory
    start_time = time.time()
    try:
        pid = os.getpid()
        t = threading.Thread(target=monitor_memory, args=(pid,))
        t.daemon = True
        t.start()
    except Exception:
        pass
    ''' 1. Check command-line options
    '''
    cmd = args[0]
    try:
        shortopts = "hDa:ci:b:t:s:p:W:T:M:SVE:u:r:"
        longopts = ["help", "debug", "extra=", "cex", "input=",
                    "backend=", "threads=", "spec=", "path=", "witness=",
                    "timelimit=", "memorylimit=", "skip", "verbose",
                    "clang-path=", "error-label=", "round=", "unwind=", "RespCount=", "loopAbs", "ignore-masking"]
        opts, args = getopt.getopt(sys.argv[1:], shortopts, longopts)
    except getopt.GetoptError, err:
        usage(cmd, "error: " + str(err), showhelp=True)
        sys.exit(2)

    inputfile = seconds = witness = ''
    threads = 3
    timelimit = 86400
    memorylimit = 0
    label = 'ERROR'   # Default
    outputcounterexample = donotsequentialize = verbose = False
    debug = False
    format = 'cpachecker'  # Default is cpachecker
    path = ''
    extra = ''
    clangpath = ''
    unwind = 1
    round = 0
    RespCount = 1
    loopAbs = False
    ignore_masking = False

    for o, a in opts:
        if o in ("-h", "--help"):
            usage(cmd, '', showhelp=True)
        elif o in ("-D", "--debug"):
            debug = True
        elif o in ("-a", "--extra"):
            extra = a
        elif o in ("-u", "--unwind"):
            unwind = int(a)
        elif o in ("-r", "--round"):
            round = int(a)
        elif o in ("-V", "--verbose"):
            verbose = True
        elif o in ("-c", "--cex"):
            outputcounterexample = True
        elif o in ("-i", "--input"):
            inputfile = a
        elif o in ("-b", "--backend"):
            format = a
        elif o in ("-p", "--path"):
            path = a
        elif o in ("-t", "--threads"):
            threads = int(a)
        elif o in ("-W", "--witness"):
            witness = a
        elif o in ("-T", "--timelimit"):
            timelimit = int(a)
        elif o in ("-M", "--memorylimit"):
            memorylimit = int(a)
        elif o in ("-S", "--skip"):
            donotsequentialize = True
        elif o in ("-s", "--spec"):
            spec = a
            if not os.path.isfile(spec):
                usage(cmd, 'error: unable to open spec file (%s)' % spec)
            label = geterrorlabel(spec)
        elif o in ("-E", "--error-label"):
            label = a
        elif o in ("--clang-path"):
            clangpath = a
        elif o in ("--RespCount"):
            RespCount = int(a)
        elif o in ("--loopAbs"):
            loopAbs = True
        elif o in ("--ignore-masking"):
            ignore_masking = True
        else:
            assert False, "unhandled option"

    if inputfile == '':
        usage(cmd, '')
        print "error: input file name not specified\n"
        sys.exit(2)

    if format not in ('cpachecker', 'cbmc', 'esbmc', 'llbmc', '2ls',
                      'uautomizer', 'ukojak', 'cpabam', 'seahorn',
                      'vvt'):
        usage(cmd, 'error: backend (%s) not supported' % format)

    '''
        0. Check for the present of backend
    '''

    # tool configuration/installation/integrity check (TODO)
    if path == '':
        path = backendFilename[format]
    # if not os.path.isfile(path):
    #     usage(cmd, "error: unable to find the given backend executable file (%s)" % path)
    #     sys.exit(2)

    '''
        1. File name handling and modification
    '''
    # yuan zhang: 获取 abs_invoker.py 的绝对路径，此处注意需要修改文件在自己系统的'绝对路径'，使用'./bin/abs_invoker.py'会导致run_scripts中的脚本运行出错，但不影响单次unicseq.py的执行
    # abs_invoker_path = os.path.abspath('./bin/abs_invoker.py')
    abs_invoker_path = os.path.abspath('/home/dell/zyworkspace/unichecker/bin/abs_invoker.py')
    abs_invoker_dir = os.path.dirname(abs_invoker_path)

    # Name of squentialized file
    dirname, filename = os.path.split(os.path.abspath(inputfile))
    seqfile = dirname + '/_cseq_' + format + '_' + filename
    if seqfile.endswith('.i'):
        seqfile = seqfile[:-2] + '.c'
    oldinputfile = inputfile

    # For SV-COMP junk benchmark
    if inputfile.endswith('.i'):
        text = utils.stripIfNeeded(inputfile)[1]
        inputfile = inputfile[:-2] + '.c'
        utils.saveFile(inputfile, text)

    logfilename = seqfile + '.%s.log' % format if witness == '' else witness

    '''
        2. Call ABS CSeq and save the sequentialised file
    '''
    if donotsequentialize is False:
        if verbose:
            print("\ninput:  %s") % (inputfile)
        dirname = os.path.dirname(__file__)

        # 构造命令行
        cmdline = '/home/dell/anaconda3/envs/py27/bin/python2.7 {} -i {} -b {}  --RespCount {} -e {} -r {}'.format(
            abs_invoker_path,
            inputfile,  
            format,
            RespCount,
            label,
            round
        )   
        # print("Translator path:", translator)
        # print("Command line:", cmdline)
        if debug:
            cmdline += ' -D'
        if loopAbs: # add by zy, loop abstraction
            cmdline += ' --loopAbs'
        if ignore_masking:
            cmdline += ' --ignore-masking'
        # p = subprocess.Popen(shlex.split(cmdline), stdout=subprocess.PIPE)
        # 调用 abs_invoker.py，设置工作目录
        p = subprocess.Popen(
            shlex.split(cmdline),
            cwd=abs_invoker_dir,  # 设置 abs_invoker.py 的工作目录
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        out, err = p.communicate()
        cseqanswer = p.returncode
        # print("Standard Output:\n", out.decode())
        # print("Standard Error:\n", err.decode())
        # print("Return Code:", cseqanswer)

        if verbose:
            print "cmd:    " + cmdline

        ''' now check that the sequentialisation went fine '''
        if cseqanswer != 0:
            if err:
                print(err.decode() if hasattr(err, 'decode') else err)
            if out:
                print(out.decode() if hasattr(out, 'decode') else out)
            if verbose:
                print "\n   unable to sequentialise input file\n"
            if verbose:
                print utils.colors.YELLOW + "        UNKNOWN\n" + utils.colors.NO
            # printStats(seqfile, 'REJECT', -1)
            printStats(logfilename, 'UNKNOWN', -1)
            sys.exit(1)
        else:
            print('abs_invoker.py: The sequential file was successfully generated\n')
    else:
        seqfile = oldinputfile
        cmdLineOptions[format] = cmdLineOptionsNOSEQ[format]

    '''
        3. Run the verification tool
        (from the command-line option -b) on the sequentialised file
    '''
    if verbose:
        print "output: %s" % (seqfile)
    timeBeforeCallingBackend = time.time()    # save wall time
    outputextra = ''
    if format == 'cpachecker':
        if extra == '':
            extra = 'predicateAnalysis'
            # extra = 'config /home/dell/zyworkspace/CPAchecker-4.0/config/components/kInduction/kInduction.properties'
        if outputcounterexample:
            # outputextra = ' -outputpath output'
            outputextra = '--output-path'
        else:
            # outputextra = ' -noout' # add by zy
            outputextra = ' --no-output-files'
        outputextra += ' --timelimit %s ' % timelimit

    '''
        Preprocess for LLBMC
    '''

    if format == 'llbmc':
        llvmcmd = ''
        # Check for clang version
        if clangpath == '':
            try:
                output = subprocess.check_output("which clang", shell=True)
            except subprocess.CalledProcessError:
                usage('', 'error: llbmc require clang version 3.3 installed in the system')
                sys.exit(2)
            try:
                output = subprocess.check_output("clang --version", shell=True)
                if 'version 3.3' not in output:
                    print 'error: the version of clang in the system does not match llbmc requirement (require version 3.3)'
                    sys.exit(2)
                else:
                    llvmcmd = "clang -c -g -emit-llvm %s -o %s" % (seqfile, seqfile[:-2] + '.bc')
            except subprocess.CalledProcessError:
                pass   # supress error
        else:
            llvmcmd = "%s -c -g -emit-llvm %s -o %s" % (clangpath, seqfile, seqfile[:-2] + '.bc')

        # Run command line
        if verbose:
            print "clangcmd:    %s\n" % llvmcmd
        command = utils.Command(llvmcmd)
        out, err, code = command.run(timeout=864400)
        seqfile = seqfile[:-2] + '.bc'

    if format == 'cbmc':
        outputextra += '--unwind %s ' % unwind

    if format == 'esbmc':
        outputextra += '--unwind %s ' % unwind

    if format == 'llbmc':
        outputextra += ' --max-loop-iterations=%s' % unwind

    if format == 'uautomizer' or format == 'ukojak':
        if extra == '':
            # outputextra = ' precise '
            outputextra = ''

    if format == 'seahorn':
        if extra == '':
            outputextra = ' no_inline '

    # verification
    cmdline = path + cmdLineOptions[format] + extra + outputextra + ' ' + seqfile
    print("Run the backend to perform the analysis:")
    print(cmdline)

    if verbose:
        print "log:    %s\n" % (logfilename)
    if verbose:
        print "cmd:    " + cmdline
    if verbose:
        print "start:  %s\n" % (strftime("%Y-%m-%d %H:%M:%S", gmtime()))

    # verification
    command = utils.Command(cmdline)

    currentpath = os.getcwd()
    currentdir = os.path.dirname(__file__)
    if format == 'uautomizer':
        # os.chdir(currentdir + '/backends/UAutomizer_linux/')
        currentdir = os.path.dirname(os.path.abspath(__file__))
        os.chdir(os.path.join(currentdir, 'backends', 'UAutomizer_linux'))
    if format == 'ukojak':
        os.chdir(currentdir + '/backends/UKojak/')
    if format == 'seahorn':
        os.chdir(currentdir + '/backends/SeaHorn/bin')
    if format == 'vvt':
        os.chdir(currentdir + '/backends/vvt/bin')

    # verification
    out, err, code = command.run(timeout=timelimit)
    # print "RETURN VALUE: <%s>" % code

    # Go back to current path
    os.chdir(currentpath)

    # verification
    utils.saveFile(logfilename, err + out) 

    print("Analysis result:")
    # report analysis details
    if os.path.isfile(logfilename):
        myfile = open(logfilename)
        backendAnswer = list(myfile)

        outcome = ''
        mem = maxmem = cpu = stale = variables = clauses = 0

        for line in backendAnswer:
            if ' variables, ' in line:
                splitline = line.split()
                variables = splitline[0]
                clauses = splitline[2]

        backendtime = time.time() - timeBeforeCallingBackend
        overalltime = time.time() - realstarttime

        if verbose:
            print "size:   %s variables" % variables
            print "        %s clauses" % clauses
            # print ""
            # print "space:  %s " % mem
            # print "        %s peak" % maxmem
            print ""
            print "time:   %0.2fs preprocess" % (timeBeforeCallingBackend - realstarttime)
            print "        %0.2fs backend" % (backendtime)
            print "        %0.2fs overall" % (overalltime)
            print ""

            if 'warning' in err:
                print utils.colors.YELLOW + "       (warnings on stderr from the backend)" + utils.colors.NO

        # scan the backend's output to check the outcome of the verification
        for line in backendAnswer:
            if verificationFAIL[format] in line:
                if verbose:
                    print utils.colors.RED + "        FALSE" + utils.colors.NO
                outcome = 'FALSE'
                break
            elif verificationOK[format] in line:
                if verbose:
                    print utils.colors.GREEN + "        TRUE" + utils.colors.NO
                outcome = 'TRUE'
                break

        if outcome == '' and code == -9:  # backend killed due to timeout
            if verbose:
                print utils.colors.YELLOW + "        TIMEOUT" + utils.colors.NO
            outcome = 'TIMEOUT'

        if outcome == '':
            if verbose:
                print utils.colors.YELLOW + "        UNKNOWN" + utils.colors.NO
            outcome = 'UNKNOWN'

        if verbose:
            print ''

        if not verbose:
            verdict = ''
            if outcome == 'UNKNOWN':
                verdict = utils.colors.BLUE + '--' + utils.colors.NO
            elif ('_false' in inputfile or '_unsafe' in inputfile) and outcome == 'TRUE':
                verdict = utils.colors.RED + 'ko' + utils.colors.NO
            elif ('_true' in inputfile or '_safe' in inputfile) and outcome == 'FALSE':
                verdict = utils.colors.RED + 'ko' + utils.colors.NO
            else:
                verdict = utils.colors.GREEN + 'ok' + utils.colors.NO
            # print "%s, %s, %s, %2.2f" % (verdict, outcome, logfilename, overalltime)
            printStats(inputfile, outcome, overalltime)

    if outputcounterexample:
        with open(logfilename) as file:
            data = file.read()
            print data
            # Save counter example file
            # utils.saveFile('___12_cex.log', data)

    end_time = time.time()
    elapsed = end_time - start_time
    # 稍微等监控线程采集
    time.sleep(0.2)
    # print("\n[Resource] Total running time: %.2f seconds" % elapsed)
    print("[Resource] Peak memory usage: %.2f MB" % peak_mem_mb[0])

if __name__ == '__main__':
    main(sys.argv[0:])
