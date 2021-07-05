#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define SEPARATE_N 100;

double f(double x){
    return (2 / (pow(x, 2)));
}

double g(double x){
    return 4/(1 + pow(x, 2));
}

/**
 * 台形公式による数値積分
 * */
bool main(void) {
    double y = 0.0;
    double h = 0.0;
    double sp = 0.0;
    double end = 0.0;
    double n = 0.0;
    double sep = 0.0;
    
    /**
     * f(x)の導出過程
     * */
    sp = 1.0;
    end = 2.0;
    sep = (end - sp)/SEPARATE_N;
    n = (end - sp)/sep;
    h = (end - sp)/n;

    for (double x = sp; x <= (end + sep); x += sep) {
        if (x == sp || x == end) {
            y += f(x);
        } else {
            y += (2 * f(x));
        }
    }

    y = y * (h / 2);

    printf("Anser of S1 %lf\n", y);

    /**
     * g(x)の導出過程
     * */
    y = 0.0;
    sp = 0.0;
    end = 1.0;
    sep = (end - sp)/SEPARATE_N;
    n = (end - sp)/sep;
    h = (end - sp)/n;

    for (double x = sp; x <= (end + sep); x += sep) {
        if (x == sp || x == end) {
            y += g(x);
        } else {
            y += (2 * g(x));
        }
    }

    y = y * (h / 2);

    printf("Anser of S2 %lf\n", y);


    return true;
}