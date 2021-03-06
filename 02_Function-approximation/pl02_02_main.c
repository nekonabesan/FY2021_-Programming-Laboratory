#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define CODE_LENGTH 1
#define CODE_WEIGHT 2
#define CODE_MAX 1
#define CODE_MIN 2

// 課題(2)4.より繰り返し回数を100回とする
#define MAX_COUNT 100
// 0以上1未満の実数値の乱数を生成
#define randDouble ((double)rand()+1.0)/((double)RAND_MAX+2.0) 

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
    a = (s1 - (avg_x * avg_y))/(s2 - powl(avg_x, 2));
    
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
// genertate-data.cより移植
// @param double mu
// @param double sigma
// @return double mu + sigma * e;
//============================================================================//
double rand_normal(double mu, double sigma) {
    double e = sqrt(-2.0*log(randDouble)) * sin(2.0*M_PI*randDouble);
    return mu + sigma*e;
}

//============================================================================//
// genertate-data.cより移植
// @paramunsigned int cnt
// @param char *path
// @return struct person *t
//============================================================================//
bool generete_data(unsigned int max, const char* path) {
    double a = 0.8; 
    double b = 1.5; 
    double e = 0.0;
    double x = 0.0; 
    double y = 0.0;
    FILE *tmp_file;

    // 一時ファイルを開く
    tmp_file = fopen(path, "w");
    if (tmp_file == NULL) {
        printf("cannot open tmp \n");
        return false;
    }

    // データ対を生成する
    for(unsigned int i = 0; i < max; i++){
        x = randDouble * 10.0;
        e = rand_normal(0, 1);
        y = a * x + b + e;
        fprintf(tmp_file, "%d,%lf,%lf\n", i, x, y);
    }

    // 一時ファイルを閉じる
    fclose(tmp_file);

    return true;
}

//============================================================================//
// 課題(2)のmain関数
// generete_data.cの処理を100回繰り返す
// @paramu int argc
// @param char *argv[]
// @return bool 
//============================================================================//
bool main(int argc, char *argv[]) {
    struct person *t = NULL;
    unsigned int max = 0;
    const char *tmp_file_path = "data/tmp.csv";
    const char *data_file_path = "data/data_02_02_re.csv";
    double a = 0.0;
    double b = 0.0;
    double rand_double = 0.0;
    FILE *file;

    // 引数が未定義の場合、データ数の上限値を100対で初期化する
    if(argv[1] == NULL || strlen(argv[1]) == 0) {
        max = 100;
    } else {
        max = atoi(argv[1]);
    }

    // データファイルを開く
    file = fopen(data_file_path, "w");
    if (file == NULL) {
        printf("cannot open data file\n");
        return false;
    }
    
    // 乱数を生成する
    srand((unsigned int)time(NULL));
    rand();

    // ヒストグラム用データを生成する
    for (unsigned int i = 0; i < MAX_COUNT; i++) {

        // genertate-dataでデータ対を生成する
        generete_data(max, tmp_file_path);

        // 一時ファイルを読み込み構造体を初期化
        t = init_data(tmp_file_path);

        // 課題(1)で提出済みの関数calc_aによりデータ対から傾きを導出する
        t = head_person(t);
        a = calc_a(t, CODE_LENGTH);
        // 課題(1)で提出済みの関数calc_bによりデータ対から切片を導出する
        t = head_person(t);
        b = calc_b(t, CODE_LENGTH);

        // ファイルへ書き込む
        fprintf(file, "%d,%lf,%lf\n", i, a, b);

        // 一時ファイルを削減する
        //remove(tmp_file_path);

        // メモリ解放
        del_person_array(head_person(t));
    }

    // データファイルを閉じる
    fclose(file);

    return true;  
}