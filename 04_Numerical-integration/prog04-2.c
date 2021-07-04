#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define SEPARATE_N 50;

double f(double x){
    return (2 / (pow(x, 2)));
}

double g(double x){
    return 4/(1 + pow(x, 2));
}
/**
 * シンプソン公式による数値積分
 * */
bool main(void) {
    double y = 0.0;
    double h = 0.0;
    double sp = 0.0;
    double end = 0.0;
    double sep = 0.0;
    double n = 0.0;
    long cnt = 0;
    
    /**
     * f(x)の導出過程
     * */
    sp = 1.0;
    end = 2.0;
    sep = (end - sp)/SEPARATE_N;
    n = (end - sp)/(sep * 2);
    h = (end - sp)/(2 * n);

    for (double x = sp; x <= (end + sep); x += sep) {
        if(x == sp || x == end) {
            y += f(x);
        } else if ((cnt % 2) == 0) {
            y += (2 * f(x));
        } else {
            y += (4 * f(x));
        }
        cnt++;
    }

    y = y * (h / 3);

    printf("Anser of S1 %lf\n", y);


    /**
     * g(x)の導出過程
     * */
    y = 0.0;
    sp = 0.0;
    end = 1.0;
    sep = (end - sp)/SEPARATE_N;
    n = (end - sp)/(sep * 2);
    h = (end - sp)/(2 * n);

    for (double x = sp; x <= (end + sep); x += sep) {
        if(x == sp || x == end) {
            y += g(x);
        } else if ((cnt % 2) == 0) {
            y += (2 * g(x));
        } else {
            y += (4 * g(x));
        }
        cnt++;
    }

    y = y * (h / 3);

    printf("Anser of S2 %lf\n", y);

    return true;
}