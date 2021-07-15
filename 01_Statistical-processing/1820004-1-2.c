#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define CODE_LENGTH 1
#define CODE_WEIGHT 2
#define CODE_MAX 1
#define CODE_MIN 2
#define UNDER_WEIGHT 0
#define STD_WEIGHT 1
#define OBESITY_WEIGHT 2
#define HEGH_OBESITY_WEIGHT 3

struct person {
  unsigned int seq;
  double length;
  double weight;
  struct person *prev;
  struct person *next;
};

//--------------------------------------------------------------//
// データを上書きする処理
// @param int char r
// @param double char g
// @param double char b
// @return struct person *t
//--------------------------------------------------------------//
struct person * writeperson(struct person* t, unsigned int seq, double length, double weight) {
    t->seq = seq;
    t->length = length;
    t->weight = weight;
    return t;
}

//--------------------------------------------------------------//
// 構造体を初期化する処理
// @return struct person *t
//--------------------------------------------------------------//
struct person * initialize(struct person *t) {
    unsigned int seq = 0;
    double length = 0;
    double weight = 0;
    t = writeperson(t, seq, length, weight);
    return t;
}

//--------------------------------------------------------------//
// リストを初期化する処理
// int cnt
// return struct collor t
//--------------------------------------------------------------//
struct person * person_clear(int length) {
    struct person *t = NULL;
    struct person *n = NULL;
    struct person *prev = NULL;
    struct person *start = NULL;
    for(int x = 0; x < length; x++) {
        t = (struct person*)malloc(sizeof(struct person) * 1);
        // リストの先頭要素を取得
        if(x == 0){
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
        t->seq = x;
        t->next = NULL;
    }
    return start;
}

//--------------------------------------------------------------//
// 先頭のアドレスを返す処理
// @param struct ent2 *pos
// @return struct ent2 *start
//--------------------------------------------------------------//
struct person * head_person(struct person *pos) {
    if(pos->prev == NULL || pos == NULL){
        return pos;
    }
    struct person *head = pos->prev;
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
struct person * eol_person(struct person *pos) {
    if(pos->next == NULL){
        return pos;
    }
    struct person *next = pos->next;
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
// @param struct person *p
// @return bool
//============================================================================//
bool del_person_array(struct person *p) {
    if(p == NULL){
        return false;
    }
    struct person *pos = p;
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
// @return struct person *t
//============================================================================//
struct person* init_data(const char* path) {
    FILE *fp;
    int ret;
    int seq = 0;
    char buf[3][10];
    double data[3];

    struct person *t = NULL;
    struct person *n = NULL;
    struct person *prev = NULL;
    struct person *start = NULL;

    fp = fopen(path, "r" );
    if(fp == NULL){
        t = initialize(t);
        return t;
    }

    while((ret=fscanf(fp, "%lf,%lf,%lf", &data[0], &data[1], &data[2])) != EOF){
        t = (struct person*)malloc(sizeof(struct person) * 1);
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
        t->length = data[1];
        t->weight = data[2];
        t->next = NULL;
        seq++;
    }

    fclose(fp);
    t = head_person(t);

    return t;
}

//============================================================================//
// BMIを計算する
// @param double length (m)
// @param double weight (kg)
// @return double bmi
//============================================================================//
double derivation_bmi(double length, double weight) {
    double bmi = 0.0;

    // BMIを導出する
    bmi = (weight/pow(length, 2));

    return bmi;
}

//============================================================================//
// 標準体重を計算する
// @param double length (m)
// @param double weight (kg)
// @return double std_weight
//============================================================================//
double calc_std_weight(double length, double weight) {
    double std_weight = 0.0;

    // 標準体重を計算する
    std_weight = length * length * 22.0;

    return std_weight;
}

//============================================================================//
// 課題2 肥満度を判定するプログラム
// @param double length
// @param double weight
// @return double bmi
//============================================================================//
unsigned int calc_bmi(double length, double weight) {
    unsigned int bmi = 0;
    double tmp = 0.0;

    // BMIを導出する
    tmp = derivation_bmi(length, weight);

    // 判定基準をパラメータへセットする
    if (tmp < 18.5) {
        bmi = UNDER_WEIGHT;
    } else if (18.5 <= tmp && tmp < 25.0) {
        bmi = STD_WEIGHT;
    } else if (25.0 <= tmp && tmp < 30.0) {
        bmi = OBESITY_WEIGHT;
    } else if (30 <= tmp) {
        bmi = HEGH_OBESITY_WEIGHT;
    }

    return bmi;
}

//--------------------------------------------------------------//
// 身長の単位を(cm->m)へ変換する処理
// @param struct person *p
// @return struct person *p
//--------------------------------------------------------------//
struct person * from_cm_to_m_for_length(struct person* p) {
    unsigned int max = 0;

    // 要素数を取得
    p = eol_person(p);
    max = p->seq;

    p = head_person(p);
    for (unsigned int i = 0; i <= max; i++) {
        p->length = p->length * 0.01;
        if(p->next != NULL) {
        p = p->next;
        }
    }

    p = head_person(p);

    return p;
}

/**
 * 課題(2)
 * */
bool main(void) {
    struct person *t = NULL;
    unsigned int max = 0;

    // データをCSVから読み込む場合
    // 以下のコメントを外し「データを配列から読み込む場合(ここから)～(ここまで)」をコメント
    //const char *path = "./data/data01_02_02.csv";
    //t = init_data(path);

    // データを配列から読み込む場合(ここから)
    struct person *n = NULL;
    struct person *prev = NULL;
    struct person *start = NULL;
    unsigned int seq = 0;
    // データを配列として定義する
    double data[4][3] = {
        {1,170,50}
        ,{2,170,65}
        ,{3,170,80}
        ,{4,170,95}
    };
    // 配列として定義したデータから構造体を初期化する
    for (unsigned int i = 0; i < 4; i ++) {
        t = (struct person*)malloc(sizeof(struct person) * 1);
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
        t->length = data[i][1];
        t->weight = data[i][2];
        t->next = NULL;
        seq++;
    }
    // データを配列から読み込む場合(ここまで)

    // 身長の単位を(m)へ変換する
    t = head_person(t);
    t = from_cm_to_m_for_length(t);


    // データ数を取得する
    t = head_person(t);
    t= eol_person(t);
    max = t->seq;

    t = head_person(t);
    for(unsigned int i = 0; i <= max; i++) {
        printf("length : %f(m), weight : %f(kg), Std Weight : %f(kg), BMI rate : %f ", t->length, t->weight, calc_std_weight(t->length, t->weight), derivation_bmi(t->length, t->weight));
        switch (calc_bmi(t->length, t->weight))
        {
        case UNDER_WEIGHT:
            printf(" -> Underweight\n");
            break;
        case STD_WEIGHT:
            printf(" -> standard\n");
            break;
        case OBESITY_WEIGHT:
            printf(" -> obesity\n");
            break;
        case HEGH_OBESITY_WEIGHT:
            printf(" -> Severe obesity\n");
            break;
        default:
            break;
        }

        if(t->next != NULL) {
            t = t->next;
        }
    }
 
    // メモリ解放
    del_person_array(head_person(t));

    return true;
}