#!/bin/bash
# SPDX-FileCopyrightText: 2024 Yuichiro Hatanaka
# SPDX-License-Identifier: BSD-3-Clause

distance=$1
echo $1
if [ -z "$1" ]; then
distance=0
fi

echo "gcc irreversible.c restore.c -o out -I ../include"
gcc irreversible.c restore.c -o out -I ../include
echo "./out "$distance" > ../sim16/ir$distance/data.log"
./out "$distance" > ../sim16/ir$distance/data.log
echo "cat ../sim16/ir$distance/data.log | grep 一致 | sort | uniq -c > ../sim16/ir$distance/same.log"
cat ../sim16/ir$distance/data.log | grep 一致 | sort | uniq -c > ../sim16/ir$distance/same.log
rm out
