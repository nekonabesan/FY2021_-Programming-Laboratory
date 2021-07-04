#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define N 40.0
#define MAX 10.0

double f(double t) {
    return t;
}

double g(double t) {
    return exp(t);
}

/**
 * 2次ルンゲクッタ法
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
    const char *path = "data/pl05_04-002.csv";


    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    dt = f(t) + f((t + 1/N));
    printf("%lf\n", dt);

    do {
        k_1 = dt * f(x);
		k_2 = dt * f(x + k_1/2.0);
        x += k_2;
        t += dt;
        d_x = (g(t) - x)/g(t);
        //printf("%.20f\n", d_x);
        fprintf(tmp_file, "%lf,%.20f\n", t, d_x);
    } while (t < MAX);

    // 一時ファイルを閉じる
    fclose(tmp_file);

    printf("%lf\n", x);

    return true;
}