/*
まずは連続するデータをベクトルとして取得して比較するプログラムを作成
非可逆の手順
比較するベクトルを要素ごとに比較できるようにする
*/
#include<stdio.h>

#define BLOCK_PATH "../sim/block.bin"
#define CODEBOOK_PATH "../sim/codebook.bin"
#define ELEMENT_NUM 4



int element_num = ELEMENT_NUM;
int same_element_num = 0;
int diff_element_num = 0;
unsigned char data1[ELEMENT_NUM];
unsigned char data2[ELEMENT_NUM];
char block[] = BLOCK_PATH;
char codebook[] = CODEBOOK_PATH;
FILE *block_fp, *codebook_fp;

int main(void){
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
	//ファイルサイズを取得
	fseek(codebook_fp, 0, SEEK_END);
	int representative_vector_num = ftell(codebook_fp)/element_num;
	printf("代表ベクトルは%d個\n", representative_vector_num);
	fseek(codebook_fp, 0, SEEK_SET);
	
	//g個のベクトルを比較
	for(int g = 0; g < 2; g++){
	fseek(codebook_fp, 0, SEEK_SET);
	//ベクトルを２つ読み込み
	fread(data1, sizeof(char), element_num, block_fp);
	//マップから読み込んだベクトルを端末に表示
	printf("data1: ");
	for(int i = 0; i < element_num; i++)
		printf("%02x ", data1[i]);
	//h個の代表ベクトル
	for(int h = 0; h < representative_vector_num; h++){
		same_element_num = 0;
		diff_element_num = 0;
		fread(data2, sizeof(char), element_num, codebook_fp);
	//代表ベクトルを端末に表示
		printf("\n%d個目の代表ベクトル: ", h+1);
		for(int i = 0; i < element_num; i++)
			printf("%02x ", data2[i]);
	//h番目の代表ベクトルと比較
		for(int i = 0; i < element_num; i++){
			if(data1[i] == data2[i]){
				same_element_num++;
			}else{
				diff_element_num++;
			}
		}
		if(diff_element_num <= 0){
			printf("\n符号帳の%d番目の代表ベクトルと一致\n\n", h + 1);
			break;
		}
	//どれくらい違ったかを記述（距離を測るのに使う）
		//printf("同じ要素は%d個\n", same_element_num);
		//printf("違う要素は%d個\n\n", diff_element_num);
	}
	}
	
	fclose(block_fp);
	fclose(codebook_fp);
	return 0;
}
