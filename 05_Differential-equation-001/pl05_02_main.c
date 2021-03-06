#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#define MAX 400

/**
 * 例題2
 * 例題１で作成したプログラムのタイムステップを
 * dt=0.025に変更した数値積分を行い、dt=0.1の結果と比較する。
 * 時間があればタイムステップと計算終了時間を変更して誤差の変化を確認する。
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double dx = 0.0;
    double t = 0.0;
    double dt = 0.025;
    const char *path = "data/pl05_02.csv";

    // 計算結果を出力するCSVファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    // オイラー法による数値解の導出
    fprintf(tmp_file, "%6f,%.20f,%.20f,%.20f\n", t, x, exp(t), dx);
    dx = fabs((x - exp(t))/exp(t));
    for (unsigned int i = 0; i < MAX; i++) {
        t += dt;
        x += (x * dt);
        dx = fabs((x - exp(t))/exp(t));
        fprintf(tmp_file, "%6f,%.20f,%.20f,%.20f\n", t, x, exp(t), dx);
    }
    
    // 計算結果を出力するCSVファイルを閉じる
    fclose(tmp_file);

    return true;
}