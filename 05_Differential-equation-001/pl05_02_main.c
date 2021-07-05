#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


#define N 40.0
#define MAX 10.0

/**
 * 例題2
 * 例題１で作成したプログラムのタイムステップを
 * dt=0.025に変更した数値積分を行い、dt=0.1の結果と比較する。
 * 時間があればタイムステップと計算終了時間を変更して
 * 誤差の変化を確認する。
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double t = 0.0;
    double dt = 0.0;
    const char *path = "data/pl05_02.csv";

    dt = 1/N;
    printf("N : %lf\n", dt);

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    while (t < MAX) {
        t += dt;
        x += (x * dt);
        //printf("%lf %lf\n", t, x);
        fprintf(tmp_file, "%lf,%lf\n", t, x);
    }
    
    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}