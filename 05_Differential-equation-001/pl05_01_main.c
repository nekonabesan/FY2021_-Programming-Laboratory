#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>



#define N 10.0
#define MAX 10.0

/**
 * 例題1
 * 以下の常微分方程式をオイラー法で解くプログラムを作成する
 * 数値積分の間隔はdt=0.1として、t=10まで計算する
 * また、解析解を求めて数値計算の結果と比較する
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double t = 0.0;
    double dt = 0.0;
    double max = 10.0;
    const char *path = "data/pl05_01.csv";

    dt = 1/N;
    //printf("N : %lf\n", dt);

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    while ((FLT_EPSILON  * fmax(1, fmax(fabs(MAX), fabs(t)))) < fabs(MAX - t)) {
        t += dt;
        x += (x * dt);
        printf("%lf %lf %lf\n", t, x, exp(t));
        fprintf(tmp_file, "%6f,%.6f,%.6f\n", t, x, exp(t));
    }
    
    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}