#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define CODE_LENGTH 1
#define CODE_WEIGHT 2

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
    //printf("%lf %lf %lf\n", data[0], data[1], data[2]);
    t = (struct person*)malloc(sizeof(struct person) * 1);
    // リストの先頭要素を取得
    if(seq == 0){
      start = t;
      t->prev = NULL;
    }
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
struct person* b_sort(struct person *p, unsigned int prefix) {
  struct person* t = head_person(p);
  struct person* c = NULL;

  /*if(t->seq == NULL) {
    return p;
  }*/

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
      switch (prefix) {
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


struct person* m_sort(struct person *p, unsigned int prefix){
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
  
  /*printf("n:%d\n", n);
  printf("na:%d\n", na);
  printf("nb:%d\n", nb);*/
  
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
  
  /*if (na != 0) {
    printf("Copy array a\n");
    printf("na:%d\n", na);
    a = head_person(a);
    for(unsigned int i = 0; i < na; i++){
      printf("%d : %f\n", a->seq, a->length);
      if(a->next != NULL) {
        a = a->next;
      } else {
        break;
      }
    }
  }*/


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

  /*printf("Copy array b\n");
  printf("nb:%d\n", nb);
  b = head_person(b);
  for(unsigned int i = 0; i < nb; i++){
    printf("%d : %f\n", b->seq, b->length);
    if(b->next != NULL) {
      b = b->next;
    } else {
      break;
    }
  }*/

  // 再帰
  p = head_person(p);
  a = head_person(a);
  b = head_person(b);
  a = m_sort(a ,prefix);
  b = m_sort(b ,prefix);

  // 比較->マージ
  p = head_person(p);
  a = head_person(a);
  b = head_person(b);
  tmp_a = a;
  tmp_b = b;
  //printf("num : %d\n", n);
  for(unsigned int i = 0; i < n; i++) {
    //printf("index : %d\n", i);
    switch (prefix){
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

  /*printf("Sorted array a %d\n", na);
  a = head_person(a);
  for (unsigned int i = 0; i < na; i++) {
    printf("%d -> %f\n", a->seq, a->length);
    if(a->next) {
      a = a->next;
    } else {
      break;
    }
  }

  printf("Sorted array b %d\n", nb);
  b = head_person(b);
  for (unsigned int i = 0; i < nb; i++) {
    printf("%d -> %f\n", b->seq, b->length);
    if(b->next) {
      b = b->next;
    } else {
      break;
    }
  }

  printf("Sorted array p %d\n", n);
  p = head_person(p);
  for (unsigned int i = 0; i < n; i++) {
    printf("%d -> %f\n", p->seq, p->length);
    if(p->next) {
      p = p->next;
    } else {
      break;
    }
  }*/
  
  // ダミーの構造体を破棄する
  a = head_person(a);
  b = head_person(b);
  p = head_person(p);

  del_person_array(head_person(a));
  del_person_array(head_person(b));
  
  return p;
}


