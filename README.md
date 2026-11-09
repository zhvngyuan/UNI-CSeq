# UNI-CSeq  |  C-to-C Sequentialization Tool for Interrupt-Driven Programs  #

## Package contents ##

| Name             | Description                                   |
| :--------------  | :-------------------------------------------- |
| README           | this file                                     |
| uni-cseq.py      | uni-cseq wrapper script                       |
| unichecker.py    | unichecker wrapper script                     |
| include/*        | include header files                          |
| bin/*.py         | module files                                  |
| modules/*.py     | module files                                  |
| examples/*       | example C with PThreads files                 |
| Experiments/*    | benchmark programs and experimental results   |
| backends/*       | supported backends                            |
| run_scripts/*.sh | batch experiment scripts                      |

## Installation ##
To install UNI-CSeq, please follow the steps below:

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
    python3 unicseq.py  -i<input_file> <options>
```
For more details, please launch the tool with the  `--help` option.

## Cite ##
Bibtex 
```
@article{zhang2027unicseq,
  title={UNI-CSeq: A tool for interrupt-driven program verification and falsification},
  author={Zhang, Yuan and Xu, Ying and Watanabe, Masahiko and Kong, Weiqiang},
  journal={Science of Computer Programming},
  volume={257},
  pages={103583},
  year={2027},
  publisher={Elsevier},
  issn = {0167-6423},
  doi = {https://doi.org/10.1016/j.scico.2026.103583},
  url = {https://www.sciencedirect.com/science/article/pii/S0167642326001498}
}
```
