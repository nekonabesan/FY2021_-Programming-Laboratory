#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define EPSILON 0.00000000000001
#define NMAX 100000000000000
#define SPLIT 10

struct answer {
    unsigned int seq;
    double x;
    double y;
    struct answer *prev;
    struct answer *next;
};

//--------------------------------------------------------------//
// 先頭のアドレスを返す処理
// @param struct ent2 *pos
// @return struct ent2 *start
//--------------------------------------------------------------//
struct answer * head_answer(struct answer *pos) {
    if(pos->prev == NULL || pos == NULL){
        return pos;
    }
    struct answer *head = pos->prev;
    while(1){
        if(head->prev){
        head = head->prev;
        } else {
        break;
        }
    }
    return head;
}

//--------------------------------------------------------------//
// 最後尾のアドレスを返す処理
// @param struct ent2 *pos
// @return struct ent2 *next
//--------------------------------------------------------------//
struct answer * eol_answer(struct answer *pos) {
    if(pos->next == NULL){
        return pos;
    }
    struct answer *next = pos->next;
    while(1){
        if(next->next != NULL){
            next = next->next;
        } else {
            break;
        }
    }
    return next;
}

//============================================================================//
// リストを全て削除する処理
// @param struct answer *p
// @return bool
//============================================================================//
bool del_answer_array(struct answer *p) {
    if(p == NULL){
        return false;
    }
    struct answer *pos = p;
    while(pos->next){
        pos = pos->next;
        free(pos->prev);
    }
    return true;
}

double f(double x) {
    return powl(x, 5) - (5 * powl(x, 3)) + (4 * x); 
}

//============================================================================//
// 二分法で解を導出する処理
// @param double num1
// @param double num2
// @return struct answer * t
//============================================================================//
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

//============================================================================//
// 演習課題二分法
// @param void
// @return bool
//============================================================================//
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