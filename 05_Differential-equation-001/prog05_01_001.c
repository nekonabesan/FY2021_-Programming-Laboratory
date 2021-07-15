#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

double f(double t) {
    return t;
}

double g(double t) {
    return exp(t);
}

/** 
 * 例題２で作成したプログラム（タイムステップ： ，
 * および ）において， 計算終了時間をt=2,4,6,8,10
 * と変更した際の相対誤差 （次ページ参照）の変化を確認せよ．
 * なお，値は指数関数表記とし，仮数部は⼩数点以下第６位までとする．
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double t = 0.0;
    double dt = 0.0;
    double d_x = 0.0;
    double max = 0.0;
    const char *path = "data/prog05_01_001.csv";
    double list_dt[2] = {0.1, 0.025};
    double list_time[5] = {2.0, 4.0, 6.0, 8.0, 10.0};

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    for (unsigned int i = 0; i < 2; i++) {
        dt = list_dt[i];
        for (unsigned int j = 0; j < 5; j++) {
            max = list_time[j];
            while ((FLT_EPSILON  * fmax(1, fmax(fabs(max), fabs(t)))) < fabs(max - t)) {
                //printf("%6f,%6f,%6f,%6f,%6f,\n", dt, max, t, x, exp(t));
                t += dt;
                x += (x * dt);
            }
            d_x = fabs((x - g(t))/g(t));
            //printf("%6f,%6f,%6f,%6f\n", dt, max, t, y);
            fprintf(tmp_file, "%.6f,%.6f,%.20f,%.20f,%.20f,%.20f\n", dt, max, t, x, exp(t),d_x);
            t = 0.0;
            x = 1.0;
            d_x = 0.0;
        }
    }

    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}