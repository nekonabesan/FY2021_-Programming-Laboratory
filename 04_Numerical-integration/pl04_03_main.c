#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

struct data {
    unsigned int seq;
    double sep;
    double trapezoid;
    double simpson;
    struct data *prev;
    struct data *next;
};

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
struct data * head_data(struct data *pos) {
    if(pos->prev == NULL || pos == NULL){
        return pos;
    }
    struct data *head = pos->prev;
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
struct data * eol_data(struct data *pos) {
    if(pos->next == NULL){
        return pos;
    }
    struct data *next = pos->next;
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
bool del_data_array(struct data *p) {
    if(p == NULL){
        return false;
    }
    struct data *pos = p;
    while(pos->next){
        pos = pos->next;
        free(pos->prev);
    }
    return true;
}

//============================================================================//
// 
// @param double x
// @return double 
//============================================================================//
double f(double x){
    return (2 / (pow(x, 2)));
}

//============================================================================//
// 
// @param double x
// @return double 
//============================================================================//
double g(double x){
    return 4/(1 + pow(x, 2));
}

//============================================================================//
// 台形公式による数値積分
// @param struct answer *p
// @return bool
//============================================================================//
struct answer * trapezoid(double sep_n){
    struct answer *a = NULL;
    struct answer *prev = NULL;
    struct answer *start = NULL;
    double y = 0.0;
    double h = 0.0;
    double sp = 0.0;
    double end = 0.0;
    double n = 0.0;
    double sep = 0.0;
    
    /**
     * f(x)の導出過程
     * */

    // 構造体を初期化
    a = (struct answer*)malloc(sizeof(struct answer) * 1);
    a->prev = NULL;
    a->seq = 0;

    // 変数を初期化
    sp = 1.0;
    end = 2.0;
    sep = (end - sp)/sep_n;
    n = (end - sp)/sep;
    h = (end - sp)/n;

    for (double x = sp; x <= (end + sep); x += sep) {
        if (x == sp || x == end) {
            y += f(x);
        } else {
            y += (2 * f(x));
        }
    }

    a->y = y = y * (h / 2);

    /**
     * g(x)の導出過程
     * */

    // 構造体を初期化
    prev = a;
    a = (struct answer*)malloc(sizeof(struct answer) * 1);
    a->seq = 1;
    prev->next = a;
    a->prev = prev;
    a->next = NULL;
    
    // 変数を初期化
    y = 0.0;
    sp = 0.0;
    end = 1.0;
    sep = (end - sp)/sep_n;
    n = (end - sp)/sep;
    h = (end - sp)/n;

    for (double x = sp; x <= (end + sep); x += sep) {
        if (x == sp || x == end) {
            y += g(x);
        } else {
            y += (2 * g(x));
        }
    }

    a->y = y = y * (h / 2);

    return head_answer(a);
}

//============================================================================//
// シンプソン公式による数値積分
// @param struct answer *p
// @return bool
//============================================================================//
struct answer * simpson(double sep_n){
    struct answer *a = NULL;
    struct answer *prev = NULL;
    struct answer *start = NULL;
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

    // 構造体を初期化
    a = (struct answer*)malloc(sizeof(struct answer) * 1);
    a->prev = NULL;
    a->seq = 0;

    // 変数を初期化
    sp = 1.0;
    end = 2.0;
    sep = (end - sp)/sep_n;
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

    a->y = y * (h / 3);

    /**
     * g(x)の導出過程
     * */

    // 構造体を初期化
    prev = a;
    a = (struct answer*)malloc(sizeof(struct answer) * 1);
    a->seq = 1;
    prev->next = a;
    a->prev = prev;
    a->next = NULL;

    // 変数を初期化
    sp = 0.0;
    end = 1.0;
    sep = (end - sp)/sep_n;
    n = (end - sp)/(sep * 2);
    h = (end - sp)/(2 * n);

    y = 0.0;
    sp = 0.0;
    end = 1.0;
    sep = (end - sp)/sep_n;
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

    a->y = y * (h / 3);

    return head_answer(a);
}


//============================================================================//
// genertate-data.cより移植
// @paramunsigned int cnt
// @param char *path
// @return struct person *t
//============================================================================//
bool write_data(struct data * d, const char* path) {
    FILE *tmp_file;
    unsigned int max = 0;

    d = eol_data(d);
    max = d->seq;
    d = head_data(d);

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    // データを書き込む
    for(unsigned int i = 0; i <= max; i++) {
         fprintf(tmp_file, "%lf,%lf,%lf\n", d->sep, d->trapezoid, d->simpson);
         if (d->next != NULL) {
            d = d->next;
         }
    }
    
    // 一時ファイルを閉じる
    fclose(tmp_file);

    d = head_data(d);
    return true;
}

bool main(void) {
    struct answer *a = NULL;
    struct answer *answer_prev = NULL;
    struct answer *answer_next = NULL;
    struct answer *answer_start = NULL;
    struct data *f = NULL;
    struct data *f_prev = NULL;
    struct data *f_next = NULL;
    struct data *f_start = NULL;
    struct data *g = NULL;
    struct data *g_prev = NULL;
    struct data *g_next = NULL;
    struct data *g_start = NULL;
    unsigned int values = 12;
    unsigned int seq = 0;
    const char *f_file_path = "f_x.csv";
    const char *g_file_path = "g_x.csv";
    double sep_n[12] = {200.0, 500.0, 1000.0, 2000.0, 5000.0, 10000.0, 20000.0, 50000.0, 100000.0, 200000.0, 500000.0, 1000000.0};
    
    f = (struct data*)malloc(sizeof(struct data) * 1);
    f->prev = NULL;
    g = (struct data*)malloc(sizeof(struct data) * 1);
    g->prev = NULL;

    for (unsigned int i = 0; i < values; i++) {
        f->seq = seq;
        f->sep = sep_n[i];
        g->seq = seq;
        g->sep = sep_n[i];
        seq++;
        // 台形公式による解の導出
        a = trapezoid(sep_n[i]);  
        f->trapezoid = a->y;
      //printf("%lf\n", a->y);  
        a = a->next;
        g->trapezoid = a->y;
        
        del_answer_array(head_answer(a));
        // シンプソン公式による解の導出
        
        a = simpson(sep_n[i]);
        f->simpson = a->y;    
        a = a->next;
        g->simpson = a->y;
        del_answer_array(head_answer(a));        
        // 構造体の操作
        if(i == (values - 1)) {
            f->next = NULL;
            g->next = NULL;
        } else {
            f_prev = f;
            f = (struct data*)malloc(sizeof(struct data) * 1);
            f_prev->next = f;
            f->prev = f_prev;
            g_prev = g;
            g = (struct data*)malloc(sizeof(struct data) * 1);
            g_prev->next = g;
            g->prev = g_prev;
        }
    }

    // f(x)の書き出し
    if(!write_data(f, f_file_path)) {
        printf("cannot write f(x) data\n");
    }
    del_data_array(head_data(f));

    // f(x)の書き出し
    if(!write_data(g, g_file_path)) {
        printf("cannot write g(x) data\n");
    }
    del_data_array(head_data(g));

    return true;
}