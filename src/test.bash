#!/bin/bash
# SPDX-FileCopyrightText: 2024 Yuichiro Hatanaka
# SPDX-License-Identifier: BSD-3-Clause

distance=$1
echo $1
if [ -z "$1" ]; then
distance=0
fi
gcc irreversible.c restore.c -o out -I ../include
./out "$distance" > data.log
rm out
