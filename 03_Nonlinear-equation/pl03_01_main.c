#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include  "../modules/pl03_01_module.c"

#define EPSILON 0.000000000001
#define SPLIT 10



double f(double x) {
    return powl(x, 5) - (5 * powl(x, 3)) + (4 * x); 
}

struct answer * dichotomy(double num1, double num2){
    struct answer *t = NULL;
    struct answer *prev = NULL;
    struct answer *start = NULL;
    double c = 0.0;
    double a = 0.0;
    double b = 0.0;
    double tmp_a = 0.0;
    double tmp_b = 0.0;
    double h = 0.0;
    double x_k = 0.0;
    double x_k_b = 0.0;
    unsigned int index = 0;
    unsigned int seq = 0;

    // 大小比較して変数へ値を格納
    if(num1 < num2) {
        a = num1;
        b = num2;
    } else {
        a = num2;
        b = num1;
    }

    // 微小区間の幅を導出する
    h = (b - a) / SPLIT;
    x_k = a + h;
    x_k_b = a;

    for (unsigned int i = 0; i < SPLIT; i++) {
        if((f(x_k) * f(x_k_b)) < 0) {
            t = (struct answer*)malloc(sizeof(struct answer) * 1);

            // リストの先頭要素を取得
            if(seq == 0){
                start = t;
                t->prev = NULL;
            }

            if (prev != NULL) {
                t->prev = prev;
                prev->next = t;
            }

            // 線形リスト
            prev = t;
            t->next = NULL;
            t->seq = seq;
            seq++;

            tmp_a = x_k_b;
            tmp_b = x_k;
            do {
                c = (tmp_a + tmp_b) / 2;

                if ((f(tmp_a) * f(c)) < 0) {
                    tmp_b = c;
                } else {
                    tmp_a = c;
                }
            } while (fabs(tmp_a - tmp_b) > EPSILON);

            // 線形リストへ解を格納する
            t->y = c;
        }
        // 計算範囲をインクリメントする
        x_k += h;
        x_k_b += h;
    }

    if (t != NULL) {
        head_answer(t);
    }
    return t;
}

bool main(void) {
    struct answer *t = NULL;
    double a = -3.0;
    double b = 3.0;
    unsigned int max = 0;

    t = dichotomy(a, b);

    if (t != NULL) {
        t = eol_answer(t);
        max = t->seq;
        
        t = head_answer(t);
        for(unsigned int i = 0; i <= max; i++) {
            printf("Answer %lf\n", t->y);
            if(t->next != NULL) {
                t = t->next;
            }
        }

        t = head_answer(t);
    }
   
    return del_answer_array(t);
}