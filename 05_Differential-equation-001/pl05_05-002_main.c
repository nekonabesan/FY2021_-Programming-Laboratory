#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#define N 10.0
#define MAX 10.0

double f(double t) {
    return t;
}

double g(double t) {
    return exp(t);
}

/**
 * 例題5
 * 以下の常微分方程式を4次ルンゲクッタ法で解くプログラムを作成する
 * 数値積分の間隔はdt=0.1として、t=10まで計算する
 * 計算して得られた値の相対誤差を求める
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double d_x = 0.0;
    double t = 0.0;
    double dt = 0.0;
    double k_1 = 0.0;
    double k_2 = 0.0;
    double k_3 = 0.0;
    double k_4 = 0.0;
    const char *path = "data/pl05_05-002.csv";


    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    dt = f(t) + f((t + 1/N));
    printf("%lf\n", dt);

    while ((FLT_EPSILON  * fmax(1, fmax(fabs(MAX), fabs(t)))) < fabs(MAX - t)) {
        k_1 = dt * f(x);
		k_2 = dt * f(x + k_1/2.0);
		k_3 = dt * f(x + k_2 / 2.0);
		k_4 = dt * f(x + k_3);
		x = (x + (k_1 + 2.0 * k_2 + 2.0 * k_3 + k_4) / 6.0);
        t += dt;
        d_x = fabs((x - g(t))/g(t));
        //printf("%.20f\n", d_x);
        fprintf(tmp_file, "%lf,%.20f\n", t, d_x);
    }

    // 一時ファイルを閉じる
    fclose(tmp_file);

    printf("%lf\n", x);

    return true;
}