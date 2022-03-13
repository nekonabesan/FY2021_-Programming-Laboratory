#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

double f(double x, double y) {
    return (2 * x * y);
}

double g(double x_0, double x) {
    return x_0 * exp(powl(x, 2));
}

bool main(void) {
    FILE *tmp_file;
    double x = 0.0;
    double y = 1.0;
    double dx = 0.1;
    double max = 1.0;
    double exat = 0.0;
    double fi = 0.0;

    // オイラー法による数値解の導出
    for (unsigned int i = 0; i < 10; i++) {
        fi = f(x, y);
        y += (fi * dx);
        x += dx;
        exat = fabs(y - g(1.0, x));
        printf("y(%f) = %.9f\n", x, y);
    }
    printf("error = %.9f\n", exat);
    printf("ground trouth = %.9f\n", g(1.0, x));
    

    return true;

}