#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "../01_Statistical-processing/modules/pl01_01_module.c"

//--------------------------------------------------------------//
// 身長の単位を(cm->m)へ変換する処理
// @param struct person *p
// @return struct person *p
//--------------------------------------------------------------//
struct person * from_cm_to_m_for_length(struct person* p) {
  unsigned int max = 0;

  // 要素数を取得
  p = eol_person(p);
  max = p->seq + 1;

  p = head_person(p);
  for (unsigned int i = 0; i < max; i++) {
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
  max = p->seq + 1;

  p = head_person(p);
  for (unsigned int i = 0; i < max; i++) {
    tmp += ((p->length) * p->weight);
    if(p->next != NULL) {
      p = p->next;
    }
  }

  // S1を導出する
  s1 = tmp/max;

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
  max = p->seq + 1;

  p = head_person(p);
  for (unsigned int i = 0; i < max; i++) {
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
  s2 = tmp/max;

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
  long s1 = 0;
  long s2 = 0;
  long avg_x = 0;
  long avg_y = 0;

  p = head_person(p);

  // x軸の設定でパラメータの導出を切り替え
  switch (x_axis) {
    case CODE_LENGTH:
      avg_x = round(avg_parson(p, CODE_LENGTH) * 10000);
      avg_y = round(avg_parson(p, CODE_WEIGHT) * 10000);
      s2 = round(calc_S2(p, CODE_LENGTH) * 10000);
      break;
    case CODE_WEIGHT:
      avg_x = round(avg_parson(p, CODE_WEIGHT) * 10000);
      avg_y = round(avg_parson(p, CODE_LENGTH) * 10000);
      s2 = round(calc_S2(p, CODE_WEIGHT) * 10000);
      break;
    default:
      break;
  }

  s1 = round(calc_S1(p) * 10000);
  a = ((s1 - (avg_x * avg_y))/(s2 - pow(avg_x, 2)));
  
  p = head_person(p);

  return a;
}

//--------------------------------------------------------------//
// aを導出する処理
// @param struct person *p
// @param unsigned int x_axis
// @return double a
//--------------------------------------------------------------//
double calc_b(struct person *p, unsigned int x_axis) {
  double b = 0.0;
  long s1 = 0;
  long s2 = 0;
  long avg_x = 0;
  long avg_y = 0;

  p = head_person(p);

  // x軸の設定でパラメータの導出を切り替え
  switch (x_axis) {
    case CODE_LENGTH:
      avg_x = round(avg_parson(p, CODE_LENGTH) * 10000);
      avg_y = round(avg_parson(p, CODE_WEIGHT) * 10000);
      s2 = round(calc_S2(p, CODE_LENGTH) * 10000);
      break;
    case CODE_WEIGHT:
      avg_x = round(avg_parson(p, CODE_WEIGHT) * 10000);
      avg_y = round(avg_parson(p, CODE_LENGTH) * 10000);
      s2 = round(calc_S2(p, CODE_WEIGHT) * 10000);
      break;
    default:
      break;
  }

  p = head_person(p);
  s1 = round(calc_S1(p) * 10000);
  b = (((avg_y * s2) - (avg_x * s1))/(s2 - pow(avg_x, 2)));

  p = head_person(p);

  return b;
}


