#!/home/dell/anaconda3/envs/py27/bin/python2.7
#coding=utf-8
# ------------------------------------------------------------------------------
# NAME = abs_invoker
# -----------------------------------------------------------------------------
# VERSION = 0.2
# -----------------------------------------------------------------------------
# Description:
#   - This file invokes the translator for concurrent C program and to transform it into a
#     sequentialized file that can be verified by chosen backend
#
# TODO:
#
# Changelog:
#   2016.05.05   Add UAutomizer and UKojak as proving correctness backends
# -----------------------------------------------------------------------------

import json
from pathlib2 import Path
import pickle
import sys
import getopt
import importlib
import traceback
import os.path
import time
import collections
import dataType

from pycparser.plyparser import ParseError
from abs_module import ModuleError
import utils

import sys
sys.path.insert(0, '/home/dell/zyworkspace/unichecker/modules')
from LoopAbstraction import LoopAbstraction
from instrumenter import instrumenter




FRAMEWORK_VERSION = '0.2'


class ABSEnvironment:
    errorlabel = ''
    backend = ''
    threads = 3       # Auto
    debug = False
    round = 0

    loopAbs = False
    transforms = 0
    paramvalues = {}

    ISR_num = 0  # add by zy 记录中断服务历程的数量

    RespCount = 1 # add by zy 默认每个中断服务历程最多执行1次

    switch_goto = False  # Use switch+goto optimization instead of Res/Exe/Sus mode

    ignore_masking = False  # skip encoding disable_isr/enable_isr flag assignments


def _fileToString(filename):
    inputfile = open(filename)
    string = inputfile.read()
    inputfile.close()
    return string


def searchFunc(inputfile):
    # 输入源程序路径
    # 搜索中断函数名，返回中断函数及优先级
    funcInfo = collections.OrderedDict()  # 存储函数信息
    source = open(inputfile, "r")
    lines = (source.read()).split('\n')

    q = 0
    while q < len(lines):
        if lines[q].strip().startswith('//'):
            q += 1
            continue
        if lines[q].strip().startswith('/*'):
            while not lines[q].strip().endswith('*/'):
                q += 1
            q += 1
            continue

        if lines[q].strip().find('//') != -1 and lines[q].find("priority") == -1:
            lines[q] = lines[q][:lines[q].find('//')]

        # 检测中断函数定义
        if ((lines[q].find('interrupt') != -1 or lines[q].find('ISR') != -1 or lines[q].find('isr') != -1) and
                lines[q].find(';') == -1 and lines[q].find('*') == -1 and lines[q].find('void') != -1):
            # 中断函数定义，解析函数名和优先级
            isMt = False
            name = lines[q][lines[q].find('d') + 2:lines[q].find('(')].strip()
            if lines[q - 1].find("priority") != -1:
                # 如果上一行包含优先级信息，则解析优先级
                funcInfo[name] = dataType.isrInfo("random")
                index = lines[q - 1].strip().rfind(" ") + 1
                funcInfo[name].prio = int(lines[q - 1][index:].strip())

        q += 1
    return funcInfo

def getISRandPrio(inputfile):
    # 获取 abs_invoker.py 所在目录的绝对路径
    current_dir = os.path.dirname(os.path.abspath(__file__))

    # 设置 FuncInfo 和 data.json 的绝对路径
    output_dir = os.path.join(current_dir, "FuncInfo")
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)  # 自动创建目录

    dictfile_path = os.path.join(output_dir, "dictfile")
    json_file_path = os.path.join(current_dir, "data.json")

    # 搜索中断函数并生成 funcInfo
    funcInfo = searchFunc(inputfile)

    # 将 funcInfo 写入 dictfile
    with open(dictfile_path, 'wb') as dictfile:
        pickle.dump(funcInfo, dictfile)

    # 读取 dictfile 内容
    with open(dictfile_path, 'rb') as dictfile:
        isrdict = pickle.load(dictfile)

    # 生成 JSON 数据
    data = {isr: isr_info.prio for isr, isr_info in isrdict.items()}
    data['main_task'] = 0

    # 保存 JSON 数据到文件
    with open(json_file_path, 'w') as f:
        json.dump(data, f, indent=4)

    # print("Generated data.json at:", json_file_path)  # 调试信息
    return data

    # # 获取优先级和函数信息
    # funcInfo = searchFunc(inputfile)

    # # 确保目录存在
    # output_dir = Path("./FuncInfo")
    # output_dir.mkdir(parents=True, exist_ok=True)  # 自动创建目录

    # # 使用 output_dir 拼接 dictfile 的路径
    # dictfile_path = output_dir / "dictfile"

    # with open(str(dictfile_path), 'wb') as dictfile:
    #     pickle.dump(funcInfo, dictfile)

    # # 解析 dictfile_path 中的内容
    # with open(str(dictfile_path), 'rb') as dictfile:
    #     isrdict = pickle.load(dictfile)  # 加载文件内容

    # # 数据的目标字典
    # data = {}
 
    # # 从 isrdict 中提取信息，添加到 data 字典
    # for isr, isr_info in isrdict.items():
    #     data[isr] = isr_info.prio

    # # 添加 main_task 键值对
    # data['main_task'] = 0

    # # 将 data 转换为 JSON 文件
    # with open('data.json', 'w') as f:
    #     json.dump(data, f, indent=4)  # 保存为 JSON 文件，格式化输出

    # return data

