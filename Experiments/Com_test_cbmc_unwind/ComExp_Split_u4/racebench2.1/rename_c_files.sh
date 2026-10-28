#!/bin/bash

BASE_DIR="/home/dell/zyworkspace/unichecker/Experiments/racebench2.1"
REALWORLD_DIRS="$BASE_DIR/testdirs.sh"

# 检查 testdirs.sh 是否存在
if [ ! -f "$REALWORLD_DIRS" ]; then
    echo "Error: $REALWORLD_DIRS not found."
    exit 1
fi

source "$REALWORLD_DIRS"

for DIR in $TEST_DIRS
do
    SUBDIR="$BASE_DIR/$DIR"
    # 查找该子目录下所有 .c 文件
    for f in "$SUBDIR"/*.c; do
        [ -e "$f" ] || continue # 如果没有.c文件则跳过
        fname=$(basename "$f")
        new_name="$SUBDIR/$DIR.c"
        if [ "$f" != "$new_name" ]; then
            echo "重命名 $f -> $new_name"
            mv "$f" "$new_name"
        fi
    done
done

echo "Done!"