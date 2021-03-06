#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#define MAX 100

/**
 * 例題1
 * 以下の常微分方程式をオイラー法で解くプログラムを作成する
 * 数値積分の間隔はdt=0.1として、t=10まで計算する
 * また、解析解を求めて数値計算の結果と比較する
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double dx = 0.0;
    double t = 0.0;
    double dt = 0.1;
    double max = 2.0;
    const char *path = "data/pl05_01.csv";

    // 計算結果を出力するCSVファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    // オイラー法による数値解の導出
    dx = fabs((x - exp(t))/exp(t));
    fprintf(tmp_file, "%6f,%.20f,%.20f,%.20f\n", t, x, exp(t), dx);
    printf("%lf, %lf, %lf\n", t, x, dx);
    for (unsigned int i = 0; i < MAX; i++) {
        t += dt;
        x += (x * dt);
        dx = fabs((x - exp(t))/exp(t));
        fprintf(tmp_file, "%6f,%.20f,%.20f,%.20f\n", t, x, exp(t), dx);
        printf("%d, %lf, %lf, %lf\n", i, t, x, dx);
    }
    
    // 計算結果を出力するCSVファイルを閉じる
    fclose(tmp_file);

    return true;
}