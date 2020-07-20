#!/bin/bash

python scripts/cpplint.py --headers=hpp $1 || scripts/test_compile.sh && valgrind --leak-check=full --show-leak-kinds=all --log-file=vlog.txt --track-origins=yes -v ./build/test_fastmatch && tail vlog.txt