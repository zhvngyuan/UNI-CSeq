#!/bin/sh

find . -name '*_result' | xargs rm -rf
find . -name '*.out' | xargs rm -f
find . -name '*time.txt' | xargs rm -f
find . -name '*var.txt' | xargs rm -f
find . -name '_mt_*.c' | xargs rm -f
find . -name '*.log' | xargs rm -f
find . -name '_cseq_*.c' | xargs rm -f
find . -name '_cs_*.c' | xargs rm -f