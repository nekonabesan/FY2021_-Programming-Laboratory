#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <float.h>

#define MAX 400

double f(double t) {
    return t;
}

double g(double t) {
    return exp(t);
}

/**
 * 例題5
 * 以下の常微分方程式を4次ルンゲクッタ法で解くプログラムを作成する
 * 数値積分の間隔はdt=0.025として、t=10まで計算する
 * 計算して得られた値の相対誤差を求める
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double dx = 0.0;
    double t = 0.0;
    double dt = 0.025;
    double k_1 = 0.0;
    double k_2 = 0.0;
    double k_3 = 0.0;
    double k_4 = 0.0;
    const char *path = "data/pl05_05-003.csv";


    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    // ルンゲクッタ法による数値解の導出
    dx = fabs((x - g(t))/g(t));
    fprintf(tmp_file, "%6f,%.20f,%.20f,%.20f\n", t, x, exp(t), dx);
    for (unsigned int i = 0; i < MAX; i++) {
        t += dt;
        k_1 = dt * f(x);
		k_2 = dt * f(x + (k_1 * 0.5));
		k_3 = dt * f(x + (k_2 * 0.5));
		k_4 = dt * f(x + k_3);
		x = (x + (k_1 + 2.0 * k_2 + 2.0 * k_3 + k_4) / 6.0);
        dx = fabs((x - g(t))/g(t));
        fprintf(tmp_file, "%6f,%.20f,%.20f,%.20f\n", t, x, exp(t), dx);
    }

    // 一時ファイルを閉じる
    fclose(tmp_file);

    printf("%lf\n", x);

    return true;
}