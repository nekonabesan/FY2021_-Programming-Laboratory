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
    if(next->next){
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
