// SPDX-FileCopyrightText: 2024 Yuichiro Hatanaka
// SPDX-License-Identifier: BSD-3-Clause

#ifndef __RESTORE_H__
#define __RESTORE_H__

#include<stdio.h>

int restore(char codebook[], char vq[], char restore[], int width, int height, int start, int rowElem, int colElem, char reData[], int row, int relength);

#endif
