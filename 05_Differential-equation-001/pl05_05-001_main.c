#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define N 10.0
#define MAX 10.0

double f(double t) {
    return t;
}

double g(double t) {
    return exp(t);
}

bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double d_x = 0.0;
    double t = 0.0;
    double h = 0.0;
    double k_1 = 0.0;
    double k_2 = 0.0;
    double k_3 = 0.0;
    double k_4 = 0.0;
    const char *path = "data/pl05_05-001.csv";


    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    h = f(t) + f((t + 1/N));
    printf("%lf\n", h);

    do {
        k_1 = h * f(x);
		k_2 = h * f(x + k_1/2.0);
		k_3 = h * f(x + k_2 / 2.0);
		k_4 = h * f(x + k_3);
		x = (x + (k_1 + 2.0 * k_2 + 2.0 * k_3 + k_4) / 6.0);
        t += h;
        d_x = (g(t) - x)/g(t);
        fprintf(tmp_file, "%lf,%.20f\n", t, x);
    } while (t < MAX);

    // 一時ファイルを閉じる
    fclose(tmp_file);

    printf("%lf\n", x);

    return true;
}