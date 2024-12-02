# vector_distance
ベクトル間の距離を各要素の違いをもとに定義するC言語でプログラムしたリポジトリです

## 使用方法
- パッケージを入手
```
git clone https://github.com/YuichiroHatanaka/vector_distance.git
```
- 移動
```
cd vector_distance/src/
```
- 下記のコマンドでコンパイル  
```
gcc irreversible.c restore.c -o out -I ../include/
```
- 実行
```
./out
```
## 各自変更する場所
- ベクトルの許容範囲
  - もとのベクトルの要素が代表ベクトルとどれだけ違うかを下記のパラメータで変更
  - 後で追記します

- マップと結果を格納するディレクトリ
   - 複数の結果を見たい場合は下記の部分を変更するといい
   - 後で追記します
 
## ライセンス
- このソフトウェアパッケージは, 3乗降BSDライセンスの下, 再頒布および仕様が許可されます.
- © 2024 Yuichiro Hatanaka
