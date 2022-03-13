#include <stdio.h>
#include <quadmath.h>  
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <time.h>


struct answer {
    unsigned int seq;
    __float128 x;
    __float128 y;
    __float128 exat;
    __float128 t;
    __float128 d_x;
    unsigned long time;
    struct answer *prev;
    struct answer *next;
};

__float128 f(__float128 t) {
    return t;
}

__float128 g(__float128 t) {
    return exp(t);
}

struct answer * euler_method(struct answer *a, __float128 dt, __float128 max){
    __float128 t = 0.0;
    __float128 x = 1.0;
    __float128 d_x = 0.0;
    __float128 exat = 0.0;
    struct timespec start;
    struct timespec end;

    // 実行時間計測(ナノ秒)START
    timespec_get(&start, TIME_UTC);
    for (unsigned int i = 0; i < max; i++) {
        t += dt;
        x += (x * dt);
    }
    // 実行時間計測(ナノ秒)END
    timespec_get(&end, TIME_UTC);
    a->time = end.tv_nsec - start.tv_nsec;
    //
    exat = g(t);
    d_x = fabs((x - exat)/exat);
    
    a->x = x;
    a->t = t;
    a->d_x = d_x;
    a->exat = exat;

    return a;
}

struct answer * runge_kutta_method_02(struct answer *a, __float128 dt, __float128 max){
    __float128 x = 1.0;
    __float128 d_x = 0.0;
    __float128 t = 0.0;
    __float128 k_1 = 0.0;
    __float128 k_2 = 0.0;
    __float128 k_3 = 0.0;
    __float128 k_4 = 0.0;
    __float128 exat = 0.0;
    struct timespec start;
    struct timespec end;

    // 実行時間計測(ナノ秒)START
    timespec_get(&start, TIME_UTC);
    for (unsigned int i = 0; i < max; i++) {
        t += dt;
        k_1 = dt * f(x);
        k_2 = dt * f(x + (k_1 * 0.5));
        x += k_2;
    }
    // 実行時間計測(ナノ秒)END
    timespec_get(&end, TIME_UTC);
    a->time = end.tv_nsec - start.tv_nsec;

    //
    exat = g(t);
    d_x = fabs((x - exat)/exat);

    a->x = x;
    a->t = t;
    a->d_x = d_x;
    a->exat = exat;

    return a;

}

struct answer * runge_kutta_method_04(struct answer *a, __float128 dt, __float128 max){
    __float128 x = 1.0;
    __float128 d_x = 0.0;
    __float128 t = 0.0;
    __float128 k_1 = 0.0;
    __float128 k_2 = 0.0;
    __float128 k_3 = 0.0;
    __float128 k_4 = 0.0;
    __float128 exat = 0.0;
    struct timespec start;
    struct timespec end;

    // 実行時間計測(ナノ秒)START
    timespec_get(&start, TIME_UTC);
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
    // 
    if (exat == HUGE_VAL) {
        printf("overflow: %f", HUGE_VAL);
    }
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
 * gcc prog05_02_03_004.c -lm -lquadmath
 * */
bool main(void) {
    FILE *tmp_file;
    __float128 x = 1.0;
    __float128 t = 0.0;
    __float128 dt = 0.0;
    int max = 0;
    int values = 7;
    const char *path = "data/prog05_02_03_001__float128 .csv";
    __float128 list_dt[7] = {0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001, 0.0000001};
    //__float128 list_dt[5] = {0.2, 0.1, 0.05, 0.025, 0.0125};
    int list_max[7] = {100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    //int list_max[5] = {50, 100, 200, 400, 800};
    __float128 list_time[1] = {10.0};

    char dt_s[80];
    char max_s[80];

    char a_t[80];
    char a_x[80];
    char a_exp[80];
    char a_dx[80];
    char a_time[80];
    char a_exat[80];

    char b_t[80];
    char b_x[80];
    char b_exp[80];
    char b_dx[80];
    char b_time[80];
    char b_exat[80];

    char c_t[80];
    char c_x[80];
    char c_exp[80];
    char c_dx[80];
    char c_time[80];
    char c_exat[80];


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
            
            quadmath_snprintf(dt_s,80,"%.40Qf",dt);
            //
            quadmath_snprintf(a_t,80,"%.40Qf",a->t);
            quadmath_snprintf(a_x,80,"%.40Qf",a->x);
            quadmath_snprintf(a_exp,80,"%.40Qf",a->exat);
            quadmath_snprintf(a_dx,80,"%.40Qf",a->d_x);
            //
            quadmath_snprintf(b_t,80,"%.40Qf",b->t);
            quadmath_snprintf(b_x,80,"%.40Qf",b->x);
            quadmath_snprintf(b_exp,80,"%.40Qf",b->exat);
            quadmath_snprintf(b_dx,80,"%.40Qf",b->d_x);
            //
            quadmath_snprintf(c_t,80,"%.40Qf",c->t);
            quadmath_snprintf(c_x,80,"%.40Qf",c->x);
            quadmath_snprintf(c_exp,80,"%.40Qf",c->exat);
            quadmath_snprintf(c_dx,80,"%.40Qf",c->d_x);
            

            fprintf(tmp_file, "%s,%d,%s,%s,%s,%s,%ld,%s,%s,%s,%s,%ld,%s,%s,%s,%s,%ld\n", dt_s, max, a_t, a_x, a_exp, a_dx, a->time, b_t, b_x, b_exp, b_dx, b->time, c_t, c_x, c_exp, c_dx, c->time);
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