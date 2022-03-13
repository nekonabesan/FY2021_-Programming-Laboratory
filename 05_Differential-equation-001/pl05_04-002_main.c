#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#define MAX 400

double f(double t) {
    return t;
}

double g(double t) {
    return exp(t);
}

/**
 * 例題4(2次ルンゲクッタ法)
 * 例題３で作成したプログラムを相対誤差Δxを出力するように変更する
 * 数値積分の間隔はdt=0.1, 0.025として、t=10まで計算する
 * 時間があれば時間刻みを変更して誤差の振る舞いを確認する
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double dx = 0.0;
    double t = 0.0;
    double dt = 0.025;
    double k_1 = 0.0;
    double k_2 = 0.0;
    const char *path = "data/pl05_04-002.csv";


    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    // ルンゲクッタ法による数値解の導出
    dx = fabs((x - exp(t))/exp(t));
    fprintf(tmp_file, "%lf,%.20f,%.20f,%.20f\n", t, x, exp(t),dx);
    for (unsigned int i = 0; i <= MAX; i++) {
        x += k_2;
        k_1 = dt * f(x);
		k_2 = dt * f(x + (k_1 * 0.5));
        dx = fabs((x - g(t))/g(t));
        fprintf(tmp_file, "%lf,%.20f,%.20f,%.20f\n", t, x, exp(t),dx);
        t += dt;
    }

    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}