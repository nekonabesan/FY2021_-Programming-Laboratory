#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**********************************************
 generate-data.c
 
 y = ax + b + e (eはN(0,1)) から x,y を生成するプログラム

 **********************************************/

#define randDouble ((double)rand()+1.0)/((double)RAND_MAX+2.0) // 0以上1未満の実数値の乱数を生成

double rand_normal(double mu, double sigma)
{
  double e = sqrt(-2.0*log(randDouble)) * sin(2.0*M_PI*randDouble);
  return mu + sigma*e;
}

int main(int argc, char *argv[])
{
  int i, n = 100;
  double a = 0.8, b = 1.5, e;
  double x, y;

  if(argc >= 2)
    n = atoi(argv[1]);

  srand((unsigned int)time(NULL));
  rand();

  for(i=0; i<n; i++){
    x = randDouble * 10.0;
    e = rand_normal(0,1);
    y = a * x + b + e;
    printf("%d,%.3lf,%.3lf\n", i,x,y);
  }
}