def usage(cmd, errormsg):
    print "ABS-CSeq   |   C-to-C sequentialiser"
    print "           |   October 2014"
    print ""
    print "Usage: "
    print ""
    print "   %s -i [input.c] [options]" % cmd
    print ""
    print "   options: "
    print "   -h, --help                 display this help screen"
    print "   -D, --debug                debug mode"
    print "   -M  --modules              only list the modules then quit"
    print "   -E  --exit <module>        show the output from module and quit"
    print ""
    print "   -i<file>, --input=<file>   input filename"
    print "   -o<filename>, --output=<filename>  output filename"
    print "   -b<fmt>, --backend=<fmt>   backend"
    print "   -r<X>, --round=<X>         static main driver unwinding (default: 0)"
    print "   -t<X>, --threads<X>        max number of threads (default: auto)"
    print "   -e<X>, --error-label<X>    error label to check reachability for (default: ERROR)"
    print " --RespCount=<X>              count of interrupt responses to monitor (default: 1)" # add by zy
    print " --loopAbs                    enable loop abstraction (default: False)"# add by zy
    print " --switch-goto                use switch+goto optimization instead of Res/Exe/Sus mode (default: False)"
    print " --ignore-masking             ignore interrupt masking encoding (default: off)"
    print ""
    if errormsg:
        print errormsg + '\n'
    sys.exit(1)


moduleNames = [
    'abs_preprocessor',
    'abs_simplifier',
    'abs_switchconversion',
    'abs_loopconversion',
    'abs_jumpconversion',
    'abs_atomicitizer',
    'abs_extractor',
    'abs_varnames',
    'abs_inliner',
    'abs_unroller',
    'abs_threadduplicator',
    'LoopAbstraction', 
    'abs_sequentializer_toC'
]

