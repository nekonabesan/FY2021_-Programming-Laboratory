#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <time.h>

struct step {
    unsigned int seq;
    double dt;
    unsigned int max;
    struct step *prev;
    struct step *next;
};

//============================================================================//
// データを上書きする処理
// @param int char r
// @param double char g
// @param double char b
// @return struct step *t
//============================================================================//
struct step * writestep(struct step* p, unsigned int seq, double dt, double max) {
    p->seq = seq;
    p->dt = dt;
    p->max = max;
    return p;
}

//============================================================================//
// 構造体を初期化する処理
// @return struct step *t
//============================================================================//
struct step * initialize(struct step *p) {
    unsigned int seq = 0;
    double dt = 0;
    double max = 0;
    p = writestep(p, seq, dt, max);
    return p;
}

//============================================================================//
// リストを初期化する処理
// int cnt
// return struct collor p
//============================================================================//
struct step * step_clear(int values) {
    struct step *p = NULL;
    struct step *prev = NULL;
    struct step *start = NULL;
    for(unsigned int i = 0; i < values; i++) {
        p = (struct step*)malloc(sizeof(struct step) * 1);
        // リストの先頭要素を取得
        if(i == 0){
            start = p;
            p->prev = NULL;
        }
        // 構造体を初期化
        p = initialize(p);
        if(prev){
            p->prev = prev;
            prev->next = p;
        }
        prev = p;
        p->seq = i;
        p->next = NULL;
    }

    return start;
}

//============================================================================//
// 先頭のアドレスを返す処理
// @param struct ent2 *pos
// @return struct ent2 *start
//============================================================================//
struct step * head_step(struct step *pos) {
    if(pos->prev == NULL || pos == NULL){
        return pos;
    }
    struct step *head = pos->prev;
    while(1){
        if(head->prev != NULL){
            head = head->prev;
        } else {
            break;
        }
    }
    return head;
}

//============================================================================//
// 最後尾のアドレスを返す処理
// @param struct ent2 *pos
// @return struct ent2 *next
//============================================================================//
struct step * eol_step(struct step *pos) {
    if(pos->next == NULL){
        return pos;
    }
    struct step *next = pos->next;
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
// @param struct step *p
// @return bool
//============================================================================//
bool del_step_array(struct step *p) {
    if(p == NULL){
        return false;
    }
    struct step *pos = p;
    while(1){
        if(pos->next != NULL) {
            pos = pos->next;
            free(pos->prev);
        } else {
            break;
        }
    }
    return true;
}

//============================================================================//
// CSVデータを読み込み線形リストを生成する処理
// @param char *path
// @return struct step *t
//============================================================================//
struct step* init_data(const char* path) {
    FILE *fp;
    int ret;
    int seq = 0;
    char buf[3][10];
    unsigned int tmp = 0;
    double dt = 0.0;
    unsigned int max = 0;

    struct step *t = NULL;
    struct step *prev = NULL;
    struct step *start = NULL;

    fp = fopen(path, "r" );
    if(fp == NULL){
        t = initialize(t);
        return t;
    }

    while((ret=fscanf(fp, "%d,%d,%lf", &tmp, &max, &dt)) != EOF){
        t = (struct step*)malloc(sizeof(struct step) * 1);
        // リストの先頭要素を取得
        if(seq == 0){
            start = t;
            t->prev = NULL;
        }
        // 構造体を初期化
        t = initialize(t);
        if(prev){
            t->prev = prev;
            prev->next = t;
        }
        prev = t;
        t->seq = seq;
        t->max = max;
        t->dt = dt;
        t->next = NULL;
        seq++;
    }

    fclose(fp);
    t = head_step(t);

    return t;
}

//============================================================================//
// dx/dtを返す処理
// @param double t
// @return double t
//============================================================================//
double f(double t) {
    return t;
}

//============================================================================//
// 厳密解を返す処理
// @param double t
// @return exp(t)
//============================================================================//
double g(double t) {
    return exp(t);
}

/** 
 * (課題1)
 * 例題２で作成したプログラム（タイムステップ：dt = 0.1, およびdt = 0.025）において， 
 * 計算終了時間をt=2,4,6,8,10と変更した際の相対誤差 （次ページ参照）の変化を確認せよ．
 * なお，値は指数関数表記とし，仮数部は⼩数点以下第６位までとする．
 * */
bool main(void) {
    FILE *tmp_file;
    double x = 1.0;
    double t = 0.0;
    double dt = 0.0;
    double d_x = 0.0;
    unsigned int max = 0.0;
    double exat = 0.0;
    unsigned int values = 0;
    struct step *p = NULL;
    const char *out = "data/2-1.csv";
    const char *path = "data/kadai1.csv";

    // ファイルから計算終了時間とタイムステップを読み込む
    p = init_data(path);

    // 構造体の要素数を数える
    p = head_step(p);
    while(1) {
        if(p->next != NULL) {
            values++;
            p = p->next;
        } else {
            break;
        }
    };

    // 計算結果を出力するCSVファイルを開く
    tmp_file = fopen(out, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    // オイラー法による数値解の導出
    p = head_step(p);
    for (unsigned int i = 0; i <= values; i++) {
        max = p->max;
        dt = p->dt;
        for (unsigned int j = 0; j < max; j++) {
            t += dt;
            x += (x * dt);
        }
        exat = g(t);
        d_x = fabs((x - exat)/exat);
        // 計算結果をファイルへ出力する
        fprintf(tmp_file, "%.6f,%d,%.20f,%.20f,%.20f,%.20f\n", dt, max, t, x, exp(t), d_x);
        x = 1.0;
        t = 0.0;
        exat = 0.0;
        d_x = 0.0;
        
        if(p->next != NULL) {
            p = p->next;
        } else {
            break;
        }
    }

    // 計算結果を出力するCSVファイルを閉じる
    fclose(tmp_file);

    del_step_array(head_step(p));

    return true;
}