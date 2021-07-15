#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

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
    double dt = 0.025;
    const char *path = "data/pl05_02.csv";

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    while ((FLT_EPSILON  * fmax(1, fmax(fabs(MAX), fabs(t)))) < fabs(MAX - t)) {
        t += dt;
        x += (x * dt);
        //printf("%lf %lf\n", t, x);
        fprintf(tmp_file, "%6f,%6f,%6f\n", t, x, exp(t));
    }
    
    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}