def main(args):
    cmd = args[0]
    try:
        shortargs = "hi:o:b:t:e:DME:vr:irqc:"
        longargs = ["help", "input=", "output=", "backend=", "threads=",
                    "error-label=", "debug", "modules",
                    "round=", "exit=", "version", "--output-json=", "SVP", "RespCount=", "loopAbs", "switch-goto", "ignore-masking"]
        opts, args = getopt.getopt(sys.argv[1:], shortargs, longargs)
    except getopt.GetoptError, err:
        usage(cmd, 'error: ' + str(err))

    # Set default conversion parameters
    inputfile = outputfile = ''
    format = 'cpachecker'
    label = 'ERROR'
    threads = 3
    debug = False
    exit = ''
    round = 0
    # 添加新参数变量
    output_json = ''
    loopAbs = False #True  # add by zy 添加循环抽象LoopAbstraction的开关，默认值为 False
    svp = False
    ISR_num = 0
    RespCount = 1
    switch_goto = False  # Use switch+goto optimization
    ignore_masking = False

    # Set conversion parameters & options from command-line
    for o, a in opts:
        if o in ("-v", "--version"):
            print FRAMEWORK_VERSION
            return
        elif o in ("-h", "--help"):
            usage(cmd, '')
        elif o in ("-D", "--debug"):
            debug = True
        elif o in ("-M", "--modules"):
            print moduleNames
            return
        elif o in ("-E", "--exit"):
            exit = a
        elif o in ("-i", "--input"):
            inputfile = a
        elif o in ("-r", "--round"):
            round = int(a)
        elif o in ("-o", "--output"):
            outputfile = a
        elif o in ("-b", "--backend"):
            format = a
        elif o in ("-t", "--threads"):
            threads = int(a)
        elif o in ("-e", "--error-label"):
            label = a
        elif o in ("--output-json"):
            output_json = a
        elif o == ("--SVP"):
            svp = True
        elif o == ("--RespCount"):
            RespCount = int(a)
        elif o in ("--loopAbs"):
            loopAbs = True
        elif o in ("--switch-goto"):
            switch_goto = True
        elif o in ("--ignore-masking"):
            ignore_masking = True
        else:
            assert False, "unhandled option"

    # Check parameters
    if inputfile == '':
        usage(cmd, 'error: input file name not specified')
    if not os.path.isfile(inputfile):
        usage(cmd, 'error: unable to open input file (%s)' % inputfile)
    if format not in ('cpachecker', 'cbmc', 'esbmc', 'llbmc', '2ls', 'uautomizer', 'ukojak'):
        usage(cmd, 'error: output format (%s) not supported' % format)

    
    data = getISRandPrio(inputfile)
    # 获取 abs_invoker.py 所在目录
    current_dir = os.path.dirname(os.path.abspath(__file__))
    json_file_path = os.path.join(current_dir, "data.json")

    # 读取 data.json 并统计键的数量
    with open(json_file_path, 'r') as f:
        data = json.load(f)
    ISR_num = len(data.keys())

    # Assign value to the environment
    ABSEnvironment.errorlabel = label
    ABSEnvironment.backend = format
    ABSEnvironment.debug = debug
    ABSEnvironment.threads = threads
    ABSEnvironment.round = round

    ABSEnvironment.loopAbs = loopAbs

    ABSEnvironment.ISR_num = ISR_num
    ABSEnvironment.RespCount = RespCount
    ABSEnvironment.switch_goto = switch_goto
    ABSEnvironment.ignore_masking = ignore_masking

    # Output file for sequentialization
    dirname, filename = os.path.split(os.path.abspath(inputfile))
    if outputfile == '':
        outputfile = dirname + '/_cseq_' + format + '_' + filename
    if outputfile.endswith('.i'):
        outputfile = outputfile[:-2] + '.c'

    # Transform file to source code for processing
    sourcecode = _fileToString(inputfile)

    if debug:
        utils.saveFile('___00_original.c', sourcecode)



    transforms = 1
    for index, moduleName in enumerate(moduleNames):      
        try:
            mod = importlib.import_module(moduleName)
            timeBefore = time.time()
            if debug:
                print "/* " + moduleName,
            func = getattr(mod, moduleName[0:5].upper() + moduleName[5:])
            m = func()

            # module-specific handling of the input
            m.loadfromstring(sourcecode, ABSEnvironment)

            if moduleName == exit:
                print m.string()
                m.Parser.ast.show()
                m.Parser.printsymbols()
                return

            sourcecode = m.string()
            if debug:
                utils.saveFile('___%s_%s.c' % (str(transforms).zfill(2), moduleName), sourcecode)
            if debug:
                print "[%s] ok %0.2fs */" % (transforms, int(time.time()) - int(timeBefore))
            transforms += 1
        except ParseError as e:
            print "\nParse error (%s) while performing %s->%s:\n" % (
                str(e), moduleNames[index - 1] if index > 0 else '', moduleName)
            sys.exit(1)
        except ModuleError as e:
            print "Module error (%s) while performing %s->%s.\n" % (
                str(e), moduleNames[index - 1] if index > 0 else '', moduleName)
            sys.exit(1)
        except KeyboardInterrupt as e:
            print "\nInterrupted by user.\n"
            sys.exit(1)
        except ImportError as e:
            print "Import error (%s),\nplease re-install the tool.\n" % str(e)
            sys.exit(1)
        except:
            print "\nError while performing %s->%s:\n" % (
                moduleNames[index - 1] if index > 0 else '', moduleName)
            print "ERROR: %s */\n" % sys.exc_info()[0]
            traceback.print_exc(file=sys.stdout)
            # print "\n\n parsing coords: <%s>" % (m.Parser.currentInputCoord)
            sys.exit(1)
    # Save file for processed by backend
    utils.saveFile(outputfile, sourcecode)

if __name__ == "__main__":
    # main(sys.argv[0:])
    try:
        main(sys.argv[0:])
        sys.exit(0)  # 正常退出
    except Exception as e:
        print("Error in abs_invoker.py:", str(e))
        sys.exit(1)  # 异常退出
