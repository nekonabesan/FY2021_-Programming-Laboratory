#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <time.h>

struct answer {
    unsigned int seq;
    long double x;
    long double y;
    long double exat;
    long double t;
    long double d_x;
    unsigned long time;
    struct answer *prev;
    struct answer *next;
};

long double f(long double t) {
    return t;
}

long double g(long double t) {
    return exp(t);
}

struct answer * euler_method(struct answer *a, long double dt, long double max){
    long double t = 0.0;
    long double x = 1.0;
    long double d_x = 0.0;
    long double exat = 0.0;
    struct timespec start;
    struct timespec end;

    // 実行時間計測(ナノ秒)START
    timespec_get(&start, TIME_UTC);
    //while ((FLT_EPSILON  * fmax(1, fmax(fabs(max), fabs(t)))) < fabs(max - t)) {
    for (unsigned int i = 0; i < max; i++) {
        t += dt;
        x += (x * dt);
    }
    // 実行時間計測(ナノ秒)END
    timespec_get(&end, TIME_UTC);
    a->time = end.tv_nsec - start.tv_nsec;

    // ⊿xの導出
    exat = g(t);
    d_x = fabs((x - exat)/exat);
    

    a->x = x;
    a->t = t;
    a->d_x = d_x;
    a->exat = exat;

    return a;
}

struct answer * runge_kutta_method_02(struct answer *a, long double dt, long double max){
    long double x = 1.0;
    long double d_x = 0.0;
    long double t = 0.0;
    long double k_1 = 0.0;
    long double k_2 = 0.0;
    long double k_3 = 0.0;
    long double k_4 = 0.0;
    long double exat = 0.0;
    struct timespec start;
    struct timespec end;

    // 実行時間計測(ナノ秒)START
    timespec_get(&start, TIME_UTC);
    //while ((FLT_EPSILON  * fmax(1, fmax(fabs(max), fabs(t)))) < fabs(max - t)) {
    for (unsigned int i = 0; i < max; i++) {
        t += dt;
        k_1 = dt * f(x);
        k_2 = dt * f(x + (k_1 * 0.5));
        x += k_2;
    }
    // 実行時間計測(ナノ秒)END
    timespec_get(&end, TIME_UTC);
    a->time = end.tv_nsec - start.tv_nsec;

    // ⊿xの導出
    exat = g(t);
    d_x = fabs((x - exat)/exat);

    a->x = x;
    a->t = t;
    a->d_x = d_x;
    a->exat = exat;

    return a;

}

struct answer * runge_kutta_method_04(struct answer *a, long double dt, long double max){
    long double x = 1.0;
    long double d_x = 0.0;
    long double t = 0.0;
    long double k_1 = 0.0;
    long double k_2 = 0.0;
    long double k_3 = 0.0;
    long double k_4 = 0.0;
    long double exat = 0.0;
    struct timespec start;
    struct timespec end;

    // 実行時間計測(ナノ秒)START
    timespec_get(&start, TIME_UTC);
    //while ((FLT_EPSILON  * fmax(1, fmax(fabs(max), fabs(t)))) < fabs(max - t)) {
    for (unsigned int i = 0; i < max; i++) {
        t += dt;
        k_1 = dt * f(x);
        k_2 = dt * f(x + (k_1 * 0.5));
        k_3 = dt * f(x + (k_2 * 0.5));
        k_4 = dt * f(x + k_3);
        x += ((k_1 + (2.0 * k_2) + (2.0 * k_3) + k_4) / 6.0);
    }
    // 実行時間計測(ナノ秒)END
    timespec_get(&end, TIME_UTC);
    a->time = end.tv_nsec - start.tv_nsec;
    
    // ⊿xの導出
    exat = g(t);
    d_x = fabs((x - exat)/exat);

    a->x = x;
    a->t = t;
    a->d_x = d_x;
    a->exat = exat;

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
    long double x = 1.0;
    long double t = 0.0;
    long double dt = 0.0;
    int max = 0;
    int values = 7;
    const char *path = "data/prog05_02_03_001_long-double .csv";
    long double list_dt[7] = {0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001, 0.0000001};
    int list_max[7] = {100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    long double list_time[1] = {10.0};
    struct answer *a = (struct answer*)malloc(sizeof(struct answer) * 1);
    struct answer *b = (struct answer*)malloc(sizeof(struct answer) * 1);
    struct answer *c = (struct answer*)malloc(sizeof(struct answer) * 1);

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    for (unsigned int i = 0; i < values; i++) {
        dt = list_dt[i];
        max = list_max[i];
        //for (unsigned int j = 0; j < 1; j++) { 
            //max = list_time[j];
            a = euler_method(a, dt, max);
            b = runge_kutta_method_02(b, dt, max);
            c = runge_kutta_method_04(c, dt, max);
            //printf("%6f,%6f,%6f,%6f\n", dt, max, t, y);
            fprintf(tmp_file, "%.10Lf,%d,%.6Lf,%.20Lf,%.20Lf,%.20Lf,%ld,%.6Lf,%.20Lf,%.20Lf,%.20Lf,%ld,%.6Lf,%.20Lf,%.20Lf,%.20Lf,%ld\n", dt, max, a->t, a->x, a->exat, a->d_x, a->time, b->t, b->x, b->exat, b->d_x, b->time, c->t, c->x, c->exat, c->d_x, c->time);
            a->t = 0.0;
            a->x = 1.0;
            a->d_x = 0.0;
            b->t = 0.0;
            b->x = 1.0;
            b->d_x = 0.0;
            c->t = 0.0;
            c->x = 1.0;
            c->d_x = 0.0;
        //}
    }
 
    free(a);
    free(b);
    free(c);

    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}