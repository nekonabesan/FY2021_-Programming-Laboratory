#include <stdio.h>

#include <math.h>

double f(double x,double y,double p) {
    return -y;
}


double g(double p) {
    return p;
}


void RungeKutta2(double x, double y, double p, double h, int n) {

    double k11, k12, k21, k22;
    int i;


    printf("%f %f %f %f \n",x,y,p,y*y+p*p);

    for (i = 1 ; i <= n; i++) {
         k11= h*g(p);

         k21= h*f(x,y,p);
         k12= h*g(p+k21/2);

         k22= h*f(x+h/2,y+k11/2,p+k21/2);
         x=x+h;

         y=y+k12;
         p=p+k22;

         printf("%f %f %f %f \n", x,y,p,y*y+p*p);
}

}

void main(void) {
    double x,y,h,p;
    int n;


    n=120;

    h=0.1;
    x=0;y=0;p=1;
    RungeKutta2(x,y,p,h,n);
}