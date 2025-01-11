// SPDX-FileCopyrightText: 2024 Yuichiro Hatanaka
// SPDX-License-Identifier: BSD-3-Clause

/*
まずは連続するデータをベクトルとして取得して比較するプログラムを作成
非可逆の手順
比較するベクトルを要素ごとに比較できるようにする
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vq/restore.h>

#define UP_DIR "../"
#define DIR_NAME "sim16"
#define BLOCK_FILE "/block.bin"
#define DIRECTORY_PATH "/ir"
#define IVQ "/irreversible_vq.bin"
#define IRE "/irreversible_restore.pgm"
#define CODEBOOK_FILE "/codebook_freq.bin"
#define ELEMENT_NUM 16



unsigned char element_num = ELEMENT_NUM;
int same_element_num = 0;
int diff_element_num = 0;
unsigned char data1[ELEMENT_NUM];
unsigned char data2[ELEMENT_NUM];
char block[100];
char codebook[100];
char vq[100];//= VQ_PATH;
FILE *block_fp, *codebook_fp, *vq_fp;
unsigned short cnt = 0;
unsigned char rep_mum = 0;
//restore
char re[100];// = RESTORE_MAP_PATH;
char reData[15] = {0x50, 0x35, 0x0A, 0x33, 0x38, 0x34, 0x20, 0x34, 0x34, 0x34, 0x0A, 0x32, 0x35, 0x35, 0x0A};
int col = 384;
char relength = sizeof(reData);
int vector_distance = 0;


int main(int argc, char *argv[]){
	//引数を確認
	vector_distance = atoi(argv[1]);
	strcat(vq, UP_DIR);
	strcat(vq, DIR_NAME);
	strcat(vq, DIRECTORY_PATH);
	strcat(vq, argv[1]);
	strcpy(re, vq);
	strcat(vq, IVQ);
	strcat(re, IRE);
	strcat(block, UP_DIR);
	strcat(block, DIR_NAME);
	strcat(block, BLOCK_FILE);
	strcat(codebook, UP_DIR);
	strcat(codebook, DIR_NAME);
	strcat(codebook, CODEBOOK_FILE);
	printf("vq %s\n", vq);
	printf("re %s\n", re);
	printf("許容できるベクトルの違う要素の数は%d\n", vector_distance);

	if((block_fp = fopen(block, "rb")) == NULL){
		perror("ERROR: cannot open block file\n");
		fclose(block_fp);
		return 1;
	}
	if((codebook_fp = fopen(codebook, "rb")) == NULL){
		perror("ERROR: cannot open codebook file\n");
		fclose(block_fp);
		fclose(codebook_fp);
	}
	if((vq_fp = fopen(vq, "w+b")) == NULL){
		perror("ERROR: cannot open vq file\n");
		fclose(block_fp);
		fclose(codebook_fp);
		fclose(vq_fp);
	}
	//ファイルサイズを取得
	fseek(codebook_fp, 0, SEEK_END);
	int representative_vector_num = ftell(codebook_fp)/element_num;
	printf("代表ベクトルは%d個\n", representative_vector_num);
	fseek(codebook_fp, 0, SEEK_SET);
	
	//ブロックの数を取得
	fseek(block_fp, 0, SEEK_END);
	int block_num = ftell(block_fp)/element_num;
	printf("ブロック数は%d個\n", block_num);
	fseek(block_fp, 0, SEEK_SET);

	//g個のベクトルを比較
	for(int g = 0; g < block_num; g++){
		fseek(codebook_fp, 0, SEEK_SET);
		//ベクトルを２つ読み込み
		fread(data1, sizeof(char), element_num, block_fp);
		//マップから読み込んだベクトルを端末に表示
		//printf("data1: ");
		//for(int i = 0; i < element_num; i++)
		//	printf("%02x ", data1[i]);
		//h個の代表ベクトル
		for(cnt = 0; cnt < representative_vector_num; cnt++){
			same_element_num = 0;
			diff_element_num = 0;
			fread(data2, sizeof(char), element_num, codebook_fp);
		//代表ベクトルを端末に表示
		//	printf("\n%d個目の代表ベクトル: ", cnt + 1);
		//	for(int i = 0; i < element_num; i++)
		//		printf("%02x ", data2[i]);
		//h番目の代表ベクトルと比較
			for(int i = 0; i < element_num; i++){
				if(data1[i] == data2[i]){
					same_element_num++;
				}else{
					diff_element_num++;
				}
			}
			if(diff_element_num <= vector_distance){
				printf("符号帳の%03d番目の代表ベクトルと一致\n", cnt + 1);
				//新しいコードブックを作成
				fwrite(&cnt, sizeof(short), 1, vq_fp);
				break;
			}
		}
	}
	fclose(block_fp);
	fclose(codebook_fp);
	fclose(vq_fp);
	
	restore(codebook, vq, re, 384, 444, 15, 4, 4, reData, col, relength);
	return 0;
}
