#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

struct answer {
    unsigned int seq;
    double x;
    double y;
    double t;
    double d_x;
    struct answer *prev;
    struct answer *next;
};

double f(double t) {
    return t;
}

double g(double t) {
    return exp(t);
}

struct answer * euler_method(struct answer *a, double dt, double max){
    double t = 0.0;
    double x = 1.0;
    double d_x = 0.0;

    while ((FLT_EPSILON  * fmax(1, fmax(fabs(max), fabs(t)))) < fabs(max - t)) {
        t += dt;
        x += (x * dt);
    }

    d_x = fabs((x - g(t))/g(t));

    a->x = x;
    a->t = t;
    a->d_x = d_x;

    return a;
}

struct answer * runge_kutta_method_02(struct answer *a, double dt, double max){
    double x = 1.0;
    double d_x = 0.0;
    double t = 0.0;
    double k_1 = 0.0;
    double k_2 = 0.0;
    double k_3 = 0.0;
    double k_4 = 0.0;

    while ((FLT_EPSILON  * fmax(1, fmax(fabs(max), fabs(t)))) < fabs(max - t)) {
        k_1 = dt * f(x);
        k_2 = dt * f(x + k_1/2.0);
        x += k_2;
        t += dt;
    }

    d_x = fabs((x - g(t))/g(t));

    a->x = x;
    a->t = t;
    a->d_x = d_x;

    return a;

}

struct answer * runge_kutta_method_04(struct answer *a, double dt, double max){
    double x = 1.0;
    double d_x = 0.0;
    double t = 0.0;
    double k_1 = 0.0;
    double k_2 = 0.0;
    double k_3 = 0.0;
    double k_4 = 0.0;

    while ((FLT_EPSILON  * fmax(1, fmax(fabs(max), fabs(t)))) < fabs(max - t)) {
        k_1 = dt * f(x);
		k_2 = dt * f(x + k_1/2.0);
		k_3 = dt * f(x + k_2 / 2.0);
		k_4 = dt * f(x + k_3);
		x = (x + (k_1 + 2.0 * k_2 + 2.0 * k_3 + k_4) / 6.0);
        t += dt;
    }

    d_x = fabs((x - g(t))/g(t));

    a->x = x;
    a->t = t;
    a->d_x = d_x;

    return a;
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
    double max = 0.0;
    const char *path = "data/prog05_02_001.csv";
    double list_dt[5] = {0.2, 0.1, 0.05, 0.025, 0.0125};
    double list_time[5] = {10.0};
    struct answer *a = (struct answer*)malloc(sizeof(struct answer) * 1);
    struct answer *b = (struct answer*)malloc(sizeof(struct answer) * 1);
    struct answer *c = (struct answer*)malloc(sizeof(struct answer) * 1);

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    for (unsigned int i = 0; i < 5; i++) {
        dt = list_dt[i];
        for (unsigned int j = 0; j < 1; j++) { 
            max = list_time[j];
            a = euler_method(a, dt, max);
            b = runge_kutta_method_02(b, dt, max);
            c = runge_kutta_method_04(c, dt, max);
            //printf("%6f,%6f,%6f,%6f\n", dt, max, t, y);
            fprintf(tmp_file, "%.6f,%.6f,%.6f,%.20f,%.20f,%.20f,%.6f,%.20f,%.20f,%.20f,%.6f,%.20f,%.20f,%.20f\n", dt, max, a->t, a->x, exp(a->t), a->d_x, b->t, b->x, exp(b->t), b->d_x, c->t, c->x, exp(c->t), c->d_x);
            a->t = 0.0;
            a->x = 1.0;
            a->d_x = 0.0;
            b->t = 0.0;
            b->x = 1.0;
            b->d_x = 0.0;
            c->t = 0.0;
            c->x = 1.0;
            c->d_x = 0.0;
        }
    }
 
    free(a);
    free(b);
    free(c);

    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}