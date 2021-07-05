#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define EPSILON 0.000000000001
#define NMAX 1000000000000

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

//============================================================================//
// @param double x
// @return double powl(x, 3) + (-1 * (3 * powl(x, 2))) + (-1 * x) + 3
//============================================================================//
double g(double x) {
    return powl(x, 3) + (-1 * (3 * powl(x, 2))) + (-1 * x) + 3; 
}

//============================================================================//
// @param double x
// @return (3 * powl(x, 2)) + (-1 * (6 * x)) - 1; 
//============================================================================//
double g_2(double x) {
    return (3 * powl(x, 2)) + (-1 * (6 * x)) - 1; 
}

//============================================================================//
// ニュートン法で解を導出する処理
// @param struct answer *p
// @return bool
//============================================================================//
struct answer * newton(struct answer *q) {
    struct answer *t = NULL;
    struct answer *prev = NULL;
    struct answer *start = NULL;
    unsigned int seq = 0;
    unsigned int n = 0;
    double d = 0.0;
    double x = 0.0;
    
    q = head_answer(q);

    while (1) {
        // xを初期化する
        x = q->x;

        // 構造体を初期化する
        t = (struct answer*)malloc(sizeof(struct answer) * 1);

        // リストの先頭要素を取得
        if(seq == 0){
            start = t;
            t->prev = NULL;
        }

        // 解の導出を試行する
        do {
            d = ((-1 * g(x))/g_2(x));
            x = x + d;
            n++;
        } while (fabs(d) > EPSILON && n < NMAX);
        // 失敗の場合xへ未定義値を設定する
        if (n == NMAX) {
            x = NMAX;
        }
        t->x = x;
        // 線形リスト
        if (prev != NULL) {
            t->prev = prev;
            prev->next = t;
        }
        // 線形リスト
        prev = t;
        t->next = NULL;
        t->seq = seq;
        seq++;

        if(q->next != NULL) {
            q = q->next;
        } else {
            break;
        }
    }

    del_answer_array(head_answer(q));
    if (t != NULL) {
        t = head_answer(t);
    }

    return t;
}

//============================================================================//
// 解を表示する処理
// @param struct answer *a
// @return struct answer *a
//============================================================================//
struct answer * print_answer(struct answer *a) {
    a = head_answer(a);

    while (1) {
        printf("Answer %lf\n", a->x);
        if(a->next == NULL) {
            break;
        } else {
            a = a->next;
        }
    }

    return head_answer(a);
}

//============================================================================//
// 演習課題ニュートン法
// @param void
// @return bool
//============================================================================//
bool main(void) {
    struct answer *q = NULL;
    struct answer *a = NULL;
    struct answer *prev = NULL;
    double arr1[3] = {-2.0, 1.5, 5.0};
    
    for (unsigned int i = 0; i < 3; i++) {
        q = (struct answer*)malloc(sizeof(struct answer) * 1);
        if (prev != NULL) {
            q->prev = prev;
            prev->next = q;
        }
        // 線形リスト
        prev = q;
        q->next = NULL;
        q->seq = i;
        q->x = arr1[i];
    }

    a = newton(head_answer(q));
    a = print_answer(a);

    return del_answer_array(head_answer(a));
}

