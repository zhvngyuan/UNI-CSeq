# UL-CSeq  |  C-to-C Sequentialization Tool #

## Package contents ##

| Name        |   Description                         |
| :-----------|--------------------------------------:|
| README      |   this file                           |
| ul-cseq.py  |   ul-cseq wrapper script              | 
| include/*   |   include header files                |
| bin/*.py    |   module files                        |
| examples/*  |   example C with PThreads files       |
| backends/*  |   supported backends                  |

## Installation ##
To install UL-CSeq, please follow the steps below:

1. Install the prerequisites:
    1. Python 2.7+
    2. PYCparser 2.14
    3. Java 1.7+
2. Create a directory, suppose this is called  /workspace
3. Extract the entire package contents in  /workspace
4. Set execution (+x) permissions for *ul-cseq.py* and *bin/abs_invoker.py*
5. Extract each backend in the same path
6. Make sure that the backend's binary is correctly set (presumably) or
   amend the command strings in   *ul-cseq.py*, sect. Options and Parameters,
   accordingly.

## Usage ##
```bash
    ./ul-cseq.py  -i<input_file> -bcpachecker
```
For more details, please launch the tool with the  `--help` option.

