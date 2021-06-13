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
  while(pos->next){
    pos = pos->next;
    free(pos->prev);
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
// リストをソートする処理
// @param char *path
// @return struct person *t
//============================================================================//
struct person* b_sort(struct person *p, unsigned int control_code) {
  struct person* t = head_person(p);
  struct person* c = NULL;

  // 変数を初期化
  struct person* next = t->next;
  struct person* prev = t->prev;
  struct person* tmp_person = (struct person*)malloc(sizeof(struct person) * 1);
  tmp_person = initialize(tmp_person);

  // 線形リストの要素数を取得
  struct person* q = eol_person(p);
  unsigned int eol = q->seq;

  for (unsigned int i = 0; i <= eol; i++) {
    c = t;
    for (unsigned int j = i; j<= eol; j++) {
      switch (control_code) {
        case CODE_LENGTH:
          if (t->length > c->length) {
            tmp_person->length = c->length;
            tmp_person->weight = c->weight;
            c->length = t->length;
            c->weight = t->weight;
            t->length = tmp_person->length;
            t->weight = tmp_person->weight;
          }
          break;
        case CODE_WEIGHT:
          if (t->weight > c->weight) {
            tmp_person->length = c->length;
            tmp_person->weight = c->weight;
            c->length = t->length;
            c->weight = t->weight;
            t->length = tmp_person->length;
            t->weight = tmp_person->weight;
          }
          break;
      }

      if(j < eol){
          c = c->next;
      }
    }
    // シーケンス番号を書き換え
    t->seq = i;
    // 検査対称の構造体のポインタをインクリメント
    if(i < eol){
        t = t->next;
    }
  }

  // 一時領域を解放
  free(tmp_person);

  return head_person(t);
}


struct person* m_sort(struct person *p, unsigned int control_code){
  struct person* tmp_person = (struct person*)malloc(sizeof(struct person) * 1); 
  tmp_person = initialize(tmp_person);
  struct person* h = head_person(p);
  struct person* e = eol_person(p);
  struct person *prev = NULL;
  struct person* buf = NULL;
  struct person* t = NULL;
  struct person* tmp_a = NULL;
  struct person* tmp_b = NULL;
  unsigned int n = e->seq + 1;
  unsigned int na = 0;
  unsigned int nb = 0;
  bool odd_flg = false;

  // 要素数1の場合処理は行わない
  if(e->seq == 0){
    return p;
  }

  if(n % 2 == 0){
    na = (n / 2);
    nb = (n / 2);
  } else {
    na = (n / 2);
    nb = (n / 2) + (n % 2);
  }
  
  // 一時領域を初期化する
  struct person* a = (struct person*)malloc(sizeof(struct person) * na);
  struct person* b = (struct person*)malloc(sizeof(struct person) * nb);

  p = head_person(p);
  for(unsigned int i = 0; i < na; i++){
    t = (struct person*)malloc(sizeof(struct person) * 1);
    a = initialize(t);
    // リストの先頭要素を取得
    if(i == 0){
      a->prev = NULL;
    }
    if(prev){
      a->prev = prev;
      prev->next = a;
    }
    prev = a;
    a->seq = i;
    a->length = p->length;
    a->weight = p->weight;
    a->next = NULL;
    p = p->next;
  }
  
  prev = NULL;
  for(unsigned int i = 0; i < nb; i++) {
    t = (struct person*)malloc(sizeof(struct person) * 1);
    b = initialize(t);
    // リストの先頭要素を取得
    if(i == 0){
      b->prev = NULL;
    }
    if(prev){
      b->prev = prev;
      prev->next = b;
    }
    prev = b;
    b->seq = i;
    b->length = p->length;
    b->weight = p->weight;
    b->next = NULL;
    if(p->next != NULL){
      p = p->next;
    }
  }

  // 再帰
  p = head_person(p);
  a = head_person(a);
  b = head_person(b);
  a = m_sort(a ,control_code);
  b = m_sort(b ,control_code);

  // 比較->マージ
  p = head_person(p);
  a = head_person(a);
  b = head_person(b);
  tmp_a = a;
  tmp_b = b;
  for(unsigned int i = 0; i < n; i++) {
    switch (control_code){
      case CODE_LENGTH:
        if(tmp_b == NULL || tmp_a != NULL && (tmp_b->length > tmp_a->length)) {
          p->length = tmp_a->length;
          p->weight = tmp_a->weight;
          if(tmp_a->next != NULL){
            tmp_a = tmp_a->next;
          } else {
            tmp_a->length = 9999;
          }
        } else {
          p->length = tmp_b->length;
          p->weight = tmp_b->weight;
          if(tmp_b->next != NULL){
            tmp_b = tmp_b->next;
          } else {
            tmp_b->length = 9999;
          }
        }
        break;
      case CODE_WEIGHT:
        if(tmp_b == NULL || tmp_a != NULL && (tmp_b->weight > tmp_a->weight)) {
          p->length = tmp_a->length;
          p->weight = tmp_a->weight;
          if(tmp_a->next != NULL){
            tmp_a = tmp_a->next;
          } else {
            tmp_a->weight = 9999;
          }
        } else {
          p->length = tmp_b->length;
          p->weight = tmp_b->weight;
          if(tmp_b->next != NULL){
            tmp_b = tmp_b->next;
          } else {
            tmp_b->weight = 9999;
          }
        }
        break;
    }
    if (p->next != NULL){
      p = p->next;
    } else {
      break;
    }
  }
  
  // 一時領域を破棄する
  a = head_person(a);
  b = head_person(b);
  del_person_array(head_person(a));
  del_person_array(head_person(b));

  p = head_person(p);
  
  return p;
}

//============================================================================//
// 1.最大値と最小値
// @param struct person* p
// @patram unsigned int max_min_code
// @patram unsigned int control_code
// @return struct person* p
//============================================================================//
struct person* max_min_parson(struct person* p, unsigned int max_min_code, unsigned int control_code) {
  p = head_person(p);
  // データを整列
  p = b_sort(p, control_code);
  // 制御コードで返却するポインタのアドレスを切り替え
  switch (max_min_code) {
    case CODE_MAX:
      p = eol_person(p);
      break;
    case CODE_MIN:
      p = head_person(p);
      break;
  }
  return p;
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
  do {
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
    }
  } while(p->next != NULL);

  // 平均値を導出する
  avg = total/cnt;
  // ポインタを先頭へ戻す
  p = head_person(p);

  return avg;
}

