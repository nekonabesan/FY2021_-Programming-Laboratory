#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define CODE_LENGTH 1
#define CODE_WEIGHT 2
#define CODE_MAX 1
#define CODE_MIN 2

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
// 2.平均値
// @param struct person* p
// @patram unsigned int control_code
// @return double avg
//============================================================================//
double avg_parson(struct person* p, unsigned int control_code) {
    double total = 0.0;
    double avg = 0.0;
    double cnt = 0.0;
    p = head_person(p);
    while(1) {
        switch (control_code)
        {
        case CODE_LENGTH:
            total += p->length;
            break;
        case CODE_WEIGHT:
            total += p->weight;
            break;
        }
        cnt++;
        if(p->next != NULL) {
            p = p->next;
        } else {
            break;
        }
    }

    // 平均値を導出する
    avg = total/cnt;
    // ポインタを先頭へ戻す
    p = head_person(p);

    return avg;
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
};


//--------------------------------------------------------------//
// S1を導出する処理
// @param struct person *p
// @return double s1
//--------------------------------------------------------------//
double calc_S1(struct person *p) {
  double s1 = 0.0;
  double tmp = 0.0;
  unsigned int max = 0;

  p = head_person(p);

  // 要素数を取得
  p = eol_person(p);
  max = p->seq;

  p = head_person(p);
  for (unsigned int i = 0; i <= max; i++) {
    tmp += (p->length * p->weight);
    if(p->next != NULL) {
      p = p->next;
    }
  }

  // S1を導出する
  s1 = tmp/(max + 1);

  p = head_person(p);

  return s1;
}

//--------------------------------------------------------------//
// S2を導出する処理
// @param struct person *p
// @param unsigned int x_axis
// @return double s1
//--------------------------------------------------------------//
double calc_S2(struct person *p, unsigned int x_axis) {
  double s2 = 0.0;
  double tmp = 0.0;
  unsigned int max = 0;

  p = head_person(p);

  // 要素数を取得
  p = eol_person(p);
  max = p->seq;

  p = head_person(p);
  for (unsigned int i = 0; i <= max; i++) {
    switch (x_axis) {
      case CODE_LENGTH:
        tmp += pow(p->length, 2);
        break;
      case CODE_WEIGHT:
        tmp += pow(p->weight, 2);
        break;
      default:
        break;
    }
    
    if(p->next != NULL) {
      p = p->next;
    }
  }

  // S1を導出する
  s2 = tmp/(max + 1);

  p = head_person(p);

  return s2;
}

//--------------------------------------------------------------//
// aを導出する処理
// @param struct person *p
// @param unsigned int x_axis
// @return double a
//--------------------------------------------------------------//
double calc_a(struct person *p, unsigned int x_axis) {
    double a = 0.0;
    double s1 = 0;
    double s2 = 0;
    double avg_x = 0;
    double avg_y = 0;

    p = head_person(p);

    // x軸の設定でパラメータの導出を切り替え
    switch (x_axis) {
        case CODE_LENGTH:
        avg_x = avg_parson(p, CODE_LENGTH);
        avg_y = avg_parson(p, CODE_WEIGHT);
        s2 = calc_S2(p, CODE_LENGTH);
        break;
        case CODE_WEIGHT:
        avg_x = avg_parson(p, CODE_WEIGHT);
        avg_y = avg_parson(p, CODE_LENGTH);
        s2 = calc_S2(p, CODE_WEIGHT);
        break;
        default:
        break;
    }

    p = head_person(p);
    s1 = calc_S1(p);
    a = (s1 - (avg_x * avg_y))/(s2 - pow(avg_x, 2));
    
    p = head_person(p);

    return a;
}

//--------------------------------------------------------------//
// bを導出する処理
// @param struct person *p
// @param unsigned int x_axis
// @return double a
//--------------------------------------------------------------//
double calc_b(struct person *p, unsigned int x_axis) {
  double b = 0.0;
  double s1 = 0;
  double s2 = 0;
  double avg_x = 0;
  double avg_y = 0;

  p = head_person(p);

  // x軸の設定でパラメータの導出を切り替え
  switch (x_axis) {
    case CODE_LENGTH:
      avg_x = avg_parson(p, CODE_LENGTH);
      avg_y = avg_parson(p, CODE_WEIGHT);
      s2 = calc_S2(p, CODE_LENGTH);
      break;
    case CODE_WEIGHT:
      avg_x = avg_parson(p, CODE_WEIGHT);
      avg_y = avg_parson(p, CODE_LENGTH);
      s2 = calc_S2(p, CODE_WEIGHT);
      break;
    default:
      break;
  }

  p = head_person(p);
  s1 = calc_S1(p);
  b = (((avg_y * s2) - (avg_x * s1))/(s2 - pow(avg_x, 2)));

  p = head_person(p);

  return b;
}

//============================================================================//
// 課題(1)のmain関数
// @return bool 
//============================================================================//
bool main(void) {
    struct person *t = NULL;
    unsigned int max = 0;
    //const char *path = "data/data02_01.csv";

    // データをCSVから読み込む場合
    // 以下のコメントを外し「データを配列から読み込む場合(ここから)～(ここまで)」をコメント
    //t = init_data(path);

    // データを配列から読み込む場合(ここから)
    struct person *n = NULL;
    struct person *prev = NULL;
    struct person *start = NULL;
    unsigned int seq = 0;
    double a = 0.0;
    double b = 0.0;

    // データを配列として定義する
    double data[11][3] = {
        {1,168,60}
        ,{2,162,55}
        ,{3,171,65}
        ,{4,159,60}
        ,{5,174,72}
        ,{6,166,57}
        ,{7,175,61}
        ,{8,176,66}
        ,{9,168,56}
        ,{10,182,69}
        ,{11,179,62}
    };

    // 配列として定義したデータから構造体を初期化する
    for (unsigned int i = 0; i < 11; i ++) {
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


    // 身長の単位を(m)へ変換
    t = from_cm_to_m_for_length(t);

    // 傾きと切片を導出する    
    t = head_person(t);
    a = calc_a(t, CODE_LENGTH);
    t = head_person(t);
    b = calc_b(t, CODE_LENGTH);

    // 傾きを表示する
    printf("a : %lf\n", a);
    // 切片を表示する
    printf("b : %lf\n", b);
    // 近似式を表示する
    if(b < 0) {
        printf("y = %lfx - %lf\n", a, fabs(b));
    } else {
        printf("y = %lfx + %lf\n", a, b);
    }

    return true;
}