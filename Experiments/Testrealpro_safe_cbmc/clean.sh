#!/bin/bash

find . -name '*_result' | xargs rm -rf
find . -name '*.out' | xargs rm -f
find . -name '*time.txt' | xargs rm -f
find . -name '*var.txt' | xargs rm -f
find . -name '_mt_main_n.c' | xargs rm -f
find . -name '*.log' | xargs rm -f
find . -name '_cseq_main_n.c' | xargs rm -f
find . -name '_cseq_main.c' | xargs rm -f

echo "Cleanup completed successfully."