//============================================================================//
// 3.中央値
// @param struct person* p
// @patram unsigned int control_code
// @return double med
//============================================================================//
double med_parson(struct person* p, unsigned int control_code) {
  double med = 0.0;
  unsigned int cnt = 0;
  unsigned int max = 0;

  // 構造体の要素数を数える
  p = head_person(p);
  do {
    cnt++;
    if(p->next != NULL) {
      p = p->next;
    }
  } while (p->next != NULL);
  cnt+=1;

  // データを整列する
  p = head_person(p);
  p = m_sort(p, control_code);


  // 中央値を導出する
  p = head_person(p);
  if(cnt % 2 == 0) {
    max = cnt / 2;
    // 要素数が偶数の場合
    for (int i = 1; i <= max; i++) {
      if (i == max){
        switch (control_code) {
          case CODE_LENGTH:
            med = (p->length + p->next->length) / 2.0;
            break;
          case CODE_WEIGHT:
            med = (p->weight + p->next->weight) / 2.0;
            break;
        }
      } else {
        p = p->next;
      }
    }
  } else {
    // 要素数が奇数の場合
    max = (cnt / 2) + 1;
    for (int i = 1; i <= max; i++) {
      if (i == max){
        switch (control_code) {
          case CODE_LENGTH:
            med = p->length;
            break;
          case CODE_WEIGHT:
            med = p->weight;
            break;
        }
      } else {
        p = p->next;
      }
    }
  }
  p = head_person(p);

  return med;
}

//============================================================================//
// 4.標準偏差
// @param struct person* p
// @patram unsigned int control_code
// @return double std_dev
//============================================================================//
double std_dev_parson(struct person* p, unsigned int control_code) {
  double std_dev = 0.0;
  double avg = 0.0;
  double total = 0.0;
  unsigned int cnt = 0;

  // 平均値の導出
  p = head_person(p);
  avg = avg_parson(p, control_code);

  // 構造体の要素数を数える
  p = head_person(p);
  do {
    cnt++;
    if(p->next != NULL) {
      p = p->next;
    }
  } while (p->next != NULL);
  cnt+=1;

  // 標準偏差の導出
  p = head_person(p);
  for (int i = 0; i < cnt; i++) {
    switch (control_code) {
      case CODE_LENGTH:
        total += pow(fabs(avg - p->length), 2);
        break;
      case CODE_WEIGHT:
        total += pow(fabs(avg - p->weight), 2);
        break;
    }
    if(p->next != NULL) {
      p = p->next;
    } else {
      break;
    }
  }
  std_dev = sqrt(total/cnt);

  return std_dev;
}

//============================================================================//
// 5.身長と体重の）相関係数
// @param struct person* p
// @return double std_dev
//============================================================================//
double correlation_coefficient_parson(struct person* p) {
  double correlation_coefficient = 0.0;
  double avg_length = 0.0;
  double avg_weight = 0.0;
  double std_dev_length = 0.0;
  double std_dev_weight = 0.0;
  double total_length = 0.0;
  double total_weight = 0.0;
  double total = 0.0;
  unsigned int cnt = 0;

  // 平均値の導出
  p = head_person(p);
  avg_length = avg_parson(p, CODE_LENGTH);
  p = head_person(p);
  avg_weight = avg_parson(p, CODE_WEIGHT);

  // 構造体の要素数を数える
  p = head_person(p);
  do {
    cnt++;
    if(p->next != NULL) {
      p = p->next;
    }
  } while (p->next != NULL);
  cnt+=1;

  // 標準偏差の導出
  p = head_person(p);
  std_dev_length = std_dev_parson(p, CODE_LENGTH);
  p = head_person(p);
  std_dev_weight = std_dev_parson(p, CODE_WEIGHT);

  // 偏差積和の導出
  p = head_person(p);
  for (int i = 0; i < cnt; i++) {
    total_length = fabs(avg_length - p->length);
    total_weight = fabs(avg_weight - p->weight);
    total += (total_length * total_weight);
    if(p->next != NULL) {
      p = p->next;
    } else {
      break;
    }
  }
  p = head_person(p);

  correlation_coefficient = ((total/cnt)/(std_dev_length * std_dev_weight));

  return correlation_coefficient;
}

